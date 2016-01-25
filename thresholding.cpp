#include "thresholding.h"



/*!
Esta función umbraliza una imagen realzada de manera manual
*/
void Manual (float *datos, float *resultados, long int anchura, long int altura, float umbral)
{
    long int tam_plano = anchura * altura;
    int i1 = 0;
     float *datos_aux;

    // Se reserva memoria para "datos_aux", que va a almacenar una copia de "datos"
    datos_aux = (float *) malloc(anchura * altura * sizeof (float));

    //Se copia "datos" en "datos_aux"
    for(i1 = 0; i1 < tam_plano; i1++)
        datos_aux[i1]=datos[i1];

    //Se normaliza la imagen de entrada a valores entre 0 y 100
    normalizar(datos_aux, anchura, altura, 0.00, 100.00);

    //Se procede a umbralizar a partir del umbral dado
    for(i1 = 0; i1 < tam_plano; i1++)
    {
        if (datos_aux[i1] <= umbral)
            resultados[i1] = 0;
        else
            resultados[i1] = 255;
    }

}




/*!
Esta función umbraliza una imagen realzada de manera porcentual
*/
void Porcentual (float *datos, float *resultados, long int anchura, long int altura, float porc)
{
    float *datos_aux;
    long int tam_plano = anchura * altura;
    int i1 = 0;
    float total_corte, umbral;

    // Se reserva memoria para "datos_aux", que va a almacenar una copia de "datos"
    datos_aux = (float *) malloc(anchura * altura * sizeof (float));

    //Se copia "datos" en "datos_aux"
    for(i1 = 0; i1 < tam_plano; i1++)
        datos_aux[i1]=datos[i1];

    //Se normaliza la imagen de entrada "auxiliar" a valores entre 0 y 100
    normalizar(datos_aux, anchura, altura, 0.00, 100.00);

    //Se utiliza el metodo de Quicksort para obtener el umbral asociado al porcentaje
    quicksort(datos_aux, 0, tam_plano-1);

    total_corte = ((float)tam_plano)*(porc/100);
    umbral = datos_aux[(int)total_corte];

    //Se procede a umbralizar a partir del umbral calculado
    for(i1 = 0; i1 < tam_plano; i1++)
    {
        if (datos[i1] <= umbral)
            resultados[i1] = 0;
        else
            resultados[i1] = 255;
    }
}




/*!
Esta función umbraliza una imagen realzada mediante el método de histéresis
*/
void Histeresis (float *datos, float *resultados, long int anchura, long int altura, float umbral_mayor, float umbral_menor)
{
    //Vector de posiciones relativas de los coeficientes de la máscara
    float POS[9];
    float *datos_aux;

    int i, j, k;
    bool borde;
    long int tam_plano = anchura * altura;
    int i1 = 0;

    //Posición del primer elemento de la fila del pixel que se esté procesando
    long int FILA;
    long int COORDENADAS;

    // Se reserva memoria para "datos_aux", que va a almacenar una copia de "datos"
    datos_aux = (float *) malloc(anchura * altura * sizeof (float));

    //Se copia "datos" en "datos_aux"
    for(i1 = 0; i1 < tam_plano; i1++)
        datos_aux[i1]=datos[i1];

    //Se normaliza la imagen de entrada a valores entre 0 y 100
    normalizar(datos_aux, anchura, altura, 0.00, 100.00);

    /* SE INICIALIZAN A 0 LOS DATOS DE SALIDA */
     for(i1 = 0; i1 < tam_plano; i1++)
         resultados[i1] = 0;

     /* SE REALIZA LA UMBRALIZACION LOCAL */

    /* POSICIONES RELATIVAS RESPECTO AL PUNTO CENTRAL   */

     /*
            ----- Anchura ------
            --------------------
           /   /   /   /   /   / |
           --------------------  |
          /   / 0 / 1 / 2 /   /  A
          --------------------   l
         /   / 7 / 8 / 3 /   /   t
         --------------------    u
        /   / 6 / 5 / 4 /   /    r
        --------------------     a
       /   /   /   /   /   /     |
       --------------------      |

     */

     POS[0] = -anchura - 1;
     POS[1] = -anchura;
     POS[2] = -anchura + 1;
     POS[3] = 1;
     POS[4] = anchura + 1;
     POS[5] = anchura;
     POS[6] = anchura - 1;
     POS[7] = -1;
     POS[8] = 0;


     /* ESTE BUCLE RECORRE DESDE LA 1ª HASTA LA ULTIMA FILA */
     for(i = 0; i < altura; i++)
       {
             /* SE CALCULA LA POSICION DEL PRIMER ELEMENTO DE LA FILA i */
             FILA = i*anchura;

             /* ESTE BUCLE RECORRE DESDE LA 1ª HASTA LA ULTIMA COLUMNA */
             for(j = 0; j < anchura; j++)
               {
                 /* SE CALCULAN LAS COORDENADAS DE (i,j) */
                 COORDENADAS = FILA + j;

                 /* SE COMPRUEBA SI EL PIXEL SUPERA EL UMBRAL MAYOR */
                 if (datos_aux[COORDENADAS] > umbral_mayor)
                          resultados[COORDENADAS]=255;
                 else
                  {
                    /* SE COMPRUEBA SI EL PIXEL SUPERA EL UMBRAL MENOR */
                    if (datos_aux[COORDENADAS]> umbral_menor)
                       /* SE COMPRUEBA SI TIENE ALGUN VECINO QUE SUPERE AL UMBRAL MAYOR */
                       {
                          borde=FALSE;
                          k=0;
                          while((borde==FALSE) && (k<8))
                          {
                                if (datos_aux[COORDENADAS+(int)POS[k]] > umbral_mayor)
                                  borde = TRUE;
                                else
                                  k++;
                                /* SI LO HAY, ENTONCES SE MARCA COMO BORDE */
                                if (borde==TRUE)
                                     resultados[COORDENADAS]=255;
                                else
                                     resultados[COORDENADAS]=0;
                          }
                       }

                   }

               }

         }
}





