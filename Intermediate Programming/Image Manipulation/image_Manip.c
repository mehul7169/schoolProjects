// Aditya Khandeshi
// akhande3
// Mehul Agarwal
// magarw13
#include <assert.h>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include "ppm_io.h"
#include "image_Manip.h"

#define PI 3.141592653


unsigned char multply_blend(unsigned char color_value1, unsigned char color_value2, double blend_value) {
	unsigned char result = blend_value * color_value1 + (1 - blend_value)*color_value2;
	
	return result;
}

unsigned char multiply_exposure(unsigned char color_value, double exposure_value) {
	double result = color_value * pow(2.0, exposure_value);
	if (result > 255) {
		return (unsigned char) 255;
	}
	return (unsigned char) result;
} 

/* Read a PPM-formatted image from a file (assumes fp != NULL).
 * Returns the address of the heap-allocated Image struct it
 * creates and populates with the Image data.
 */
Image * exposure(Image * im, double exposure_value) {
	Image * output = malloc(sizeof(Image));
	output->rows = im->rows;
	output->cols = im->cols;
	output->data = (Pixel *) malloc(sizeof(Pixel) * output->rows * output->cols);
	for (int i = 0; i < im->rows * im->cols; i++) {
		Pixel * curr_pixel = &output->data[i];
		curr_pixel->r = multiply_exposure(curr_pixel->r, exposure_value);
		curr_pixel->g = multiply_exposure(curr_pixel->g, exposure_value);
		curr_pixel->b = multiply_exposure(curr_pixel->b, exposure_value);
	}
	return output;
}

Image * blending(Image * im_1, Image * im_2, double blend_value) {
	int max_cols, max_rows, min_rows, min_cols, col1, col2, row1, row2;
	col1 = im_1->cols;
	col2 = im_2->cols;
	row1 = im_1->rows;
	row2 = im_2->rows;
	if (im_1->rows > im_2->rows) {
		max_rows = im_1->rows;
		min_rows = im_2->rows;
	}
	else {
		max_rows = im_2->rows;
		min_rows = im_1->rows;
	}
	if (im_1->cols > im_2->cols) {
		max_cols = im_1->cols;
		min_cols = im_2->cols;
	}
	else {
		max_cols = im_2->cols;
		min_cols = im_1->cols;
	}
	Image * output = malloc(sizeof(Image));
	output->rows = max_rows;
	output->cols = max_cols;
	output->data = (Pixel *) malloc(sizeof(Pixel) * max_cols * max_rows);
	for(int i = 0; i < min_rows; i++) {
		for (int j = 0; j < min_cols; j++) {
			Pixel * curr_pixel = &output->data[i*max_cols+j];
			curr_pixel->r = multply_blend(im_1->data[i*col1 + j].r, im_2->data[i*col2 + j].r, blend_value);
			curr_pixel->g = multply_blend(im_1->data[i*col1 + j].g, im_2->data[i*col2 + j].g, blend_value);
			curr_pixel->b = multply_blend(im_1->data[i*col1 + j].b, im_2->data[i*col2 + j].b, blend_value);

		}
		for (int j = min_cols; j < max_cols; j++) {
			Pixel * curr_pixel = &output->data[i*max_cols + j];
			if (im_1->cols > im_2->cols) {
				curr_pixel->r = im_1->data[i*col1 + j].r;
				curr_pixel->g = im_1->data[i*col1 + j].g;
				curr_pixel->b = im_1->data[i*col1 + j].b;
			}
			else {
				curr_pixel->r = im_2->data[i*col2 + j].r;
				curr_pixel->g = im_2->data[i*col2 + j].g;
				curr_pixel->b = im_2->data[i*col2 + j].b;	
			}
		}
	}
	for (int i = min_rows+1; i <= max_rows; i++) {
		if (row1 > row2) {
			for (int j = 0; j < col1; j++) {
				Pixel * curr_pixel = &output->data[i*max_cols + j];
				curr_pixel->r = im_1->data[i*col1 + j].r;
				curr_pixel->g = im_1->data[i*col1 + j].g;
				curr_pixel->b = im_1->data[i*col1 + j].b;
			}
		}
		else {
			for (int j = 0; j < col2; j++) {
				Pixel * curr_pixel = &output->data[i*max_cols + j];
				curr_pixel->r = im_2->data[i*col2 + j].r;
				curr_pixel->g = im_2->data[i*col2 + j].g;
				curr_pixel->b = im_2->data[i*col2 + j].b;
			}
		}
	}
	return output;	
}

Image * zoom_in(Image * im) {
	Image * output = malloc(sizeof(Image));
	output->rows = im->rows * 2;
	output->cols = im->cols * 2;
	output->data = (Pixel *) malloc(sizeof(Pixel) * im->cols * im->rows * 4);
	for (int i = 0; i < im->rows * im->cols; i++) {
		int row = i / im->cols;
		int col = i % im->cols;
		int start_i = (row * 2) * output->cols + (col* 2);
		output->data[start_i] = im->data[i];
		output->data[start_i + 1] = im->data[i];
		output->data[start_i + output->cols] = im->data[i];
		output->data[start_i + 1 + output->cols] = im->data[i];		
	  }
	return output;
}

