#include "edge.h"




/*
Esta función aplica el detector de bordes de imágenes en color de Lee y Cok
IMPORTANTE: se necesita que la imagen en color tenga los planos separados y consecutivos
*/
void  Lee_Cok (float *datos, float *resultados, long int anchura, long int altura,int operador_basico)
{

 VECINDARIO v[9];
 VECINDARIO parcial_x, parcial_y;
 float mx[9],my[9];
 float lambda, gxx, gyy, gxy;
 int R[9], G[9], B[9];
 long int fila, coordenadas, tam_plano;
 int i1, i2, i3;

 switch(operador_basico)
    {
     case 1:
        mx[0]=-0.25; mx[1]=0.0; mx[2]=0.25;
        mx[3]=-0.5;  mx[4]=0.0; mx[5]=0.5;
        mx[6]=-0.25; mx[7]=0.0; mx[8]=0.25;

        my[0]=-0.25; my[1]=-0.5; my[2]=-0.25;
        my[3]=0;     my[4]=0.0;  my[5]=0;
        my[6]=0.25;  my[7]=0.5;  my[8]=0.25;
        break;
     case 2:
        mx[0]=-1.0/3.0; mx[1]=0.0; mx[2]=1.0/3.0;
        mx[3]=-1.0/3.0; mx[4]=0.0; mx[5]=1.0/3.0;
        mx[6]=-1.0/3.0; mx[7]=0.0; mx[8]=1.0/3.0;

        my[0]=-1.0/3.0; my[1]=-1.0/3.0; my[2]=-1.0/3.0;
        my[3]=0.0;      my[4]=0.0;      my[5]=0.0;
        my[6]=1.0/3.0;  my[7]=1.0/3.0;   my[8]=1.0/3.0;
        break;
     case 3:
        mx[0]=-3.0/15.0; mx[1]=-3.0/15.0 ; mx[2]=5.0/15.0;
        mx[3]=-3.0/15.0; mx[4]=0.0;        mx[5]=5.0/15.0;
        mx[6]=-3.0/15.0; mx[7]=-3.0/15.0 ; mx[8]=5.0/15.0;

        my[0]=5.0/15.0;  my[1]=5.0/15.0;  my[2]=5.0/15.0;
        my[3]=-3.0/15.0; my[4]=0.0;       my[5]=-3.0/15.0;
        my[6]=-3.0/15.0; my[7]=-3.0/15.0; my[8]=-3.0/15.0;
    }

 tam_plano = anchura * altura;

 /* SE ESTABLECEN LAS COORDENADAS RELATIVAS DEL VECINDARIO 3 X 3 */
 /*
        0 1 2
    3 4 5
    6 7 8
 */


   R[0] = - anchura - 1;
   R[1] = - anchura;
   R[2] = - anchura + 1;
   R[3] = - 1;
   R[4] =   0;
   R[5] =   1;
   R[6] =  anchura - 1;
   R[7] =  anchura;
   R[8] =  anchura + 1;

   for (i1 = 0; i1 < 9; i1++)
    {
      G[i1] = R[i1] + tam_plano;
      B[i1] = R[i1] + 2 *tam_plano;
    }

  /* SE PONEN A CERO LOS PUNTOS DE LA PRIMERA Y ULTIMA COLUMNAS */
  for (i1 = 0 ; i1 < altura - 1; i1++)
    {
     fila = i1 * anchura;
     resultados[fila] = 0;
     resultados[fila + anchura - 1] = 0;
    }


  /* SE PONEN A CERO LOS PUNTOS DE LA PRIMERA Y ULTIMA FILAS QUE NO FUERON TRATADOS EN EL BUCLE ANTERIOR */
  for (i1 = 1 ; i1 < anchura ; i1++)
    {
     resultados[i1] = 0;
     resultados[i1 + tam_plano - anchura] = 0;
    }

  /* SE RECORRE DESDE LA SEGUNDA HASTA LA PENULTIMA FILA */
  for (i1 = 1; i1 < altura - 1; i1++)
  {
    fila = i1 * anchura;
    /* SE RECORRE DESDE LA SEGUNDA HASTA LA PENULTIMA COLUMNA */
    for (i2 = 1; i2 < anchura - 1; i2++)
    {
    /* COORDENADAS DEL PUNTO CENTRAL */
    coordenadas = fila + i2;

    /* VALORES DE LOS PUNTOS */
    for (i3 = 0; i3 < 9; i3++)
        {
          v[i3].R  = datos[coordenadas + R[i3]];
          v[i3].G  = datos[coordenadas + G[i3]];
          v[i3].B  = datos[coordenadas + B[i3]];
        }

    /* CALCULO DE LA DERIVADA PARCIAL EN EL PLANO R RESPECTO DE X */
    parcial_x.R=0.0;
    for (i3=0; i3<9;i3++)
        parcial_x.R += v[i3].R * mx[i3];


    /* CALCULO DE LA DERIVADA PARCIAL EN EL PLANO R RESPECTO DE Y */
    parcial_y.R=0.0;
    for (i3=0; i3<9;i3++)
        parcial_y.R += v[i3].R * my[i3];

    /* CALCULO DE LA DERIVADA PARCIAL EN EL PLANO G RESPECTO DE X */
    parcial_x.G=0.0;
    for (i3=0; i3<9;i3++)
        parcial_x.G += v[i3].G * mx[i3];

    /* CALCULO DE LA DERIVADA PARCIAL EN EL PLANO G RESPECTO DE Y */
    parcial_y.G=0.0;
    for (i3=0; i3<9;i3++)
        parcial_y.G += v[i3].G * my[i3];

    /* CALCULO DE LA DERIVADA PARCIAL EN EL PLANO B RESPECTO DE X */
    parcial_x.B=0.0;
    for (i3=0; i3<9;i3++)
        parcial_x.B += v[i3].B * mx[i3];

    /* CALCULO DE LA DERIVADA PARCIAL EN EL PLANO B RESPECTO DE Y */
    parcial_y.B=0.0;
    for (i3=0; i3<9;i3++)
        parcial_y.B += v[i3].B * my[i3];

    /* CALCULO DE gxx(x,y) */
    gxx = parcial_x.R * parcial_x.R + parcial_x.G * parcial_x.G + parcial_x.B * parcial_x.B;

    /* CALCULO DE gyy(x,y) */
    gyy = parcial_y.R * parcial_y.R + parcial_y.G * parcial_y.G + parcial_y.B * parcial_y.B;

    /* CALCULO DE gxy(x,y) */
    gxy = parcial_x.R * parcial_y.R + parcial_x.G * parcial_y.G + parcial_x.B * parcial_y.B;

    /* CALCULO DEL AUTOVALOR MAS GRANDE */
    lambda = 0.5 * (
            gxx + gyy +
            sqrt(
                (gxx+gyy)*(gxx+gyy)
                - 4 * (gxx*gyy-gxy*gxy)
                )
            );
    /* SE ASIGNA COMO MAGNITUD DEL GRADIENTE LA RAIZ CUADRADA DE LAMBDA */
    resultados[coordenadas] = sqrt(lambda);
    }

  }

 return;

}




