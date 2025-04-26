#!/bin/bash

tower S84.CTCode.dbnf DSA::Vent::Tower::CPPGenerator

ctcode S84.CTCode.CPPTranspiler.ctcode s84::ctcode::CPPTranspiler

$(dirname $0)/build_source.sh