/*!
Esta función umbraliza una imagen realzada mediante el método de Otsu
*/
float Otsu(float *datos, long int anchura, long int altura)
{
    float *entrada;
    long int tam_plano = anchura * altura; /* Anchura*Altura */
    int i=0, i1, i2=0;
    float threshold;
    int bins = 256;
    int ts;
    float h_mean;
    float h_var=0;
    float P1=0,M1=0,P2=0,M2=0;
    float var_inter_class=0;
    float max_v = 0;
    int max_ts = 0;
    float sum=0;
    float hist[256];

    // Se reserva memoria para "entrada", que va a almacenar una copia de "datos"
    entrada = (float *) malloc(anchura * altura * sizeof (float));

    //Se copia "datos" en "entrada"
    for(i = 0; i < tam_plano; i++)
        entrada[i]=datos[i];

    //Se normaliza la imagen de entrada "auxiliar" a valores entre 0 y 100
    normalizar(entrada, anchura, altura, 0.00, 100.00);

    int min=(int)entrada[0];
    int max=(int)entrada[0];

    //calculo minimo y maximo
    for(i1=0;i1<tam_plano;i1++)
    {
        if(entrada[i1]<min)min=(int)entrada[i1];
        if(entrada[i1]>max)max=(int)entrada[i1];
    }


    //proporciono la imagen entre 0 y 100
    //entrada_aux=malloc(256*sizeof(double));
    for(i1=0;i1<(tam_plano-1);i1++)
    {
        entrada[i1]=(entrada[i1]-min)*255/max;
    }

    //CREACION HISTOGRAMA
    for(i1=0;i1<bins;i1++)
    {
        hist[i1]=0;
    }

    for(i1=1;i1<(tam_plano-1);i1++)
    {
        i2=(int)entrada[i1];
        hist[i2]=hist[i2]+1;
    }
    //NORMALIZACION
    for(i1=0;i1<bins;i1++)
    {
        hist[i1]/=tam_plano;
        sum+=hist[i1];
    }

    //CALCULO MEDIA
    h_mean=0;
    for(i1=0;i1<bins;i1++)
    {
        h_mean+=(hist[i1]*i1);
    }

    //CALCULO VARIANCIA
    h_var=0;
    for(i1=0;i1<bins;i1++)
    {
        h_var+=((pow((hist[i1]-h_mean),2))*hist[i1]);
    }

    //Prueba todos los posibles umbrales
    max_ts=0;
    max_v=0;
    for (ts=0; ts<bins-1; ts++)
    {
        //valor normalizado de l'histograma
        P1+= hist[ts];	//(probabilidad que el pixel sea a la izquierda)
        P2=(1-P1);	//(probabilidad que el pixel sea a la derecha)

        //media izquierda
        M1=0;
        for(i1=0;i1<ts;i1++)
        {
            M1+=hist[i1]*i1;
        }
        M1/=P1;

        //media derecha
        M2=0;
        for(i1=ts;i1<bins;i1++)
        {
            M2+=hist[i1]*i1;
        }
        M2/=P2;

        //varianza entre clases
        var_inter_class = P1  *  P2 * (pow((M1-M2), 2));

        if (var_inter_class>max_v)
        {
            max_v=var_inter_class;
            max_ts=(int)ts;
        }

    }

    threshold=(float)max_ts;//threshold
    return (threshold);
}