/***********************************************
Esta función aplica el detector de bordes de imágenes en color direccional de Scharcanski y Venetsanopoulos
IMPORTANTE: se necesita que la imagen en color tenga los planos separados y consecutivos
************************************************/
void Direccional (float *datos, float *resultados, long int anchura, long int altura, int tamano_ventana)
{

/* ARRAY DE PIXELES VECINOS */
 VECINDARIO *v;

 /* H[0] REPRESENTA H+(xO,y0)*/
 /* H[1] REPRESENTA H-(xO,y0)*/
 /* V[0] REPRESENTA V+(xO,y0)*/
 /* V[1] REPRESENTA V-(xO,y0)*/
 VECINDARIO H[2], V[2];

 /* dH = H+(x0,y0) - H-(x0,y0) */
VECINDARIO dH;

 /* dV = V+(x0,y0) - V-(x0,y0) */
 VECINDARIO dV;

 float mH2, mV2, modulo;

 int n,t,p,k=3;
 int i1,i2,i3,i4;

 /* LOS SIGUIENTES 3 VECTORES PERMITEN LOCALIZAR LA POSICION DE       */
 /* LOS PIXELS EN UNA REGION DE nXn  EN LOS PLANOS ROJO, VERDE Y AZUL */
 long int *R;
 long int *G;
 long int *B;

/* PARA POSICIONARNOS EN LA FILA DEL PIXEL ACTUAL */
 long int fila;

/* INDICA LAS COORDENADAS DEL PIXEL ACTUAL */
 long int coordenadas;

    /* Anchura*Altura                   */
 long int tam_plano;


 /* RESERVA DE MEMORIA PARA LA PUNTOS DEL VECINDARIO */
 switch(tamano_ventana)
  {
   case 1: k = 3;
       break;
   case 2: k = 5;
       break;
   case 3: k = 7;
 }
 n = k * k;

 R = (long int *)malloc(n*sizeof(long int));
 G = (long int *)malloc(n*sizeof(long int));
 B = (long int *)malloc(n*sizeof(long int));


 v = (VECINDARIO *)malloc(n*sizeof(VECINDARIO));

 tam_plano = anchura*altura;

 /* POSICIONES RELATIVAS DENTRO DE LA IMAGEN DE ENTRADA DE LOS PIXELS */
 /* DE UNA REGION kxk  PARA LOS 3 PLANOS (R, G, B)                    */
 /*
   0  1  2  3  4  5  6
   7  8  9 10 11 12 13      0  1  2  3  4
  14 15 16 17 18 19 20      5  6  7  8  9     0 1 2
  21 22 23 24 25 26 27     10 11 12 13 14     3 4 5
  28 29 30 31 32 33 34     15 16 17 18 19     6 7 8
  35 36 37 38 39 40 41     20 21 22 23 24
  42 43 44 45 46 47 48
 */

 t = (k-1)/2;
 i3 = 0;
 for (i1 = -t; i1 < t+1; i1++)
  for(i2 = -t; i2 < t+1; i2++)
  {
   R[i3] = i1 * anchura + i2;
   G[i3] =  R[i3] + tam_plano;
   B[i3] =  R[i3] + 2 *  tam_plano;
   i3++;
  }

/* SE INICIALIZAN A "0" LOS ELEMENTOS DE LAS t PRIMERAS Y ULTIMAS COLUMNAS DE */
 /* LA IMAGEN DE SALIDA                                                */
 /*
        --------------------
       / 0 /   /   /   / 0 /
       --------------------
      / 0 /   /   /   / 0 /
      --------------------
     / 0 /   /   /   / 0 /
     --------------------
    / 0 /   /   /   / 0 /
    --------------------
   / 0 /   /   /   / 0 /
   --------------------

 */

  for (i1 = 0; i1 < altura ; i1++)
   for (i2 = 0; i2 < t; i2++)
    {
     fila = i1 * anchura + i2;
     resultados[fila] = 0;
     resultados[fila+anchura - 1 - 2 * i2]=0;
    }


 /* SE INICIALIZAN A 0 LOS ELEMENTOS DE LAS t PRIMERAS Y ULTIMAS FILAS DE   */
 /* LA IMAGEN DE SALIDA, EXCEPTO LOS t PRIMEROS Y ULTIMOS DE CADA FILA, YA */
 /* INICIALIZADOS EN EL BUCLE ANTERIOR.                               */
 /*
        --------------------
       /   / 0 / 0 / 0 /   /
       --------------------
      /   /   /   /   /   /
      --------------------
     /   /   /   /   /   /
     --------------------
    /   /   /   /   /   /
    --------------------
   /   / 0 / 0 / 0 /   /
   --------------------

 */

  for (i1 = 0; i1 < t; i1++)
   for (i2 = t; i2 < anchura - t ; i2++)
    {
     resultados[i1 * anchura + i2] = 0;
     resultados[tam_plano - (i1+1) *  anchura + i2]=0;
    }

  p = (n-1)/2; /* PUNTO CENTRAL */

 /* ESTE BUCLE RECORRE DESDE LA tª HASTA LA altura - t FILA */
 for(i1 = t; i1 < altura - t; i1++)
    {
     /* SE CALCULA LA POSICION DEL PRIMER ELEMENTO DE LA FILA i1 */
     fila = i1*anchura;

     /* ESTE BUCLE RECORRE DESDE LA tª HASTA LA  Anchura - t COLUMNA */
     for(i2 = t; i2 < anchura - t; i2++)
        {
         /* SE CALCULAN LAS COORDENADAS DEL PIXEL CENTRAL DE LA REGION DE w x w */
         coordenadas= fila  + i2;

         /* SE CALCULAN LOS VALORES DE LOS PIXELS DE LA REGION w x w */
         for(i3 = 0; i3 < n; i3++)
            {
             v[i3].R = datos[coordenadas + R[i3]];
             v[i3].G = datos[coordenadas + G[i3]];
             v[i3].B = datos[coordenadas + B[i3]];
            }

      /* SE CALCULA EL VALOR DE H+(x0,y0) SUMANDO LOS VALORES DE LOS PUNTOS SITUADOS EN LAS FILAS SIGUIENTES A LA DEL PUNTO CENTRAL */
         H[0].R = 0.0;
         H[0].G = 0.0;
         H[0].B = 0.0;

         for (i3 = p+t+1; i3<n; i3++)
            {
             H[0].R += v[i3].R;
             H[0].G += v[i3].G;
             H[0].B += v[i3].B;
            }
             H[0].R /= k*t;
             H[0].G /= k*t;
             H[0].B /= k*t;

      /* SE CALCULA EL VALOR DE H-(x0,y0)  SUMANDO LOS VALORES DE LOS PUNTOS SITUADOS EN LAS FILAS ANTERIORES A LA DEL PUNTO CENTRAL */
         H[1].R = 0.0;
         H[1].G = 0.0;
         H[1].B = 0.0;
         for (i3 = 0; i3 <=p-t-1; i3++)
            {
             H[1].R += v[i3].R;
             H[1].G += v[i3].G;
             H[1].B += v[i3].B;
            }
             H[1].R /= k*t;
             H[1].G /= k*t;
             H[1].B /= k*t;

      /* SE CALCULA EL VALOR DE V+(x0,y0) SUMANDO LOS VALORES DE LOS PUNTOS SITUADOS EN LAS COLUMNAS SIGUIENTES A LA DEL PUNTO CENTRAL */
         V[0].R = 0;
         V[0].G = 0;
         V[0].B = 0;
    for (i3 = (k+1)/2; i3<=(k*k)-(k-1)/2; i3 = i3 + k)
     for(i4 = 0; i4 < t ; i4++)
            {
             V[0].R += v[i3+i4].R;
             V[0].G += v[i3+i4].G;
             V[0].B += v[i3+i4].B;
            }
             V[0].R /= k*t;
             V[0].G /= k*t;
             V[0].B /= k*t;

      /* SE CALCULA EL VALOR DE V-(x0,y0) SUMANDO LOS VALORES DE LOS PUNTOS SITUADOS EN LAS COLUMNAS ANTERIORES A LA DEL PUNTO CENTRAL */
         V[1].R = 0;
         V[1].G = 0;
         V[1].B = 0;
    for (i3 = 0; i3<=k*(k-1); i3 = i3 + k)
     for(i4 = 0; i4 < t; i4++)
            {
             V[1].R += v[i3+i4].R;
             V[1].G += v[i3+i4].G;
             V[1].B += v[i3+i4].B;
            }
             V[1].R /= k*t;
             V[1].G /= k*t;
             V[1].B /= k*t;

    /* SE CALCULAN LOS VECTORES dH(x0,y0) y dV(x0,y0) */
    dH.R= H[0].R - H[1].R;
    dH.G= H[0].G - H[1].G;
    dH.B= H[0].B - H[1].B;

    dV.R= V[0].R - V[1].R;
    dV.G= V[0].G - V[1].G;
    dV.B= v[0].B - V[1].B;

    /* SE CALCULAN LOS CUADRADOS DE LOS MODULOS DE dH y dV */
    mH2 = dH.R * dH.R + dH.G * dH.G + dH.B * dH.B;
    mV2 = dV.R * dV.R + dV.G * dV.G + dV.B * dV.B;

    /* SE CALCULA EL MODULO DE f(x0,y0) = (mH(x0,y0),mV(x0,y0)) */
    modulo = sqrt(mH2+mV2);

         /* SE ASIGNA EL RESULTADO AL PIXEL DE SALIDA EN LAS MISMAS */
         /* COORDENADAS QUE EL PIXEL CENTRAL DE LA REGION w x w     */
         resultados[coordenadas] = modulo;

    }
}

 return;
}




