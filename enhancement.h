#ifndef ENHANCEMENT_H
#define ENHANCEMENT_H
#include "assistant.h"

#define		WHITE_LAB	255
#define		BLACK_LAB	0


void linear(Mat img, float *datos, long int anchura, long int altura, double start, double end, double s_gray, float slope, int change);

int maxMinSlide(Mat img, int maxSlope);

void remap_Image(Mat img, float *datos, long int dmin, long int dmax);

void hist_slide(Mat img, float *datos,int slide);

void hist_shrink(Mat img,float *datos, int upper, int lower);

void hist_stretch(Mat img, int low_limit, int high_limit, float low_clip, float high_clip, float * datos4);

void hist_stretch_gray(Mat img, int low_limit, int high_limit, float low_clip, float high_clip, float * datos2);

void adaptive_contrast_filter(Mat img, float k1, float k2, unsigned int kernel_size, float min_gain,  float max_gain, float *datos);

void adaptive_contrast_filter_gray(Mat img, float k1, float k2,unsigned int kernel_size, float min_gain,  float max_gain, float *datos);

Mat image_sharp( Mat inputImage);

Mat high_pass(Mat img);

Mat High_Freq_Emphasis(Mat img, int block_size, int dc, int	Cutoff, float alfa, int	order);

Mat High_Freq_Emphasis_gray(Mat img, int block_size, int dc, int Cutoff, float alfa, int order);

void unsharp_filter(Mat img, int lower, int upper,float low_clip, float high_clip,float *datos);

Mat homomorphic_filter(Mat img, float upper, float lower, int threshold);

void hef(Mat& input, Mat& output, float lower, float upper, float threshold);

Mat threshold_detect(Mat img, float threshold);

Mat threshold_detect_gray(Mat img, float threshold);

Mat moravec_corner_filter(Mat img, float threshval);

Mat moravec_corner_filter_gray(Mat img, float threshval);

Mat kuwahara_filter(Mat img, int mask_size);

Mat kuwahara_filter_gray(Mat img, int mask_size);

#endif // ENHANCEMENT_H
