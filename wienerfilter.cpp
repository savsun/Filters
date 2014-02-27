#include "wienerfilter.h"
#include "gaussfilter.h"
#include <complex.h>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;

WienerFilter::WienerFilter(int parM,
                           int parN,
                           double parWienerKoef,
                           double parSigma)
{
    GaussFilter gaussFilter(parN,parM,parSigma);
    vector <vector<complex<double> > > gaussFilterFourie;
    dft(gaussFilter.filter, gaussFilterFourie, DFT_COMPLEX_OUTPUT);
    filter.resize(parM);
    for (int i = 0; i < parM; i++)
    {
        filter[i].resize(parN);
        for (int j = 0; j < parN; j++)
        {
            complex<double> gaussFilterFourieAbs = gaussFilterFourie[i][j]
                    * conj(gaussFilterFourie[i][j]);

            filter[i][j] = gaussFilterFourieAbs /
                    (gaussFilterFourie[i][j] * (gaussFilterFourieAbs + parWienerKoef));
        }
    }

}

//Метод получения фильтра Винера в комплексном виде
//parN, parM - размерность получаемого фильтра
//parWienerKoef - коэффициент в формуле Винера (соотношение сигнал/шум)
//parSigma - значение сигмы в формуле Гаусса
/*complex<double> WienerFilter::FilterComplex(int parM,
                                            int parN,
                                            double parWienerKoef,
                                            double parSigma)
{
    complex<double> gaussFilter = GaussFilter::GaussFilter(parM, parN, parSigma);

    complex<double> gaussFilterFourie;
    //Здесь делается преобразование Фурье над матрицей, полученной из фильтра Гаусса
    //результат будет лежать в gaussFilterFourie

    complex<double>[][] filter = new complex<double>[parM][parN];

    for (int i = 0; i < parM; i++)
    {
        for (int j = 0; j < parN; j++)
        {
            complex<double> gaussFilterFourieAbs = gaussFilterFourie * conj(gaussFilterFourie);
            filter[i][j] = gaussFilterFourieAbs /
                           (gaussFilterFourie * (gaussFilterFourieAbs + parWienerKoef));
        }
    }

    return filter;
}*/
