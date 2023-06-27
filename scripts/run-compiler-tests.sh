#!/bin/bash

FILES=$(find test-units -iname "*.b" | sort)
TIMEOUT=5s
FLATB_EXECUTABLE=./build/flatb

set -x

# The following tests are disabled until I can fix the LLVM parts of it.
for file in ${FILES[@]}; do
  echo $FLATB_EXECUTABLE -c $file
  timeout $TIMEOUT $FLATB_EXECUTABLE -c $file > $file.ll
  llc -O3 $file.ll -o $file.s
  gcc $file.s -o a.out -static
  ./a.out
done
