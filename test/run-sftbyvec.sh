#!/bin/bash

# Test ASCII PGM (P2)
#for img in "lena"
for img in "whitetiger"
do
  echo "Read image: ${img}.ascii.pgm; write image: ${img}.out.ascii.pgm"
#  ../bin/sftbyvec.exe -vx 3 -vy 4 -i ../images/${img}.ascii.pgm -o ${img}.sft.ascii.pgm
  ../bin/sftbyvec.exe -vx 16 -vy 20 -i ../images/${img}.ascii.pgm -o ${img}.sft.ascii.pgm
done

if [ $SECONDS -eq 1 ]
then
  units=second
else
  units=seconds
fi

echo "This script has been running for $SECONDS $units."