/*********************************************
Esta función aplica el detector de bordes de imágenes en color dv
IMPORTANTE: se necesita que la imagen en color tenga los planos separados y consecutivos
**********************************************/
void Dv(float *datos,
     float *resultados,
     long int anchura,
     long int altura,
     int ventana,
     int filtro,
     float alfa,
     int tipo_distancia)
{

/* VECTOR PARA ALMACENAR LOS VALORES DE LOS PUNTOS VECINOS */
 VECINDARIO *v;

/* VECTOR PARA ALMACENAR LOS VALORES DE LOS PUNTOS VECINOS DE LAS SUBVENTANAS QUE SE VAN A FILTRAR */
 VECINDARIO *v_aux;

 /* VECTOR PARA ALMACENAR LOS VALORES DE LAS DIFERENCIAS DE VECTORES DE LOS PUNTOS VECINOS */
 VECINDARIO d[4];

 /* VECTOR PARA ALMACENAR LOS VALORES DE LOS VECTORES X DEL VECINDARIO */
 VECINDARIO x[4];

 /* VECTOR PARA ALMACENAR LOS VALORES DE LOS VECTORES Y DEL VECINDARIO */
 VECINDARIO y[4];

/* VECTOR PARA ALMECENAR LOS MODULOS DE LAS DIFERENCIAS DE VECTORES*/
 float m[4];

int indice_mediana;

/* VECTORES PARA DETERMINAR LAS POSICIONES RELATIVAS DE LOS PUNTOS VECINOS */
 long int *R, *G, *B;

 /* VARIABLE PARA CALCULAR EL MAXIMO DE LOS MODULOS DE LOS VECTORES DE DIFERENCIAS */
 float maximo;

 /* Tamano total de la imagen */
 long int tam_plano;

 /* VARIABLES UTILIZADAS PARA DETERMINAR LA POSICION DE CADA PUNTO CENTRAL */
 long int fila, coordenadas;


 int i1, i2, i3, i4, i5;
 int n, k, t;
 int divisor;

 tam_plano = anchura * altura;

 /* SE DETERMINA EL NUMERO DE PUNTOS */

/* VENTANA DE 3 X 3 */
 if (ventana == 2)
    k  = 3;

/* VENTANA DE 5 X 5 */
 else
    k  = 5;

  n = k * k;


 /* SE RESERVA MEMORIA PARA LAS VARIABLES AUXILIARES */
 v = (VECINDARIO *)malloc(n*sizeof(VECINDARIO));

 R = (long *)malloc(n*sizeof(long int));
 G = (long *)malloc(n*sizeof(long int));
 B = (long *)malloc(n*sizeof(long int));


/* SE ESTABLECEN LAS COORDENADAS RELATIVAS DEL VECINDARIO 3 X 3 */
/*
    0 1 2
    3 4 5
    6 7 8

         0  1  2  3  4
         5  6  7  8  9 int  vector_mediana(VECINDARIO *v, int n, int tipo_distancia)
    10 11 12 13 14
    15 16 17 18 19
    20 21 22 23 24

 */

 t = (k-1)/2;
 i3 = 0;
 for (i1 = -t; i1 < t + 1; i1++)
   for (i2 = -t; i2 < t + 1; i2++)
      {
    R[i3] = i1 * anchura + i2;
    G[i3] = R[i3] + tam_plano ;
    B[i3] = R[i3] + 2 * tam_plano ;
    i3++;
      }

 /* SE PONEN A CERO LOS PUNTOS DE LAS t PRIMERAS Y ULTIMAS COLUMNAS DE LA IMAGEN DE SALIDA */
  for (i1 = 0; i1 < altura; i1++)
   for (i2 = 0; i2 < t; i2++)
    {
     fila = i1  * anchura;
     resultados[fila] = 0;
     resultados[fila+anchura-1-2*i2]=0;
    }

 /* SE PONEN A CERO LOS PUNTOS DE LAS t PRIMERAS Y ULTIMAS FILAS DE LA IMAGEN DE SALIDA QUE NO FUERON CONSIDERADOS EN EL BULCLE ANTERIOR */
  for (i1 = 0; i1 < t; i1++)
   for (i2 = t; i2 < anchura - t; i2++)
    {
     resultados[i1 * anchura + i2] = 0;
     resultados[tam_plano - (i1 +1) * anchura + i2] = 0;
    }

 /* ESTE BUCLE RECORRE DESDE tª HASTA LA altura A- t FILA */
 for (i1 = t; i1 < altura - t ; i1++)
  {
     fila = i1 * anchura;
   /* ESTE BUCLE RECORRE DESDE LA tª HASTA la anchura - t COLUMNA */
     for (i2 = t; i2 < anchura - t ; i2++)
    {
    /* COORDENADAS DEL PUNTO CENTRAL */
    coordenadas = fila + i2;

    /* VALORES DE LOS PUNTOS DEL VECINDARIO */
    for (i3 =0; i3 < n; i3++)
     {
      v[i3].R=datos[coordenadas+R[i3]];
      v[i3].G=datos[coordenadas+G[i3]];
      v[i3].B=datos[coordenadas+B[i3]];
     }

    if (ventana == 1) /* VENTANA 5 X 5 */
         {
              /* SE APLICA EL FILTRO DE SUAVIZACION PARA OBTENER UN VECTOR EN CADA SUBVENTANA*/
             switch(filtro)
              {
           case 1: /* FILTRO DE LA MEDIA ARIMETICA */

        /* SE INICIALIZAN LOS VECTORES */
                     for (i3 = 0; i3 < 4; i3++)
              {
            x[i3].R=0.0;
            x[i3].G=0.0;
            x[i3].B=0.0;

            y[i3].R=0.0;
            y[i3].G=0.0;
            y[i3].B=0.0;
              }

                 /* DIRECCION 0 GRADOS */

                     for (i3 = 0; i3 < 10; i3++)
              {
            x[0].R +=v[i3].R;
            x[0].G +=v[i3].G;
            x[0].B +=v[i3].B;

            y[0].R +=v[i3+15].R;
            y[0].G +=v[i3+15].G;
            y[0].B +=v[i3+15].B;
              }

                 /* DIRECCION 90 GRADOS */
                     for (i3 = 0; i3 < 5; i3++)
                       for (i4 = 0; i4 < 2; i4++)
              {
            x[1].R +=v[i3*5+i4].R;
            x[1].G +=v[i3*5+i4].G;
            x[1].B +=v[i3*5+i4].B;

            y[1].R +=v[i3*5+i4+3].R;
            y[1].G +=v[i3*5+i4+3].G;
            y[1].B +=v[i3*5+i4+3].B;
              }

                 /* DIRECCION 45 GRADOS */
                     for (i3 = 0; i3 < 5; i3++)
                       for (i4 = i3+1; i4 < 5; i4++)
              {
            x[2].R +=v[i3*5+i4].R;
            x[2].G +=v[i3*5+i4].G;
            x[2].B +=v[i3*5+i4].B;

            y[2].R +=v[i4*5+i3].R;
            y[2].G +=v[i4*5+i3].G;
            y[2].B +=v[i4*5+i3].B;
              }

                 /* DIRECCION 135 GRADOS */
                     for (i3 = 1; i3 < 5; i3++)
                       for (i4 = 5 - i3; i4 < 5; i4++)
              {
            x[3].R +=v[i3*5+i4].R;
            x[3].G +=v[i3*5+i4].G;
            x[3].B +=v[i3*5+i4].B;

            y[3].R +=v[24-(i3*5+i4)].R;
            y[3].G +=v[24-(i3*5+i4)].G;
            y[3].B +=v[24-(i3*5+i4)].B;
              }

                     for (i3 = 0; i3 < 4; i3++)
              {
            x[i3].R /= 10.0;
            x[i3].G /= 10.0;
            x[i3].B /= 10.0;

            y[i3].R /= 10.0;
            y[i3].G /= 10.0;
            y[i3].B /= 10.0;
              }


                  break;
           case 2: /* FILTRO DEL VECTOR MEDIANA*/
            /* SE RESERVA MEMORIA PARA EL VECTOR AUXILIAR */
            v_aux = (VECINDARIO *)malloc(10*sizeof(VECINDARIO));

                 /* DIRECCION 0 GRADOS */

                     for (i3 = 0; i3 < 10; i3++)
              {
            v_aux[i3].R =v[i3].R;
            v_aux[i3].G =v[i3].G;
            v_aux[i3].B =v[i3].B;
              }

              indice_mediana = vector_mediana(v_aux,10,tipo_distancia);
              x[0].R = v_aux[indice_mediana].R;
              x[0].G = v_aux[indice_mediana].G;
              x[0].B = v_aux[indice_mediana].B;

                     for (i3 = 0; i3 < 10; i3++)
              {
            v_aux[i3].R =v[i3+15].R;
            v_aux[i3].G =v[i3+15].G;
            v_aux[i3].B =v[i3+15].B;
              }

              indice_mediana = vector_mediana(v_aux,10,tipo_distancia);
              y[0].R = v_aux[indice_mediana].R;
              y[0].G = v_aux[indice_mediana].G;
              y[0].B = v_aux[indice_mediana].B;


                 /* DIRECCION 90 GRADOS */
                     for (i3 = 0; i3 < 5; i3++)
                       for (i4 = 0; i4 < 2; i4++)
              {
            v_aux[i3+i4*5].R =v[i3*5+i4].R;
            v_aux[i3+i4*5].G =v[i3*5+i4].G;
            v_aux[i3+i4*5].B =v[i3*5+i4].B;
              }

              indice_mediana = vector_mediana(v_aux,10,tipo_distancia);
              x[1].R = v_aux[indice_mediana].R;
              x[1].G = v_aux[indice_mediana].G;
              x[1].B = v_aux[indice_mediana].B;

                     for (i3 = 0; i3 < 5; i3++)
                       for (i4 = 0; i4 < 2; i4++)
              {
            v_aux[i4*5+i3].R =v[i3*5+i4+3].R;
            v_aux[i4*5+i3].G =v[i3*5+i4+3].G;
            v_aux[i4*5+i3].B =v[i3*5+i4+3].B;
              }

              indice_mediana = vector_mediana(v_aux,10,tipo_distancia);
              y[1].R = v_aux[indice_mediana].R;
              y[1].G = v_aux[indice_mediana].G;
              y[1].B = v_aux[indice_mediana].B;

                 /* DIRECCION 45 GRADOS */
             i5 = 0;
                     for (i3 = 0; i3 < 5; i3++)
                       for (i4 = i3+1; i4 < 5; i4++)
              {
            v_aux[i5].R =v[i3*5+i4].R;
            v_aux[i5].G =v[i3*5+i4].G;
            v_aux[i5].B =v[i3*5+i4].B;
            i5 ++;
              }

              indice_mediana = vector_mediana(v_aux,10,tipo_distancia);
              x[2].R = v_aux[indice_mediana].R;
              x[2].G = v_aux[indice_mediana].G;
              x[2].B = v_aux[indice_mediana].B;

             i5 = 0;
                     for (i3 = 0; i3 < 5; i3++)
                       for (i4 = i3+1; i4 < 5; i4++)
            {
            v_aux[i5].R =v[i4*5+i3].R;
            v_aux[i5].G =v[i4*5+i3].G;
                v_aux[i5].B =v[i4*5+i3].B;
            i5++;
               }

              indice_mediana = vector_mediana(v_aux,10,tipo_distancia);
              y[2].R = v_aux[indice_mediana].R;
              y[2].G = v_aux[indice_mediana].G;
              y[2].B = v_aux[indice_mediana].B;

                 /* DIRECCION 135 GRADOS */
             i5 = 0;
                     for (i3 = 0; i3 < 5; i3++)
                       for (i4 = i3+1; i4 < 5; i4++)
              {
            v_aux[i5].R =v[i3*5+i4].R;
            v_aux[i5].G =v[i3*5+i4].G;
            v_aux[i5].B =v[i3*5+i4].B;
            i5 ++;
              }

              indice_mediana = vector_mediana(v_aux,10,tipo_distancia);
              x[3].R = v[indice_mediana].R;
              x[3].G = v[indice_mediana].G;
              x[3].B = v[indice_mediana].B;

             i5 = 0;
                     for (i3 = 0; i3 < 5; i3++)
                       for (i4 = i3+1; i4 < 5; i4++)
            {
            v_aux[3].R =v[24-(i3*5+i4)].R;
            v_aux[3].G =v[24-(i3*5+i4)].G;
            v_aux[3].B =v[24-(i3*5+i4)].B;
            i5++;
               }

              indice_mediana = vector_mediana(v_aux,10,tipo_distancia);
              y[3].R = v_aux[indice_mediana].R;
              y[3].G = v_aux[indice_mediana].G;
              y[3].B = v_aux[indice_mediana].B;

              break;


           case 3: /* FILTRO DE LA MEDIA "ALFA AJUSTADA" */
            /* SE RESERVA MEMORIA PARA EL VECTOR AUXILIAR */
            v_aux = (VECINDARIO *)malloc(10*sizeof(VECINDARIO));

             /* SE PONEN A CERO LAS VECTORES AUXILIARES */
                     for (i3 = 0; i3 < 4; i3++)
              {
            x[i3].R=0.0;
            x[i3].G=0.0;
            x[i3].B=0.0;

            y[i3].R=0.0;
            y[i3].G=0.0;
            y[i3].B=0.0;
              }

                 /* DIRECCION 0 GRADOS */

                     for (i3 = 0; i3 < 10; i3++)
              {
            v_aux[i3].R =v[i3].R;
            v_aux[i3].G =v[i3].G;
            v_aux[i3].B =v[i3].B;
              }

             ordenamiento_distancias_agregadas(v_aux,10,tipo_distancia);
              for (i3 = 0; i3 < 10 * (1-2*alfa); i3++)
            {
                 x[0].R += v_aux[i3].R;
                 x[0].G += v_aux[i3].G;
                 x[0].B += v_aux[i3].B;
            }

                     for (i3 = 0; i3 < 10; i3++)
              {
            v_aux[i3].R =v[i3+15].R;
            v_aux[i3].G =v[i3+15].G;
            v_aux[i3].B =v[i3+15].B;
              }

             ordenamiento_distancias_agregadas(v_aux,10,tipo_distancia);
              for (i3 = 0; i3 < 10 * (1-2*alfa); i3++)
            {
                 y[0].R += v_aux[i3].R;
                 y[0].G += v_aux[i3].G;
                 y[0].B += v_aux[i3].B;
            }


                 /* DIRECCION 90 GRADOS */
                     for (i3 = 0; i3 < 5; i3++)
                       for (i4 = 0; i4 < 2; i4++)
              {
            v_aux[i3+i4*5].R =v[i3*5+i4].R;
            v_aux[i3+i4*5].G =v[i3*5+i4].G;
            v_aux[i3+i4*5].B =v[i3*5+i4].B;
              }

             ordenamiento_distancias_agregadas(v_aux,10,tipo_distancia);
              for (i3 = 0; i3 < 10 * (1-2*alfa); i3++)
            {
                 x[1].R += v_aux[i3].R;
                 x[1].G += v_aux[i3].G;
                 x[1].B += v_aux[i3].B;
                }

                     for (i3 = 0; i3 < 5; i3++)
                       for (i4 = 0; i4 < 2; i4++)
              {
            v_aux[i4*5+i3].R =v[i3*5+i4+3].R;
            v_aux[i4*5+i3].G =v[i3*5+i4+3].G;
            v_aux[i4*5+i3].B =v[i3*5+i4+3].B;
              }

             ordenamiento_distancias_agregadas(v_aux,10,tipo_distancia);
              for (i3 = 0; i3 < 10 * (1-2*alfa); i3++)
            {
                 y[1].R += v_aux[i3].R;
                 y[1].G += v_aux[i3].G;
                 y[1].B += v_aux[i3].B;
            }

                 /* DIRECCION 45 GRADOS */
             i5 = 0;
                     for (i3 = 0; i3 < 5; i3++)
                       for (i4 = i3+1; i4 < 5; i4++)
              {
            v_aux[i5].R =v[i3*5+i4].R;
            v_aux[i5].G =v[i3*5+i4].G;
            v_aux[i5].B =v[i3*5+i4].B;
            i5 ++;
              }

             ordenamiento_distancias_agregadas(v_aux,10,tipo_distancia);
              for (i3 = 0; i3 < 10 * (1-2*alfa); i3++)
            {
                 x[2].R += v_aux[i3].R;
                 x[2].G += v_aux[i3].G;
                 x[2].B += v_aux[i3].B;
            }

             i5 = 0;
                     for (i3 = 0; i3 < 5; i3++)
                       for (i4 = i3+1; i4 < 5; i4++)
            {
            v_aux[i5].R =v[i4*5+i3].R;
            v_aux[i5].G =v[i4*5+i3].G;
                v_aux[i5].B =v[i4*5+i3].B;
            i5++;
               }

              for (i3 = 0; i3 < 10 * (1-2*alfa); i3++)
            {
                 y[2].R += v_aux[i3].R;
                 y[2].G += v_aux[i3].G;
                 y[2].B += v_aux[i3].B;
            }

                 /* DIRECCION 135 GRADOS */
             i5 = 0;
                     for (i3 = 0; i3 < 5; i3++)
                       for (i4 = i3+1; i4 < 5; i4++)
              {
            v_aux[i5].R =v[i3*5+i4].R;
            v_aux[i5].G =v[i3*5+i4].G;
            v_aux[i5].B =v[i3*5+i4].B;
            i5 ++;
              }

             ordenamiento_distancias_agregadas(v_aux,10,tipo_distancia);
              for (i3 = 0; i3 < 10 * (1-2*alfa); i3++)
            {
                 x[3].R += v_aux[i3].R;
                 x[3].G += v_aux[i3].G;
                 x[3].B += v_aux[i3].B;
            }

             i5 = 0;
                     for (i3 = 0; i3 < 5; i3++)
                       for (i4 = i3+1; i4 < 5; i4++)
            {
            v_aux[3].R =v[24-(i3*5+i4)].R;
            v_aux[3].G =v[24-(i3*5+i4)].G;
            v_aux[3].B =v[24-(i3*5+i4)].B;
            i5++;
               }

             ordenamiento_distancias_agregadas(v_aux,10,tipo_distancia);
              for (i3 = 0; i3 < 10 * (1-2*alfa); i3++)
            {
                 y[3].R += v_aux[i3].R;
                 y[3].G += v_aux[i3].G;
                 y[3].B += v_aux[i3].B;
            }

        /* SE PROMEDIAN LOS VECTORES AUXILIARES */

            divisor = (int) 10 * (1-2*alfa);
                     for (i3 = 0; i3 < 4; i3++)
              {
            x[i3].R /= divisor;
            x[i3].G /= divisor;
            x[i3].B /= divisor;

            y[i3].R /= divisor;
            y[i3].G /= divisor;
            y[i3].B /= divisor;
              }
          }

      /* SE ESTABLECEN LAS COORDENADAS DE LOS VECTORES DE DIFERENCIAS */
          for (i3 = 0; i3 < 4; i3++)
           {
        d[i3].R=y[i3].R-x[i3].R;
        d[i3].G=y[i3].G-x[i3].G;
        d[i3].B=y[i3].B-x[i3].B;
           }

         }

        else /* VENTANA DE 3 x 3 */
       /* SE ESTABLECEN LAS COORDENADAS DE LOS VECTORES DE DIFERENCIAS */
            for (i3 = 0; i3 < 4; i3 ++)
         {
          d[i3].R=v[8-i3].R-v[i3].R;
          d[i3].G=v[8-i3].G-v[i3].G;
          d[i3].B=v[8-i3].B-v[i3].B;
          }


    /* SE CALCULAN LOS MODULOS DE LOS VECTORES DE DIFERENCIAS */
    for (i3=0; i3 < 4; i3++)
      m[i3] = sqrt(d[i3].R*d[i3].R + d[i3].G*d[i3].G + d[i3].B*d[i3].B);


    /* SE CALCULA EL MAXIMO DE LOS MODULOS */
    maximo = m[0];
    for (i3 = 1; i3 < 4; i3++)
      if (maximo < m[i3]) maximo = m[i3];

    /* EL VALOR MAXIMO ES ASIGNADO COMO ESTIMACION DE LA MAGNITUD DEL GRADIENTE AL PUNTO CENTRAL */
    resultados[coordenadas] = maximo;
    }

   }
 return;
}




