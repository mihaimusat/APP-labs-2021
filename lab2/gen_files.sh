#!/bin/bash

mkdir -p files
for i in $(seq 1 1000); do
	chunk=$(($RANDOM/100))

	base64 /dev/urandom | head -c ${chunk} > files/f${i}
done
