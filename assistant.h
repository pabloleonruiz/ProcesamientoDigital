#ifndef ASSISTANT_H
#define ASSISTANT_H

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <string.h>


// Para usar malloc
#include "stdlib.h"


using namespace cv;
using namespace std;


struct VECINDARIO{
    float R;
    float G;
    float B;
};




/***************************************/
// Prototipos
/***************************************/

/*!
    \brief Redondea un número dado con el número de decimales deseado

    \param x 	Contiene el número que se va a redondear
    \param k    Número de dígitos decimales que queremos
*/
float Round(float x, int k);




/*!
    \brief Normaliza un vector de datos de una imagen entre dos valores

    \param datos_imagen 	Vector de datos de la imagen que se va a normalizar
    \param altura   Altura de la imagen
    \param anchura  Anchura de la imagen

    \param valor_minimo	Valor mínimo con el que se va a normalizar
    \param valor_maxinmo	Valor máximo con el que se va a normalizar


*/
void normalizar(float * datos_imagen, int anchura, int altura, float valor_minimo, float valor_maximo);




/*!
    \brief Esta función extrae los datos una imagen en color y los almacena como reales de punto flotante en un vector
     de forma que
        - primero estén los valores del plano B,
        - después los del plano G
        - y, por último, los del plano R

    \param imagen Imagen del espacio de color BGR
    \param datos  Vector que va a contener los valores de cada punto
*/
void extraer_datos_imagen_BGR_separados(Mat &image, float *datos);




/*!
    \brief Esta función extrae los datos una imagen realzada y los almacena como reales de punto flotante en un vector

    \param imagen Imagen de entrada
    \param datos  Vector que va a contener los valores de cada punto
*/
void extraer_datos_realzada(Mat &image, float *datos);




/*!
    \brief Crea una imagen de niveles de gris con los datos pasados como parámetros

    \param imagen  Imagen que se va a crear
    \param height  Altura de la imagen
    \param widht   Anchura de la imagen
    \param datos   Vector que contiene los niveles de gris
*/
void crear_imagen_niveles_gris(Mat *image, int width, int height, float *datos);


/*!
    \brief Crea una imagen en color con los datos pasados como parámetros

    \param imagen  Imagen que se va a crear
    \param height  Altura de la imagen
    \param widht   Anchura de la imagen
    \param datos   Vector que contiene los datos de la imagen en color
    \param canales Numero de canales de la imagen
*/
void crear_imagen_BGR(Mat *image, int width, int height, float *datos, int canales);

/*!
    \brief Calcula el valor máximo de dos números reales

    \param x 	Primer número real
    \param y	Segundo número real

    \return		Máximo valor de x e y
*/
float max(float x, float y);


/*************************************/
/* Otros prototipos auxiliares *******/
/*************************************/


// Devuelve el índice del punto que dista menos de sus vecinos
int vector_mediana(VECINDARIO *v, int n, int tipo_distancia);


// Ordena los puntos de un vecindario utilizando las
// distancias agredadas al resto de puntos del vecindario
void ordenamiento_distancias_agregadas(VECINDARIO *v, int n, int tipo_distancia);


// Ordena los elementos de un vector en orden creciente
// y aplicando el algoritmo de ordenación Shell
int ordenacion_shell(float *distancias, int* orden, int dimension);


//Método de Quicksort
void quicksort (float  *p, long int izquierda, long int derecha);


/*************************************/

#endif
