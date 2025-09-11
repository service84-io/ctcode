#!/bin/bash

echo Building cpp source...
echo

g++ -std=c++17 *.cpp -o ctcode

echo Done building cpp source!
echo

echo Building java source...
echo

javac $(find ./ -name '*.java')
jar cfe ctcode.jar ctcode $(find ./ -name '*.class') $(find ./ -name '*.java')

echo Done building java source!
echo
