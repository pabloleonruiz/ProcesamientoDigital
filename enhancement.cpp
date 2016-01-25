#include "enhancement.h"

int maxSlide(Mat img,double maxSlope)
{
    int i1;
    int canales= img.channels();
    int filas=img.rows;
    int columnas=img.cols;
    int numero_puntos=columnas*filas;
    double max=maxSlope;

   // Se declara la variable que va a acceder a los datos de la imagen
    uchar *auxiliar;

    // Se accede a los datos de la imagen
    auxiliar = (uchar *)img.data;

    max=auxiliar[0];

       for (i1 = 0; i1 < canales * numero_puntos; i1++)
       {

                if(auxiliar[i1]>max)
               {
                   max=auxiliar[i1];
               }

       }
return max;
}

void linear(Mat img, float *datos, long int columnas, long int filas, double start, double end, double s_gray, float slope,int change)
{
 int i1;
 int canales= img.channels();
 int numero_puntos=columnas*filas;
 double value;

 // Se declara la variable que va a acceder a los datos de la imagen
 uchar *auxiliar;

 // Se accede a los datos de la imagen
 auxiliar = (uchar *)img.data;

 //Se copian los datos a auxiliar
 for (i1 = 0; i1 < canales * numero_puntos; i1++)
    {
                            //Si el valor no se encuentra entre start y end se copia tal y como esta, o se pone a 0
                            if (auxiliar[i1] < start || auxiliar[i1] > end)
                             {
                                  if (change)
                                  datos[(i1 % canales) * numero_puntos + i1/canales] = auxiliar[i1];
                                  else
                                  datos[(i1 % canales) * numero_puntos + i1/canales] = 0;
                             }

                            //Si el valor se encuentra entre start y end se modifica
                            else
                             {
                               value = s_gray + slope*( auxiliar[i1] - start);
                               if (value>255) value=255; if (value<0) value=0;
                               datos[(i1 % canales) * numero_puntos + i1/canales] = value;
                              }
    }

}

/****************************************************************
                   Name: remap_Image
             Parameters: <img> - Imagen de tipo Mat
             <dmin> - valor minimo del rango
             <dmax> - valor maximo del rango
                Returns: pointer to a new instance of the Image <imageP>
             that has been mapped into the range [<dmin>...<dmax>].
*****************************************************************/


void remap_Image(Mat img, float *datos, long int dmin, long int dmax)
{
    int i1;
    int canales= img.channels();
    int filas=img.rows;
    int columnas=img.cols;
    int numero_puntos=columnas*filas;

    double 		maxspread=0, factor;
    double		temp_min,temp_max;


 // Se declara la variable que va a acceder a los datos de la imagen
 uchar *auxiliar;

 // Se accede a los datos de la imagen
 auxiliar = (uchar *)img.data;

 temp_min=auxiliar[0];
 temp_max=auxiliar[0];

    for (i1 = 0; i1 < canales * numero_puntos; i1++)
    {

            if(auxiliar[i1]<temp_min)
            {
                temp_min=auxiliar[i1];
            }

            if(auxiliar[i1]>temp_max)
            {
                temp_max=auxiliar[i1];
            }

    }

    maxspread = temp_max -temp_min;

    if(maxspread == 0.0)
        maxspread = dmax - dmin;

    factor = ((double)dmax-dmin)/maxspread;

    for(i1 = 0; i1 < canales * numero_puntos; i1++)
          datos[(i1 % canales) * numero_puntos + i1/canales] = dmin + factor*( auxiliar[i1] - temp_min ) + 0.5 ;

}

/***************************************************************************
*             File Name: hist_slide.c
*           Description: This file contains function for two types of
*			 operations, histogram shrink(or stretch), histogram
*			 slide.
*			 Histogram shrink and stretch is implemented in
*			 hist_shrink_Setup, which takes one argument, input
*			 image pointer. It asks for the upper and lower
*			 limit histogram of the output image, then it
*			 calls remap_Image to map the image to the destined
*			 histogram range.
*
*			 Histogram slide is implemented in function
*			 hist_slide. There are two arguments:
*			    Image *input, pointer contains image data
*			    int   slide, amount of slide, can be positive
*				or negative. When it is negative, it makes
*				image darker. When it is positive, it makes
*				image brighter.
*			 HistSlide_Setup is a setup function for hist_slide
*			 It acts interactively.
****************************************************************************/

void hist_slide(Mat img, float *datos,int slide){
    int temp;
    int i1;
    int canales= img.channels();
    int filas=img.rows;
    int columnas=img.cols;
    int numero_puntos=columnas*filas;

   // Se declara la variable que va a acceder a los datos de la imagen
    uchar *auxiliar;

    // Se accede a los datos de la imagen
    auxiliar = (uchar *)img.data;

    for (i1 = 0; i1 < canales * numero_puntos; i1++)
    {
              temp=auxiliar[i1];
              temp+=slide;
              if(temp>255)
                 temp=255;
              else if(temp < 0)
                 temp=0;
              datos[(i1 % canales) * numero_puntos + i1/canales]=temp;
    }
}


