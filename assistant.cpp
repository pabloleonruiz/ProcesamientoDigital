#include "assistant.h"

/*! Redondea un número dado con el número de decimales deseado
****************************************/
float Round(float x, int k)
{

    return floor( pow(10,k)*x + 0.5) / pow(10,k) ;

}




/*! Normaliza un vector de datos de una imagen entre dos valores
*****************************************/
void normalizar(float * datos_imagen, int anchura, int altura, float valor_minimo, float valor_maximo)
{
 float min, max;
 long int i1, i2;

 min = datos_imagen[0];
 max = datos_imagen[0];

 for (i1 = 0; i1 < altura; i1++)
    for (i2 = 0; i2 < anchura; i2++)
        {
         if (min > datos_imagen[i1 * anchura + i2])
            min = datos_imagen[i1 * anchura + i2];

         if (max < datos_imagen[i1 * anchura + i2])
            max = datos_imagen[i1 * anchura + i2];
        }

 float factor;
 factor = 256 / (valor_maximo + 1);

 for (i1 = 0; i1 < altura; i1++)
    for (i2 = 0; i2 < anchura; i2++)
        {
         datos_imagen[i1 * anchura + i2] =  ((datos_imagen[i1 * anchura + i2] - min) / (max - min))  * valor_maximo + valor_minimo;

         datos_imagen[i1 * anchura + i2] = factor * ( (float) (int) datos_imagen[i1 * anchura + i2]);
       }

 return;
}




/*!
 Esta función extrae los datos una imagen en color y los almacena en un vector
 de forma que primero estén los valores del plano B, después los del plano G
 y, por último, los del plano R
*/
void extraer_datos_imagen_BGR_separados(Mat &image, float *datos)
{
  int i1;

  int channels;

  long int anchura, altura, numero_puntos;

  // Se declara la variable que va a acceder a los datos de la imagen
  uchar *auxiliar;

  // Se accede a los datos de la imagen
  auxiliar = (uchar *)image.data;

  // Este valor debe ser 3
  channels = image.channels();

  altura = image.rows;
  anchura = image.cols;

  numero_puntos = altura * anchura;

 // Se separan los puntos por planos y se hace la conversión a float
 for (i1 = 0; i1 < channels * numero_puntos; i1++)
    {
       datos[(i1 % channels) * numero_puntos + i1/channels] = (float) auxiliar[i1];
    }

 return;
}

/*!
 Se crea una imagen BGR con los datos pasados como parámetros
*/
void crear_imagen_BGR(Mat *image, int width, int height, float *datos, int canales)
{
    int i1;
    long int numero_puntos;

    // Se reserva memoria para la imagen
    image->create(height,width,CV_8UC3);

    // Se declara la variable que va a acceder a los datos de la imagen
    uchar *auxiliar;

    // Se accede a los datos de la imagen
    auxiliar = (uchar *)image->data;

    numero_puntos = height * width;

   // Se separan los puntos por planos y se hace la conversión a float
   for (i1 = 0; i1 < canales * numero_puntos; i1++)
      {
         auxiliar[i1] = (uchar) datos[(i1 % canales) * numero_puntos + i1/canales];
      }

   return;
}



/*!
 Esta función extrae los datos de una imagen realzada y los almacena en un vector
*/
void extraer_datos_realzada(Mat &image, float *datos)
{
  int i1=0;

  long int anchura, altura, numero_puntos;

  // Se declara la variable que va a acceder a los datos de la imagen
  uchar *auxiliar;

  // Se accede a los datos de la imagen
  auxiliar = (uchar *)image.data;

  altura = image.rows;
  anchura = image.cols;

  numero_puntos = altura * anchura;

 // Se hace la conversión a float
 for (i1 = 0; i1 < numero_puntos; i1++)
    {
       datos[i1] = (float) auxiliar[i1];
    }

 return;
}




