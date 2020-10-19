/*
 * File       : randimg.c                                                          
 * Description: Generate PPM and PGM images with random content.
 * Author     : Nikolaos Kavvadias <nikolaos.kavvadias@gmail.com>                
 * Copyright  : (C) Nikolaos Kavvadias 2012, 2013, 2014, 2015, 2016, 2017
 *                                     2018, 2019, 2020
 * Website    : http://www.nkavvadias.com                            
 *                                                                          
 * This file is part of libpnmio, and is distributed under the terms of the  
 * Modified BSD License.
 *
 * A copy of the Modified BSD License is included with this distribution 
 * in the file LICENSE.
 * libpnmio is free software: you can redistribute it and/or modify it under the
 * terms of the Modified BSD License. 
 * libpnmio is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the Modified BSD License for more details.
 * 
 * You should have received a copy of the Modified BSD License along with 
 * libpnmio. If not, see <http://www.gnu.org/licenses/>. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pnmio.h"

#define  XDIM_DEFAULT     256
#define  YDIM_DEFAULT     256
//#define  PFM_SCALE        15.0
#define  PFM_SCALE        1.0

int copied_imgout_file_name=0;
int enable_pbm=1, enable_ppm=0, enable_pgm=0, enable_pfm=0;
int enable_ascii=1, enable_binary=0;
int enable_rgb=1, enable_greyscale=0;
char imgout_file_name[96];
FILE *imgout_file;
//
int x_dim=XDIM_DEFAULT, y_dim=YDIM_DEFAULT;


/* print_usage:
 * Print usage instructions for the "randimg" program.
 */
static void print_usage()
{
  printf("\n");
  printf("* Usage:\n");
  printf("* randimg [options] <outfile>\n");
  printf("* \n");
  printf("* Options:\n");
  printf("*   -h:              Print this help.\n");
  printf("*   -pbm:            Generate a PBM image with random content (default).\n");
  printf("*   -pgm:            Generate a PGM image with random content.\n");
  printf("*   -ppm:            Generate a PPM image with random content.\n");
  printf("*   -pfm:            Generate a PFM image with random content.\n");
  printf("*   -ascii:          Emit PNM image in the ASCII format (default).\n");
  printf("*   -binary:         Emit PNM image in the binary format.\n");
  printf("*   -rgb:            Emit a color PFM image (default).\n");
  printf("*   -greyscale:      Emit a greyscale PFM image.\n");
  printf("*   -x <num>:        Value for the x-dimension of the image (default:256).\n");
  printf("*   -y <num>:        Value for the y-dimension of the image (default:256).\n");
  printf("* \n");
  printf("* For further information, please refer to the website:\n");
  printf("* http://www.nkavvadias.com\n\n");
}

/* main:
 * The main "randimg" routine.
 */
