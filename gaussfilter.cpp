#include "gaussfilter.h"

#include <math.h>
#include <opencv2/opencv.hpp>
#include <complex.h>

//const double GaussFilter::DEFAULT_SIGMA = 3 ;

GaussFilter::GaussFilter(int parM, int parN,double parSigma)
{
    filter.resize(parM);
    double sigma2=parSigma*parSigma;
    for (int i=0; i<parM; i++)
    {
        filter[i].resize(parN);
        int x=(i - parM/2);
        int x2=x*x;
        for (int j=0; j<parN; j++ )
        {
            int y=(j - parN/2);
            int y2=y*y;
            filter[i][j]=complex<double>(1/(2*M_PI*sigma2)*exp(x2+ y2)/2*sigma2,0);
        }
    }

}



//Метод получения фильтра Гаусса в комплексном виде
//parN, parM - размерность получаемого фильтра
//parSigma - значение сигмы в формуле Гаусса
/*complex<double>** GaussFilter::Filter(int parM, int parN, double parSigma)
{
    complex<double>[][]filter= new complex<double>[parM][parN];
    double sigma2=parSigma*parSigma;
    for (int i=0; i<parM; i++)
    {
        int x2=(i - parM/2)*(i - parM/2);
        for (int j=0; j<parN; j++ )
        {
            int y2=(j - parN/2)*(j - parN/2);
            filter[i][j]=complex<double>(1/(2*M_PI*sigma2)*exp(x2+ y2)/2*sigma2,0);
        }
    }
    return filter;
}*/