/*!
Esta función umbraliza una imagen realzada utilizando el método de Rosin
*/
int Rosin (float *datos, long int anchura, long int altura)
{

    int i1 = 0;
    int i2 = 0;
    int max = 0; //Coordenada 'x' con mayor densidad
    int punto = 0; //valor x del punto adaptativo
    float distancia = 0, dist_aux = 0;
    float a=0.00, b=0.00, c=0.00;//Parámetros recta de Rosin
    int umbral_x = 0;//Punto seleccionado

    int aux = 0;
    long int mayor = 0; //Variable que almacenará el valor de brillo con mayor densidad
    long int tam_plano = anchura * altura;
    long int v[101]; //Variable vector contador número de cada brillo

    //Variable que almacenará una copia de la imagen
    float *resultados;
    resultados = (float *) malloc(anchura * altura * sizeof (float));

    //Inicializo vectores
    for(i2 = 0; i2 < 101; i2++)
    {
        v[i2] = 0;
    }

    //Se hace una copia de la imagen a tratar
    for(i1 = 0; i1 < tam_plano; i1++)
    {
        resultados[i1]=datos[i1];
    }

    //Se normaliza la imagen de entrada a valores entre 0 y 100
    normalizar(resultados, anchura, altura, 0.0, 100.0);

    //Se calcula el numero de puntos con igual brillo
    for(i1 = 0; i1 < tam_plano; i1++)
    {
        //Se pasa de rango 0-255 a rango 0-100
        aux = (int) round(resultados[i1]*100/255);
        for(i2 = 0; i2 < 101; i2++)
        {
            if (aux == i2)
            {
                v[i2] = v[i2] + 1;
            }
        }
    }


    //Se determina el valor de brillo con mayor densidad
    for(i2 = 0; i2 < 101; i2++)
    {
        if (v[i2] > mayor)
        {
            mayor = v[i2];
            max = i2;
        }
    }


    //Se halla la coordenada 'x' del punto donde densidad 'y' sea mas cercana a cero
    for(i2 = max; i2 < 101; i2++)
      if (v[i2] > 0)
        {
            punto = i2;
        }


    //Calculamos parámetros de la recta de Rosin
    // Recta entre P1(x1,y1) y P2(x2,y2) =>  r  => ax + by + c = 0
    // siendo  a = y2-y1,  b = x1-x2  y  c = x2y1 - x1y2
    a = v[punto] - v[max];
    b = max - punto;
    c = (punto*v[max]) - (max*v[punto]);


    //Se halla el punto de la zona de interés de la curva de significación
    //con mayor distancia a la recta de Rosin.
    //Para ello recorremos cada punto de la zona de interés
    for(i2 = max; i2 < punto+1; i2++)
    {
        //Calculamos la distancia del punto a la recta de rosin
        dist_aux = abs((a*i2)+(b*v[i2])+c) / sqrt(pow(a,2)+pow(b,2));

        //Comprobamos la distancia y nos vamos quedando con la mayor.
        //El valor de x para la mayor distancia es el umbral elegido
        if (dist_aux > distancia)
        {
         distancia = dist_aux;
         umbral_x = i2;
        }

    }

    //Se devuelve la coordenada 'x' del punto hallado, siendo éste el valor umbral
    return umbral_x;
}

/*!
Esta función normaliza una imagen realzada a 1 tanto en el valor
de brillo como en la densidad de dicho brillo
*/
void Normalizar1_1 (float *datos, float *f, long int anchura, long int altura)
{
    long int tam_plano = anchura * altura;
    int i1 = 0, i2 = 0;
    int aux = 0;

    //Variable que almacenará el valor de brillo con mayor densidad
    long int mayor = 0;

   //Variable vector contador
    long int v[101];

    //Variable que almacenará una copia de la imagen
    float *resultados;
    resultados = (float *) malloc(anchura * altura * sizeof (float));

    //Inicializo vector contador a cero (almacenará el número de puntos de cada brillo)
    for(i2 = 0; i2 < 101; i2++)
    {
        v[i2] = 0;
    }

    //Se hace una copia de la imagen a tratar
    for(i1 = 0; i1 < tam_plano; i1++)
    {
        resultados[i1]=datos[i1];
    }

    //Se normaliza la imagen de entrada a valores entre 0 y 100
    normalizar(resultados, anchura, altura, 0.0, 100.0);

    //Se calcula el numero de puntos con igual brillo
    for(i1 = 0; i1 < tam_plano; i1++)
    {
        //Se pasa de rango 0-255 a rango 0-100
        aux = (int) round(resultados[i1]*100.0/255.0);
        for(i2 = 0; i2 < 101; i2++)
        {
            if (aux == i2)
            {
                v[i2] = v[i2] + 1;
            }
        }
    }

    //Se determina el valor de brillo con mayor densidad
    for(i2 = 0; i2 < 101; i2++)
    {
        if (v[i2] > mayor)
        {
            mayor = v[i2];
        }
    }

    //Se calcula la densidad normalizada de cada valor de brillo
    for(i2 = 0; i2 < 101; i2++)
    {
        f[i2] = Round((float)v[i2]/(float)mayor,2);
    }

}




