cmake_minimum_required(VERSION 2.8)

project(drivecode)

add_executable(drivecode motortest.cpp ct_time.cpp ct_time.h gpiopin.cpp gpiopin.h motor.cpp motor.h)