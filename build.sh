#!/usr/bin/env bash
set -e
CXX=g++
CXX_FLAGS="-std=c++17 -Wall -Wextra -Werror -pedantic"

set -x
$CXX $CXX_FLAGS -g -O0 -o tests tests.cpp
$CXX $CXX_FLAGS    -O3 -o msf   msf.cpp

