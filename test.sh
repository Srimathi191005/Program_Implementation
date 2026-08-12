#!/bin/bash

sudo insmod mychardriver.ko

echo "Embedded Linux" | sudo tee /dev/mychardev > /dev/null

sudo cat /dev/mychardev

sudo rmmod mychardriver

