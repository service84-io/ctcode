#!/bin/bash

$(dirname $0)/build_source.sh

$(dirname $0)/build_full_using_cpp.sh
$(dirname $0)/build_full_using_csharp.sh
$(dirname $0)/build_full_using_java.sh
$(dirname $0)/build_full_using_node.sh
$(dirname $0)/build_full_using_php.sh
$(dirname $0)/build_full_using_python.sh
$(dirname $0)/build_full_using_ruby.sh
