cmake_minimum_required(VERSION 3.5)

set(This App)

project(${This} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set( Sources
   main.cpp
)

add_executable(${PROJECT_NAME} ${Sources})

target_link_libraries(${This} PUBLIC
    Rational
)
