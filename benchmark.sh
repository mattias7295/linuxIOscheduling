#!/bin/bash
echo "Setting up workspace"
mkdir files
cd files/
for i in {10..110}; do dd if=/dev/urandom bs=1000 count=1 of=sfile$i; done >& /dev/null
cd ..
echo "Starting test."
./out/prog 10

echo "Cleaning up workspace"
rm -rf files