void hist_shrink(Mat img,float *datos, int upper, int lower)
{
   if(upper > 255)
    upper = 255;
   else if(upper < 1)
    upper = 1;
   if(lower < 0)
    lower = 0;
   else if(lower > 254)
    lower = 254;
    remap_Image(img,datos,lower,upper);
}


void hist_stretch(Mat img, int low_limit, int high_limit, float low_clip, float high_clip, float * datos4)
{
    Mat tempImage;
    int rows, cols;
    float *datos1,*datos2,*datos3;

    rows = img.rows;
    cols = img.cols;

    tempImage = img.clone();

    datos1 = (float *) malloc(3 * cols * rows * sizeof (float));
    datos2 = (float *) malloc(3 * cols * rows * sizeof (float));
    datos3 = (float *) malloc(3 * cols * rows * sizeof (float));


    int			i, j, k, l, h;
    int 		      * ptr;
    long			total, suml, sumh;


    vector<Mat> bgr_planes;
    split( tempImage, bgr_planes );

    int histSize = 256;

    float range[] = { 0, 255 } ;
    const float* histRange = { range };

    bool uniform = true; bool accumulate = false;

    Mat b_hist, g_hist, r_hist;

    /// Compute the histograms:
    calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

    extraer_datos_realzada(b_hist,datos1);
    extraer_datos_realzada(g_hist,datos2);
    extraer_datos_realzada(r_hist,datos3);


      total = rows * cols;
      ptr = (int *)malloc(img.channels() * 2 * sizeof(int));

k=0;
          l = -1;
          h = 256;
          suml = 0;
          sumh = 0;
          while ((suml/(float)total) < low_clip)
        { l++;
          suml += datos1[k*256 + l];
        }
          if ((suml/(float)total) >= (low_clip + 0.01)) l--;
          while ((sumh/(float)total) < high_clip)
        { h--;
          sumh += datos1[k*256 + h];
        }
          if ((sumh/(float)total) >= (high_clip + 0.01)) h++;
          ptr[k*2] = l;
          ptr[k*2 + 1] = h;

k=1;

         l = -1;
         h = 256;
         suml = 0;
         sumh = 0;
         while ((suml/(float)total) < low_clip)
        { l++;
        suml += datos2[k*256 + l];
        }
        if ((suml/(float)total) >= (low_clip + 0.01)) l--;
        while ((sumh/(float)total) < high_clip)
        { h--;
        sumh += datos2[k*256 + h];
        }
        if ((sumh/(float)total) >= (high_clip + 0.01)) h++;
        ptr[k*2] = l;
        ptr[k*2 + 1] = h;

k=2;

        l = -1;
        h = 256;
        suml = 0;
        sumh = 0;
        while ((suml/(float)total) < low_clip)
        { l++;
        suml += datos3[k*256 + l];
        }
        if ((suml/(float)total) >= (low_clip + 0.01)) l--;
        while ((sumh/(float)total) < high_clip)
        { h--;
        sumh += datos3[k*256 + h];
        }
        if ((sumh/(float)total) >= (high_clip + 0.01)) h++;
        ptr[k*2] = l;
        ptr[k*2 + 1] = h;


    for (k=0; k<img.channels(); k++)
      {
        l = ptr[k*2];
        h = ptr[k*2 + 1];
        for (i=0; i<rows; i++)
          for (j=0; j<cols; j++)
        { if ((int)img.at<Vec3b>(i,j)[k] <= l) img.at<Vec3b>(i,j)[k] = (uchar)l+1;
              if ((int)img.at<Vec3b>(i,j)[k] >= h) img.at<Vec3b>(i,j)[k]  = (uchar)h-1;
            }
      }
  remap_Image(img,datos4,low_limit,high_limit);
}

void hist_stretch_gray(Mat img, int low_limit, int high_limit, float low_clip, float high_clip, float * datos2)
{
  Mat tempImage;
  int rows, cols;
  float *datos1;

  rows = img.rows;
  cols = img.cols;

  tempImage = img.clone();

datos1 = (float *) malloc(1 * cols * rows * sizeof (float));


    int			i, j, l, h;
    int 		      * ptr;
    long			total, suml, sumh;


    vector<Mat> bgr_planes;
    split( tempImage, bgr_planes );

    int histSize = 256;

    float range[] = { 0, 255 } ;
    const float* histRange = { range };

    bool uniform = true; bool accumulate = false;

    Mat b_hist;

    /// Compute the histograms:
    calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );

    extraer_datos_realzada(b_hist,datos1);


      total = rows * cols;
      ptr = (int *)malloc(img.channels() * 2 * sizeof(int));


          l = -1;
          h = 256;
          suml = 0;
          sumh = 0;
          while ((suml/(float)total) < low_clip)
        { l++;
          suml += datos1[l];
        }
          if ((suml/(float)total) >= (low_clip + 0.01)) l--;
          while ((sumh/(float)total) < high_clip)
        { h--;
          sumh += datos1[h];
        }
          if ((sumh/(float)total) >= (high_clip + 0.01)) h++;
          ptr[0] = l;
          ptr[1] = h;



        l = ptr[0];
        h = ptr[1];
        for (i=0; i<rows; i++)
          for (j=0; j<cols; j++)
        { if ((int)img.at<uchar>(i,j) <= l) img.at<uchar>(i,j) = (uchar)l+1;
              if ((int)img.at<uchar>(i,j) >= h) img.at<uchar>(i,j)  = (uchar)h-1;
            }

  remap_Image(img,datos2,low_limit,high_limit);
}