/***********************************************
Esta función aplica el detector de bordes de imágenes en color de dv-hv
IMPORTANTE: se necesita que la imagen en color tenga los planos separados y consecutivos
************************************************/
void Dv_hv(float *datos,
     float *resultados,
     long int anchura,
     long int altura,
     int ventana,
     int filtro,
     float alfa,
     int tipo_distancia)
{

 VECINDARIO *v; /* VECTOR PARA ALMACENAR LOS VALORES DE LOS PUNTOS VECINOS */
 VECINDARIO *v_aux; /* VECTOR PARA ALMACENAR LOS VALORES DE LOS PUNTOS VECINOS DE LAS SUBVENTANAS QUE SE VAN A FILTRAR */
 VECINDARIO d[2]; /* VECTOR PARA ALMACENAR LOS VALORES DE LAS DIFERENCIAS DE VECTORES DE LOS PUNTOS VECINOS */
 VECINDARIO x[2]; /* VECTOR PARA ALMACENAR LOS VALORES DE LOS VECTORES X DEL VECINDARIO */
 VECINDARIO y[2]; /* VECTOR PARA ALMACENAR LOS VALORES DE LOS VECTORES Y DEL VECINDARIO */

 float m[2]; /* VECTOR PARA ALMECENAR LOS MODULOS DE LAS DIFERENCIAS DE VECTORES*/
int indice_mediana;

 long int *R, *G, *B; /* VECTORES PARA DETERMINAR LAS POSICIONES RELATIVAS DE LOS PUNTOS VECINOS */


 float maximo; /* VARIABLE PARA CALCULAR EL MAXIMO DE LOS MODULOS DE LOS VECTORES DE DIFERENCIAS */

 long int tam_plano; /* Tamano total de la imagen */
 long int fila, coordenadas; /* VARIABLES UTILIZADAS PARA DETERMINAR LA POSICION DE CADA PUNTO CENTRAL */
 int i1, i2, i3, i4;
 int n, k, t;
 int divisor;

 tam_plano = anchura * altura;

 /* SE DETERMINA EL NUMERO DE PUNTOS */
 if (ventana == 2) /* VENTANA DE 3 X 3 */
    k  = 3;
 else /* VENTANA DE 5 X 5 */
    k  = 5;

  n = k * k;


 /* SE RESERVA MEMORIA PARA LAS VARIABLES AUXILIARES */
 v = (VECINDARIO *)malloc(n*sizeof(VECINDARIO));

 R = (long *)malloc(n*sizeof(long int));
 G = (long *)malloc(n*sizeof(long int));
 B = (long *)malloc(n*sizeof(long int));


/* SE ESTABLECEN LAS COORDENADAS RELATIVAS DEL VECINDARIO 3 X 3 */
/*
    0 1 2
    3 4 5
    6 7 8
*/

/* SE ESTABLECEN LAS COORDENADAS RELATIVAS DEL VECINDARIO 5 X 5 */
/*
         0  1  2  3  4
         5  6  7  8  9
    10 11 12 13 14
    15 16 17 18 19
    20 21 22 23 24

 */

 t = (k-1)/2;
 i3 = 0;
 for (i1 = -t; i1 < t + 1; i1++)
   for (i2 = -t; i2 < t + 1; i2++)
      {
    R[i3] = i1 * anchura + i2;
    G[i3] = R[i3] + tam_plano ;
    B[i3] = R[i3] + 2 * tam_plano ;
    i3++;
      }

 /* SE PONEN A CERO LOS PUNTOS DE LAS t PRIMERAS Y ULTIMAS COLUMNAS DE LA IMAGEN DE SALIDA */
  for (i1 = 0; i1 < altura; i1++)
   for (i2 = 0; i2 < t; i2++)
    {
     fila = i1  * anchura;
     resultados[fila] = 0;
     resultados[fila+anchura-1-2*i2]=0;
    }

 /* SE PONEN A CERO LOS PUNTOS DE LAS t PRIMERAS Y ULTIMAS FILAS DE LA IMAGEN DE SALIDA QUE NO FUERON CONSIDERADOS EN EL BULCLE ANTERIOR */
  for (i1 = 0; i1 < t; i1++)
   for (i2 = t; i2 < anchura - t; i2++)
    {
     resultados[i1 * anchura + i2] = 0;
     resultados[tam_plano - (i1 +1) * anchura + i2] = 0;
    }

 /* ESTE BUCLE RECORRE DESDE tª HASTA LA altura A- t FILA */
 for (i1 = t; i1 < altura - t ; i1++)
  {
     fila = i1 * anchura;
   /* ESTE BUCLE RECORRE DESDE LA tª HASTA la anchura - t COLUMNA */
     for (i2 = t; i2 < anchura - t ; i2++)
    {
    /* COORDENADAS DEL PUNTO CENTRAL */
    coordenadas = fila + i2;

    /* VALORES DE LOS PUNTOS DEL VECINDARIO */
    for (i3 =0; i3 < n; i3++)
     {
      v[i3].R=datos[coordenadas+R[i3]];
      v[i3].G=datos[coordenadas+G[i3]];
      v[i3].B=datos[coordenadas+B[i3]];
     }

    if (ventana == 1) /* VENTANA 5 X 5 */
         {
              /* SE APLICA EL FILTRO DE SUAVIZACION PARA OBTENER UN VECTOR EN CADA SUBVENTANA*/
             switch(filtro)
              {
           case 1: /* FILTRO DE LA MEDIA ARIMETICA */

        /* SE INICIALIZAN LOS VECTORES */
                     for (i3 = 0; i3 < 2; i3++)
              {
            x[i3].R=0.0;
            x[i3].G=0.0;
            x[i3].B=0.0;

            y[i3].R=0.0;
            y[i3].G=0.0;
            y[i3].B=0.0;
              }

                 /* DIRECCION 0 GRADOS */

                     for (i3 = 0; i3 < 10; i3++)
              {
            x[0].R +=v[i3].R;
            x[0].G +=v[i3].G;
            x[0].B +=v[i3].B;

            y[0].R +=v[i3+15].R;
            y[0].G +=v[i3+15].G;
            y[0].B +=v[i3+15].B;
              }

                 /* DIRECCION 90 GRADOS */
                     for (i3 = 0; i3 < 5; i3++)
                       for (i4 = 0; i4 < 2; i4++)
              {
            x[1].R +=v[i3*5+i4].R;
            x[1].G +=v[i3*5+i4].G;
            x[1].B +=v[i3*5+i4].B;

            y[1].R +=v[i3*5+i4+3].R;
            y[1].G +=v[i3*5+i4+3].G;
            y[1].B +=v[i3*5+i4+3].B;
              }

            /* SE PROMEDIAN LOS VECTORES */
                     for (i3 = 0; i3 < 2; i3++)
              {
            x[i3].R /= 10.0;
            x[i3].G /= 10.0;
            x[i3].B /= 10.0;

            y[i3].R /= 10.0;
            y[i3].G /= 10.0;
            y[i3].B /= 10.0;
              }


                  break;
           case 2: /* FILTRO DEL VECTOR MEDIANA*/
            /* SE RESERVA MEMORIA PARA EL VECTOR AUXILIAR */
            v_aux = (VECINDARIO *)malloc(10*sizeof(VECINDARIO));

                 /* DIRECCION 0 GRADOS */

                     for (i3 = 0; i3 < 10; i3++)
              {
            v_aux[i3].R =v[i3].R;
            v_aux[i3].G =v[i3].G;
            v_aux[i3].B =v[i3].B;
              }

              indice_mediana = vector_mediana(v_aux,10,tipo_distancia);
              x[0].R = v_aux[indice_mediana].R;
              x[0].G = v_aux[indice_mediana].G;
              x[0].B = v_aux[indice_mediana].B;

                     for (i3 = 0; i3 < 10; i3++)
              {
            v_aux[i3].R =v[i3+15].R;
            v_aux[i3].G =v[i3+15].G;
            v_aux[i3].B =v[i3+15].B;
              }

              indice_mediana = vector_mediana(v_aux,10,tipo_distancia);
              y[0].R = v_aux[indice_mediana].R;
              y[0].G = v_aux[indice_mediana].G;
              y[0].B = v_aux[indice_mediana].B;


                 /* DIRECCION 90 GRADOS */
                     for (i3 = 0; i3 < 5; i3++)
                       for (i4 = 0; i4 < 2; i4++)
              {
            v_aux[i3+i4*5].R =v[i3*5+i4].R;
            v_aux[i3+i4*5].G =v[i3*5+i4].G;
            v_aux[i3+i4*5].B =v[i3*5+i4].B;
              }

              indice_mediana = vector_mediana(v_aux,10,tipo_distancia);
              x[1].R = v_aux[indice_mediana].R;
              x[1].G = v_aux[indice_mediana].G;
              x[1].B = v_aux[indice_mediana].B;

                     for (i3 = 0; i3 < 5; i3++)
                       for (i4 = 0; i4 < 2; i4++)
              {
            v_aux[i4*5+i3].R =v[i3*5+i4+3].R;
            v_aux[i4*5+i3].G =v[i3*5+i4+3].G;
            v_aux[i4*5+i3].B =v[i3*5+i4+3].B;
              }

              indice_mediana = vector_mediana(v_aux,10,tipo_distancia);
              y[1].R = v_aux[indice_mediana].R;
              y[1].G = v_aux[indice_mediana].G;
              y[1].B = v_aux[indice_mediana].B;

              break;


           case 3: /* FILTRO DE LA MEDIA "ALFA AJUSTADA" */
            /* SE RESERVA MEMORIA PARA EL VECTOR AUXILIAR */
            v_aux = (VECINDARIO *)malloc(10*sizeof(VECINDARIO));

             /* SE PONEN A CERO LAS VECTORES AUXILIARES */
                     for (i3 = 0; i3 < 2; i3++)
              {
            x[i3].R=0.0;
            x[i3].G=0.0;
            x[i3].B=0.0;

            y[i3].R=0.0;
            y[i3].G=0.0;
            y[i3].B=0.0;
              }

                 /* DIRECCION 0 GRADOS */

                     for (i3 = 0; i3 < 10; i3++)
              {
            v_aux[i3].R =v[i3].R;
            v_aux[i3].G =v[i3].G;
            v_aux[i3].B =v[i3].B;
              }

             ordenamiento_distancias_agregadas(v_aux,10,tipo_distancia);
              for (i3 = 0; i3 < 10 * (1-2*alfa); i3++)
            {
                 x[0].R += v_aux[i3].R;
                 x[0].G += v_aux[i3].G;
                 x[0].B += v_aux[i3].B;
            }

                     for (i3 = 0; i3 < 10; i3++)
              {
            v_aux[i3].R =v[i3+15].R;
            v_aux[i3].G =v[i3+15].G;
            v_aux[i3].B =v[i3+15].B;
              }

             ordenamiento_distancias_agregadas(v_aux,10,tipo_distancia);
              for (i3 = 0; i3 < 10 * (1-2*alfa); i3++)
            {
                 y[0].R += v_aux[i3].R;
                 y[0].G += v_aux[i3].G;
                 y[0].B += v_aux[i3].B;
            }


                 /* DIRECCION 90 GRADOS */
                     for (i3 = 0; i3 < 5; i3++)
                       for (i4 = 0; i4 < 2; i4++)
              {
            v_aux[i3+i4*5].R =v[i3*5+i4].R;
            v_aux[i3+i4*5].G =v[i3*5+i4].G;
            v_aux[i3+i4*5].B =v[i3*5+i4].B;
              }

             ordenamiento_distancias_agregadas(v_aux,10,tipo_distancia);
              for (i3 = 0; i3 < 10 * (1-2*alfa); i3++)
            {
                 x[1].R += v_aux[i3].R;
                 x[1].G += v_aux[i3].G;
                 x[1].B += v_aux[i3].B;
                }

                     for (i3 = 0; i3 < 5; i3++)
                       for (i4 = 0; i4 < 2; i4++)
              {
            v_aux[i4*5+i3].R =v[i3*5+i4+3].R;
            v_aux[i4*5+i3].G =v[i3*5+i4+3].G;
            v_aux[i4*5+i3].B =v[i3*5+i4+3].B;
              }

             ordenamiento_distancias_agregadas(v_aux,10,tipo_distancia);
              for (i3 = 0; i3 < 10 * (1-2*alfa); i3++)
            {
                 y[1].R += v_aux[i3].R;
                 y[1].G += v_aux[i3].G;
                 y[1].B += v_aux[i3].B;
            }

            divisor = (int) 10 * (1-2*alfa);
                     for (i3 = 0; i3 < 2; i3++)
              {
            x[i3].R /= divisor;
            x[i3].G /= divisor;
            x[i3].B /= divisor;

            y[i3].R /= divisor;
            y[i3].G /= divisor;
            y[i3].B /= divisor;
              }
          }

      /* SE ESTABLECEN LAS COORDENADAS DE LOS VECTORES DE DIFERENCIAS */
          for (i3 = 0; i3 < 2; i3++)
           {
        d[i3].R=y[i3].R-x[i3].R;
        d[i3].G=y[i3].G-x[i3].G;
        d[i3].B=y[i3].B-x[i3].B;
           }

         }

        else /* VENTANA DE 3 x 3 */
     {
       /* SE ESTABLECEN LAS COORDENADAS DE LOS VECTORES DE DIFERENCIAS */
          d[0].R=v[7].R-v[1].R;
          d[0].G=v[7].G-v[1].G;
          d[0].B=v[7].B-v[1].B;

          d[1].R=v[5].R-v[3].R;
          d[1].G=v[5].G-v[3].G;
          d[1].B=v[5].B-v[3].B;
          }




    /* SE CALCULAN LOS MODULOS DE LOS VECTORES DE DIFERENCIAS */
    for (i3=0; i3 < 2; i3++)
      m[i3] = sqrt(d[i3].R*d[i3].R + d[i3].G*d[i3].G + d[i3].B*d[i3].B);


    /* SE CALCULA EL MAXIMO DE LOS MODULOS */
    if (m[0] >= m[1]) maximo = m[0];
        else   maximo = m[1];

    /* EL VALOR MAXIMO ES ASIGNADO COMO ESTIMACION DE LA MAGNITUD DEL GRADIENTE AL PUNTO CENTRAL */
    resultados[coordenadas] = maximo;
    }

   }
 return;
}




