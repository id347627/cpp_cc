#include <gtest/gtest.h>
#include "../Rational.hpp"

TEST(RationalTesting, Reduce)
{
    EXPECT_TRUE(Rational(5) == Rational(5, 1));
    EXPECT_TRUE(Rational(4, 8) == Rational(1,2));
    EXPECT_TRUE(Rational(16, 4) == Rational(4, 1));
}

TEST(RationalTesting, Add)
{
    Rational r1 = Rational(3, 2);
    Rational r2 = Rational(1, 3);
    r1+=r2;
    EXPECT_TRUE(r1 == Rational(11, 6));
}

TEST(RationalTesting, Sub)
{
    Rational r1 = Rational(1, 4);
    Rational r2 = Rational(1, 2);
    r1-=r2;
    EXPECT_TRUE(r1 == Rational(-1, 4));
}

TEST(RationalTesting, Mul)
{
    Rational r1 = Rational(1, 4);
    Rational r2 = Rational(1, 2);
    r1*=r2;
    EXPECT_TRUE(r1 == Rational(1, 8));
}

TEST(RationalTesting, Div)
{
    Rational r1 = Rational(1, 4);
    Rational r2 = Rational(1, 2);
    r1/=r2;
    EXPECT_TRUE(r1 == Rational(1, 2));
}

TEST(RationalTesting, Output)
{
    std::string output;
    Rational r;

    testing::internal::CaptureStdout();
    r = Rational();
    std::cout << r;
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "0");

    testing::internal::CaptureStdout();
    r = Rational(3, 4);
    std::cout << r;
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "3/4");

    testing::internal::CaptureStdout();
    r = Rational(5, 0);
    std::cout << r;
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Inf");

    testing::internal::CaptureStdout();
    r = Rational(0, 0);
    std::cout << r;
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "NaN");

}
