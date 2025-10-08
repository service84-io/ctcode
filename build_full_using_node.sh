#!/bin/bash

$(dirname $0)/clean_cpp.sh
$(dirname $0)/clean_csharp.sh
$(dirname $0)/clean_java.sh
$(dirname $0)/clean_php.sh
$(dirname $0)/clean_python.sh

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
  node ctcode.js ${CTCodeFile} CPPTranspiler
  echo Done generating CPP!
  echo Generating CSharp...
  node ctcode.js ${CTCodeFile} CSharpTranspiler
  echo Done generating CSharp!
  echo Generating Java11...
  node ctcode.js ${CTCodeFile} Java11Transpiler
  echo Done generating Java11!
  echo Generating NodeJS...
  node ctcode.js ${CTCodeFile} NodeJSTranspiler
  echo Done generating NodeJS!
  echo Generating PHP...
  node ctcode.js ${CTCodeFile} PHPTranspiler
  echo Done generating PHP!
  echo Generating Python3...
  node ctcode.js ${CTCodeFile} Python3Transpiler
  echo Done generating Python3!
  echo Done processing ${CTCodeFile}!
  echo
done

echo Done processing CTCode files!
echo

$(dirname $0)/build_source.sh
