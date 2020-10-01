cmake_minimum_required(VERSION 3.5)

set(This Rational)

project(${This} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(googletest)

enable_testing()

set( Sources
   Rational.cpp
)

set( Headers
   Rational.hpp
)

add_library(${PROJECT_NAME} STATIC ${Sources} ${Headers})

add_subdirectory(test)

add_subdirectory(App)