/******************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================

                   Name: adaptive_contrast.c
          Expanded Name: adaptive contrast filter

             Parameters: inputImage -- Pointer to the input image of type
                       Image.

             k1 -- A constant between 0 and 1.
             k2 -- Another constant between 0 and 1.

             kernel_size -- size of the kernel(should be an
                    odd number).

             min_gain -- the minimum gain factor
             max_gain -- the maximum gain factor

                Returns: pointer to an image that is the filtering result
             of the input image using adaptive contrast filter.

            Description: The input image is a real image, it can be
             multi_band and of any data type: CVIP_BYTE, CVIP_SHORT,
                         CVIP_INTEGER, CVIP_FLOAT and CVIP_DOUBLE.



*******************************************************************************/

void adaptive_contrast_filter(Mat img, float k1, float k2,unsigned int kernel_size, float min_gain,  float max_gain, float *datos)
{

  double sum,offset;
  int canales= img.channels();
  int filas=img.rows;
  int columnas=img.cols;
  int numero_puntos=columnas*filas;
  double *mean;
  mean = (double *)calloc(canales, sizeof(double));
  Mat temp (filas,columnas,CV_8UC3);
  if (kernel_size != 1)
{

  //  if (adap_prep(inputImage, kernel_size)) return NULL;
for(int k=0;k< canales;k++)
{
    sum=0;
    for(int i=0;i< filas;i++)
         for(int j=0;j< columnas;j++)
            sum += (float)img.at<Vec3b>(i,j)[k];

mean[k]=sum/numero_puntos;
}

offset = kernel_size / 2;

int		x_, y_;
float   value_,sum_ave_,sum_var_,factor_;

for(int k=0;k< canales;k++)
{
    for(int i=0;i< filas;i++)
    {
        for(int j=0;j< columnas;j++)
        {
           if (i>=(filas-offset) || i<offset || j>=(columnas-offset) || j<offset)
                temp.at<Vec3b>(i,j)[k]=img.at<Vec3b>(i,j)[k];

            else
            {
                sum_ave_ = 0;
                sum_var_ = 0;
              for (x_=-offset; x_<=offset; x_++)
                for (y_=-offset; y_<=offset; y_++)
                  {
                    value_ = img.at<Vec3b>(i+x_,j+y_)[k];
                    sum_ave_ += value_;
                    sum_var_ += value_ * value_;
                  }

              sum_ave_ /= (kernel_size*kernel_size);
              sum_var_ /= (kernel_size*kernel_size);
              sum_var_ -= sum_ave_ * sum_ave_;
              if (sum_var_ != 0)
                   factor_ = k1 * (mean[k] / sum_var_);
              else factor_ = max_gain;
              if (factor_ > max_gain) factor_ = max_gain;
              if (factor_ < min_gain) factor_ = min_gain;
              temp.at<Vec3b>(i,j)[k] =factor_*(img.at<Vec3b>(i,j)[k] - sum_ave_) + k2*sum_ave_;
            }
         }
     }
    }
remap_Image(temp,datos,0,255);
  }
  else
      extraer_datos_imagen_BGR_separados(img, datos);
}


void adaptive_contrast_filter_gray(Mat img, float k1, float k2,unsigned int kernel_size, float min_gain,  float max_gain, float *datos)
{

  double sum,offset;
  int filas=img.rows;
  int columnas=img.cols;
  int numero_puntos=columnas*filas;
  double mean=0;
  Mat temp (filas,columnas,CV_8UC1);
  if (kernel_size != 1)
{
    sum=0;
    for(int i=0;i< filas;i++)
         for(int j=0;j< columnas;j++)
            sum += (float)img.at<uchar>(i,j);

mean=sum/numero_puntos;


offset = kernel_size / 2;

int		x_, y_;
float   value_,sum_ave_,sum_var_,factor_;


    for(int i=0;i< filas;i++)
    {
        for(int j=0;j< columnas;j++)
        {
           if (i>=(filas-offset) || i<offset || j>=(columnas-offset) || j<offset)
                temp.at<uchar>(i,j)=img.at<uchar>(i,j);

            else
            {
                sum_ave_ = 0;
                sum_var_ = 0;
              for (x_=-offset; x_<=offset; x_++)
                for (y_=-offset; y_<=offset; y_++)
                  {
                    value_ = img.at<uchar>(i+x_,j+y_);
                    sum_ave_ += value_;
                    sum_var_ += value_ * value_;
                  }

              sum_ave_ /= (kernel_size*kernel_size);
              sum_var_ /= (kernel_size*kernel_size);
              sum_var_ -= sum_ave_ * sum_ave_;
              if (sum_var_ != 0)
                   factor_ = k1 * (mean / sum_var_);
              else factor_ = max_gain;
              if (factor_ > max_gain) factor_ = max_gain;
              if (factor_ < min_gain) factor_ = min_gain;
              temp.at<uchar>(i,j) =factor_*(img.at<uchar>(i,j) - sum_ave_) + k2*sum_ave_;
            }
         }
     }
    remap_Image(temp,datos,0,255);
      }
      else
          extraer_datos_realzada(img, datos);

}