/*!
Esta función umbraliza una imagen realzada utilizando el método de proximidad
al punto (max/N,0.0)
*/
float* Proximidad (float *datos, long int anchura, long int altura)
{
    int i2 = 0;
    float f[101]; //Vector para almacenar las densidades
    float aux = 0;
    float punto = 0; //Coordenada 'x' con mayor densidad
    float distancia = 3, dist_aux = 0;
    float umbral_x = 0; //Punto seleccionado

    float *result;
    result = (float *) malloc(2*sizeof(float));


    //Se normaliza la imagen a 1
    Normalizar1_1 (datos, f, anchura, altura);

    //Se calcula el punto 'x' de brillo con mayor densidad 'y'
    for(i2 = 0; i2 < 101; i2++)
    {
        if (f[i2] == 1)
        {
            punto = (float)i2;
        }
    }

    //Se halla el punto de la curva de significación más proximo
    //al punto (x,0.0), siendo 'x' el punto de máxima densidad
    for(i2 = punto; i2 < 101; i2++)
    {
        aux = (float)(i2)/100.00;
        dist_aux = sqrt(pow(aux-(punto/100.00),2)+pow(f[i2],2));
        if ( dist_aux < distancia)
        {
           distancia = dist_aux;
           umbral_x = aux;
        }
    }


    result[0]=umbral_x;//Coordenada 'x' del punto hallado, siendo éste el valor umbral
    result[1]=punto;//Punto 'x' de brillo con mayor densidad 'y'

    //Se devuelven los resultados
    return result;
}




/*!
Esta función umbraliza una imagen realzada utilizando el método del punto
más distante respecto del punto (1.0,1.0)
*/
float Distante (float *datos, long int anchura, long int altura)
{
    int i2 = 0;
    float f[101]; //Vector para almacenar las densidades
    float aux = 0;
    float punto = 0; //Coordenada 'x' con mayor densidad
    float distancia = 0, dist_aux = 0;
    float umbral_x = 0; //Punto seleccionado

    //Se normaliza la imagen a 1
    Normalizar1_1 (datos, f, anchura, altura);

    //Se calcula el punto 'x' de brillo con mayor densidad 'y'
    for(i2 = 0; i2 < 101; i2++)
    {
        if (f[i2] == 1)
        {
            punto = (float)i2;
        }
    }

    //Se halla el punto de la curva de significación más distante al punto (1.0,1.0)
    for(i2 = punto; i2 < 101; i2++)
    {
        aux = (float)(i2)/100.00;
        dist_aux = sqrt(pow(aux-1.00,2)+pow(f[i2]-1.00,2));
        if ( dist_aux > distancia)
        {
           distancia = dist_aux;
           umbral_x = aux;
        }
    }

    //Se devuelve la coordenada 'y' del punto hallado, siendo éste el valor umbral
    return umbral_x;
}




/*!
Esta función umbraliza una imagen realzada utilizando el método del punto
de menor distancia bajo la diagonal
*/
float Diagonal (float *datos, long int anchura, long int altura)
{
    int i2 = 0;
    float distancia = 3, aux_dist = 0;
    float f[101]; //Vector para almacenar las densidades
    float aux = 0;
    float umbral_x = 0; //Punto seleccionado

    //Se normaliza la imagen a 1
    Normalizar1_1 (datos, f, anchura, altura);

    //Se halla el punto de la curva de significación de menor distancia bajo la diagonal
    for(i2 = 0; i2 < 101; i2++)
    {
        aux = Round((float)(i2)/100.00, 2);
        if (Round(f[i2],2) < aux)
        {
          aux_dist = sqrt(pow(aux-aux,2)+pow(f[i2]-aux,2));
          if (aux_dist < distancia)
           {
            distancia = aux_dist;
            umbral_x = aux;
           }
        }
    }

    //Se devuelve la coordenada 'y' del punto hallado, siendo éste el valor umbral
    return umbral_x;
}




