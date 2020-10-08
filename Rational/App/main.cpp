#include <iostream>
#include <cmath>
#include "../Rational.hpp"

using namespace std;

int main()
{
    Rational r = Rational();
    r = Rational(1, pow(2,31)-1 );
    cout << r;

    cout << "Enter rational number #/#:";
    cin >> r;
    cout << "Your rational number r:" << r << endl << endl;

    cout << "print r++ " << r++ << " " << "print ++r "  << ++r << endl;
    cout << "print r-- " << r-- << " " << "print --r " << --r << endl;

//    cout << "pi number calculation" << endl;

//    double pi = 0;
//    int n = 0;
//    while (pi < 3.1414 && pi > 3.1416)
//    {
//        pi += Rational(4*pow(-1,n),2*n+1);
//        n++;
//        cout << pi << endl;
//    }

//    cout << "n=" << n << endl;
//    cout << "pi=" << pi << endl;

    return 0;
}