Mat high_pass(Mat img)
{
//Se puede añadir a la imagen
    Mat temp (img.rows,img.cols,img.type());

    Mat kernel=(Mat_<float>(3,3)<<  0, -1, 0,
                                -1, 4,  -1,
                                 0, -1, 0);

    filter2D(img,temp,-1,kernel,Point(-1,-1),0,BORDER_DEFAULT);

    return temp;
}

Mat High_Freq_Emphasis(Mat img, int block_size, int dc, int	Cutoff, float alfa, int	order)
{
  int i,ii, jj,  x, y,x1, y1;
  int a=0, b=0, nofblk, Hnofblk, Hcounter=1;
  float C=0.414;
  double H=0, temp, r1;
  int h, w;


  h = img.cols;
  w = img.rows;

  nofblk=(h/block_size)*(w/block_size);  /* total number of blocks */
  Hnofblk=w/block_size;
  order *= 2;

  for(i=1; i<= nofblk; ){

    x1 = a+block_size/2; y1 = b+block_size/2;
    for(x=a; x< (a+block_size); x++ ){
      for(y=b; y<(b+block_size); y++){

        ii=abs(x-x1);
        jj=abs(y-y1);
        r1=sqrt((double)(ii*ii)+(double)(jj*jj)); /* D(u, v) */

        if(r1 != 0){
           temp = (double)(Cutoff/r1);
           H = (1/ ( 1 + C*(pow(temp, (double)(order)))));
           H += alfa;
        }
        if(!(x==x1 && y==y1) ) {

            img.at<Vec3b>(x,y)[0] *= H;

           if(img.channels() == 3) {

               img.at<Vec3b>(x,y)[1] *= H;
               img.at<Vec3b>(x,y)[2] *= H;

            }
        }
      } /* end y=a..*/
    } /* end x=a... */

    if (!dc){
        img.at<Vec3b>(x1,y1)[0] = 0;


      if(img.channels() == 3) {

          img.at<Vec3b>(x1,y1)[1] = 0;
          img.at<Vec3b>(x1,y1)[2] = 0;

        }
    }
    i++; /* one block done */

    Hcounter++;      /* counter to keep track of Hori Blk performed */

    if(Hcounter > Hnofblk){ /* reset Hcounter  */
        a = 0;
        b += block_size;
        Hcounter = 1;
    } else
        a += block_size;

  } /* end (for i=1 ; */

 return img;
}

Mat High_Freq_Emphasis_gray(Mat img, int block_size, int dc, int Cutoff, float alfa, int order)
{
  int i,ii, jj,  x, y,x1, y1;
  int a=0, b=0, nofblk, Hnofblk, Hcounter=1;
  float C=0.414;
  double H=0, temp, r1;
  int h, w;


  h = img.cols;
  w = img.rows;

  nofblk=(h/block_size)*(w/block_size);  /* total number of blocks */
  Hnofblk=w/block_size;
  order *= 2;

  for(i=1; i<= nofblk; ){

    x1 = a+block_size/2; y1 = b+block_size/2;
    for(x=a; x< (a+block_size); x++ ){
      for(y=b; y<(b+block_size); y++){

        ii=abs(x-x1);
        jj=abs(y-y1);
        r1=sqrt((double)(ii*ii)+(double)(jj*jj)); /* D(u, v) */

        if(r1 != 0){
           temp = (double)(Cutoff/r1);
           H = (1/ ( 1 + C*(pow(temp, (double)(order)))));
           H += alfa;
        }
        if(!(x==x1 && y==y1) )
            img.at<uchar>(x,y) *= H;

      } /* end y=a..*/
    } /* end x=a... */

    if (!dc)
        img.at<uchar>(x1,y1) = 0;

    i++; /* one block done */

    Hcounter++;      /* counter to keep track of Hori Blk performed */

    if(Hcounter > Hnofblk){ /* reset Hcounter  */
        a = 0;
        b += block_size;
        Hcounter = 1;
    } else
        a += block_size;

  } /* end (for i=1 ; */

 return img;
}