/*!
Esta función umbraliza una imagen realzada utilizando el método adaptativo
*/
float* Adaptativo (float *datos, long int anchura, long int altura)
{
    int i1 = 0, i2 = 0;
    float punto = 0; //valor x del punto adaptativo
    float distancia = 0, dist_aux = 0;
    int max = 0; //Coordenada 'x' con mayor densidad
    float f[101]; //Vector para almacenar las densidades
    float aux = 0;
    float umbral_x = 0; //Punto seleccionado

    float *result;
    result = (float *) malloc(2*sizeof(float));

    //Se normaliza la imagen a 1
    Normalizar1_1 (datos, f, anchura, altura);

    //Se calcula el punto 'x' de brillo con mayor densidad 'y'
    for(i2 = 0; i2 < 101; i2++)
    {
        if (f[i2] == 1)
        {
            max = i2;
        }
    }

    //Se halla la coordenada x del punto adaptativo (x,1.0)
    i1 = max;
    while (Round(f[i1],2) > 0.00)
        {
            punto = (float)(i1+1);
            i1++;
        }


    //Se halla el punto de la curva de significación con mayor distancia al
    //punto adaptativo (x,1.0)
    for(i2 = max; i2 < punto; i2++)
    {
        aux = (float)(i2)/100.00;
        dist_aux = sqrt(pow(aux-(punto/100.00),2)+pow(f[i2]-1.00,2));
        if ( dist_aux > distancia)
        {
           distancia = dist_aux;
           umbral_x = aux;
        }

    }

    result[0]=umbral_x;//Coordenada 'x' del punto hallado, siendo éste el valor umbral
    result[1]=punto;//Punto 'x' del punto adaptativo (x, 1.0)

    //Se devuelven los resultados
    return result;
}




/*!
Esta función umbraliza una imagen realzada utilizando el método semi-adaptativo
*/
float* Semi_adaptativo (float *datos, long int anchura, long int altura)
{
    int i1 = 0, i2 = 0;
    float punto = 0, punto_semi = 0; //valor x del punto adaptativo
    float distancia = 0, dist_aux = 0;
    float max = 0; //Coordenada 'x' con mayor densidad
    float f[101]; //Vector para almacenar las densidades
    float aux = 0;
    float umbral_x = 0; //Punto seleccionado

    float *result;
    result = (float *) malloc(3*sizeof(float));

    //Se normaliza la imagen a 1
    Normalizar1_1 (datos, f, anchura, altura);

    //Se calcula el punto 'x' de brillo con mayor densidad 'y'
    for(i2 = 0; i2 < 101; i2++)
    {
        if (f[i2] == 1)
        {
            max = (float)i2/100;
        }
    }

    //Se halla la coordenada x del punto adaptativo (x,1.0)
    i1 = max*100;
    while (Round(f[i1],2) > 0.00)
        {
            punto = ((float)i1+1)/100;
            i1++;
        }

    //Se halla la coordenada x del punto semi-adaptativo (x,1.0)
    punto_semi = (punto+1)/2;

    //Se halla el punto de la curva de significación con mayor distancia al
    //punto semi-adaptativo (x,1.0)
    for(i2 = max*100; i2 < punto*100; i2++)
    {
        aux = (float)i2/100;
        dist_aux = sqrt(pow(aux-punto_semi,2)+pow(f[i2]-1,2));
        if ( dist_aux > distancia)
        {
           distancia = dist_aux;
           umbral_x = aux;
        }

    }

    result[0]=umbral_x;//Coordenada 'x' del punto hallado, siendo éste el valor umbral
    result[1]=punto*100.00;//Punto 'x' del punto adaptativo (x, 0.0)
    result[2]=punto_semi*100.00;//Coordenada x del punto semi-adaptativo (x,1.0)

    //Se devuelven los resultados
    return result;
}




