cmake_minimum_required(VERSION 3.5)

set(This TicTacToe)

project(${This} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set( Sources
   main.cpp
)

set( Headers
)

add_executable(${This} ${Sources} ${Headers})

