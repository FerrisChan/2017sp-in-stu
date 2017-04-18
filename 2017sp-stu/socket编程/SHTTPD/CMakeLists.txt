cmake_minimum_required(VERSION 3.7)
project(SHTTPD)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES SHTTPD.c thread_set.c SHTTP.h cmake-build-debug/test.c)
add_executable(SHTTPD ${SOURCE_FILES} SHTTP.h)