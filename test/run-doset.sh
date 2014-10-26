#!/bin/sh

# Change path for your system.
PPMTOGIF_PATH=/c/GnuWin32/bin

../bin/doset.exe
# Uncomment in case you have ppmtogif on your system.
#${PPMTOGIF_PATH}/ppmtogif.exe <doset.ppm >doset.gif

if [ "$SECONDS" -eq 1 ]
then
  units=second
else
  units=seconds
fi
echo "This script has been running for $SECONDS $units."
exit 0
