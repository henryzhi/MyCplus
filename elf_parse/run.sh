#!/bin/bash 

g++ -Wall -Werror -O2 -static test.c -o test
g++ -Wall -Werror -O2 -static parse.cc -o parse