/*!
Esta función umbraliza una imagen realzada utilizando el método de Rosin normalizado
*/
float Rosin_normalizado (float *datos, long int anchura, long int altura)
{

    int i1 = 0;
    int i2 = 0;
    float max = 0; //Coordenada 'x' con mayor densidad
    float punto = 0; //valor 'x' del punto con primera 'y' igual a cero
    float distancia = 0, dist_aux = 0;
    float a=0.00, b=0.00, c=0.00;//Parámetros recta de rosin
    float f[101]; //Vector para almacenar las densidades
    float aux = 0;
    float umbral_x = 0; //Punto seleccionado

    //Se normaliza la imagen a 1
    Normalizar1_1 (datos, f, anchura, altura);

    //Se calcula el punto 'x' de brillo con mayor densidad 'y'
    for(i2 = 0; i2 < 101; i2++)
    {
        if (f[i2] == 1)
        {
            max = (float)(i2)/100.00;
        }
    }

    //Se halla la coordenada 'x' del punto donde densidad 'y' sea cero
    i1 = (int)(max*100.00);
    while (Round(f[i1],2) > 0.00)
        {
            punto = (float)(i1+1)/100.00;
            i1++;
        }


    //Calculamos parámetros de la recta de Rosin
    // Recta entre P1(x1,y1) y P2(x2,y2) =>  r  => ax + by + c = 0
    // siendo  a = y2-y1,  b = x1-x2  y  c = x2y1 - x1y2
    a = 0.00 - 1.00;
    b = max - punto;
    c = (punto*1.00) - (max*0.00);

    //Se halla el punto de la zona de interés de la curva de significación
    //con mayor distancia a la recta de Rosin.
    //Para ello recorremos cada punto de la zona de interés
    for(i2 = max*100; i2 < punto*100; i2++)
    {
        aux = (float)(i2)/100.00;

        //Calculamos la distancia del punto a la recta de rosin
        dist_aux = abs((a*aux)+(b*f[i2])+c) / sqrt(pow(a,2)+pow(b,2));

        //Comprobamos la distancia y nos vamos quedando con la mayor.
        //El valor de x para la mayor distancia es el umbral elegido
        if (dist_aux > distancia)
        {
         distancia = dist_aux;
         umbral_x = aux;
        }
    }

    //Se devuelve la coordenada 'y' del punto hallado, siendo éste el valor umbral
    return umbral_x;
}





//////////////////////////////////////////////////
//////       ACUMULATIVOS E INVERSOS         /////
//////////////////////////////////////////////////

/*!
Esta función umbraliza una imagen realzada utilizando el método de proximidad
al punto (max/N,0.0)
*/
float* Proximidad_Acumulado_Inverso (float *datos, long int anchura, long int altura)
{
    int i2 = 0;
    float f[101]; //Vector para almacenar las densidades
    float aux = 0;
    float punto = 0; //Coordenada 'x' con mayor densidad
    float distancia = 3, dist_aux = 0;
    float umbral_x = 0; //Punto seleccionado

    float *result;
    result = (float *) malloc(2*sizeof(float));

    //Se normaliza la imagen a 1
    Normalizar1_1 (datos, f, anchura, altura);


///////////////////////////////////////////////
  Transformar_Acumulado_Inverso_Normalizado(f);
///////////////////////////////////////////////

    //Se calcula el punto 'x' de brillo con mayor densidad 'y'
    for(i2 = 0; i2 < 101; i2++)
    {
        if (f[i2] == 1)
        {
            punto = (float)i2;
        }
    }

    //Se halla el punto de la curva de significación más proximo
    //al punto (x,0.0), siendo 'x' el punto de máxima densidad
    for(i2 = punto; i2 < 101; i2++)
    {
        aux = (float)(i2)/100.00;
        dist_aux = sqrt(pow(aux-(punto/100.00),2)+pow(f[i2],2));
        if ( dist_aux < distancia)
        {
           distancia = dist_aux;
           umbral_x = aux;
        }
    }


    result[0]=umbral_x;//Coordenada 'x' del punto hallado, siendo éste el valor umbral
    result[1]=punto;//Punto 'x' de brillo con mayor densidad 'y'

    //Se devuelven los resultados
    return result;
}




/*!
Esta función umbraliza una imagen realzada utilizando el método del punto
más distante respecto del punto (1.0,1.0)
*/
float Distante_Acumulado_Inverso (float *datos, long int anchura, long int altura)
{
    int i2 = 0;
    float f[101]; //Vector para almacenar las densidades
    float aux = 0;
     float punto = 0; //Coordenada 'x' con mayor densidad
    float distancia = 0, dist_aux = 0;
    float umbral_x = 0; //Punto seleccionado

    //Se normaliza la imagen a 1
    Normalizar1_1 (datos, f, anchura, altura);


///////////////////////////////////////////////
  Transformar_Acumulado_Inverso_Normalizado(f);
///////////////////////////////////////////////

    //Se calcula el punto 'x' de brillo con mayor densidad 'y'
    for(i2 = 0; i2 < 101; i2++)
    {
        if (f[i2] == 1)
        {
            punto = (float)i2;
        }
    }

    //Se halla el punto de la curva de significación más distante al punto (1.0,1.0)
    for(i2 = punto; i2 < 101; i2++)
    {
        aux = (float)(i2)/100.00;
        dist_aux = sqrt(pow(aux-1.00,2)+pow(f[i2]-1.00,2));
        if ( dist_aux > distancia)
        {
           distancia = dist_aux;
           umbral_x = aux;
        }
    }

    //Se devuelve la coordenada 'y' del punto hallado, siendo éste el valor umbral
    return umbral_x;
}




