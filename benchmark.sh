#!/bin/bash
echo "Setting up workspace"
mkdir files
cd files/
for i in {10..110}; do dd if=/dev/urandom bs=1000 count=1 of=sfile$i; done >& /dev/null
cd ..
echo "Starting test."
echo "Test 1: 20MB"
echo "noop scheduler"
echo noop > /sys/block/mmcblk0/queue/scheduler
sleep 3
./out/prog 20

echo "deadline scheduler"
echo deadline > /sys/block/mmcblk0/queue/scheduler
sleep 3
./out/prog 20

echo "cfq scheduler"
echo cfq > /sys/block/mmcblk0/queue/scheduler
sleep 3
./out/prog 20

echo "Test 2: 40MB"
echo "noop scheduler"
echo noop > /sys/block/mmcblk0/queue/scheduler
sleep 3
./out/prog 40

echo "deadline scheduler"
echo deadline > /sys/block/mmcblk0/queue/scheduler
sleep 3
./out/prog 40

echo "cfq scheduler"
echo cfq > /sys/block/mmcblk0/queue/scheduler
sleep 3
./out/prog 40

echo "Test 3: 60MB"
echo "noop scheduler"
echo noop > /sys/block/mmcblk0/queue/scheduler
sleep 3
./out/prog 60

echo "deadline scheduler"
echo deadline > /sys/block/mmcblk0/queue/scheduler
sleep 3
./out/prog 60

echo "cfq scheduler"
echo cfq > /sys/block/mmcblk0/queue/scheduler
sleep 3
./out/prog 60

echo "Test 4: 80MB"
echo "noop scheduler"
echo noop > /sys/block/mmcblk0/queue/scheduler
sleep 3
./out/prog 80

echo "deadline scheduler"
echo deadline > /sys/block/mmcblk0/queue/scheduler
sleep 3
./out/prog 80

echo "cfq scheduler"
echo cfq > /sys/block/mmcblk0/queue/scheduler
sleep 3
./out/prog 80

echo "Test 5: 100MB"
echo "noop scheduler"
echo noop > /sys/block/mmcblk0/queue/scheduler
sleep 3
./out/prog 100

echo "deadline scheduler"
echo deadline > /sys/block/mmcblk0/queue/scheduler
sleep 3
./out/prog 100

echo "cfq scheduler"
echo cfq > /sys/block/mmcblk0/queue/scheduler
sleep 3
./out/prog 100


echo "Cleaning up workspace"
rm -rf files
