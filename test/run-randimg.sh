#!/bin/sh

### TESTS
#
# Test PBM, PGM, PPM image generation.
for mode in "pbm" "pgm" "ppm"
do
  for x in "16" "64" "256"
  do
    for y in "16" "64" "256" 
    do
	    for variant in "ascii" "binary"
	    do
        echo "Generating image: randimg-${x}-${y}-${variant}.${mode}"
        ../bin/randimg.exe -x ${x} -y ${y} -${mode} -${variant} -o randimg-${x}-${y}.${variant}.${mode}
      done
    done	
  done 
done

# Test PFM image generation.
for mode in "pfm"
do
  for x in "16" "64" "256"
  do
    for y in "16" "64" "256" 
    do
      for variant in "rgb" "greyscale"
      do      
        echo "Generating image: randimg-${x}-${y}-${variant}.${mode}"
        ../bin/randimg.exe -x ${x} -y ${y} -${mode} -${variant} -o randimg-${x}-${y}.${variant}.${mode}
      done      
    done 
  done 
done

if [ "$SECONDS" -eq 1 ]
then
  units=second
else
  units=seconds
fi

echo "This script has been running for $SECONDS $units."
exit 0
