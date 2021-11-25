#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "image_Manip.h"
#include "ppm_io.h"

int main(int args, char * argv[]) {
  if (args < 3) {
    return 1;
  }

  char * input = argv[1];
  char * output = argv[2];
  Image * output_im;

  FILE * fp = fopen(input, "r");
  Image * im = read_ppm(fp);

  if (args <= 3) {
    fprintf(stderr, "Failed to supply input filename or output filename, or both");
    return 1;
  } 
  else if (args <= 3) {
    fprintf(stderr, "No operation name was specified");
    return 3;
  }
  else if (!strcmp(argv[3], "exposure")){
     if (args <= 3) {
      fprintf(stderr, "Invalid number of arguments.");
      return 5;
     }
     else {
      double a;
      if(sscanf(argv[4], " %lf", &a) != 1) {
        fprintf(stderr, "%s\n", "Error");
        return 1;
      }
      double exposure_value = a;
      output_im = exposure(im, exposure_value);
     }
  }

  else if (!strcmp(argv[3], "blend")){
    if (args <= 5) {
      fprintf(stderr, "Invalid number of arguments");
      return 5;
    }
    else {
      char * input2 = argv[4];
      FILE * fp2 = (fopen(input2, "r"));
      Image * im2 = read_ppm(fp2);
      double blend_value;
      if(sscanf(argv[5], " %lf", &blend_value) != 1) {
        fprintf(stderr, "%s\n", "Error");
        return 1;
      }
      output_im = blending(im, im2, blend_value);
    }
  }

  else if (!strcmp(argv[3],"zoom_in")){
    if (args != 4) {
      fprintf(stderr, "Invalid number of arguments");
      return 5;
    }
    else {
      output_im = zoom_in(im);
    }
  }


  else if (!strcmp(argv[3], "zoom_out")){
    if (args != 4) {
      fprintf(stderr, "Invalid number of arguments");
      return 5;
    }
    else {
      output_im = zoom_out(im);
    } 
  }


  else if (!strcmp(argv[3], "pointilism")){
    if (args != 4) {
      fprintf(stderr, "Invalid number of arguments");
      return 5;
    }
    else {
      pointilism(im);
      output_im = im;
    }
  }


  else if (!strcmp(argv[3], "swirl")){
    if (args != 7) {
      fprintf(stderr, "Invalid number of arguments");
      return 5;
    }
    else {
      int cx;
      int cy;
      int scale;
      if(sscanf(argv[4], " %d", &cx) != 1 || sscanf(argv[6], " %d", &scale) != 1 || sscanf(argv[5], " %d", &cy) != 1) {
        fprintf(stderr, "%s\n", "Error");
        return 1;
      }
      
      output_im = swirl(im, cx, cy, scale);
    }
  }
  else if (!strcmp(argv[3],"blur")){
    if (args != 5) {
      fprintf(stderr, "Invalid number of arguments");
      return 5;
    }
    else {
      double sigma;
      if (sscanf(argv[4], " %lf", &sigma) != 1) {
        fprintf(stderr, "%s\n", "Error");
        return 1;
      }
      output_im = blur(im, sigma);
    }
  }
  else {
    fprintf(stderr, "Invalid operation name.");
    return 4;
  }


  // FILE * fp2 = fopen("data/building.ppm", "r");
  // Image * im2 = read_ppm(fp2);
  // printf("original image: r %d g %d b %d \n", im->data[0].r, im->data[0].g, im->data[0].b);
  // printf("exposure image: r %d g %d b %d \n", output_im->data[0].r, output_im->data[0].g, output_im->data[0].b);
  FILE * output_fp = fopen(output, "wb");
  if (!output_fp) {
    fprintf(stderr, "Uh oh. Output file failed to open!\n");
    free(im->data);
    free(im);
    return 7;
  }
  int num_pixels_written = write_ppm(output_fp, output_im);
  if (num_pixels_written != output_im->rows * output_im->cols) {
    fprintf(stderr, "Error in writing file output");
    return 2;
  }
  return 0;
}

