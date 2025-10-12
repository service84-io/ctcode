#!/bin/bash

$(dirname $0)/clean_cpp.sh
$(dirname $0)/clean_csharp.sh
$(dirname $0)/clean_node.sh
$(dirname $0)/clean_php.sh
$(dirname $0)/clean_python.sh
$(dirname $0)/clean_ruby.sh

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
  java -jar ctcode.jar ${CTCodeFile} CPPTranspiler
  echo Done generating CPP!
  echo Generating CSharp...
  java -jar ctcode.jar ${CTCodeFile} CSharpTranspiler
  echo Done generating CSharp!
  echo Generating Java11...
  java -jar ctcode.jar ${CTCodeFile} Java11Transpiler
  echo Done generating Java11!
  echo Generating NodeJS...
  java -jar ctcode.jar ${CTCodeFile} NodeJSTranspiler
  echo Done generating NodeJS!
  echo Generating PHP...
  java -jar ctcode.jar ${CTCodeFile} PHPTranspiler
  echo Done generating PHP!
  echo Generating Python3...
  java -jar ctcode.jar ${CTCodeFile} Python3Transpiler
  echo Done generating Python3!
  echo Generating Ruby...
  java -jar ctcode.jar ${CTCodeFile} RubyTranspiler
  echo Done generating Ruby!
  echo Done processing ${CTCodeFile}!
  echo
done

echo Done processing CTCode files!
echo

$(dirname $0)/build_source.sh
