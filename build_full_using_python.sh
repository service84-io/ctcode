#!/bin/bash

$(dirname $0)/clean_cpp.sh
$(dirname $0)/clean_csharp.sh
$(dirname $0)/clean_java.sh
$(dirname $0)/clean_node.sh

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
  echo Generating CSharp...
  python3.13 ctcode.py ${CTCodeFile} CSharpTranspiler
  echo Done generating CSharp!
  echo Generating Python3...
  python3.13 ctcode.py ${CTCodeFile} Python3Transpiler
  echo Done generating Python3!
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