/***********************************************
Esta función aplica el detector de bordes de imágenes en color de Mvd agregadas mutuas
IMPORTANTE: se necesita que la imagen en color tenga los planos separados y consecutivos
************************************************/
int Mvd_agregadas_mutuas (
               float *datos,
               float *resultados,
               long int anchura,
               long int altura,
               int tamano_ventana,
               int tipo_distancia,
               int l_mvd,
               int k_mvd)
{
/* ARRAY DE PIXELES VECINOS */
 VECINDARIO *v;

/* VECTOR MEDIANA         */
VECINDARIO mediana;

 int n,k=3,t;
 int i1,i2,i3,i4;

 /*
   VECTOR UTILIZADO PARA ORDENAR LOS VECINOS
   POR ORDEN CRECIENTE DE DISTANCIAS MUTUAS.

   EL INDICE DEL VECTOR INDICA EL ORDEN, Y EL VALOR
   DEL ELEMENTO EL PIXEL CUYO ORDEN VIENE INDICADO
   POR EL INDICE DE DICHO ELEMENTO.

   POR EJEMPLO, SI orden[2] = 5, EL PIXEL NUMERO 5
   ES EL TERCERO (EL INDICE EMPIEZA EN 0) EN LA SERIE ORDENADA.
*/

 int *orden;

 /* LOS SIGUIENTES 3 VECTORES PERMITEN LOCALIZAR LA POSICION DE       */
 /* LOS PIXELS EN UNA REGION DE nXn  EN LOS PLANOS ROJO, VERDE Y AZUL */
 long int *R;
 long int *G;
 long int *B;

/* PARA POSICIONARNOS EN LA FILA DEL PIXEL ACTUAL */
 long int fila;

/* INDICA LAS COORDENADAS DEL PIXEL ACTUAL */
 long int coordenadas;

 /* anchura*altura                   */
 long int tam_plano;

/* VALOR DEL BORDE DETECTADO */
 float distancia_minima=0.0;

/* AUXILIAR PARA CALCULAR distancia_minima */
 float distancia_actual=0.0;

/*
  DISTANCIAS DE CADA VECINO A LOS DEMAS.

  distancia[i] INDICARA LA SUMA DE LAS
  DISTANCIAS DEL PIXEL i A LOS OCHO PIXELS
  RESTANTES.
*/
 float *distancias;

 /* RESERVA DE MEMORIA PARA LA PUNTOS DEL VECINDARIO */
 switch(tamano_ventana)
  {
   case 1: k = 3;
       break;
   case 2: k = 5;
       break;
   case 3: k = 7;
 }
 n = k * k;

 R = (long int *)malloc(n*sizeof(long int));
 G = (long int *)malloc(n*sizeof(long int));
 B = (long int *)malloc(n*sizeof(long int));

 orden = (int *)malloc(n*sizeof(int));
 distancias = (float *) malloc(n*sizeof(float));

 v = (VECINDARIO *)malloc(n*sizeof(VECINDARIO));

 tam_plano = anchura*altura;

 /* POSICIONES RELATIVAS DENTRO DE LA IMAGEN DE ENTRADA DE LOS PIXELS */
 /* DE UNA REGION mxm  PARA LOS 3 PLANOS (R, G, B)                    */
 /*
   0  1  2  3  4  5  6
   7  8  9 10 11 12 13      0  1  2  3  4
  14 15 16 17 18 19 20      5  6  7  8  9     0 1 2
  21 22 23 24 25 26 27     10 11 12 13 14     3 4 5
  28 29 30 31 32 33 34     15 16 17 18 19     6 7 8
  35 36 37 38 39 40 41     20 21 22 23 24
  42 43 44 45 46 47 48
 */

 t = (k-1)/2;
 i3 = 0;
 for (i1 = -t; i1 < t+1; i1++)
  for(i2 = -t; i2 < t+1; i2++)
  {
   R[i3] = i1 * anchura + i2;
   G[i3] = R[i3] + tam_plano;
   B[i3] = R[i3] + 2 * tam_plano;
   i3++;
  }

/* SE INICIALIZAN A "0" LOS ELEMENTOS DE LAS t PRIMERAS Y ULTIMAS COLUMNAS DE */
 /* LA IMAGEN DE SALIDA                                                */
 /*
        --------------------
       / 0 /   /   /   / 0 /
       --------------------
      / 0 /   /   /   / 0 /
      --------------------
     / 0 /   /   /   / 0 /
     --------------------
    / 0 /   /   /   / 0 /
    --------------------
   / 0 /   /   /   / 0 /
   --------------------

 */

  for (i1 = 0; i1 < altura; i1++)
   for (i2 = 0; i2 < t; i2++)
    {
     fila = i1 * anchura + i2;
     resultados[fila] = 0;
     resultados[fila+anchura - 1 - 2 * i2]=0;
    }


 /* SE INICIALIZAN A 0 LOS ELEMENTOS DE LAS t PRIMERAS Y ULTIMAS FILAS DE   */
 /* LA IMAGEN DE SALIDA, EXCEPTO LOS t PRIMEROS Y ULTIMOS DE CADA FILA, YA */
 /* INICIALIZADOS EN EL BUCLE ANTERIOR.                               */
 /*
        --------------------
       /   / 0 / 0 / 0 /   /
       --------------------
      /   /   /   /   /   /
      --------------------
     /   /   /   /   /   /
     --------------------
    /   /   /   /   /   /
    --------------------
   /   / 0 / 0 / 0 /   /
   --------------------

 */

  for (i1 = 0; i1 < t; i1++)
   for (i2 = t; i2 < anchura - t ; i2++)
    {
     resultados[i1 * anchura + i2 ] = 0;
     resultados[tam_plano - (i1+1) *  anchura + i2]=0;
    }

 /* ESTE BUCLE RECORRE DESDE LA tª HASTA LA altura - t FILA */
 for(i1 = t; i1 < altura - t; i1++)
    {
     /* SE CALCULA LA POSICION DEL PRIMER ELEMENTO DE LA FILA i1 */
     fila = i1*anchura;

     /* ESTE BUCLE RECORRE DESDE LA tª HASTA LA anchura - t COLUMNA */
     for(i2 = t; i2 < anchura - t; i2++)
        {
         /* SE CALCULAN LAS COORDENADAS DEL PIXEL CENTRAL DE LA REGION DE 3x3 */
         coordenadas= fila  + i2;

         /* SE CALCULAN LOS VALORES DE LOS PIXELS DE LA REGION kxk */
         for(i3 = 0; i3 < n; i3++)
            {
             v[i3].R = datos[coordenadas + R[i3]];
             v[i3].G = datos[coordenadas + G[i3]];
             v[i3].B = datos[coordenadas + B[i3]];
            }

         /* PARA CADA PIXEL SE CALCULA EL SUMATORIO DE SU DISTANCIA */
         /* A LOS DEMAS PIXELS                                      */
         for(i3 = 0; i3 < n; i3++)
            {
             /* SE INICIALIZA EL ORDEN DE LOS PIXELS */
             orden[i3] = i3;

             distancias[i3] = 0.0;

              /* SE CALCULA LA SUMA DE DISTANCIAS ENTRE EL PIXEL i3 Y LOS */
             /* PIXELES 0, 1, 2, ... , i3 - 1.                            */
             for(i4 = 0; i4 < i3; i4++)
                {
         switch(tipo_distancia)
          {
            case 1: /* DISTANCIA EUCLIDEA */
                            distancias[i3] += sqrt(
                                             (v[i3].R - v[i4].R)*(v[i3].R - v[i4].R)
                                            +
                                             (v[i3].G - v[i4].G)*(v[i3].G - v[i4].G)
                                            +
                                             (v[i3].B - v[i4].B)*(v[i3].B - v[i4].B)
                                           );
                break;
            case 2:  /* DISTANCIA DE LA CIUDAD DE LOS BLOQUES */
                          distancias[i3] += fabs(v[i3].R - v[i4].R) +
                                      fabs(v[i3].G - v[i4].G) +
                                      fabs(v[i3].B - v[i4].B);
                break;
             case 3: /* DISTANCIA DE AJEDREZ */
                          distancias[i3] += max(
                        max(fabs(v[i3].R-v[i4].R),
                                                     fabs(v[i3].G - v[i4].G)),
                                                fabs(v[i3].B - v[i4].B)
                        );
            }
                }

              /* SE CALCULA LA SUMA DE DISTANCIAS ENTRE EL PIXEL i3 Y LOS */
             /* PIXELES i3 + 1, i3 + 2, ... , 8                           */
             for(i4 = i3 + 1; i4 < n; i4++)
                {
         switch(tipo_distancia)
          {
            case 1: /* DISTANCIA EUCLIDEA */
                            distancias[i3] += sqrt(
                                             (v[i3].R - v[i4].R)*(v[i3].R - v[i4].R)
                                            +
                                             (v[i3].G - v[i4].G)*(v[i3].G - v[i4].G)
                                            +
                                             (v[i3].B - v[i4].B)*(v[i3].B - v[i4].B)
                                           );
                break;
           case 2:  /* DISTANCIA DE LA CIUDAD DE LOS BLOQUES */
                          distancias[i3] += fabs(v[i3].R - v[i4].R) +
                                      fabs(v[i3].G - v[i4].G) +
                                      fabs(v[i3].B - v[i4].B);
                break;
             case 3: /* DISTANCIA DE AJEDREZ */
                          distancias[i3] += max(
                        max(fabs(v[i3].R-v[i4].R),
                                                    fabs(v[i3].G - v[i4].G)),
                                                    fabs(v[i3].B - v[i4].B)
                        );
            }
            }
           }

         /* SE ORDENAN LOS PIXELS VECINOS POR ORDEN CRECIENTE */
         /* DE DISTANCIAS                                     */
         if (ordenacion_shell(distancias,orden,n) == FALSE)
            {
             free(resultados);
             resultados = NULL;

             free(datos);
             datos = NULL;
             return(FALSE);
            }

         /* SE INICIALIZA EL VECTOR MEDIANA */
         mediana.R = 0.0;
         mediana.G = 0.0;
         mediana.B = 0.0;

         /* SE CALCULA EL VECTOR MEDIANA COMO LA MEDIA DE LOS l */
         /* PRIMEROS VECTORES ORDENADOS CRECIENTEMENTE          */
         for(i3 = 0; i3 < l_mvd; i3++)
            {
             mediana.R += v[orden[i3]].R;
             mediana.G += v[orden[i3]].G;
             mediana.B += v[orden[i3]].B;
            }

         mediana.R /= l_mvd;
         mediana.G /= l_mvd;
         mediana.B /= l_mvd;

         distancia_minima = 1E+10;

         /* SE CALCULA EL VALOR DEL BORDE DETECTADO COMO LA DISTANCIA       */
         /* MINIMA ENTRE LOS ULTIMOS k ELEMENTOS SEGUN EL ORDEN ESTABLECIDO */
         /* Y EL VECTOR MEDIANA                                             */
         for(i3 = n -1; i3 > n - 1 - k_mvd ; i3--)
            {
         switch(tipo_distancia)
          {
            case 1: /* DISTANCIA EUCLIDEA */
                       distancia_actual = sqrt
                                        (
                                          (v[orden[i3]].R - mediana.R)
                                           *
                                          (v[orden[i3]].R - mediana.R)
                                         +
                                          (v[orden[i3]].G - mediana.G)
                                           *
                                          (v[orden[i3]].G - mediana.G)
                                         +
                                          (v[orden[i3]].B - mediana.B)
                                           *
                                          (v[orden[i3]].B - mediana.B)
                                        );
            break;
                 case 2:  /* DISTANCIA EN VALOR ABSOLUTO */
                         distancia_actual = fabs(v[orden[i3]].R - mediana.R) +
                        fabs(v[orden[i3]].G - mediana.G) +
                        fabs(v[orden[i3]].B - mediana.B);
            break;
         case 3: /* DISTANCIA DE AJEDREZ */
                         distancia_actual = max(
                    max(fabs(v[orden[i3]].R-mediana.R),
                                        fabs(v[orden[i3]].G-mediana.G)),
                                            fabs(v[orden[i3]].B - mediana.B)
                    );
        }
             if(distancia_actual < distancia_minima)
                distancia_minima = distancia_actual;
            }
         /* SE ASIGNA EL RESULTADO AL PIXEL DE SALIDA EN LAS MISMAS */
         /* COORDENADAS QUE EL PIXEL CENTRAL DE LA REGION mxm       */
         resultados[coordenadas] = distancia_minima;
    }
}

 return(TRUE);
}