/*!
 Se crea una imagen de niveles de gris con los datos pasados como parámetros
*/
void crear_imagen_niveles_gris(Mat *image, int width, int height, float *datos)
{
  int i1, i2;
  uchar *trans;

  // Se reserva memoria para la imagen
  image->create(height,width,CV_8UC1);

  // Se acceden a sus datos
  trans = (uchar *)image->data;

  // Se copian los datos

  for(i1=0; i1<height; i1++)
  for(i2=0; i2<width; i2++)
    trans[i1*width+i2] = (uchar) datos[i1*width+i2];

  return;
}




/*!
    \brief Máximo de dos números

    \param x       Primer número real
    \param y       Segundo número real

    \return  Devuelve el máximo de "x" e "y"
*/
float max(float x, float y)
{

 if (x >= y)
    return x;
 else
    return y;

}




/*!
    \brief Devuelve el índice del punto que dista menos de sus vecinos

    \param v 	Vecindario de puntos
    \param n	Número de puntos
    \param tipo_distancia	Indica el tipo de distancia que se va a utilizar
        Valor 1: euclídea
        Valor 2: Manhattan
        Valor 3: Ajedrez

    \return  Índice del punto que dista menos de sus vecinos
*/
int  vector_mediana(VECINDARIO *v, int n, int tipo_distancia)
{
 int i1, i2;
 //VECINDARIO *v_aux;

 int menor;

 float *distancias;

 distancias = (float *) malloc(n*sizeof(float));
 //v_aux = (VECINDARIO *) malloc(n*sizeof(VECINDARIO));

  /* PARA CADA PIXEL SE CALCULA EL SUMATORIO DE SU DISTANCIA */
  /* A LOS DEMAS PIXELS                                      */
   for(i1 = 0; i1 < n; i1++)
     {
       distancias[i1] = 0.0;

       /* SE CALCULA LA SUMA DE DISTANCIAS ENTRE EL PIXEL i1 Y LOS */
       /* PIXELES 0, 1, 2, ... , i1 - 1.                            */
        for(i2 = 0; i2 < i1; i2++)
          {
           switch(tipo_distancia)
        {
          case 1: /* DISTANCIA EUCLIDEA */
                        distancias[i1] += sqrt(
                                          (v[i1].R - v[i2].R)*(v[i1].R - v[i2].R)
                                         +
                                          (v[i1].G - v[i2].G)*(v[i1].G - v[i2].G)
                                         +
                                          (v[i1].B - v[i2].B)*(v[i1].B - v[i2].B)
                                           );
                break;
             case 2:  /* DISTANCIA DE LA CIUDAD DE LOS BLOQUES */
                      distancias[i1] += fabs(v[i1].R - v[i2].R) +
                                        fabs(v[i1].G - v[i2].G) +
                                        fabs(v[i1].B - v[i2].B);
                break;
         case 3: /* DISTANCIA DE AJEDREZ */
                       distancias[i1] += max(
                        max(fabs(v[i1].R-v[i2].R),
                                                fabs(v[i1].G - v[i2].G)),
                                                    fabs(v[i1].B - v[i2].B)
                        );
            }
                }

          /* SE CALCULA LA SUMA DE DISTANCIAS ENTRE EL PIXEL i1 Y LOS */
          /* PIXELES i1 + 1, i1 + 2, ... , 8                           */
          for(i2 = i1 + 1; i2 < n; i2++)
              {
           switch(tipo_distancia)
          {
               case 1: /* DISTANCIA EUCLIDEA */
                          distancias[i1] += sqrt(
                                             (v[i1].R - v[i2].R)*(v[i1].R - v[i2].R)
                                            +
                                             (v[i1].G - v[i2].G)*(v[i1].G - v[i2].G)
                                            +
                                             (v[i1].B - v[i2].B)*(v[i1].B - v[i2].B)
                                           );
                break;
                     case 2:  /* DISTANCIA DE LA CIUDAD DE LOS BLOQUES */
                          distancias[i1] += fabs(v[i1].R - v[i2].R) +
                                            fabs(v[i1].G - v[i2].G) +
                                            fabs(v[i1].B - v[i2].B);
                break;
             case 3: /* DISTANCIA DE AJEDREZ */
                          distancias[i1] += max(
                        max(fabs(v[i1].R-v[i2].R),
                                                    fabs(v[i1].G - v[i2].G)),
                                                    fabs(v[i1].B - v[i2].B)
                        );
            }
            }
           }


    /* SE DETERMINA EL MENOR */
    menor = 0;
    for (i1 = 1; i1 < n; i1++)
     if (distancias[menor] > distancias[i1]) menor = i1;


 return menor;

}




