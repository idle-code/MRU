#!/bin/sh
PATH="/usr/local/bin:$PATH" 
cmake ./ -DCMAKE_C_COMPILER=gcc47 -DCMAKE_CXX_COMPILER=g++47 && make
