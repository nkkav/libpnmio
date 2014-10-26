/*
 * File       : rnwimg.c                                                          
 * Description: Read an input PBM, PGM, PPM or PFM image and then write it 
 *              back (for testing purposes aka exercising the API).
 * Author     : Nikolaos Kavvadias <nikolaos.kavvadias@gmail.com>                
 * Copyright  : (C) Nikolaos Kavvadias 2014
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
#define  PFM_SCALE        1.0
#define  MAXLINE         1024

int copied_imgin_file_name=0, copied_imgout_file_name=0;
int enable_pbm=0, enable_ppm=0, enable_pgm=0, enable_pfm=0;
int enable_ascii=0, enable_binary=0;
int enable_rgb=0, enable_greyscale=0;
int img_colors=1, img_type, endianess;
char *imgin_file_name, *imgout_file_name;
FILE *imgin_file, *imgout_file;
//
int x_dim=XDIM_DEFAULT, y_dim=YDIM_DEFAULT;


/* print_usage:
 * Print usage instructions for the "rnwimg" program.
 */
static void print_usage()
{
  printf("\n");
  printf("* Usage:\n");
  printf("* ./rnwimg -i <infile> -o <outfile>\n");
  printf("* \n");
  printf("* Options:\n");
  printf("*   -h:              Print this help.\n");
  printf("*   -i <infile>:     Read input from file <infile>.\n");
  printf("*   -o <outfile>:    Write output to file <outfile>.\n");
  printf("* \n");
  printf("* For further information, please refer to the website:\n");
  printf("* http://www.nkavvadias.com\n\n");
}

/* main:
 * The main "rnwimg" routine.
 */
int main(int argc, char **argv)
{
  int *img_data;
  float *pfm_data;
  int i=0;
  int pnm_type=0;
  char magic[MAXLINE];

  // Read input arguments
  if (argc < 2) {
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
    } else {
      fprintf(stderr, "Error: Unknown command-line option.\n");
      exit(1);
    }
  }

  /* Open input file. */
  if (copied_imgin_file_name==1) {
    if ((enable_ascii == 1) && (enable_pfm == 0)) {
      if ((imgin_file = fopen(imgin_file_name,"r")) == NULL) {
        fprintf(stderr, "Error: Can't open the specified input file.\n");
        exit(1);
      } 
    } else {
      if ((imgin_file = fopen(imgin_file_name,"rb")) == NULL) {
        fprintf(stderr, "Error: Can't open the specified input file.\n");
        exit(1);
      } 
    }
  }

  /* Get the PNM/PFM image type. */
  pnm_type = get_pnm_type(imgin_file);
  fprintf(stderr, "Info: pnm_type = %d\n", pnm_type);
  rewind(imgin_file);

  /* Read the image file header (the input file has been rewinded). */
  if ((pnm_type == PBM_ASCII) || (pnm_type == PBM_BINARY)) {
    read_pbm_header(imgin_file, &x_dim, &y_dim, &enable_ascii);
  } else if ((pnm_type == PGM_ASCII) || (pnm_type == PGM_BINARY)) {
    read_pgm_header(imgin_file, &x_dim, &y_dim, &img_colors, &enable_ascii);
  } else if ((pnm_type == PPM_ASCII) || (pnm_type == PPM_BINARY)) {
    read_ppm_header(imgin_file, &x_dim, &y_dim, &img_colors, &enable_ascii);
  } else if ((pnm_type == PFM_RGB) || (pnm_type == PFM_GREYSCALE)) {
    read_pfm_header(imgin_file, &x_dim, &y_dim, &img_type, &endianess);    
    enable_pfm = 1;
  } else {    
    fprintf(stderr, "Error: Unknown PNM/PFM image format. Exiting...\n");
    exit(1);
  }

  /* Open output file. */
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
  if (pnm_type == PFM_RGB) {
    pfm_data = malloc((3 * x_dim * y_dim) * sizeof(float));
  } else if (pnm_type == PFM_GREYSCALE) {
    pfm_data = malloc((x_dim * y_dim) * sizeof(float));      
  } else if ((pnm_type == PPM_ASCII) || (pnm_type == PPM_BINARY)) {
    img_data = malloc((3 * x_dim * y_dim) * sizeof(int));
  } else {
    img_data = malloc((x_dim * y_dim) * sizeof(int));
  }

  /* Read the image data. */
  if ((pnm_type == PBM_ASCII) || (pnm_type == PBM_BINARY)) {
    read_pbm_data(imgin_file, img_data, enable_ascii);
  } else if ((pnm_type == PGM_ASCII) || (pnm_type == PGM_BINARY)) {
    read_pgm_data(imgin_file, img_data, enable_ascii);
  } else if ((pnm_type == PPM_ASCII) || (pnm_type == PPM_BINARY)) {
    read_ppm_data(imgin_file, img_data, enable_ascii);
  } else if (enable_pfm == 1) {
    read_pfm_data(imgin_file, pfm_data, img_type, endianess);    
  }

  /* Write the output image file. */
  if ((pnm_type == PBM_ASCII) || (pnm_type == PBM_BINARY)) {
    write_pbm_file(imgout_file, img_data, imgout_file_name, 
      x_dim, y_dim, 1, 1, 32, enable_ascii
    );
  } else if ((pnm_type == PGM_ASCII) || (pnm_type == PGM_BINARY)) {
    write_pgm_file(imgout_file, img_data, imgout_file_name,
      x_dim, y_dim, 1, 1, img_colors, 16, enable_ascii
    );
  } else if ((pnm_type == PPM_ASCII) || (pnm_type == PPM_BINARY)) {
    write_ppm_file(imgout_file, img_data, imgout_file_name,
      x_dim, y_dim, 1, 1, img_colors, enable_ascii
    );
  } else if (enable_pfm == 1) {
    write_pfm_file(imgout_file, pfm_data, imgout_file_name,
      x_dim, y_dim, img_type, endianess
    );
  }

  if (enable_pfm == 1) {
    free(pfm_data);
  } else {
    free(img_data);
  }
  free(imgin_file);
  free(imgin_file_name);
  return 0;
}
