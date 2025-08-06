#!/bin/bash

tower S84.CTCode.dbnf DSA::Vent::Tower::CPPGenerator
tower S84.CTCode.dbnf DSA::Vent::Tower::CTCodeGeneratorBoot

ctcode S84.CTCode.CPPTranspiler.ctcode s84::ctcode::CPPTranspilerBoot
ctcode S84.CTCode.CPPTranspilerBoot.ctcode s84::ctcode::CPPTranspilerBoot
ctcode S84.CTCode.dbnf.ctcode s84::ctcode::CPPTranspilerBoot

$(dirname $0)/build_source.sh