/*!
Esta función umbraliza una imagen realzada utilizando el método del punto
de menor distancia bajo la diagonal
*/
float Diagonal_Acumulado_Inverso (float *datos, long int anchura, long int altura)
{
    int i2 = 0;
    float distancia = 3, aux_dist = 0;
    float f[101]; //Vector para almacenar las densidades
    float aux = 0;
    float umbral_x = 0; //Punto seleccionado

    //Se normaliza la imagen a 1
    Normalizar1_1 (datos, f, anchura, altura);


//////////////////////////////////////////////
  Transformar_Acumulado_Inverso_Normalizado(f);
//////////////////////////////////////////////


    //Se halla el punto de la curva de significación de menor distancia bajo la diagonal
    for(i2 = 0; i2 < 101; i2++)
    {
        aux = Round((float)(i2)/100.00, 2);
        if (Round(f[i2],2) < aux)
        {
          aux_dist = sqrt(pow(aux-aux,2)+pow(f[i2]-aux,2));
          if (aux_dist < distancia)
           {
            distancia = aux_dist;
            umbral_x = aux;
           }
        }
    }

    //Se devuelve la coordenada 'y' del punto hallado, siendo éste el valor umbral
    return umbral_x;
}




/*!
Esta función umbraliza una imagen realzada utilizando el método adaptativo acumulado inverso
*/
float* Adaptativo_Acumulado_Inverso (float *datos, long int anchura, long int altura)
{
    int i1 = 0, i2 = 0;
    //valor x del punto adaptativo
    int punto = 0;
    float distancia = 0, dist_aux = 0;

    //Coordenada 'x' con mayor densidad
    int max = 0;

    //Vector para almacenar las densidades
    float f[101];

    float aux = 0;

    //Punto seleccionado
    float umbral_x = 0;

    //Resultados devueltos
    float *result;
    result = (float *) malloc(2*sizeof(float));

    //Se normaliza la imagen a 1
    Normalizar1_1 (datos, f, anchura, altura);


///////////////////////////////////////////////
  Transformar_Acumulado_Inverso_Normalizado(f);
///////////////////////////////////////////////


    //Se calcula el punto 'x' de brillo con mayor densidad 'y'
    for(i2 = 0; i2 < 101; i2++)
    {
        if (f[i2] == 1)
        {
            max = i2;
        }
    }

    //Se halla la coordenada x del punto adaptativo (x,1.0)
    i1 = max;
    while (Round(f[i1],2) > 0.00)
        {
            punto = i1+1;
            i1++;
        }


    //Se halla el punto de la curva de significación con mayor distancia al
    //punto adaptativo (x,1.0)
    for(i2 = max; i2 < punto; i2++)
    {
        aux = (float)(i2)/100.00;
        dist_aux = sqrt(pow(aux-((float)punto/100.00),2)+pow(f[i2]-1.00,2));
        if ( dist_aux > distancia)
        {
           distancia = dist_aux;
           umbral_x = aux;
        }

    }


    result[0]=umbral_x;//Coordenada 'x' del punto hallado, siendo éste el valor umbral
    result[1]=(float)punto;//Punto 'x' del punto adaptativo (x, 1.0)

    //Se devuelven los resultados
    return result;
}




/*!
Esta función umbraliza una imagen realzada utilizando el método semi-adaptativo
*/
float* Semi_adaptativo_Acumulado_Inverso (float *datos, long int anchura, long int altura)
{
    int i1 = 0, i2 = 0;
    float punto = 0, punto_semi = 0; //valor x del punto adaptativo
    float distancia = 0, dist_aux = 0;
    float max = 0; //Coordenada 'x' con mayor densidad
    float f[101]; //Vector para almacenar las densidades
    float aux = 0;
    float umbral_x = 0; //Punto seleccionado

    float *result;
    result = (float *) malloc(3*sizeof(float));


    //Se normaliza la imagen a 1
    Normalizar1_1 (datos, f, anchura, altura);



///////////////////////////////////////////////
  Transformar_Acumulado_Inverso_Normalizado(f);
///////////////////////////////////////////////

    //Se calcula el punto 'x' de brillo con mayor densidad 'y'
    for(i2 = 0; i2 < 101; i2++)
    {
        if (f[i2] == 1)
        {
            max = (float)i2/100.00;
        }
    }

    //Se halla la coordenada x del punto adaptativo (x,1.0)
    i1 = (int)(max*100.00);
    while (Round(f[i1],2) > 0.00)
        {
            punto = (float)(i1+1)/100.00;
            i1++;
        }

    //Se halla la coordenada x del punto semi-adaptativo (x,1.0)
    punto_semi = (punto+1)/2;

    //Se halla el punto de la curva de significación con mayor distancia al
    //punto semi-adaptativo (x,1.0)
    for(i2 = max*100; i2 < punto*100; i2++)
    {
        aux = (float)(i2)/100.00;
        dist_aux = sqrt(pow(aux-punto_semi,2)+pow(f[i2]-1.00,2));
        if ( dist_aux > distancia)
        {
           distancia = dist_aux;
           umbral_x = aux;
        }

    }

    result[0]=umbral_x;//Coordenada 'x' del punto hallado, siendo éste el valor umbral
    result[1]=punto*100.00;//Punto 'x' del punto adaptativo (x, 0.0)
    result[2]=punto_semi*100.00;//Coordenada x del punto semi-adaptativo (x,1.0)

    //Se devuelven los resultados
    return result;
}




