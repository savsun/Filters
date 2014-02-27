#ifndef GAUSSFILTER_H
#define GAUSSFILTER_H
#include <complex>
#include <vector>

using namespace std;

class GaussFilter
{
public:
    //Значения сигмы по умолчанию
   // static double const DEFAULT_SIGMA = 3;
    GaussFilter(int parM, int parN,double parSigma =3);

    //Метод получения фильтра Гаусса в комплексном виде
    //parN, parM - размерность получаемого фильтра
    //parSigma - значение сигмы в формуле Гаусса
   // complex<double>** FilterComplex(int parM, int parN, double parSigma);

    vector <vector<complex<double> > > filter;


};

#endif // GAUSSFILTER_H
