#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <string>

class Rational
{
private:
        int numerator;
        int denominator;
        void reduce();
public:
        Rational(): numerator(0), denominator(1) {}
        Rational(int, int=1);
        Rational& operator+=(const Rational&);
        Rational& operator-=(const Rational&);
        Rational& operator*=(const Rational&);
        Rational& operator/=(const Rational&);
        bool operator==(const Rational&) const;
        int getNumerator() const {return numerator;}
        int getDenominator() const {return denominator;}
        friend std::ostream& operator<<(std::ostream&, const Rational&);
        friend std::istream& operator>>(std::istream&, Rational&);
};

inline Rational operator+(Rational, const Rational&);
inline Rational operator-(Rational, const Rational&);
inline Rational operator*(Rational, const Rational&);
inline Rational operator/(Rational, const Rational&);

#endif
