#!/bin/bash

tower S84.CTCode.dbnf DSA::Vent::Tower::CTCodeGenerator

ctcode S84.CTCode.CPPTranspiler.ctcode s84::ctcode::CPPTranspiler
ctcode S84.CTCode.dbnf.ctcode s84::ctcode::CPPTranspiler

$(dirname $0)/build_source.sh