/***************************************
Esta función aplica el detector de bordes de imágenes en color de Mvd punto central
IMPORTANTE: se necesita que la imagen en color tenga los planos separados y consecutivos
****************************************/
int Mvd_punto_central(
               float * datos,
               float *resultados,
               long int anchura,
               long int altura,
               int tamano_ventana,
               int tipo_distancia,
               int l_mvd,
               int k_mvd)
{
 /* ARRAY DE PIXELES VECINOS */
 VECINDARIO *v;

/* VECTOR MEDIANA         */
 VECINDARIO mediana;

 int n,t,k=3;

/* VARIABLES PARA LAS COORDENADAS DE COLOR DEL PUNTO CENTRAL */
 int Pr,Pg,Pb;

 int i1,i2,i3;

/*
    VECTOR UTILIZADO PARA ORDENAR LOS VECINOS
    POR ORDEN CRECIENTE DE DISTANCIAS MUTUAS.

    EL INDICE DEL VECTOR INDICA EL ORDEN, Y EL VALOR
    DEL ELEMENTO EL PIXEL CUYO ORDEN VIENE INDICADO
    POR EL INDICE DE DICHO ELEMENTO.

   POR EJEMPLO, SI orden[2] = 5, EL PIXEL NUMERO 5
   ES EL TERCERO (EL INDICE EMPIEZA EN 0) EN LA
   SERIE ORDENADA.
*/

 int *orden;

 /* LOS SIGUIENTES 3 VECTORES PERMITEN LOCALIZAR LA POSICION DE       */
 /* LOS PIXELS EN UNA REGION DE nXn  EN LOS PLANOS ROJO, VERDE Y AZUL */
 long int *R;
 long int *G;
 long int *B;

/* PARA POSICIONARNOS EN LA FILA DEL PIXEL ACTUAL */
 long int fila;

/* INDICA LAS COORDENADAS DEL PIXEL ACTUAL */
 long int coordenadas;

/* anchura*altura                   */
 long int tam_plano;

/* VALOR DEL BORDE DETECTADO */
 float distancia_minima=0.0;

/* AUXILIAR PARA CALCULAR distancia_minima */
 float distancia_actual=0.0;

/*
DISTANCIAS DE CADA VECINO A LOS DEMAS.
   distancia[i] INDICARA LA SUMA DE LAS
   DISTANCIAS DEL PIXEL i A LOS OCHO PIXELS
   RESTANTES.
*/
 float *distancias;

 /* RESERVA DE MEMORIA PARA LA PUNTOS DEL VECINDARIO */
 switch(tamano_ventana)
  {
   case 1: k = 3;
       break;
   case 2: k = 5;
       break;
   case 3: k = 7;
 }
 n = k * k;

 R = (long int *)malloc(n*sizeof(long int));
 G = (long int *)malloc(n*sizeof(long int));
 B = (long int *)malloc(n*sizeof(long int));

 orden = (int *)malloc(n*sizeof(int));
 distancias = (float *) malloc(n*sizeof(float));

 v = (VECINDARIO *)malloc(n*sizeof(VECINDARIO));

 tam_plano = anchura*altura;

 /* POSICIONES RELATIVAS DENTRO DE LA IMAGEN DE ENTRADA DE LOS PIXELS */
 /* DE UNA REGION mxm  PARA LOS 3 PLANOS (R, G, B)                    */
 /*
   0  1  2  3  4  5  6
   7  8  9 10 11 12 13      0  1  2  3  4
  14 15 16 17 18 19 20      5  6  7  8  9     0 1 2
  21 22 23 24 25 26 27     10 11 12 13 14     3 4 5
  28 29 30 31 32 33 34     15 16 17 18 19     6 7 8
  35 36 37 38 39 40 41     20 21 22 23 24
  42 43 44 45 46 47 48
 */

 t = (k-1)/2;
 i3 = 0;
 for (i1 = -t; i1 < t+1; i1++)
  for(i2 = -t; i2 < t+1; i2++)
  {
   R[i3] = i1 * anchura + i2;
   G[i3] = R[i3] + tam_plano;
   B[i3] = R[i3] + 2 * tam_plano;
   i3++;
  }

/* SE INICIALIZAN A "0" LOS ELEMENTOS DE LAS t PRIMERAS Y ULTIMAS COLUMNAS DE */
 /* LA IMAGEN DE SALIDA                                                */
 /*
        --------------------
       / 0 /   /   /   / 0 /
       --------------------
      / 0 /   /   /   / 0 /
      --------------------
     / 0 /   /   /   / 0 /
     --------------------
    / 0 /   /   /   / 0 /
    --------------------
   / 0 /   /   /   / 0 /
   --------------------

 */

  for (i1 = 0; i1 < altura ; i1++)
   for (i2 = 0; i2 < t; i2++)
    {
     fila = i1 * anchura + i2;
     resultados[fila] = 0;
     resultados[fila+anchura - 1 - 2 * i2]=0;
    }


 /* SE INICIALIZAN A 0 LOS ELEMENTOS DE LAS t PRIMERAS Y ULTIMAS FILAS DE   */
 /* LA IMAGEN DE SALIDA, EXCEPTO LOS t PRIMEROS Y ULTIMOS DE CADA FILA, YA */
 /* INICIALIZADOS EN EL BUCLE ANTERIOR.                               */
 /*
        --------------------
       /   / 0 / 0 / 0 /   /
       --------------------
      /   /   /   /   /   /
      --------------------
     /   /   /   /   /   /
     --------------------
    /   /   /   /   /   /
    --------------------
   /   / 0 / 0 / 0 /   /
   --------------------

 */

  for (i1 = 0; i1 < t; i1++)
   for (i2 = t; i2 < anchura - t ; i2++)
    {
     resultados[i1 * anchura + i2] = 0;
     resultados[tam_plano - (i1+1) *  anchura + i2]=0;
    }

 /* ESTE BUCLE RECORRE DESDE LA tª HASTA LA Paltura - t FILA */
 for(i1 = t; i1 < altura - t; i1++)
    {
     /* SE CALCULA LA POSICION DEL PRIMER ELEMENTO DE LA FILA i1 */
     fila = i1*anchura;

     /* ESTE BUCLE RECORRE DESDE LA tª HASTA LA anchura - t COLUMNA */
     for(i2 = t; i2 < anchura - t; i2++)
        {
         /* SE CALCULAN LAS COORDENADAS DEL PIXEL CENTRAL DE LA REGION DE mxm */
         coordenadas= fila  + i2;

         /* SE CALCULAN LOS VALORES DE LOS PIXELS DE LA REGION mxm */
         for(i3 = 0; i3 < n; i3++)
            {
             v[i3].R = datos[coordenadas + R[i3]];
             v[i3].G = datos[coordenadas + G[i3]];
             v[i3].B = datos[coordenadas + B[i3]];
            }

          /* DATOS DEL PUNTO CENTRAL */
      Pr = v[n/2].R;
      Pg = v[n/2].G;
      Pb = v[n/2].B;

         /* SE CALCULAN LAS DISTANCIAS DESDE CADA PIXEL VECINO */
         /* AL PIXEL CENTRAL                                   */
         for(i3 = 0; i3 < n/2; i3++)
            {
             /* SE INICIALIZA EL ORDEN DE CADA PIXEL DEL VECINDARIO */
             orden[i3] = i3;

              switch(tipo_distancia)
               {
                case 1: /* DISTANCIA EUCLIDEA */
                          distancias[i3] = sqrt(
                                        (v[i3].R - Pr)*(v[i3].R - Pr)
                                       +
                                        (v[i3].G - Pg)*(v[i3].G - Pg)
                                       +
                                        (v[i3].B - Pb)*(v[i3].B - Pb)
                                      );
            break;
                case 2: /* DISTANCIA DE LA CIUDAD DE LOS BLOQUES */
                          distancias[i3]  = fabs(v[i3].R - Pr) +
                                  fabs(v[i3].G - Pg) +
                                  fabs(v[i3].B - Pb);
            break;
        case 3: /* DISTANCIA DE AJEDREZ */
                          distancias[i3]  = max(
                        max(fabs(v[i3].R - Pr), fabs(v[i3].G - Pg)),
                            fabs(v[i3].B - Pb)
                        );
        }
            }

         orden[n/2] = n/2;
         distancias[n/2] = 0;

         for(i3 = (n/2)+1; i3 < n; i3++)
            {
             /* SE INICIALIZA EL ORDEN DE CADA PIXEL DEL VECINDARIO */
             orden[i3] = i3;

              switch(tipo_distancia)
               {
                case 1: /* DISTANCIA EUCLIDEA */
                          distancias[i3] = sqrt(
                                        (v[i3].R - Pr)*(v[i3].R - Pr)
                                       +
                                        (v[i3].G - Pg)*(v[i3].G - Pg)
                                       +
                                        (v[i3].B - Pb)*(v[i3].B - Pb)
                                      );
            break;
                case 2: /* DISTANCIA DE LA CIUDAD DE LOS BLOQUES */
                          distancias[i3]  = fabs(v[i3].R - Pr) +
                                  fabs(v[i3].G - Pg) +
                                  fabs(v[i3].B - Pb);
            break;
        case 3: /* DISTANCIA DE AJEDREZ */
                          distancias[i3]  = max(
                        max(fabs(v[i3].R - Pr),
                                                     fabs(v[i3].G - Pg)),
                        fabs(v[i3].B - Pb)
                        );
        }
            }

         /* SE ORDENAN LOS PIXELS VECINOS POR ORDEN CRECIENTE */
         /* DE DISTANCIAS                                     */
         if (ordenacion_shell(distancias,orden,n) == FALSE)
            {
             free(resultados);
             resultados = NULL;

             free(datos);
             datos = NULL;
             return(FALSE);
            }

         /* SE INICIALIZA EL VECTOR MEDIANA */
         mediana.R = 0.0;
         mediana.G = 0.0;
         mediana.B = 0.0;

         /* SE CALCULA EL VECTOR MEDIANA COMO LA MEDIA DE LOS l_mvd */
         /* PRIMEROS VECTORES ORDENADOS CRECIENTEMENTE          */
    /* Como el primero corresponde al punto central, se omite */
         for(i3 = 1; i3 < l_mvd+1; i3++)
            {
             mediana.R += v[orden[i3]].R;
             mediana.G += v[orden[i3]].G;
             mediana.B += v[orden[i3]].B;
            }

         mediana.R /= l_mvd;
         mediana.G /= l_mvd;
         mediana.B /= l_mvd;

         distancia_minima = 1E+10;

         /* SE CALCULA EL VALOR DEL BORDE DETECTADO COMO LA DISTANCIA       */
         /* MINIMA ENTRE LOS ULTIMOS k ELEMENTOS SEGUN EL ORDEN ESTABLECIDO */
         /* Y EL VECTOR MEDIANA                                             */
         for(i3 = n-1; i3 > n - 1 - k_mvd ; i3--)
            {
         switch(tipo_distancia)
        {
          case 1: /* DISTANCIA EUCLIDEA */
                        distancia_actual = sqrt
                                        (
                                          (v[orden[i3]].R - mediana.R)
                                           *
                                          (v[orden[i3]].R - mediana.R)
                                         +
                                          (v[orden[i3]].G - mediana.G)
                                           *
                                          (v[orden[i3]].G - mediana.G)
                                         +
                                          (v[orden[i3]].B - mediana.B)
                                           *
                                          (v[orden[i3]].B - mediana.B)
                                       );
            break;
           case 2: /* DISTANCIA DE LA CIUDAD DE LOS BLOQUES */
                    distancia_actual = fabs(v[orden[i3]].R - mediana.R) +
                                   fabs(v[orden[i3]].G - mediana.G) +
                                   fabs(v[orden[i3]].B - mediana.B);
            break;
           case 3: /* DISTANCIA DE AJEDREZ */
                    distancia_actual =
                                   max(
                    max(fabs(v[orden[i3]].R - mediana.R),
                         fabs(v[orden[i3]].G - mediana.G)),
                                        fabs(v[orden[i3]].B - mediana.B));

        }

             if(distancia_actual < distancia_minima)
                distancia_minima = distancia_actual;
            }

         /* SE ASIGNA EL RESULTADO AL PIXEL DE SALIDA EN LAS MISMAS */
         /* COORDENADAS QUE EL PIXEL CENTRAL DE LA REGION mxm       */
         resultados[coordenadas] = distancia_minima;
        }
    }

 return(TRUE);
}




