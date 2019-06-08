cmake_minimum_required(VERSION 3.13)
project(talon)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
set(Boost_NO_BOOST_CMAKE    ON)

find_package(Boost REQUIRED COMPONENTS filesystem locale system thread)


IF(${Boost_FOUND})
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

ENDIF(Boost_FOUND)

add_executable(parallel parallel.cpp headers/equetion.h headers/helpers.h headers/plot.h source/equetion.cpp source/helpers.cpp source/plot.cpp)

add_executable(seqential seqential.cpp headers/equetion.h headers/helpers.h headers/plot.h source/equetion.cpp source/helpers.cpp source/plot.cpp)

TARGET_LINK_LIBRARIES(parallel ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(seqential ${Boost_LIBRARIES})
