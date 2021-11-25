// Aditya Khandeshi
// akhande3
// Mehul Agarwal
// magarw13
// ppm_io.h
// 601.220, Spring 2019
// Starter code for midterm project - feel free to edit/add to this file


#ifndef IMAGE_MANIP_H
#define IMAGE_MANIP_H

#include <stdio.h>
#include "ppm_io.h"



/* 
 * 
 */
Image * exposure(Image * im, double exposure_value);

Image * blending(Image * im_1, Image * im_2, double blend_value);

Image * zoom_in(Image * im);

Image * zoom_out(Image * im);

Image * swirl(Image * im, int cx, int cy, int scale);

void pointilism(Image * im);

Image * blur(Image * im, double sigma);

#endif