// Aditya Khandeshi
// akhande3
// Mehul Agarwal
// magarw13
// ppm_io.c
// 601.220, Spring 2019
// Starter code for midterm project - feel free to edit/add to this file

#include <assert.h>
#include<stdio.h>
#include<stdlib.h>
#include "ppm_io.h"
#include "image_Manip.h"
#include "string.h"


/* Read a PPM-formatted image from a file (assumes fp != NULL).
 * Returns the address of the heap-allocated Image struct it
 * creates and populates with the Image data.
 */
Image * read_ppm(FILE *fp) {

  char buffer[100];
  char comment_character;
  int rows, cols, colors;

  // check that fp is not NULL
  assert(fp);
  Image * im = malloc(sizeof(Image));

  if (!im) {
    fprintf(stderr, "Uh oh. Image allocation failed!\n");
    exit(2);
  }


  if (fscanf(fp, "%s", buffer) != 1) {
    fprintf(stderr, "Unable to read specified image\n");
    exit(2);
   }

  // Check the image tag contains "P6".
  if (buffer[0] != 'P' || buffer[1] != '6') {
     fprintf(stderr, "Invalid tag for image. Can only read P6.\n");
     exit(1);
  }

  while(fgetc(fp) != '\n');

  comment_character = fgetc(fp);

  // Skip all characters on lines that start with #. 
  while (comment_character == '#') {
     while (comment_character != '\n') {
      comment_character = fgetc(fp);
     }
     comment_character = fgetc(fp);
  }

  // If the line is not a comment line we need to move back by one character.
  ungetc(comment_character,fp);

  if (fscanf(fp, "%d %d", &cols, &rows) != 2) {
    fprintf(stderr, "Unable to read image attributes.\n");
    exit(1);
  }

  if (fscanf(fp, "%d", &colors) != 1) {
    fprintf(stderr, "Unable to read colors.\n");
    exit(1);
  }

  while(fgetc(fp) != '\n');

  if (colors != 255) {
    fprintf(stderr, "There should be exactly 255 colors.\n");
    exit(1);
  }
  
  im->rows = rows;
  im->cols = cols;

  int total_pixels  = rows*cols;
  im->data = (Pixel *) malloc(sizeof(Pixel) * total_pixels);

  if (!im->data) {
    fprintf(stderr, "Uh oh. Pixel array allocation failed!\n");
    exit(1);
  }


  int size = fread(im->data, sizeof(Pixel), total_pixels, fp);

  if (  size !=  total_pixels) {
    fprintf(stderr, "Unable to read all pixels from the image.\n");
    exit(1); 
  } 

  fclose(fp);

  return im;
}


/* Write a PPM-formatted image to a file (assumes fp != NULL),
 * and return the number of pixels successfully written.
 */
int write_ppm(FILE *fp, const Image *im) {

  // check that fp is not NULL
  assert(fp); 

  // write PPM file header, in the following format
  // P6
  // cols rows
  // 255
  fprintf(fp, "P6\n%d %d\n255\n", im->cols, im->rows);

  // now write the pixel array
  int num_pixels_written = fwrite(im->data, sizeof(Pixel), im->cols * im->rows, fp);

  if (num_pixels_written != im->cols * im->rows) {
    fprintf(stderr, "Uh oh. Pixel data failed to write properly!\n");
  }

  return num_pixels_written;
}


