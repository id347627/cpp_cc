#include <gtest/gtest.h>
#include "../Rational.hpp"

TEST(RationalTesting, Reduce)
{
    EXPECT_TRUE(Rational(5)     == Rational(5, 1));
    EXPECT_TRUE(Rational(4, 8)  == Rational(1,2));
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
    r = Rational(-22, 10);
    std::cout << r;
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "-11/5");

    testing::internal::CaptureStdout();
    r = Rational(22, -10);
    std::cout << r;
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "-11/5");

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

TEST(RationalTesting, Pow)
{
    Rational r1 = Rational(1, 4);
    r1 = pow(r1, 3);
    EXPECT_TRUE(r1 == Rational(1, 64));

    r1 = Rational(2, 3);
    r1 = pow(r1, -2);
    EXPECT_TRUE(r1 == Rational(9, 4));

    r1 = pow(r1, 0);
    EXPECT_TRUE(r1 == Rational(1));
}


TEST (RationalTesting, Abs)
{
    Rational r1 = Rational(1, -4);
    r1 = abs(r1);
    EXPECT_TRUE(r1 == Rational(1, 4));

    r1 = Rational(-1, 4);
    r1 = abs(r1);
    EXPECT_TRUE(r1 == Rational(1, 4));

    r1 = Rational(-1, -4);
    r1 = abs(r1);
    EXPECT_TRUE(r1 == Rational(1, 4));
}


TEST(RationalTesting, Ceil)
{
    EXPECT_EQ(ceil(Rational(2)),        2);
    EXPECT_EQ(ceil(Rational(24, 10)),   3);
    EXPECT_EQ(ceil(Rational(29, 10)),   3);
    EXPECT_EQ(ceil(Rational(-27, 10)), -1);
    EXPECT_EQ(ceil(Rational(-2)),      -2);

    EXPECT_EQ(ceil(Rational(0, 5)),     0);
    EXPECT_EQ(ceil(Rational(2, -5)),    0);

    EXPECT_THROW(ceil(Rational(2, 0)), const char*);
    EXPECT_THROW(ceil(Rational(0, 0)), const char*);
}


TEST(RationalTesting, Floor)
{
    EXPECT_EQ(floor(Rational(2)),        2);
    EXPECT_EQ(floor(Rational(22, 10)),   2);
    EXPECT_EQ(floor(Rational(26, 10)),   2);
    EXPECT_EQ(floor(Rational(-22, 10)), -3);
    EXPECT_EQ(floor(Rational(-26, 10)), -3);
    EXPECT_EQ(floor(Rational(-2)),      -2);

    EXPECT_EQ(floor(Rational(0, 5)),     0);
    EXPECT_EQ(floor(Rational(2, -5)),   -1);

    EXPECT_THROW(floor(Rational(2, 0)), const char*);
    EXPECT_THROW(floor(Rational(0, 0)), const char*);
}

TEST(RationalTesting, toDouble){
    EXPECT_EQ((double)Rational(1, 2), 0.5);
    EXPECT_EQ((double)Rational(3, 2), 1.5);
    EXPECT_EQ((double)Rational(1, 3), (double)1/3);
}