/********************************************
Esta función aplica el detector de bordes de imágenes en color de Shiozaki
IMPORTANTE: se necesita que la imagen en color tenga los planos separados y consecutivos
*********************************************/
void Shiozaki (float *datos, float *resultados, long int anchura, long int altura)
{

 VECINDARIO v[9];
 VECINDARIO auxiliar, suma, p[9], q, H;
 int R[9], G[9], B[9];
 long int fila, coordenadas, tam_plano;
 int i1, i2, i3;
 float intensidad;

 tam_plano = anchura * altura;

 /* SE ESTABLECEN LAS COORDENADAS RELATIVAS DEL VECINDARIO 3 X 3 */
 /*
        0 1 2
    3 4 5
    6 7 8
 */


  R[0] = - anchura - 1;
  R[1] = - anchura;
  R[2] = - anchura + 1;
  R[3] = - 1;
  R[4] =   0;
  R[5] =   1;
  R[6] =  anchura - 1;
  R[7] =  anchura;
  R[8] =  anchura + 1;

  for (i1 = 0; i1 < 9; i1++)
    {
      G[i1] = R[i1] + tam_plano;
      B[i1] = R[i1] + 2 *tam_plano;
    }

  /* SE PONEN A CERO LOS PUNTOS DE LA PRIMERA Y ULTIMA COLUMNAS */
  for (i1 = 0 ; i1 < altura - 1; i1++)
    {
     fila = i1 * anchura;
     resultados[fila] = 0;
     resultados[fila + anchura - 1] = 0;
    }


  /* SE PONEN A CERO LOS PUNTOS DE LA PRIMERA Y ULTIMA FILAS QUE NO FUERON TRATADOS EN EL BUCLE ANTERIOR */
  for (i1 = 1 ; i1 < anchura ; i1++)
    {
     resultados[i1] = 0;
     resultados[i1 + tam_plano - anchura] = 0;
    }

  /* SE RECORRE DESDE LA SEGUNDA HASTA LA PENULTIMA FILA */
  for (i1 = 1; i1 < altura - 1; i1++)
   {
    fila = i1 * anchura;
    /* SE RECORRE DESDE LA SEGUNDA HASTA LA PENULTIMA COLUMNA */
    for (i2 = 1; i2 < anchura - 1; i2++)
    {
     /* COORDENADAS DEL PUNTO CENTRAL */
     coordenadas = fila + i2;

     /* VALORES DE LOS PUNTOS */
     for (i3 = 0; i3 < 9; i3++)
        {
          v[i3].R  = datos[coordenadas + R[i3]];
          v[i3].G  = datos[coordenadas + G[i3]];
          v[i3].B  = datos[coordenadas + B[i3]];
        }

     /* SE SUMA 1 PARA EVITAR PROBLEMAS CON EL CERO */
     for (i3 = 0; i3 < 9; i3++)
        {
          v[i3].R  += 1;
          v[i3].G  += 1;
          v[i3].B  += 1;
        }

     /* CALCULO DE  LOS VALORES p_X, para X= R, G, B */
     /* CALCULO DE  LOS VALORES p_X, para X= R, G, B */
     suma.R = suma.G = suma.B = 0.0;
     for (i3 = 0; i3 < 9; i3++)
        {
          suma.R += v[i3].R;
          suma.G += v[i3].G;
          suma.B += v[i3].B;
        }

     for (i3 = 0; i3 < 9; i3++)
        {
          p[i3].R= v[i3].R / suma.R;
          p[i3].G = v[i3].G / suma.G;
          p[i3].B = v[i3].B / suma.B;
        }

     /* SE CALCULA EL VALOR H_X, PARA X = R, G, B */
     auxiliar.R =  auxiliar.G =  auxiliar.B = 0.0;
     for (i3 = 0; i3 < 9; i3++)
        {
          auxiliar.R += p[i3].R * log(p[i3].R);
          auxiliar.G += p[i3].G * log(p[i3].G);
          auxiliar.B += p[i3].B * log(p[i3].B);
        }

     H.R =  - auxiliar.R / log(9.0);
     H.G =  - auxiliar.G / log(9.0);
     H.B =  - auxiliar.B / log(9.0);

     /* SE CALCULA EL VALOR DE q_X, para X = R, G, B EN EL PUNTO CENTRAL */
     intensidad = v[4].R + v[4].G + v[4].B;
     q.R = v[4].R / intensidad;
     q.G = v[4].G / intensidad;
     q.B = v[4].B / intensidad;


     /*SE ASIGNA EL VALOR DE LA  "1 - ENTROPIA" AL PUNTO CENTRAL*/
     resultados[coordenadas] = 255.0 * (1.0 - (q.R * H.R + q.G * H.G + q.B * H.B));
    }
   }

 return ;
}