Image * zoom_out(Image * im) {
	Image * output = malloc(sizeof(Image));
	output->rows = im->rows/2;
	output->cols = im->cols/2;
	output->data = (Pixel *) malloc(sizeof(Pixel) * im->cols * im->rows / 4);
	for (int i = 0; i < output->rows * output->cols; i++) {
		int row = i / output->cols;
		int col = i % output->cols;

		int start_i = (row * 2) * im->cols + (col* 2);
		output->data[i].r = (im->data[start_i].r + im->data[start_i + 1].r + im->data[start_i + im->cols].r + im->data[start_i + 1 + im->cols].r)/4;
		output->data[i].g = (im->data[start_i].g + im->data[start_i + 1].g + im->data[start_i + im->cols].g + im->data[start_i + 1 + im->cols].g)/4;
		output->data[i].b = (im->data[start_i].b + im->data[start_i + 1].b + im->data[start_i + im->cols].b + im->data[start_i + 1 + im->cols].b)/4;
	}
	return output;
}

double alpha(int x, int y, int cx, int cy, int s){
  return (sqrt(pow(x - cx, 2) + pow(y - cy, 2))) / s;
}
int pixel_index(int col, int row, int num_cols){
  return  col + row*num_cols;
}

Image * swirl(Image * im, int cx, int cy, int scale){
  Image * output = malloc(sizeof(Image));
  output->rows = im->rows;
  output->cols = im->cols;
  output->data = (Pixel *) malloc(sizeof(Pixel) * im->cols * im->rows);
  for(int i = 0; i < output->rows; i++){
    for(int j = 0; j < output->cols; j++){
      double a = alpha(j, i, cx, cy, scale);
      Pixel * curr_pixel = &output->data[pixel_index(j, i, output->cols)];
      *curr_pixel = im->data[pixel_index((j - cx)*cos(a) - (i - cy)*sin(a)+ cx, (j - cx)*sin(a) + (i - cy)*cos(a) + cy, output->cols)];
    }
  }
  return output;
}


double sq(double value) {
	return pow(value, 2.0);
}

double** get_gaussian_matrix(double sigma, int N) {
	double** gaussian_matrix = (double **) malloc(N * sizeof(double *));

	for (int i=0; i < N; i++) {
		gaussian_matrix[i] = (double *)malloc(N * sizeof(double));
		for (int j=0; j < N; j++) {
			int dx = (N/2) - i;
			int dy = (N/2) - j;
			gaussian_matrix[i][j] = (1.0 / (2.0 * PI * sq(sigma))) * exp( -(sq(dx) + sq(dy)) / (2 * sq(sigma)));
		}	
	}
	return gaussian_matrix;
}

Pixel * apply_gaussian_matrix(double** gaussian_matrix, Image * im, int i, int N) {
	double weighted_r, weighted_g, weighted_b, gaussian_weighted_sum;
	weighted_r = 0.0;
	weighted_g = 0.0;
	weighted_b = 0.0;
	gaussian_weighted_sum = 0.0;


	int row = i / im->cols;
	int col = i % im->cols;

	for (int dx = -N/2; dx <= N/2; dx ++) {
		int new_row = row + dx;
		if ( new_row < 0 || new_row >= im->rows){
			continue;
		}
		for (int dy = -N/2; dy <= N/2; dy ++) {
			int new_col = col + dy;
			if ( new_col < 0 || new_col >= im-> cols){
				continue;
			}

			int new_index = new_row * im->cols + new_col;
			double weight = gaussian_matrix[dx + N/2][dy + N/2];
			gaussian_weighted_sum += weight;
			weighted_r += im->data[new_index].r * weight;
			weighted_g += im->data[new_index].g * weight;
			weighted_b += im->data[new_index].b * weight;
		}
	}

	Pixel * output = malloc(sizeof(Pixel));
	output->r = weighted_r/gaussian_weighted_sum;
	output->g = weighted_g/gaussian_weighted_sum;
	output->b = weighted_b/gaussian_weighted_sum;
	return output;
}


Image * blur(Image * im, double sigma) {
	int N = (int) ( 5 * sigma) * 2 + 1;
	double ** gaussian_matrix = get_gaussian_matrix(sigma, N);

	Image * output = malloc(sizeof(Image));
	output->rows = im->rows;
	output->cols = im->cols;
	output->data = (Pixel *) malloc(sizeof(Pixel) * im->rows * im->cols);

	for (int i = 0; i < im->rows * im->cols; i++) {
		Pixel * new_pixel = apply_gaussian_matrix(gaussian_matrix, im, i, N);
		output->data[i] = *new_pixel;
		free(new_pixel);
	}
	return output;
}

void pointilism(Image * im){
  int num_pixels = 0.03 * (im->rows) * (im->cols);
  for(int i = 0; i < num_pixels; i++){
    int centerX = rand() % im->cols;
    int centerY = rand() % im->rows;
    int radius = (rand() % 5) + 1;
    for(int j = centerY - radius; j <= centerY + radius; j++){
      for(int k = centerX - radius; k <= centerX + radius; k++){
		if((j > 0 || j == 0) && j < im->rows && (k > 0 || k == 0) && k < im->cols){
	  		if(pow(k - centerX, 2) + pow(j - centerY, 2) <= pow(radius, 2)){
	    		im->data[pixel_index(k, j, im->cols)] = im->data[pixel_index(centerX, centerY, im->cols)];
	    	}
		}
      }
    }
  }
}
