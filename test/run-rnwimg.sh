#!/bin/bash

# Test ASCII PBM (P1)
for img in "feep" "haus" "letter_j"
do
  echo "Read image: ${img}.ascii.pbm; write image: ${img}.out.ascii.pbm"
  ../bin/rnwimg.exe -i ../images/${img}.ascii.pbm -o ${img}.out.ascii.pbm
done

# Test binary PBM (P4)
for img in "feep" #"haus"
do
  echo "Read image: ${img}.binary.pbm; write image: ${img}.out.binary.pbm"
  ../bin/rnwimg.exe -i ../images/${img}.binary.pbm -o ${img}.out.binary.pbm
done

# Test ASCII PGM (P2)
for img in "feep" "haus" "lena"
do
  echo "Read image: ${img}.ascii.pgm; write image: ${img}.out.ascii.pgm"
  ../bin/rnwimg.exe -i ../images/${img}.ascii.pgm -o ${img}.out.ascii.pgm
done

# Test binary PGM (P5)
for img in "feep" "haus" "lena92"
do
  echo "Read image: ${img}.binary.pgm; write image: ${img}.out.binary.pgm"
  ../bin/rnwimg.exe -i ../images/${img}.binary.pgm -o ${img}.out.binary.pgm
done

# Test ASCII PPM (P3)
for img in "haus" "ppmex255"
#for img in "haus" "ppmex1" "ppmex255" # Imagine may not read ppmex1 properly!
do
  echo "Read image: ${img}.ascii.ppm; write image: ${img}.out.ascii.ppm"
  ../bin/rnwimg.exe -i ../images/${img}.ascii.ppm -o ${img}.out.ascii.ppm
done

# Test binary PPM (P6)
for img in "haus" "ppmex255" "blocks" "fruit" "prague" "squares"
do
  echo "Read image: ${img}.binary.ppm; write image: ${img}.out.binary.ppm"
  ../bin/rnwimg.exe -i ../images/${img}.binary.ppm -o ${img}.out.binary.ppm
done

# Test color PFM (PF)
for img in "cornellbox_uniform_direct"
do
  echo "Read image: ${img}.pfm; write image: ${img}.out.pfm"
  ../bin/rnwimg.exe -i ../images/${img}.pfm -o ${img}.out.pfm
done

if [ $SECONDS -eq 1 ]
then
  units=second
else
  units=seconds
fi

echo "This script has been running for $SECONDS $units."
exit 0
