#!/bin/bash

function run-all {
    filename=$(basename $1 ".b")
    echo $filename >&2

    echo ./src/bci $1 
    time ./src/bci $1 > /dev/null

    # Runn lli
    echo ./src/bcc 1 > ll-src/${filename}.ll
    ./src/bcc $1 > ll-src/${filename}.ll
    echo lli ll-src/${filename}.ll
    time lli ll-src/${filename}.ll > /dev/null

    # echo llc -filetype=obj ll-src/${filename}.ll
    # llc -filetype=obj ll-src/${filename}.ll
    # /usr/bin/clang++ -fPIC ll-src/${filename}.o -o ll-out/${filename}
    echo llc -filetype=asm -relocation-model=pic ll-src/${filename}.ll
    llc -filetype=asm -relocation-model=pic ll-src/${filename}.ll
    echo clang++ -fPIC ll-src/${filename}.s -o ll-out/${filename}
    clang++ -fPIC ll-src/${filename}.s -o ll-out/${filename}
    chmod +x ll-out/${filename}
    echo ./ll-out/${filename}
    time ./ll-out/${filename} > /dev/null

}

rm ll-src/* ll-out/*
mkdir -p ll-src ll-out
files=$(find test-units/non-trivial -iname "*.b")
for file in ${files[@]}
do
    echo $file
    run-all $file
done

