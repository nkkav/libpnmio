/*
 * File       : sftbyvec.c                                                          
 * Description: Read an input ASCII PGM image, shift its contents by 
 *            : a given vector and then writes it back.
 * Author     : Nikolaos Kavvadias <nikolaos.kavvadias@gmail.com>                
 * Copyright  : (C) Nikolaos Kavvadias 2014, 2015, 2016, 2017
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
#define  MAXLINE         1024

int copied_imgin_file_name=0, copied_imgout_file_name=0;
int enable_ascii=1;
int img_colors=1, img_type;
char *imgin_file_name, *imgout_file_name;
FILE *imgin_file, *imgout_file;
//
int vx_size=0, vy_size=0;
int x_dim=XDIM_DEFAULT, y_dim=YDIM_DEFAULT;


/* sftbyvec:
 * Shift the entire image contents by a (vx, vy) vector.
 */
void sftbyvec(int *in_data, int *out_data, int vxval, int vyval)
{
  int x, y;
  int new_x, new_y;

  for (y = 0; y < y_dim; y++) {
    for (x = 0; x < x_dim; x++) {
      out_data[y * x_dim + x] = 0x00;
    }
  }
  for (y = 0; y < y_dim; y++) {
    for (x = 0; x < x_dim; x++) {
      new_x = x + vxval;
      new_y = y + vyval;
      if ((new_x >= 0 && new_x < x_dim) &&
          (new_y >= 0 && new_y < y_dim)) {
        out_data[new_y * x_dim + new_x] = in_data[y * x_dim + x];
      }
    }
  }
}

/* print_usage:
 * Print usage instructions for the "sftbyvec" program.
 */
static void print_usage()
{
  printf("\n");
  printf("* Usage:\n");
  printf("* ./sftbyvec -i <infile> -o <outfile> [-vx <num> -vy <num>]\n");
  printf("* \n");
  printf("* Options:\n");
  printf("*   -h:              Print this help.\n");
  printf("*   -vx <num>:       Value for the x-dimension of the vector (default: 0).\n");
  printf("*   -vy <num>:       Value for the y-dimension of the vector (default: 0).\n");
  printf("*   -i <infile>:     Read input from file <infile>.\n");
  printf("*   -o <outfile>:    Write output to file <outfile>.\n");
  printf("* \n");
  printf("* For further information, please refer to the website:\n");
  printf("* http://www.nkavvadias.com\n\n");
}

/* main:
 * The main "sftbyvec" routine.
 */
int main(int argc, char **argv)
{
  int *imgin_data, *imgout_data;
  int i=0;
  int pnm_type=0;

  // Read input arguments
  if (argc < 3) {
    print_usage();
    exit(1);
  }

  for (i = 1; i < argc; i++) {
    if (strcmp("-h", argv[i]) == 0) {
      print_usage();
      exit(1);
    } else if (strcmp("-i", argv[i]) == 0) {
      if ((i+1) < argc) {
        i++;
        imgin_file_name = malloc((strlen(argv[i]) + 1) * sizeof(char));
        strcpy(imgin_file_name, argv[i]);
        copied_imgin_file_name = 1;
      }
    } else if (strcmp("-o", argv[i]) == 0) {
      if ((i+1) < argc) {
        i++;
        imgout_file_name = malloc((strlen(argv[i]) + 1) * sizeof(char));
        strcpy(imgout_file_name, argv[i]);
        copied_imgout_file_name = 1;
      }     
    } else if (strcmp("-vx",argv[i]) == 0) {
      if ((i+1) < argc) {
        i++;
        vx_size = atoi(argv[i]);
      }
    }
    else if (strcmp("-vy",argv[i]) == 0) {
      if ((i+1) < argc) {
        i++;
        vy_size = atoi(argv[i]);
      }
    } else {
      fprintf(stderr, "Error: Unknown command-line option.\n");
      exit(1);
    }
  }

  /* Open input file. */
  if (copied_imgin_file_name==1) {
    if ((imgin_file = fopen(imgin_file_name, "r")) == NULL) {
      fprintf(stderr, "Error: Can't open the specified input file.\n");
      exit(1);
    }
  }

  /* Get the PNM/PFM image type. */
  pnm_type = get_pnm_type(imgin_file);
  rewind(imgin_file);

  /* Read the image file header (the input file has been rewinded). */
  if (pnm_type == PGM_ASCII) {
    read_pgm_header(imgin_file, &x_dim, &y_dim, &img_colors, &enable_ascii);
  } else {    
    fprintf(stderr, "Error: Only ASCII PGM format is supported. Exiting...\n");
    exit(1);
  }

  /* Open output file. */
  if (copied_imgout_file_name==1) {
    if ((imgout_file = fopen(imgout_file_name,"w")) == NULL) {
      fprintf(stderr, "Error: Can't create the specified output file.\n");
      exit(1);
    }
  }

  /* Perform operations. */
  imgin_data  = malloc((x_dim * y_dim) * sizeof(int));
  imgout_data = malloc((x_dim * y_dim) * sizeof(int));

  /* Read the image data. */
  read_pgm_data(imgin_file, imgin_data, enable_ascii);

  /* Shift-by-vector. */
  sftbyvec(imgin_data, imgout_data, vx_size, vy_size);

  /* Write the output image file. */
  write_pgm_file(imgout_file, imgout_data, imgout_file_name,
      x_dim, y_dim, 1, 1, img_colors, 16, enable_ascii);
#if 0
  free(img_data);
  free(imgin_file);
  free(imgin_file_name);
#endif
  return 0;
}