/*!
    \brief Ordena los puntos de un vecindario utilizando las distancias agredadas al resto de puntos del vecindario.

    \param v 	Vecindario de puntos
    \param n	Número de puntos
    \param tipo_distancia	Indica el tipo de distancia que se va a utilizar
        Valor 1: euclídea
        Valor 2: Manhattan
        Valor 3: Ajedrez

*/
void ordenamiento_distancias_agregadas(VECINDARIO *v, int n, int tipo_distancia)
{
 int i1, i2;
 VECINDARIO *v_aux;

 int *orden;

 float *distancias;

 distancias = (float *) malloc(n*sizeof(float));
 orden = (int *) malloc(n*sizeof(int));
 v_aux = (VECINDARIO *) malloc(n*sizeof(VECINDARIO));

  /* PARA CADA PIXEL SE CALCULA EL SUMATORIO DE SU DISTANCIA */
  /* A LOS DEMAS PIXELS                                      */
   for(i1 = 0; i1 < n; i1++)
     {
       distancias[i1] = 0.0;
       orden[i1] = i1;

       /* SE CALCULA LA SUMA DE DISTANCIAS ENTRE EL PIXEL i1 Y LOS */
       /* PIXELES 0, 1, 2, ... , i1 - 1.                            */
        for(i2 = 0; i2 < i1; i2++)
          {
           switch(tipo_distancia)
        {
          case 1: /* DISTANCIA EUCLIDEA */
                        distancias[i1] += sqrt(
                                          (v[i1].R - v[i2].R)*(v[i1].R - v[i2].R)
                                         +
                                          (v[i1].G - v[i2].G)*(v[i1].G - v[i2].G)
                                         +
                                          (v[i1].B - v[i2].B)*(v[i1].B - v[i2].B)
                                           );
                break;
             case 2:  /* DISTANCIA DE LA CIUDAD DE LOS BLOQUES */
                      distancias[i1] += fabs(v[i1].R - v[i2].R) +
                                     fabs(v[i1].G - v[i2].G) +
                                     fabs(v[i1].B - v[i2].B);
                break;
         case 3: /* DISTANCIA DE AJEDREZ */
                       distancias[i1] += max(
                        max(fabs(v[i1].R-v[i2].R),
                                                fabs(v[i1].G - v[i2].G)),
                                                    fabs(v[i1].B - v[i2].B)
                        );
            }
                }

          /* SE CALCULA LA SUMA DE DISTANCIAS ENTRE EL PIXEL i1 Y LOS */
          /* PIXELES i1 + 1, i1 + 2, ... , 8                           */
          for(i2 = i1 + 1; i2 < n; i2++)
              {
           switch(tipo_distancia)
          {
               case 1: /* DISTANCIA EUCLIDEA */
                          distancias[i1] += sqrt(
                                             (v[i1].R - v[i2].R)*(v[i1].R - v[i2].R)
                                            +
                                             (v[i1].G - v[i2].G)*(v[i1].G - v[i2].G)
                                            +
                                             (v[i1].B - v[i2].B)*(v[i1].B - v[i2].B)
                                           );
                break;
                     case 2:  /* DISTANCIA DE LA CIUDAD DE LOS BLOQUES */
                          distancias[i1] += fabs(v[i1].R - v[i2].R) +
                                            fabs(v[i1].G - v[i2].G) +
                                            fabs(v[i1].B - v[i2].B);
                break;
             case 3: /* DISTANCIA DE AJEDREZ */
                          distancias[i1] += max(
                        max(fabs(v[i1].R-v[i2].R),
                                                    fabs(v[i1].G - v[i2].G)),
                                                    fabs(v[i1].B - v[i2].B)
                        );
            }
            }
           }


    if (ordenacion_shell(distancias,orden,n) == FALSE)
     {
       //printf("\n Error al ordenar el vector de distancias ");
       return;
     }


    /* SE HACE UNA COPIA PARA PODER REODENARLOS CORRECTAMENTE */
    for (i1 = 0; i1 < n; i1++)
    {
     v_aux[i1].R = v[i1].R;
     v_aux[i1].G = v[i1].G;
     v_aux[i1].B = v[i1].B;
    }

    for (i1 = 0; i1 < n; i1++)
    {
     v[i1].R = v_aux[orden[i1]].R;
     v[i1].G = v_aux[orden[i1]].G;
     v[i1].B = v_aux[orden[i1]].B;
    }

}




