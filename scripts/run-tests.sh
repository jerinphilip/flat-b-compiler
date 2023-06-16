#!/bin/bash

FILES=$(find test-units -iname "*.b")
TIMEOUT=5s
FLATB_EXECUTABLE=./build/flatb


for file in ${FILES[@]}; do
  echo $FLATB_EXECUTABLE -c $file;
  timeout $TIMEOUT $FLATB_EXECUTABLE -c $file > /dev/null;
done;

for file in ${FILES[@]}; do
  echo $FLATB_EXECUTABLE -i $file;
  timeout $TIMEOUT $FLATB_EXECUTABLE -i $file > /dev/null;
done;
