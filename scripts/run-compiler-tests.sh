
#!/bin/bash

FILES=$(find test-units -iname "*.b")
TIMEOUT=5s
FLATB_EXECUTABLE=./build/flatb

# The following tests are disabled until I can fix the LLVM parts of it.
for file in ${FILES[@]}; do
  echo $FLATB_EXECUTABLE -c $file;
  timeout $TIMEOUT $FLATB_EXECUTABLE -c $file > /dev/null;
done;
