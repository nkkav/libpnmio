// BYTE Vol 11-13 1986-12 Graphics Algorithms
// doset.c
// pp. 217 (PDF)
//
// Param set 1: -2.0, -1.25, 2.5 (full-frame)
// Param set 2: -0.25, 1.13, 0.25
// Param set 3: -0.15, 0.995, 0.025 (nice zoom)
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pnmio.h"

#ifndef XDIM
#define XDIM        200
#endif
#ifndef YDIM
#define YDIM        200
#endif
#define COLOR0      0x000000 //0x222222 //0x336699
#define COLOR1      0x000000 //0xFF9933 //0xDDDDDD //0x996633
#define BLACK       0x000000
#define BRIGHTBLUE  0x0066FF
#define ORANGE      0xFF7F00
#define VIOLET      0x7F00FF
#define SKYBLUE     0x00DCFF
#define WHITE       0xFFFFFF
#define BROWN       0x7F0000
#define RED         0xFF0000
#define GREEN       0x00FF00
#define YELLOW      0x00FFFF
#define GREYBLUE    0x006699
#define GREY        0x7F7F7F


/* Function color (assigns color to counts).      
 * Input: integer count. Output integer nc (color)
 * This code can be modified to give the desired  
 * colors for different counts and ranges of counts. 
 */
int color(int count)
{
  int nc;                                /*  2 = black       */
  if (count > 995) nc = RED;             /*  3 = orange      */
  else if(count > 400) nc = COLOR1;      /*  4 = bright blue */
  else if(count > 350) nc = GREEN;       /*  5 = violet      */
  else if(count > 300) nc = BRIGHTBLUE;  /*  6 = sky blue    */
  else if(count > 250) nc = ORANGE;      /*  7 = white       */
  else if(count > 200) nc = BROWN;       /*  8 = brown       */
  else if(count > 150) nc = YELLOW;      /*  9 = red         */
  else if(count > 100) nc = GREYBLUE;    /* 10 = green       */
  else if(count > 90) nc = SKYBLUE;      /* 11 = yellow      */
  else if(count > 80) nc = GREY;         /* 12 = bright blue */
  else if(count > 70) nc = VIOLET;       /* 13 = grey blue   */
  else if(count > 60) nc = BLACK;        /* 14 = green       */
  else if(count > 50) nc = WHITE;        /* 15 = grey        */
  else if(count > 45) nc = BRIGHTBLUE;
  else if(count > 40) nc = COLOR0;
  else if(count > 35) nc = GREY;
  else if(count > 30) nc = ORANGE;
  else if(count > 20) nc = YELLOW;
  else if(count > 10) nc = BRIGHTBLUE;
  else nc = GREEN;
  if (nc == BRIGHTBLUE && count % 2 == 0) 
    nc = BROWN;
  if (nc == GREEN && count % 2 == 0) 
    nc = BROWN;
  return (nc);
} /*End function color */
 
int main (int argc, char *argv[])
{
  int y, x, count, totct;
  float x_coord, y_coord, range, gap, size, a, b, ac, bc, b1;
  int aa, bb, pixelval;
  char ct[XDIM+1][2];
  int *img_data, i=0;  
  FILE *OutFile;
  
  /* Open output file (default or command line) */
  if (argc <= 1) {
    OutFile = fopen("doset.ppm", "w");
    x_coord = -2.0;
    y_coord = -1.25;
    range = 2.5;
  } else {
    OutFile = fopen(argv[1], "w");
    /* Input x-y coordinates and range from keyboard */
    x_coord = atof(argv[2]);
    y_coord = atof(argv[3]);
    range   = atof(argv[4]);
  }  
  
  gap = range / (float)YDIM; /* Increment per pixel */
  y_coord += range;    /* Start at top of display */
  
  if (OutFile == NULL) {
    fprintf(stderr, "Error: Unable to open PPM file.");
    return 3;
  }
  
  /* Allocate space for image data storage. */
  img_data = malloc((3 * XDIM * YDIM) * sizeof(int));
  
  /* Write coordinates and range to data file */
//  fprintf(OutFile, "# x_coord = %7.6f\n", x_coord);
//  fprintf(OutFile, "# y_coord = %7.6f\n", y_coord);
//  fprintf(OutFile, "# range = %8.7f\n", range);
  
  /* Calculate count value for each pixel (200X200) */
  for (y = 1; y <= YDIM; y++) /* Each row */
  {
    bc = y_coord - y*gap; 
    totct = 0;
    for (x = 1; x <= XDIM; x++) /* Each pixel per row */
    {
      ac = x * gap + x_coord;
      a = ac; 
      b = bc; 
      size = 0.0; 
      count = 0;
      while ((size < 4.0) && (count < 1000))
      {
        /* Do complex-number multiply */
        b1 = 2*a*b;
        a = a*a - b*b + ac;
        b = b1 + bc;
        /* Pythagorean theorem */
        size = a*a + b*b;
        /* Don't need square root */
        count++;
      }
      totct += count;
      /* Code count in two bytes to save disk space */
      ct[x][0] = count / 256;
      ct[x][1] = count % 256;
    } /* End x loop */

    /* Print coded pixel-values this row to data file */
    for (x=1; x<=XDIM; x++)
    {
      aa = ct[x][0];
      bb = ct[x][1];
      count = aa*255 + bb;   /* Decode count         */
      /* Select a color based on counts using color
       * function and color each pixel accordingly    
       */
      pixelval = color(count); /* Select a color     */
	  img_data[3*i+0] = ((pixelval >> 16) & 0xFF);
	  img_data[3*i+1] = ((pixelval >> 8) & 0xFF);
	  img_data[3*i+2] = (pixelval & 0xFF);
	  i++;
    }
  } /* End y loop */
  
  /* Store image data to PPM file. */
  write_ppm_file(OutFile, img_data, "doset.ppm", XDIM, YDIM,
    1, 1, 255, 1);

  fclose(OutFile); /* Close data file */
  
  /* Free image data storage. */
  free(img_data);
  
} /* End main */
