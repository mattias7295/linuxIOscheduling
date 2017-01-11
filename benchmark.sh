#!/bin/bash
echo "Setting up workspace"
mkdir files
cd files/
for i in {10..110}; do dd if=/dev/urandom bs=1000 count=1 of=sfile$i; done >& /dev/null
cd ..
echo "Starting test."
echo "Test 1: 10MB"
echo "noop scheduler"
echo noop > /sys/block/mmcblk0/queue/scheduler
sleep 3
./out/prog 10

echo "deadline scheduler"
echo deadline > /sys/block/mmcblk0/queue/scheduler
sleep 3
./out/prog 10

echo "cfq scheduler"
echo cfq > /sys/block/mmcblk0/queue/scheduler
sleep 3
./out/prog 10


echo "Cleaning up workspace"
rm -rf files