int main(int argc, char **argv)
{
  int *img_data;
  float *pfm_data;
  int i=0;
  long int x, y, c;
  float f;

  // Read input arguments
  if (argc < 2) {
    print_usage();
    exit(1);
  }

  for (i = 1; i < argc; i++) {
    if (strcmp("-h",argv[i]) == 0) {
      print_usage();
      exit(1);
    } else if (strcmp("-pbm",argv[i]) == 0) {
      enable_pbm = 1;
      enable_pgm = 0;
      enable_ppm = 0;
      enable_pfm = 0;
    } else if (strcmp("-pgm",argv[i]) == 0) {
	    enable_pbm = 0;
      enable_pgm = 1;
      enable_ppm = 0;
      enable_pfm = 0;
    } else if (strcmp("-ppm",argv[i]) == 0) {
      enable_pbm = 0;
      enable_pgm = 0;
      enable_ppm = 1;
      enable_pfm = 0;
    } else if (strcmp("-pfm",argv[i]) == 0) {
      enable_pbm = 0;
      enable_pgm = 0;
      enable_ppm = 0;
      enable_pfm = 1;
    } else if (strcmp("-ascii",argv[i]) == 0) {
      enable_ascii  = 1;
      enable_binary = 0;
    } else if (strcmp("-binary",argv[i]) == 0) {
      enable_ascii  = 0;
      enable_binary = 1;
    } else if (strcmp("-rgb",argv[i]) == 0) {
      enable_rgb       = 1;
      enable_greyscale = 0;
    } else if (strcmp("-greyscale",argv[i]) == 0) {
      enable_rgb       = 0;
      enable_greyscale = 1;
    } else if (strcmp("-x",argv[i]) == 0) {
      if ((i+1) < argc) {
        i++;
        x_dim = atoi(argv[i]);
      }
    }
    else if (strcmp("-y",argv[i]) == 0) {
      if ((i+1) < argc) {
        i++;
        y_dim = atoi(argv[i]);
      }
    }
    else if (strcmp("-o",argv[i]) == 0) {
      if ((i+1) < argc) {
        i++;
        strcpy(imgout_file_name, argv[i]);
        copied_imgout_file_name = 1;
      }
    } else {
      fprintf(stderr, "Error: Unknown command-line option.\n");
      exit(1);
    }
  }

  if (copied_imgout_file_name==1) {
    if ((enable_ascii == 1) && (enable_pfm == 0)) {
      if ((imgout_file = fopen(imgout_file_name,"w")) == NULL) {
        fprintf(stderr, "Error: Can't create the specified output file.\n");
        exit(1);
      } 
    } else {
      if ((imgout_file = fopen(imgout_file_name,"wb")) == NULL) {
        fprintf(stderr, "Error: Can't create the specified output file.\n");
        exit(1);
      } 
    }
  }
 
  /* Perform operations. */
  if (enable_pfm == 1) {
    if (enable_rgb == 1) {
      pfm_data = malloc((3 * x_dim * y_dim) * sizeof(float));
    } else {
      pfm_data = malloc((x_dim * y_dim) * sizeof(float));
    }      
  } else if (enable_ppm == 1) {
    img_data = malloc((3 * x_dim * y_dim) * sizeof(int));
  } else {
    img_data = malloc((x_dim * y_dim) * sizeof(int));
  }
  
  c = rand();
  i = 0;
  for (y = 0; y < y_dim; y++) {
    for (x = 0; x < x_dim; x++) {
      if (enable_ppm == 1) {
	      c = rand() & 0xff;
	      img_data[3*i+0] = c;
	      c = rand() & 0xff;
	      img_data[3*i+1] = c;
	      c = rand() & 0xff;
	      img_data[3*i+2] = c;	
      } else if (enable_pgm == 1) {
        c = rand() & 0xff;
		    img_data[i] = c;
	    } else if (enable_pbm == 1) {
	      c = rand() & 0x1;
		    img_data[i] = c;
	    }
	    i++;
    }
  } 

  if (enable_pfm == 1) {
    i = 0;
    for (y = 0; y < y_dim; y++) {
      for (x = 0; x < x_dim; x++) {
        if (enable_rgb == 1) {
//          f = ceil(PFM_SCALE * frand());
          f = PFM_SCALE * frand();
          pfm_data[3*i+0] = f;
//          f = ceil(PFM_SCALE * frand());
          f = PFM_SCALE * frand();
          pfm_data[3*i+1] = f;
//          f = ceil(PFM_SCALE * frand());
          f = PFM_SCALE * frand();
          pfm_data[3*i+2] = f;
        } else if (enable_greyscale == 1) {
//          f = ceil(PFM_SCALE * frand());
          f = PFM_SCALE * frand();
          pfm_data[i]     = f;
        }
        i++;
      }
    }
  } 
  
  if (enable_ppm == 1) {
    write_ppm_file(imgout_file, img_data, imgout_file_name, 
	  x_dim, y_dim, 1, 1, 255, enable_ascii);
  } else if (enable_pgm == 1) {
    write_pgm_file(imgout_file, img_data, imgout_file_name, 
	  x_dim, y_dim, 1, 1, 255, 16, enable_ascii);
  } else if (enable_pbm == 1) {
    write_pbm_file(imgout_file, img_data, imgout_file_name, 
	  x_dim, y_dim, 1, 1, 32, enable_ascii);
  } else if (enable_pfm == 1) {
    write_pfm_file(imgout_file, pfm_data, imgout_file_name, 
    x_dim, y_dim, enable_rgb, (IS_LITTLE_ENDIAN ? -1 : 1));
  }
  
  if (enable_ppm == 1 || enable_pgm == 1 || enable_pbm == 1) {
    free(img_data);
  } else if (enable_pfm == 1) {
    free(pfm_data);
  }

  return 0;
}
