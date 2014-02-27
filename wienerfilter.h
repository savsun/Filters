#ifndef WIENERFILTER_H
#define WIENERFILTER_H
#include <complex.h>
#include <vector>

using namespace std;

class WienerFilter
{
public:
    WienerFilter(int parM,
                 int parN,
                 double parWienerKoef,
                 double parSigma);

    vector <vector<complex<double> > > filter;


    //Метод получения фильтра Винера в комплексном виде
    //parN, parM - размерность получаемого фильтра
    //parWienerKoef - коэффициент в формуле Винера (соотношение сигнал/шум)
    //parSigma - значение сигмы в формуле Гаусса
    /*static complex<double>** FilterComplex(int parM,
                                           int parN,
                                           double parWienerKoef,
                                           double parSigma);*/
};

#endif // WIENERFILTER_H