/*!
Esta función umbraliza una imagen realzada utilizando el método de Rosin normalizado
*/
float Rosin_normalizado_Acumulado_Inverso (float *datos, long int anchura, long int altura)
{

    int i1 = 0;
    int i2 = 0;
    float max = 0; //Coordenada 'x' con mayor densidad
    float punto = 0; //valor 'x' del punto con primera 'y' igual a cero
    float distancia = 0, dist_aux = 0;
    float a=0.00, b=0.00, c=0.00;//Parámetros recta de rosin
    float f[101]; //Vector para almacenar las densidades
    float aux = 0;
    float umbral_x = 0; //Punto seleccionado

    //Se normaliza la imagen a 1
    Normalizar1_1 (datos, f, anchura, altura);


///////////////////////////////////////////////
  Transformar_Acumulado_Inverso_Normalizado(f);
///////////////////////////////////////////////

    //Se calcula el punto 'x' de brillo con mayor densidad 'y'
    for(i2 = 0; i2 < 101; i2++)
    {
        if (f[i2] == 1)
        {
            max = (float)(i2)/100.00;
        }
    }

    //Se halla la coordenada 'x' del punto donde densidad 'y' sea cero
    i1 = (int)(max*100.00);
    while (Round(f[i1],2) > 0.00)
        {
            punto = (float)(i1+1)/100.00;
            i1++;
        }


    //Calculamos parámetros de la recta de Rosin
    // Recta entre P1(x1,y1) y P2(x2,y2) =>  r  => ax + by + c = 0
    // siendo  a = y2-y1,  b = x1-x2  y  c = x2y1 - x1y2
    a = 0.00 - 1.00;
    b = max - punto;
    c = (punto*1.00) - (max*0.00);

    //Se halla el punto de la zona de interés de la curva de significación
    //con mayor distancia a la recta de Rosin.
    //Para ello recorremos cada punto de la zona de interés
    for(i2 = max*100; i2 < punto*100; i2++)
    {
        aux = (float)(i2)/100.00;

        //Calculamos la distancia del punto a la recta de rosin
        dist_aux = abs((a*aux)+(b*f[i2])+c) / sqrt(pow(a,2)+pow(b,2));

        //Comprobamos la distancia y nos vamos quedando con la mayor.
        //El valor de x para la mayor distancia es el umbral elegido
        if (dist_aux > distancia)
        {
         distancia = dist_aux;
         umbral_x = aux;
        }
    }

    //Se devuelve la coordenada 'y' del punto hallado, siendo éste el valor umbral
    return umbral_x;
}




///////////////////////////////////////////////

    /* Se calcula el valor acumulativo inverso
         F[i] = Sumatorio f[i] donde i varía desde 100 hasta i
        Después se copia F[i] en f(i)
        y, por úlitmo, se normaliza f(i) entre 0 y 1.0
    */
///////////////////////////////////////////////

void Transformar_Acumulado_Inverso_Normalizado(float *f)
{
 int i1;
 float max;

  //Vector auxiliar para almacenar las densidades acumuladas
  float F[101];

   // Se ponen todos los valores a cero.
    for(i1=100; i1 >= 0; i1--)
           F[i1] = 0.0;

    F[100] = f[100];
    for(i1=99; i1 >= 0; i1--)
         {
           F[i1] = F[i1+1] + f[i1];
         }

   // Se copia F en f
    for(i1=100; i1 >= 0; i1--)
           f[i1] = F[i1];

   // Se normaliza f
    max = 0.0;
    for(i1=0; i1 <= 100; i1++)
    {
     if (max < f[i1])
               max = f[i1];
    }

   for(i1=0; i1 <= 100; i1++)
    f[i1] = f[i1] / max;

}

