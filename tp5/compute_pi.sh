#!/usr/bin/env bash

set -euo pipefail

checkSetup() {
    if [ ! -d build ]; then
        echo "[WARN]: creating build directory."
        mkdir build
    fi
    cd build/
    if [ ! -f ./tp5 ]; then
        echo "[WARN]: project not set up."
        if [ ! -f Makefile ]; then
            echo "[WARN]: run cmake."
            cmake ..
        fi
        echo "[WARN]: building project."
        make
    fi
    if [ ! -f ./mt_0 ]; then
        echo "[WARN]: running project to generate status files."
        ./tp5
    fi
    cd ..
}

checkSetup

# configure output file
outputFile=pi
if [ $# -eq 1 ]; then
    outputFile=$1
fi
mkdir -p out

# compute pi
echo "computing pi"
for i in {0..9}; do
    echo "./build/tp5 ./build/mt_$i"
    ./build/tp5 "./build/mt_$i" > "./out/$outputFile$i.out" &
done

# wait and quit
time wait
echo "done"
