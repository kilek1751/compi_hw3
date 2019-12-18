#!/bin/bash

bison -d parser.ypp
flex scanner.lex
g++ -std=c++11 *.c *.cpp -o hw3.exe