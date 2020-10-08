#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <string>

class Rational
{
private:
        int numerator;
        int denominator;
        void reduce();
        void normalizeNegativeSign();
public:
        Rational(): numerator(0), denominator(1) {}
        Rational(int, int=1);

        Rational& operator+=(const Rational&);
        Rational& operator-=(const Rational&);
        Rational& operator*=(const Rational&);
        Rational& operator/=(const Rational&);

        Rational& operator++();
        Rational operator++(int);

        Rational& operator--();
        Rational operator--(int);

        operator double();

        bool operator==(const Rational&) const;
        //bool operator!(const Rational&) const;

        friend std::ostream& operator<<(std::ostream&, const Rational&);
        friend std::istream& operator>>(std::istream&, Rational&);

        friend Rational pow(const Rational&, const int&);
        friend Rational abs(const Rational&);
        friend int ceil(const Rational&);
        friend int floor(const Rational&);
};

inline Rational operator+(Rational lhs, const Rational& rhs) {
    return lhs += rhs;
}
inline Rational operator-(Rational lhs, const Rational& rhs) {
    return lhs -= rhs;
}
inline Rational operator*(Rational lhs, const Rational& rhs) {
    return lhs *= rhs;
}
inline Rational operator/(Rational lhs, const Rational& rhs) {
    return lhs /= rhs;
}

#endif
