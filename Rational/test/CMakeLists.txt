cmake_minimum_required(VERSION 3.5)

set(This RationalTest)

set(Sources
    RationalTest.cpp
)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
    gtest_main
    Rational
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