/*! ***********************************************************
*
*  Nombre de la rutina: ordenacion_shell - Ordena los elementos de un vector
*                       en orden creciente y aplicando el algoritmo de orde-
*                       nacion Shell.
*
*       Objetivo: El objetivo de esta funcion es ordenar un vector por orden
*                 creciente de valores. Para ello se aplica el algoritmo Shell
*                 para la ordenacion de datos. Este algoritmo se basa en orde-
*                 nar los datos comparando aquellos entre los cuales haya una
*                 distancia  de posiciones  determinada. Tras ordenar todos
*                 los datos para esa distancia, se pasa a otra ordenacion con
*                 una distancia menor. Todo el proceso se repite hasta llegar
*                 a una distancia igual a 1, momento en el cual cada dato sera
*                 comparado con el adyacente. Para comprender el metodo de una
*                 forma mas clara, vease el siguiente ejemplo:
*
*                 Supongamos los siguientes datos:
*
*                 6     4     1     3     2     5
*
*                 Si se empieza a comparar con una distancia igual a 3, se pro-
*                 ducen los siguientes intercambios:
*
*                 3     4     1     6     2     5
*                 |_________________|
*
*                 3     2     1     6     4     5
*                       |_________________|
*
*                 Al intercambiar todos los datos posibles, se pasa a una distan-
*                 cia igual a 2:
*
*                 1     2     3     6     4     5
*                 |___________|
*
*                 1     2     3     5     4     6
*                                   |___________|
*
*                Ahora se pasa a una distancia igual a 1:
*
*                 1     2     3     4     5     6
*                                   |_____|
*
*
*       Argumentos de entrada:
*
*                  dimension: Numero de elementos del vector que se pretende
*                             ordenar.
*
*       Argumentos de entrada/salida:
*
*                  distancias: Vector que contiene los datos que se pretenden
*                              ordenar. Al final de la funcion, el vector con-
*                              tendra los datos ordenados en orden creciente.
*
*                  orden: Vector que contiene el orden inicial de los elementos
*                         del vector distancias. Al final de la funcion, almace-
*                         nara el orden obtenido tras aplicar el algoritmo Shell.
*                         El indice del vector hace referencia al orden de los
*                         elementos del vector distancias, mientras que el ele-
*                         mento indica la posicion de los elementos del vector
*                         distancias antes de producirse la ordenacion.
*                         Por ejemplo, considerese el caso siguiente:
*
*                         distancias[0] = 2    orden[0] = 0
*                         distancias[1] = 1    orden[1] = 1
*                         distancias[2] = 5    orden[2] = 2
*                         distancias[3] = 3    orden[3] = 3
*
*                         Tras aplicar el algoritmo Shell se obtiene:
*
*                         distancias[0] = 1    orden[0] = 1
*                         distancias[1] = 2    orden[1] = 0
*                         distancias[2] = 3    orden[2] = 3
*                         distancias[3] = 5    orden[3] = 2
*
*                         Como puede verse, por ejemplo, el valor 2 del vector
*                         distancias era el primero, por lo que orden[0] = 0.
*                         Sin embargo, tras ordenar el vector distancias, el
*                         valor 2 pasa a ser el segundo, por lo que ahora
*                         orden[0] = 1 (los indices empiezan en 0).
*
*
*
*       Funciones a las que llama:
*
*       Funciones que la llaman:
*
*       + r_ordering_central.
*
*       + r_ordering_mutuas.
*
*       Se devuelve: TRUE (1) si hay exito, FALSE (0) en caso contrario.
*
******************************************************/
int ordenacion_shell(float *distancias,
                     int* orden,
                     int dimension)
{
 /* VARIABLE AUXILIAR PARA EL INTERCAMBIO DE VALORES */
 int aux_i;

/* INDICA LA DISTANCIA ENTRE LOS ELEMENTOS COMPARADOS */
 int salto;

/* INDICADOR AUXILIAR PARA DETERMINAR SI HA HABIDO INTERCAMBIO */
 int sennal;

/* VARIABLE AUXILIAR PARA RECORRER EL VECTOR */
 int i;

 /* VARIABLE AUXILIAR PARA EL INTERCAMBIO DE VALORES */
 float aux_f;

 if (distancias == NULL)
    {
     //printf("Ordenacion_shell: el vector de distancias es NULL.");
     return(FALSE);
    }

  if (orden == NULL)
    {
     //printf("Ordenacion_shell: el vector de ordenacion es NULL.");
     return(FALSE);
    }

 if (dimension <= 3)
    {
     //printf("Ordenacion_shell: la dimension de los vectores debe ser al menos 4.");
     return(FALSE);
    }

  /* DISTANCIA DE COMPARACION INICIAL

    SE ESCOGE ESTA DISTANCIA
    YA QUE LAS FUNCIONES QUE LLAMAN A ESTA FUNCION,
    r_ordering_central Y r_ordering_mutuas,
    PASAN VECTORES DE 8 Y 9 ELEMENTOS,
    PARA LOS CUALES ES  ÓPTIMO TOMAR UN VALOR DE
    salto = 3
*/

 salto = 3;

 for(;;)
    {
     for(;;)
        {
    /* NO HA HABIDO INTERCAMBIO DE ELEMENTOS */
         sennal = 0;

    /* NOS SITUAMOS EN EL PRIMER ELEMENTO DEL VECTOR */
         i = 0;
         for(;;)
            {
             /* SE COMPRUEBA SI LOS 2 ELEMENTOS ESTAN DESORDENADOS */
             if ( distancias[i] > distancias[i + salto])
                 {
                 /* SE INTERCAMBIAN LOS ELEMENTOS */
                 aux_f = distancias[i];
                 aux_i = orden[i];
                 distancias[i] = distancias[i + salto];
                 orden[i] = orden[i + salto];
                 distancias[i + salto] = aux_f;
                 orden[i + salto] = aux_i;
                 sennal = 1; /* INTERCAMBIO DE ELEMENTOS */
                }

             /* ESTA CONDICION COMPRUEBA SI HA TERMINADO EL RECORRIDO
                DEL VECTOR PARA EL VALOR DE salto ACTUAL             */
             if ( (i + salto) == dimension - 1) break;

        /* PASAMOS A COMPARAR EL SIGUIENTE ELEMENTO DEL VECTOR */
             i++;
             }

         /* SI sennal = 0, ENTONCES SE DISMINUYE EL VALOR DE LA DISTANCIA
            DE COMPARACION ENTRE ELEMENTOS, LA CUAL VIENE DADA POR salto */
         if (!sennal) break;
        }
     /* SI LA ULTIMA DISTANCIA DE COMPARACION FUE 1 SE TERMINA LA ORDENACION */
     if(salto == 1) break;

     /* SE PASA A LA SIGUIENTE DISTANCIA DE COMPARACION */
     salto = (int) ((salto - 1) / 2);
    }

 return(TRUE);
}




/*!
 * \brief Método de Quicksort
 */
void quicksort (float  *p, long int izquierda, long int derecha)
{
 long int i, j;
 float mitad;
 float auxiliar;

 i = izquierda;
 j = derecha;
 mitad = p[(i+j) / 2];

 do {
     while (p[i] > mitad)   i++;
     while (p[j] < mitad)   j--;
     if (i==j)
           {
             i++;
             j--;
           }
       else if (i<j)
                 {
          auxiliar = p[i];
          p[i] = p[j];
          p[j] = auxiliar;
                  i++;
                  j--;
                 }
    }while (i<=j);

   if (izquierda<j) quicksort (p,izquierda,j);
   if (i<derecha) quicksort (p,i,derecha);

 return;
}