/***************************************************************************
*
*             File Name: homomorphic.c
*           Description: This file contain the code for homomorphic filter.
*
*****************************************************************************/

void hef(Mat& input, Mat& output, float lower, float upper, float threshold)
{
    Mat* i_ptr = &input;
    int width = i_ptr->cols;
    int height = i_ptr->rows;
    int channel = i_ptr->channels();

    Mat* o_ptr = &output;
    if(i_ptr != o_ptr) {
        *o_ptr = Mat(height, width, CV_MAKETYPE(CV_32F, channel));
    }

    for(int y=0; y<height; y++) {
        for(int x=0; x<width; x++) {
            float r = sqrt((float)(x*x + y*y));
            double coeff = (1.0 - 1.0 / (1.0 + exp(r - threshold))) * (upper - lower) + lower;
            for(int c=0; c<channel; c++) {
                o_ptr->at<float>(y, x*channel+c) = coeff * i_ptr->at<float>(y, x*channel+c);
            }
        }
    }
}

Mat homomorphic_filter(Mat img,float upper, float lower, int threshold)
{

        int width = img.cols;
        int height = img.rows;
        int channel = img.channels();

        img.convertTo(img, CV_32FC3, 1.0 / 255.0);

        // Aplica DFT, high emphasis filter y IDFT
        vector<Mat> chs, spc(channel, Mat(height, width, CV_32FC1));
        split(img, chs);
        for(int c=0; c<channel; c++) {
            dft(chs[c], spc[c]);
            hef(spc[c], spc[c], lower, upper, threshold);
            idft(spc[c], chs[c]);
        }
        Mat out;
        merge(chs, out);
        out.convertTo(out, CV_8UC3, 255.0);
        return out;

}

/***************************************************************************
*             File Name: unsharp.c
*           Description: the file contains program to implement unsharp mask
*			 The function call takes five arguments
*			    Image *inputImage, image image data
*			    int lower, the lower limit for shrink histogram
*			    int upper, the upper limit for shrink histogram
*			    float low_clip, % clip low end for hist stretch
*			    float high_clip,% clip high end for hist stretch
****************************************************************************/

void unsharp_filter(Mat img, int lower, int upper,float low_clip, float high_clip,float *datos2)
{
    Mat copyImage, temp,remap,diff;

    float *datos;

    datos = (float *) malloc(img.channels() * img.cols * img.rows * sizeof (float));

    copyImage = img.clone();

    Mat kernel=(Mat_<float>(3,3)<<  0, -1, 0,
                                -1, 4,  -1,
                                 0, -1, 0);

    filter2D(img,temp,-1,kernel,Point(-1,-1),0,BORDER_DEFAULT);

    hist_shrink(temp,datos,upper,lower);

    if(img.channels()==3)
    {
    crear_imagen_BGR(&remap,temp.cols, temp.rows, datos,temp.channels());

    diff= img-remap;

    hist_stretch(diff,0,255,low_clip, high_clip,datos2);
    }
    else
    {
        crear_imagen_niveles_gris(&remap,temp.cols,temp.rows,datos);
        diff= img-remap;

        hist_stretch_gray(diff,0,255,low_clip, high_clip,datos2);
    }
}

/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE
*
* =========================================================================
*
*             File Name: moravec_corner_detection.c
*           Description: function to detect edges in the image
****************************************************************************/


Mat moravec_corner_filter(Mat img, float threshval)

{
        int 	r,	c, 	bands, i=0 ,j =0;

        int 	no_of_rows,	no_of_cols,	no_of_bands;

        no_of_bands = img.channels();

        no_of_rows =  img.rows;

        no_of_cols =  img.cols;

        Mat output (img.rows,img.cols,img.type());


        if(threshval>255)

            threshval=255;

        else if(threshval<0)

            threshval=0;

        /*Calculating the average of the surrounding pixels*/

        for(bands=0; bands < no_of_bands; bands++)

        {

            for(i=0;i<no_of_rows;i++)
            {
                for(j=0;j<no_of_cols;j++)
                {
                    output.at<Vec3b>(i,j)[bands]=0.0f;

                    if(i==0||j==0||i==no_of_rows-1||j==no_of_cols-1)

                        output.at<Vec3b>(i,j)[bands]=0.0f;

                    else

                    {
                        for(r=i-1; r <= i+1; r++)

                        {
                            for(c=j-1; c <= j+1; c++)

                                output.at<Vec3b>(i,j)[bands]=output.at<Vec3b>(i,j)[bands]+(img.at<Vec3b>(i,j)[bands]-img.at<Vec3b>(r,c)[bands]);
                        }

                        output.at<Vec3b>(i,j)[bands]=output.at<Vec3b>(i,j)[bands]/8;
                    }
                }
            }
        }

        output=threshold_detect(output,threshval);

        return output;
    }

Mat moravec_corner_filter_gray(Mat img, float threshval)

