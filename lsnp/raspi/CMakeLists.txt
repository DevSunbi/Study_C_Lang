cmake_minimum_required(VERSION 3.1)

project(MyProject VERSION 1.0.0 LANGUAGES C)

add_library(rpi SHARED led.c)
target_link_libraries(rpi PRIVATE wiringPi crypt)

add_executable(main main.c)
target_link_libraries(main PRIVATE dl pthread)