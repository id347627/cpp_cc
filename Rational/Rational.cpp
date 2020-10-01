#include <iostream>
#include <string>
#include "Rational.hpp"

using namespace std;


Rational::Rational(int num, int den) {
    if(den < 0) den = -den, num = -num;
    denominator = den;
    numerator = num;
    reduce();
}

void Rational::reduce(){
    int a = numerator;
    int b = denominator;
    int c;
    if(a > b) {
        c = a;
        a = b;
        b = c;
    }
    while(a) {
        c = a;
        a = b % a;
        b = c;
    }

    if (b != 0){
        numerator/=b;
        denominator/=b;
    }

}

Rational& Rational::operator+=(const Rational& rhs) {
    numerator = numerator * rhs.denominator + rhs.numerator * denominator;
    denominator = denominator * rhs.denominator;
    reduce();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs) {
    numerator = numerator * rhs.denominator - rhs.numerator * denominator;
    denominator = denominator * rhs.denominator;
    reduce();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs) {
    numerator = numerator * rhs.numerator;
    denominator = denominator * rhs.denominator;
    reduce();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
    numerator = numerator * rhs.denominator;
    denominator = denominator * rhs.numerator;
    if(denominator < 0)denominator = -denominator, numerator = -numerator;
    reduce();
    return *this;
}

bool Rational::operator==(const Rational& rhs) const {
    return this->getNumerator() == rhs.getNumerator() && this->getDenominator() == rhs.getDenominator();
}

inline Rational operator+(Rational lhs, const Rational& rhs) {
    lhs += rhs;
    return lhs;
}
inline Rational operator-(Rational lhs, const Rational& rhs) {
    lhs -= rhs;
    return lhs;
}
inline Rational operator*(Rational lhs, const Rational& rhs) {
    lhs *= rhs;
    return lhs;
}
inline Rational operator/(Rational lhs, const Rational& rhs) {
    lhs /= rhs;
    return lhs;
}

std::ostream& operator<<(std::ostream& os, const Rational& print) {
    if (print.numerator != 0 && print.denominator == 0)
        os << "Inf";
    else if (print.numerator == 0 && print.denominator == 0)
        os << "NaN";
    else
    {
        os << print.numerator;
        if(print.denominator > 1)
            os << "/" << print.denominator;
    }
    return os;
}

std::istream& operator>>( std::istream& input, Rational& in )
  {
     input >> in.numerator >> in.denominator;
     return input;
  }






