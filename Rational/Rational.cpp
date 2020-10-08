#include <iostream>
#include <string>
#include "Rational.hpp"

using namespace std;

Rational::Rational(int num, int den) {
    denominator = den;
    numerator   = num;
    normalizeNegativeSign();
    reduce();
}

void Rational::normalizeNegativeSign(){
    if(denominator < 0) {
        denominator = -denominator;
        numerator = -numerator;
    }
}

void Rational::reduce(){
    bool isNegative = false;
    if (numerator < 0)
        isNegative = true;

    int a = isNegative ? -numerator : numerator;
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


Rational& Rational::operator++()
{
   numerator += denominator;
   return *this;
}


Rational Rational::operator++(int)
{
   Rational temp = *this;
   ++*this;
   return temp;
}


Rational& Rational::operator--()
{
   numerator -= denominator;
   return *this;
}


Rational Rational::operator--(int)
{
   Rational temp = *this;
   --*this;
   return temp;
}

Rational::operator double(){
    return (double)numerator/denominator;
}

bool Rational::operator==(const Rational& rhs) const {
    return this->numerator == rhs.numerator && this->denominator == rhs.denominator;
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

std::istream& operator>>( std::istream& input, Rational& in ){

    input>>in.numerator;
    input.ignore(1);
    input>>in.denominator;

    in.normalizeNegativeSign();
    in.reduce();

    return input;
}

Rational pow(const Rational& base, const int& exp){
    auto powLambda = [] (int b, int e) {
         int result = 1;
         for(int i = 0; i < e; ++i) result *= b;
         return result;
    };
    if (exp == 0){
        return Rational(1);
    }
    else if (exp < 0){
       return Rational(powLambda(base.denominator, -exp), powLambda(base.numerator, -exp));
    }
    else {
        return Rational(powLambda(base.numerator, exp), powLambda(base.denominator, exp));
    }
}

Rational abs(const Rational& r){
    auto absLambda = [](int a){
        return (a >= 0) ? a : -a;
    };
    return Rational(absLambda(r.numerator), absLambda(r.denominator));
}

int ceil(const Rational& r){
    if (r.numerator == 0 && r.denominator == 0){
        throw "NaN";
    }
    else if (r.denominator == 0){
        throw "Inf";
    }
    return (r.numerator + r.denominator - 1)/r.denominator;
}

int floor(const Rational& r){
    if (r.numerator == 0 && r.denominator == 0){
        throw "NaN";
    }
    else if (r.denominator == 0){
        throw "Inf";
    }
    if (r.numerator < 0)
        return r.numerator/r.denominator - (r.numerator%r.denominator!=0);
    else
        return r.numerator/r.denominator;
}
