#!/bin/bash

FILES=$(find test-units -iname "*.b")
TIMEOUT=5s

for file in ${FILES[@]}; do
  echo ./build/src/fb -i $file;
  timeout $TIMEOUT ./build/src/fb -i $file;
done;
