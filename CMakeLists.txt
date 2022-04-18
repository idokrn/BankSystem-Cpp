cmake_minimum_required(VERSION 3.20)
project(assignment)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(assignment
        Account.cpp
        Account.h
        Bank.cpp
        Bank.h
        MainTrain.cpp
        Person.cpp
        Person.h
        Transaction.cpp
        Transaction.h)
