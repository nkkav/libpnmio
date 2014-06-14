#!/bin/sh

### TESTS
for mode in "pbm" "pgm" "ppm"
do
  for x in "16" "64" "256"
  do
    for y in "16" "64" "256" 
	do
	  for variant in "ascii" "binary"
	  do
	    echo "Generating image: randimg-${x}-${y}-${variant}.${mode}"
        ../bin/randimg.exe -x ${x} -y ${y} -${mode} -${variant} -o randimg-${x}-${y}-${variant}.${mode}
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
echo "This script has been running $SECONDS $units."
exit 0
