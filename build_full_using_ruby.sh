#!/bin/bash

$(dirname $0)/clean_cpp.sh
$(dirname $0)/clean_csharp.sh
$(dirname $0)/clean_java.sh
$(dirname $0)/clean_node.sh
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
  ruby -I. ctcode.rb ${CTCodeFile} CPPTranspiler
  echo Done generating CPP!
  echo Generating CSharp...
  ruby -I. ctcode.rb ${CTCodeFile} CSharpTranspiler
  echo Done generating CSharp!
  echo Generating Java11...
  ruby -I. ctcode.rb ${CTCodeFile} Java11Transpiler
  echo Done generating Java11!
  echo Generating NodeJS...
  ruby -I. ctcode.rb ${CTCodeFile} NodeJSTranspiler
  echo Done generating NodeJS!
  echo Generating PHP...
  ruby -I. ctcode.rb ${CTCodeFile} PHPTranspiler
  echo Done generating PHP!
  echo Generating Python3...
  ruby -I. ctcode.rb ${CTCodeFile} Python3Transpiler
  echo Done generating Python3!
  echo Generating Ruby...
  ruby -I. ctcode.rb ${CTCodeFile} RubyTranspiler
  echo Done generating Ruby!
  echo Done processing ${CTCodeFile}!
  echo
done

echo Done processing CTCode files!
echo

$(dirname $0)/build_source.sh