/*******************************************
Esta función aplica el detector de bordes de imágenes en color de Pietikainen
IMPORTANTE: se necesita que la imagen en color tenga los planos separados y consecutivos
********************************************/
void Pietikainen (float *datos, float *resultados, long int anchura, long int altura)
{
 VECINDARIO v[9], maximo, auxiliar;
 float *diferencias;

 int i1, i2, i3;
 int i, j, k;
 int R[9], G[9], B[9];
 long int tam_plano, fila, coordenadas;

 int ***frecuencia_relativa;
 int ***frecuencia_acumulada;


 frecuencia_relativa = (int ***) malloc(256 * sizeof(int **));
 frecuencia_acumulada = (int ***) malloc(256 * sizeof(int **));

 for(i1 = 0; i1 < 256; i1++)
  frecuencia_relativa[i1] = (int **) malloc(256 * sizeof(int *));

 for(i1 = 0; i1 < 256; i1++)
  frecuencia_acumulada[i1] = (int **) malloc(256 * sizeof(int *));

 for(i1 = 0; i1 < 256; i1++)
  for(i2 = 0; i2 < 256; i2++)
   frecuencia_relativa[i1][i2] = (int *) malloc(256 * sizeof(int));

 for(i1 = 0; i1 < 256; i1++)
  for(i2 = 0; i2 < 256; i2++)
   frecuencia_acumulada[i1][i2] = (int *) malloc(256 * sizeof(int));

 for(i1 = 0; i1 < 256; i1++)
  for(i2 = 0; i2 < 256; i2++)
   for(i3 = 0; i3 < 256; i3++)
      frecuencia_relativa[i1][i2][i3] = 0;

 tam_plano = anchura * altura;

 diferencias = (float *) malloc(3*tam_plano*sizeof(float));

/*
  2  1  8
  3  0  7
  4  5  6
*/

 R[0] = 0;
 R[1] = -anchura;
 R[2] = -anchura -1;
 R[3] = -1;
 R[4] = anchura - 1;
 R[5] = anchura;
 R[6] = anchura + 1;
 R[7] = 1;
 R[8] = -anchura +1;

 for (i1 = 0; i1 < 9; i1++)
   {
    G[i1] = R[i1] + tam_plano;
    B[i1] = G[i1] + tam_plano;
   }

 for (i1 = 1; i1 < altura-1; i1++)
 {
  fila = i1 * anchura;
  for (i2 = 1; i2 < anchura-1; i2++)
   {
    coordenadas = fila + i2;

    for(i3 = 0; i3 < 9; i3++)
      {
       v[i3].R = datos[coordenadas+R[i3]];
       v[i3].G = datos[coordenadas+G[i3]];
       v[i3].B = datos[coordenadas+B[i3]];
      }

    maximo.R = fabs(v[0].R-v[1].R);
    maximo.G = fabs(v[0].G-v[1].G);
    maximo.B = fabs(v[0].B-v[1].B);

    for (i3 = 2; i3 < 9; i3++)
     {
      auxiliar.R = fabs(v[0].R-v[i3].R);
      auxiliar.G = fabs(v[0].G-v[i3].G);
      auxiliar.B = fabs(v[0].B-v[i3].B);

      if (maximo.R < auxiliar.R) maximo.R = auxiliar.R;

      if (maximo.G < auxiliar.G) maximo.G = auxiliar.G;

      if (maximo.B < auxiliar.B) maximo.B = auxiliar.B;
     }

    diferencias[coordenadas] = maximo.R;
    diferencias[coordenadas+tam_plano] = maximo.G;
    diferencias[coordenadas+2*tam_plano] = maximo.B;

    i = (int) maximo.R;
    j = (int) maximo.G;
    k = (int) maximo.B;
    frecuencia_relativa[i][j][k] += 1;
   }
 }


 frecuencia_acumulada[255][255][255] = frecuencia_relativa[255][255][255];

 for (i1=254; i1 >=0; i1--)
   frecuencia_acumulada[i1][255][255] = frecuencia_relativa[i1][255][255]
                                      + frecuencia_acumulada[i1+1][255][255];

 for (i1=254; i1 >=0; i1--)
   frecuencia_acumulada[255][i1][255] = frecuencia_relativa[255][i1][255]
                                      + frecuencia_acumulada[255][i1+1][255];

 for (i1=254; i1 >=0; i1--)
   frecuencia_acumulada[255][255][i1] = frecuencia_relativa[255][255][i1]
                                      + frecuencia_acumulada[255][255][i1+1];

 for (i1=254; i1>=0; i1--)
  for (i2=254; i2>=0; i2--)
    frecuencia_acumulada[i1][i2][255] = frecuencia_relativa[i1][i2][255]
                                      + frecuencia_acumulada[i1+1][i2][255]
                                      + frecuencia_acumulada[i1][i2+1][255]
                                      - frecuencia_acumulada[i1+1][i2+1][255];

 for (i1=254; i1>=0; i1--)
  for (i2=254; i2>=0; i2--)
    frecuencia_acumulada[i1][255][i2] = frecuencia_relativa[i1][255][i2]
                                      + frecuencia_acumulada[i1+1][255][i2]
                                      + frecuencia_acumulada[i1][255][i2+1]
                                      - frecuencia_acumulada[i1+1][255][i2+1];

 for (i1=254; i1>=0; i1--)
  for (i2=254; i2>=0; i2--)
    frecuencia_acumulada[255][i1][i2] = frecuencia_relativa[255][i1][i2]
                                      + frecuencia_acumulada[255][i1+1][i2]
                                      + frecuencia_acumulada[255][i1][i2+1]
                                      - frecuencia_acumulada[255][i1+1][i2+1];

 for (i1=254; i1>=0; i1--)
  for (i2=254; i2>=0; i2--)
   for (i3=254; i3>=0; i3--)
    frecuencia_acumulada[i1][i2][i3] = frecuencia_relativa[i1][i2][i3]
                                      + frecuencia_acumulada[i1+1][i2][i3]
                                      + frecuencia_acumulada[i1][i2+1][i3]
                                      + frecuencia_acumulada[i1][i2][i3+1]
                                      - frecuencia_acumulada[i1+1][i2+1][i3]
                                      - frecuencia_acumulada[i1+1][i2][i3+1]
                                      - frecuencia_acumulada[i1][i2+1][i3+1]
                                      + frecuencia_acumulada[i1+1][i2+1][i3+1];



  /* SE PONEN A CERO LOS PUNTOS DE LA PRIMERA Y ULTIMA COLUMNAS */
  for (i1 = 0 ; i1 < altura - 1; i1++)
    {
     fila = i1 * anchura;
     resultados[fila] = 0;
     resultados[fila + anchura - 1] = 0;
    }


  /* SE PONEN A CERO LOS PUNTOS DE LA PRIMERA Y ULTIMA FILAS QUE NO FUERON TRATADOS EN EL BUCLE ANTERIOR */
  for (i1 = 1 ; i1 < anchura ; i1++)
    {
     resultados[i1] = 0;
     resultados[i1 + tam_plano - anchura] = 0;
    }

  /* SE RECORRE DESDE LA SEGUNDA HASTA LA PENULTIMA FILA */
  for (i1 = 1; i1 < altura - 1; i1++)
   {
      fila = i1 * anchura;
      /* SE RECORRE DESDE LA SEGUNDA HASTA LA PENULTIMA COLUMNA */
      for (i2 = 1; i2 < anchura - 1; i2++)
       {
       /* COORDENADAS DEL PUNTO CENTRAL */
         coordenadas = fila + i2;
         i = (int) diferencias[coordenadas];
         j = (int) diferencias[coordenadas+tam_plano];
         k = (int) diferencias[coordenadas+2*tam_plano];

       /*
       SE ASIGNA A CADA PUNTO EL VALOR "1.0 - proporcion"
       */
         resultados[coordenadas] = 1.0 - (float) frecuencia_acumulada[i][j][k]/(float )frecuencia_acumulada[0][0][0];
       }
   }

}