{
        int 	r,	c, i=0 ,j =0;

        int 	no_of_rows,	no_of_cols;

        no_of_rows =  img.rows;

        no_of_cols =  img.cols;

        Mat output (img.rows,img.cols,img.type());

        if(threshval>255)

            threshval=255;

        else if(threshval<0)

            threshval=0;

        /*Calculating the average of the surrounding pixels*/

           for(i=0;i<no_of_rows;i++)
            {
                for(j=0;j<no_of_cols;j++)
                {
                    output.at<uchar>(i,j)=0.0f;

                    if(i==0||j==0||i==no_of_rows-1||j==no_of_cols-1)

                        output.at<uchar>(i,j)=0.0f;

                    else

                    {
                        for(r=i-1; r <= i+1; r++)

                        {
                            for(c=j-1; c <= j+1; c++)

                                output.at<uchar>(i,j)=output.at<uchar>(i,j)+(img.at<uchar>(i,j)-img.at<uchar>(r,c));
                        }

                        output.at<uchar>(i,j)=output.at<uchar>(i,j)/8;
                    }
                }
            }


        output=threshold_detect_gray(output,threshval);

        return output;
    }

    /*Threshold Function*/

    Mat threshold_detect(Mat img, float threshold)
    {

        int 		r,	c, bands;

        int 	no_of_rows,	no_of_cols, no_of_bands;

        no_of_bands = img.channels();

        no_of_rows =  img.rows;

        no_of_cols =  img.cols;

        for(bands=0;bands<no_of_bands;bands++)
        {
            for(r=0; r < no_of_rows; r++)

            {
                for(c=0; c < no_of_cols; c++)

                {
                    if(img.at<Vec3b>(r,c)[bands] > threshold)

                        img.at<Vec3b>(r,c)[bands] = WHITE_LAB;

                    else

                        img.at<Vec3b>(r,c)[bands] = BLACK_LAB;
                }
            }
        }
        return img;
    }

    Mat threshold_detect_gray(Mat img, float threshold)
    {

        int 		r,	c;

        int 	no_of_rows,	no_of_cols;


        no_of_rows =  img.rows;

        no_of_cols =  img.cols;


            for(r=0; r < no_of_rows; r++)

            {
                for(c=0; c < no_of_cols; c++)

                {
                    if(img.at<uchar>(r,c) > threshold)

                        img.at<uchar>(r,c) = WHITE_LAB;

                    else

                        img.at<uchar>(r,c) = BLACK_LAB;
                }
            }

        return img;
    }


    Mat kuwahara_filter(Mat img, int mask_size)
    {

        unsigned int    nofrows,  nofcols, nofbands, bands;
        unsigned int d = 0, r, c, i, j;
        float localMean, localVariance, bestMean, bestVariance, mean[2], sum=0, count=0,temp;


        nofbands = img.channels();
        nofrows =  img.rows;
        nofcols =  img.cols;
        Mat outputImage (nofrows,nofcols,CV_8UC3);


        d=(mask_size-1)/2;

          for(bands=0; bands < nofbands; bands++) {
              for(r=d; r < nofrows-d; r++){
                  for(c=d; c < nofcols-d; c++){
                      sum=0;count=0;
                      for(i=(r-d); i<=r; i++)
                      {
                        for(j=(c-d); j<=c; j++)
                        {

                            sum = sum + img.at<Vec3b>(i,j)[bands];
                            count = count + 1;
                        }
                      }
                      mean[0] = (float)(sum/count);
                      sum =0;
                      for(i=(r-d); i<=r; i++)
                      {
                        for(j=(c-d); j<=c; j++)
                        {
                            temp = mean[0] - img.at<Vec3b>(i,j)[bands];
                            sum = sum + (temp * temp);
                        }
                      }
                      mean[1] = (float)(sum/count);
                      localMean = (float)mean[0];
                      localVariance = (float)mean[1];
                      bestMean = localMean;
                      bestVariance = localVariance;
                      if (localVariance < bestVariance)
                      {
                          bestMean     = localMean;
                          bestVariance = localVariance;
                      }
                      sum=0;count=0;

                      //mean = (float*)mean_and_variance (r, (c-d), (r+d), c, image);
                      for(i=r; i<=(r+d); i++)
                      {
                        for(j=(c-d); j<=c; j++)
                        {
                            //v = image1[i][j];
                            sum = sum + img.at<Vec3b>(i,j)[bands];
                            count = count + 1;
                        }
                      }
                      mean[0] = (float)(sum/count);
                      sum =0;
                      for(i=r; i<=(r+d); i++)
                      {
                        for(j=(c-d); j<=c; j++)
                        {
                            temp = mean[0] - img.at<Vec3b>(i,j)[bands];
                            sum = sum + (temp * temp);
                        }
                      }
                      mean[1] = (float)(sum/count);
                      localMean = (float)mean[0];
                      localVariance = (float)mean[1];
                      if (localVariance < bestVariance)
                      {
                          bestMean     = localMean;
                          bestVariance = localVariance;
                      }
                      sum=0;count=0;
                      //mean = (float*)mean_and_variance ((r-d), c, r, (c+d), image);
                      for(i=(r-d); i<=r; i++)
                      {
                        for(j=c; j<=(c+d); j++)
                        {
                            //v = image1[i][j];
                            sum = sum + img.at<Vec3b>(i,j)[bands];
                            count = count + 1;
                        }
                      }
                      mean[0] = (float)(sum/count);
                      sum =0;
                      for(i=(r-d); i<=r; i++)
                      {
                        for(j=c; j<=(c+d); j++)
                        {
                            temp = mean[0] - img.at<Vec3b>(i,j)[bands];
                            sum = sum + (temp * temp);
                        }
                      }
                      mean[1] = (float)(sum/count);
                      localMean = (float)mean[0];
                      localVariance = (float)mean[1];
                      if (localVariance < bestVariance)
                      {
                          bestMean     = localMean;
                          bestVariance = localVariance;
                      }
                      sum=0;count=0;
                      //mean = (float*)mean_and_variance (r, c, (r+d), (c+d), image);
                      for(i=r; i<=(r+d); i++)
                      {
                        for(j=c; j<=(c+d); j++)
                        {
                            //v = image1[i][j];
                            sum = sum + img.at<Vec3b>(i,j)[bands];
                            count = count + 1;
                        }
                      }
                      mean[0] = (float)(sum/count);
                      sum =0;
                      for(i=r; i<=(r+d); i++)
                      {
                        for(j=c; j<=(c+d); j++)
                        {
                            temp = mean[0] - img.at<Vec3b>(i,j)[bands];
                            sum = sum + (temp * temp);
                        }
                      }
                      mean[1] = (float)(sum/count);
                      localMean = (float)mean[0];
                      localVariance = (float)mean[1];
                      if (localVariance < bestVariance)
                      {
                          bestMean     = localMean;
                          bestVariance = localVariance;
                      }
                      outputImage.at<Vec3b>(r,c)[bands] = (float)bestMean;
                  }
              }
          }
        return outputImage;
    }


    Mat kuwahara_filter_gray(Mat img, int mask_size)
    {

        unsigned int    nofrows,  nofcols;
        unsigned int d = 0, r, c, i, j;
        float localMean, localVariance, bestMean, bestVariance, mean[2], sum=0, count=0,temp;


        nofrows =  img.rows;
        nofcols =  img.cols;
        Mat outputImage (nofrows,nofcols,CV_8UC1);


        d=(mask_size-1)/2;

                for(r=d; r < nofrows-d; r++){
                  for(c=d; c < nofcols-d; c++){
                      sum=0;count=0;
                      for(i=(r-d); i<=r; i++)
                      {
                        for(j=(c-d); j<=c; j++)
                        {

                            sum = sum + img.at<uchar>(i,j);
                            count = count + 1;
                        }
                      }
                      mean[0] = (float)(sum/count);
                      sum =0;
                      for(i=(r-d); i<=r; i++)
                      {
                        for(j=(c-d); j<=c; j++)
                        {
                            temp = mean[0] - img.at<uchar>(i,j);
                            sum = sum + (temp * temp);
                        }
                      }
                      mean[1] = (float)(sum/count);
                      localMean = (float)mean[0];
                      localVariance = (float)mean[1];
                      bestMean = localMean;
                      bestVariance = localVariance;
                      if (localVariance < bestVariance)
                      {
                          bestMean     = localMean;
                          bestVariance = localVariance;
                      }
                      sum=0;count=0;

                      //mean = (float*)mean_and_variance (r, (c-d), (r+d), c, image);
                      for(i=r; i<=(r+d); i++)
                      {
                        for(j=(c-d); j<=c; j++)
                        {
                            //v = image1[i][j];
                            sum = sum + img.at<uchar>(i,j);
                            count = count + 1;
                        }
                      }
                      mean[0] = (float)(sum/count);
                      sum =0;
                      for(i=r; i<=(r+d); i++)
                      {
                        for(j=(c-d); j<=c; j++)
                        {
                            temp = mean[0] - img.at<uchar>(i,j);
                            sum = sum + (temp * temp);
                        }
                      }
                      mean[1] = (float)(sum/count);
                      localMean = (float)mean[0];
                      localVariance = (float)mean[1];
                      if (localVariance < bestVariance)
                      {
                          bestMean     = localMean;
                          bestVariance = localVariance;
                      }
                      sum=0;count=0;
                      //mean = (float*)mean_and_variance ((r-d), c, r, (c+d), image);
                      for(i=(r-d); i<=r; i++)
                      {
                        for(j=c; j<=(c+d); j++)
                        {
                            //v = image1[i][j];
                            sum = sum + img.at<uchar>(i,j);
                            count = count + 1;
                        }
                      }
                      mean[0] = (float)(sum/count);
                      sum =0;
                      for(i=(r-d); i<=r; i++)
                      {
                        for(j=c; j<=(c+d); j++)
                        {
                            temp = mean[0] - img.at<uchar>(i,j);
                            sum = sum + (temp * temp);
                        }
                      }
                      mean[1] = (float)(sum/count);
                      localMean = (float)mean[0];
                      localVariance = (float)mean[1];
                      if (localVariance < bestVariance)
                      {
                          bestMean     = localMean;
                          bestVariance = localVariance;
                      }
                      sum=0;count=0;
                      //mean = (float*)mean_and_variance (r, c, (r+d), (c+d), image);
                      for(i=r; i<=(r+d); i++)
                      {
                        for(j=c; j<=(c+d); j++)
                        {
                            //v = image1[i][j];
                            sum = sum + img.at<uchar>(i,j);
                            count = count + 1;
                        }
                      }
                      mean[0] = (float)(sum/count);
                      sum =0;
                      for(i=r; i<=(r+d); i++)
                      {
                        for(j=c; j<=(c+d); j++)
                        {
                            temp = mean[0] - img.at<uchar>(i,j);
                            sum = sum + (temp * temp);
                        }
                      }
                      mean[1] = (float)(sum/count);
                      localMean = (float)mean[0];
                      localVariance = (float)mean[1];
                      if (localVariance < bestVariance)
                      {
                          bestMean     = localMean;
                          bestVariance = localVariance;
                      }
                      outputImage.at<uchar>(r,c) = (float)bestMean;
                  }
              }

        return outputImage;
    }

    /*****************************************************************************
        ======================================================================
        Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
        ======================================================================
               Name: image_sharp
              Expanded Name: image sharpening
                 Parameters: Pointer to original image of type Image
                    Returns: Image Pointer
                Description: Sharpens (brigthens the edges) the given image.
                Diagnostics: None as yet
                 References: None
                  Author(s): Srinivas Madiraju
                             Southern Illinois University @ Edwardsville
    ______________________________________________________________________________

    For Image Sharpening, the roberts gradient algorithm is used. This algorithm brightens the edges of the image thus creating a high constrast background/foreground image thus increasing in the sharpness of the image.

    To the function, image_sharp(), the pointer to the original image structure is passed. For each pixel, it's gradient is calculated as the difference in gray levels betweem adjacent pixels. The gradient is added to the original pixel value, thus resulting in a crisp image. Since the gradient assumes large values for prominent edges in the image, and small values in the regions that are fairly smooth, being zero in regions of constant gray levels, the original pixel value is added to get a constrasted sharp image.

    After computing the resultant image, the Image pointer is returned to the calling function.

    ****************************************************************************/


    Mat image_sharp( Mat inputImage)
    {
       int  i, j, cols, rows, bands, col_initial = 0, row_initial = 0, temp1, temp2;

       rows = inputImage.rows;
       cols = inputImage.cols;
       bands = inputImage.channels();
       if (bands == 1)
        {
          for (i = col_initial; i < (cols - col_initial - 1); i++)
             for (j = row_initial; j < (rows - row_initial - 1); j++)
               {
                 temp1 = abs(inputImage.at<uchar>(j,i) - inputImage.at<uchar>(j+1,i));
                 temp2 = abs(inputImage.at<uchar>(j,i) - inputImage.at<uchar>(j,i+1));
                 inputImage.at<uchar>(j,i) += abs(temp1 - temp2);
           }
         }
       else if (bands == 3)
        {
          for (i = col_initial; i < (cols - col_initial - 1); i++)
             for (j = row_initial; j < (rows - row_initial - 1); j++)
               {
                 temp1 = abs(inputImage.at<Vec3b>(j,i)[2] - inputImage.at<Vec3b>(j+1,i+1)[2]);
                 temp2 = abs(inputImage.at<Vec3b>(j+1,i)[2] - inputImage.at<Vec3b>(j,i+1)[2]);
                 inputImage.at<Vec3b>(j,i)[2] += (int) sqrt(temp1*temp1 + temp2*temp2);

                 temp1 = abs(inputImage.at<Vec3b>(j,i)[0] - inputImage.at<Vec3b>(j+1,i+1)[0]);
                 temp2 = abs(inputImage.at<Vec3b>(j+1,i)[0] - inputImage.at<Vec3b>(j,i+1)[0]);
                 inputImage.at<Vec3b>(j,i)[0] += (int) sqrt(temp1*temp1 + temp2*temp2);

                 temp1 = abs(inputImage.at<Vec3b>(j,i)[1] - inputImage.at<Vec3b>(j+1,i+1)[1]);
                 temp2 = abs(inputImage.at<Vec3b>(j+1,i)[1] - inputImage.at<Vec3b>(j,i+1)[1]);
                 inputImage.at<Vec3b>(j,i)[1] += (int) sqrt(temp1*temp1 + temp2*temp2);
           }
        }
       return inputImage;
     }
