//Mahmudul Hasan and Aninda
#include "IP.h"
#include <math.h>    // pow
using namespace IP;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_gammaCorrect:
//
// Gamma correct image I1. Output is in I2.
//
void
HW_gammaCorrect(ImagePtr I1, double gamma, ImagePtr I2)
{
	// s = c * r^gamma. c=1, r=image input
	// gamma correction: s = c * r^(1/gamma).

	// copy image header (width, height) of input image I1 to output image I2
	IP_copyImageHeader(I1, I2);
	// declarations for image channel pointers and datatype
	ChannelPtr<uchar> p1, p2;
	int type;

	// init vars for width, height, and total number of pixels
	int w = I1->width();
	int h = I1->height();
	int total = w * h;

	// init lookup table
	int c = 255;
	int lut[MXGRAY];
	for (int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) { // get input pointer for the channel 'ch' we are working on. This is the grayscale channel. so only one iteration  
		for (int i = 0; i < MXGRAY; i++) {					  // LUT: generage an output grayscale value for every possible input gray scale [0,255]
			// log moves the gamma * log(i +1); moves the graph as u go
			int output = pow(i, 1/gamma);
			//int output = pow(i, 1 / gamma)*log(i +1);
			//int output = pow(i, 1/gamma)*log(i + 1);

			if (output < 0) output = 0;
			if (output > 255) output = 255;
			lut[i] = (int)output;
		}
	}

	// visit all image channels and evaluate output image
	for (int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) {	// get input  pointer for channel ch
		IP_getChannel(I2, ch, p2, type);						// get output pointer for channel ch
		for (int i = 0; i < total; i++)
			*p2++ = lut[*p1++];			                        // use lut[] to eval output
	}
}

//int output = pow(i, 1 / gamma)*log(i +1);

//
//// init lookup table
//int c = 255;
//int lut[MXGRAY];
//for (int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) { // get input pointer for the channel 'ch' we are working on. This is the grayscale channel. so only one iteration  
//	for (int i = 0; i < MXGRAY; i++) {					  // go throught image
//		int output = pow(i, 1 / gamma);
//
//		if (output < 0) output = 0;
//		if (output > 255) output = 255;
//		lut[i] = (int)output;
//	}
//}
//
//// visit all image channels and evaluate output image
//for (int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) {	// get input  pointer for channel ch
//	IP_getChannel(I2, ch, p2, type);						// get output pointer for channel ch
//	for (int i = 0; i < total; i++)
//		*p2++ = lut[*p1++];			// use lut[] to eval output
//}




















	//int c = 100;
	//int lut[MXGRAY];
	//for (int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) { // get input  pointer for channel ch ***(i think this returns the pointer that points to the first pixel in each row of pixels in the imgae or maybe each bit of a 8bit pixel)
	//	IP_getChannel(I2, ch, p2, type);
	//	for (int i = 0; i < total; i++) {					  // go throught image
	//		int input = *p1++;
	//		int output = (int) (gamma * pow(input, 1/gamma));
	//		if (output < 0) output = 0;
	//		if (output > 255) output = 255;

	//		*p2++ = output;
	//		  
	//		
	//	}
	//}

	// visit all image channels and evaluate output image
	//for (int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) {	// get input  pointer for channel ch
	//	IP_getChannel(I2, ch, p2, type);	// get output pointer for channel ch
	//	for (int i = 0; i < total; i++)
	//		*p2++ = lut[*p1++];				// use lut[] to eval output
	//}



