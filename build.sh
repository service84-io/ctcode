#!/bin/bash

tower S84.CTCode.dbnf DSA::Vent::Tower::CPPGenerator
gcc *.cpp -lstdc++ -o ctcode
