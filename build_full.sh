#!/bin/bash

echo Processing DBNF files...
echo

for DBNFFile in *.dbnf; do
  echo Processing ${DBNFFile}...
  tower ${DBNFFile} S84::Tower::CTCodeGenerator
  echo Done processing ${DBNFFile}!
  echo
done

echo Done processing DBNF files!
echo

echo Processing CTCode files...
echo

for CTCodeFile in *.ctcode; do
  echo Processing ${CTCodeFile}...
  echo Generating CPP...
  ctcode ${CTCodeFile} s84::ctcode::CPPTranspiler
  echo Done generating CPP!
  echo Generating Python...
  ctcode ${CTCodeFile} s84::ctcode::Python3Transpiler
  echo Done generating Python!
  echo Done processing ${CTCodeFile}!
  echo
done

echo Done processing CTCode files!
echo

$(dirname $0)/build_source.sh
