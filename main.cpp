#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <QDebug>
#include <wienerfilter.h>

using namespace std;
using namespace cv;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    string filename="/home/alexandra/WienerFilter/video.avi";
    string filenameNew="/home/alexandra/WienerFilter/videonew.avi";
    VideoCapture capture;

    //capture.open(filename);
    Mat frame;


     if (!capture.open(filename))
    {
         qDebug() << "Very bad";
    throw "Error read video\n";
    return 0;
    }
     double fps = capture.get(CV_CAP_PROP_FPS);
     capture.read(frame);
     int frameHeight = frame.rows;
     int frameWidth = frame.cols;
     VideoWriter resultVideo(filenameNew,CV_FOURCC_DEFAULT,
                             fps,Size(frameHeight,frameWidth));
     while (1)
     {

         //qDebug() << "Happy end!";

         blur(frame,frame,Size(3,3));

         Mat resultFrame;

         vector<Mat> channels,result;
         split(frame,channels);
         for (auto partColor:channels)
         {

             Mat partColorReal;
             Mat partColorFourie;
             //Добавили нули, сделали 2х канальным
             vector<Mat> partColorChannel2 = { Mat_<double>(partColor),
                                      Mat::zeros(frameHeight, frameWidth, CV_64F) };

             merge(partColorChannel2, partColorReal);

             //Преобразование Фурье к изображению в 1м цвете
             dft(partColorReal, partColorFourie, DFT_COMPLEX_OUTPUT);
             //Применяем Винера
             WienerFilter kernel(3,3,1,5);
             Mat matRealKernel(3,3,CV_32FC1);
             Mat matImaginaryKernel(3,3,CV_32FC1);
             for (int i = 0; i < 3; i++)
             {
                 for(int j = 0; j<3; j++)
                 {
                     matRealKernel.row(i).col(j) = real(kernel.filter[i][j]);
                     matImaginaryKernel.row(i).col(j) = imag(kernel.filter[i][j]);
                 }
             }

             Mat filter;
             merge({matRealKernel,matImaginaryKernel},filter);



             //перемножениe
             Mat partColorFourieResult;
             Mat partColorResult;
             Mat partColorResultComplexChannel;
             mulSpectrums(partColorFourie, filter, partColorFourieResult, 0);

             //Обратное преобразование Фурье
             idft(partColorFourieResult, partColorResultComplexChannel, DFT_SCALE);

             // Бьем на каналы для выделения действительной и мнимой части
             vector<Mat> partColorResultChannels;
             split(partColorResultComplexChannel, partColorResultChannels);

             partColorResult=partColorResultChannels[0];
             // Добавляем обработанный канал в вектор матриц
             result.push_back(partColorResult);

         }
         merge(result,resultFrame);
         resultVideo.write(resultFrame);

         if (!capture.read(frame))
         {
             break;
         }

     }


        capture.release();
        resultVideo.release();
    
    return a.exec();
}
