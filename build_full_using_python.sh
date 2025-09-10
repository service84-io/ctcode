#!/bin/bash

echo Processing DBNF files...
echo

for DBNFFile in *.dbnf; do
  echo Processing ${DBNFFile}...
  tower ${DBNFFile} CTCodeGenerator
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
  python3.13 ctcode.py ${CTCodeFile} CPPTranspiler
  echo Done generating CPP!
  echo Generating Python...
  python3.13 ctcode.py ${CTCodeFile} Python3Transpiler
  echo Done generating Python!
  echo Generating NodeJS...
  python3.13 ctcode.py ${CTCodeFile} NodeJSTranspiler
  echo Done generating NodeJS!
  echo Generating Java11...
  python3.13 ctcode.py ${CTCodeFile} Java11Transpiler
  echo Done generating Java11!
  echo Done processing ${CTCodeFile}!
  echo
done

echo Done processing CTCode files!
echo

$(dirname $0)/build_source.sh
