#!/bin/bash

echo Building CPP source...
echo

g++ -std=c++17 *.cpp -o ctcode

echo Done building CPP source!
echo

echo Building CSharp source...
echo

dotnet build -c Release

echo Done building CSharp source!
echo

echo Building Java11 source...
echo

javac $(find ./ -name '*.java')
jar cfe ctcode.jar ctcode $(find ./ -name '*.class') $(find ./ -name '*.java')

echo Done building Java11 source!
echo
