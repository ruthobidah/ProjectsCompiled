#!/bin/sh

mkdir output
for i in scenes/*.txt; do
	echo $i
  f=`basename $i .txt`
  ./raytrace -i $i -o output/${f}.png -d output/${f}_depth.png > output/${f}_log.txt 2>&1 &
done

