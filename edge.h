#ifndef EDGE_H
#define EDGE_H


#include "assistant.h"


/*! *************************************************
    \brief Detector de bordes direccional de Lee y Cok
    \brief IMPORTANTE: se necesita que la imagen en color tenga los planos separados y consecutivos

    \param datos       Vector que contiene la información de la imagen en color BGR
    \param resultados  Vector que va a contener al imagen realzada generada por el dectector de bordes
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la iamgen
    \param operador_basico Indica el tipo de máscara para calcular el gradiente
            valor 1:
            valor 2:
            valor 3:
******************************************************/
void Lee_Cok (float *datos, float *resultados, long int anchura, long int altura, int operador_basico);




/*! **************************************************
    \brief Detector de bordes direccional de Scharcanski y Venetsanopoulos

    \param datos       Vector que contiene la información de la imagen en color BGR
    \param resultados  Vector que va a contener al imagen realzada generada por el dectector de bordes
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la iamgen
    \param tamano_ventana Indica el tamaño de la máscara utilizada para la convolución
            valor 1: ventana de 3 x 3
            valor 2: ventana de 5 x 5
            valor 3: ventana de 7 x 7
******************************************************/
void Direccional (float *datos, float *resultados, long int anchura, long int altura, int tamano_ventana);




/*! **************************************************
    \brief Detector de bordes "dv"

    \param datos       Vector que contiene la información de la imagen en color BGR
    \param resultados  Vector que va a contener al imagen realzada generada por el dectector de bordes
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la iamgen
    \param ventana Indica el tamaño de la máscara utilizada para la convolución
            si ventana vale 2 entonces el tamaño de la ventana es de 3 x 3
            en caso contrario, el tamaño de la ventana es de 5 x 5

    \param filtro: tipo de filtro de suavizacion
            1: filtro de la media aritmética
            2: filtro de la mediana
                3: filtro alfa ajustada

    \param alfa: parametro para el filtro de media alfa ajustada
            toma valores en el intervalo [0, 0.5)
                        si filtro toma el valor 3

    \parama tipo_distancia:
            Valor 1: distancia “euclídea”.
            Valor 2: “distancia de la ciudad de los bloques”.
            Valor 3: distancia de “ajedrez”.
*******************************************************/
void Dv(float *datos,
        float *resultados,
        long int anchura,
        long int altura,
        int ventana,
        int filtro,
        float alfa,
        int tipo_distancia);




/*! ***************************************************
    \brief Detector de bordes "dv_hv"

    \param datos       Vector que contiene la información de la imagen en color BGR
    \param resultados  Vector que va a contener al imagen realzada generada por el dectector de bordes
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la iamgen
    \param ventana Indica el tamaño de la máscara utilizada para la convolución
            si ventana vale 2 entonces el tamaño de la ventana es de 3 x 3
            en caso contrario, el tamaño de la ventana es de 5 x 5

    \param filtro: tipo de filtro de suavizacion
            1: filtro de la media aritmética
            2: filtro de la mediana
                3: filtro alfa ajustada

    \param alfa: parametro para el filtro de media alfa ajustada
            toma valores en el intervalo [0, 0.5)
                        si filtro toma el valor 3

    \parama tipo_distancia:
            Valor 1: distancia “euclídea”.
            Valor 2: “distancia de la ciudad de los bloques”.
            Valor 3: distancia de “ajedrez”.
********************************************************/
void Dv_hv(float *datos,
           float *resultados,
           long int anchura,
           long int altura,
           int ventana,
           int filtro,
           float alfa,
           int tipo_distancia);




/*! *****************************************************
    \brief  mvd_agregadas_mutuas - Detecta los bordes de una imagen
*                       mediante el metodo "mvd", el cual esta basado en
*                       la aplicacion de medidas estadisticas a una serie de
*                       vectores ordenados.
*
*       Objetivo: El objetivo de esta funcion es realzar los bordes de una
*                 imagen de entrada en color, produciendose como resultado una
*                 imagen monocromatica. Para ello, se aplica el metodo de detec-
*                 cion de bordes denominado "mvd", en concreto la variante
*                 de las distancias mutuas. Esta consiste en considerar cada
*                 pixel de la imagen en color como un vector de tres componen-
*                 tes (bandas roja, verde y azul), de forma que para cada region
*                 de tamanno mxm pixels de la imagen se calculan la suma de dis-
*                 tancias entre cada pixel (vector) y los pixels (vectores)
*                 restantes de la region. Los vectores correspondientes a los 9
*                 pixels son ordenados en orden creciente por el valor de las
*                 distancias. Despues, aplicando una combinacion lineal entre
*                 los vectores ordenados, se calcula el valor del borde detec-
*                 tado, valor escalar que se asigna al pixel central (de la re-
*                 gion 3x3) en la imagen de salida. La distancia utilizada pue-
*                 de ser la Euclidea o la distancia en valor absoluto.
*

    \param datos       Vector que contiene la información de la imagen en color BGR
    \param resultados  Vector que va a contener al imagen realzada generada por el dectector de bordes
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la iamgen

    \param tamano_ventana Indica el tamaño de la máscara utilizada para la convolución
            valor 1: ventana de 3 x 3
            valor 2: ventana de 5 x 5
            valor 3: ventana de 7 x 7

    \param tipo_distancia Indica el tipo de distancia que se va a cal-
*                                   cular. Puede tomar dos valores: 1 (distan-
*                                   cia Euclidea) y 2 (distancia en valor ab-
*                                   soluto). Si se considera un pixel P1 como un
*                                   vector de tres componentes (R1,G1,B1) y otro
*                                   P2 (R2,G2,B2):
*                                          ____________________________
*                                         /       2         2         2
*                    D.Euclidea(P1,P2): \/ (R2-R1) + (G2-G1) + (B2-B1)
*
*
*                    D.cuidad de los bloques(P1,P2): |R2-R1| + |G2-G1| + |B2-B1|
*
*                    D. ajedrez(P1,P2): max(|R2-R1|,|G2-G1|,|B2-B1|)


    \param l_mvd	Parametro que permite variar en mayor o menor cantidad
*                        la insensibilidad frente al ruido de tipo impulsivo o
*                        doble exponencial. Puede tomar uno de los siguientes
*                        valores: 1,2,3. A mayor valor se consiguen mejores re-
*                        sultados frente al ruido.
*

    \param k_mvd 	Parametro que permite variar en mayor o menor cantidad
*                        la insensibilidad frente al ruido de tipo Gaussiano.
*                        Puede tomar uno de los siguientes valores: 1,2,3. A ma-
*                        yor valor de k se consiguen mejores resultados frente
*                        al ruido.


*
*       Funciones a las que llama:
*
*       + ordenacion_shell: Utilizada para ordenar una serie de vectores en
*                           orden creciente. Para ello se utiliza el algoritmo
*                           Shell de ordenacion.
*
*       + sqrt: Calcula la raiz cuadrada de su argumento.
*
*       + fabs: Calcula el valor absoluto de su argumento.
*

*********************************************************/
int Mvd_agregadas_mutuas (
               float * datos,
               float *resultados,
               long int anchura,
               long int altura,
               int tamano_ventana,
               int tipo_distancia,
               int l_mvd,
               int k_mvd);




/*! ********************************************************
    \brief Nombre de la rutina: mvd_punto_central
            Detecta los bordes de una imagen
*                       mediante el metodo R'ordering, el cual esta basado en
*                       la aplicacion de medidas estadisticas a una serie de
*                       vectores ordenados.
*
*       Objetivo: El objetivo de esta funcion es realzar los bordes de una
*                 imagen de entrada en color, produciendose como resultado una
*                 imagen monocromatica. Para ello, se aplica el metodo de detec-
*                 cion de bordes denominado R'ordering, en concreto la varian-
*                 te de las distancias al pixel central. Esta consiste en consi-
*                 derar cada pixel de la imagen en color como un vector de tres
*                 componentes (bandas roja, verde y azul), de forma que se calcu-
*                 lan las distancias de los pixels o vectores de un vecindario de
*                 orden 8 respecto al pixel (vector) central de dicho vecinda-
*                 rio. Los vectores correspondientes a los 8 vecinos son orde-
*                 nados en orden creciente por el valor de las distancias. Des-
*                 pues, aplicando una combinacion lineal entre los vectores or-
*                 denados, se calcula el valor del borde detectado, valor esca-
*                 lar que se asigna al pixel central en la imagen de salida. La
*                 distancia utilizada puede ser la Euclidea o la distancia en
*                 valor absoluto.
*

*

    \param datos       Vector que contiene la información de la imagen en color BGR
    \param resultados  Vector que va a contener al imagen realzada generada por el dectector de bordes
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la iamgen

    \param tamano_ventana Indica el tamaño de la máscara utilizada para la convolución
            valor 1: ventana de 3 x 3
            valor 2: ventana de 5 x 5
            valor 3: ventana de 7 x 7

    \param tipo_distancia Indica el tipo de distancia que se va a cal-
*                                   cular. Puede tomar dos valores: 1 (distan-
*                                   cia Euclidea) y 2 (distancia en valor ab-
*                                   soluto). Si se considera un pixel P1 como un
*                                   vector de tres componentes (R1,G1,B1) y otro
*                                   P2 (R2,G2,B2):
*                                          ____________________________
*                                         /       2         2         2
*                    D.Euclidea(P1,P2): \/ (R2-R1) + (G2-G1) + (B2-B1)
*
*
*                    D.cuidad de los bloques(P1,P2): |R2-R1| + |G2-G1| + |B2-B1|
*
*                    D. ajedrez(P1,P2): max(|R2-R1|,|G2-G1|,|B2-B1|)


    \param l_mvd	Parametro que permite variar en mayor o menor cantidad
*                        la insensibilidad frente al ruido de tipo impulsivo o
*                        doble exponencial. Puede tomar uno de los siguientes
*                        valores: 1,2,3. A mayor valor se consiguen mejores re-
*                        sultados frente al ruido.
*

    \param k_mvd 	Parametro que permite variar en mayor o menor cantidad
*                        la insensibilidad frente al ruido de tipo Gaussiano.
*                        Puede tomar uno de los siguientes valores: 1,2,3. A ma-
*                        yor valor de k se consiguen mejores resultados frente
*                        al ruido.


*
*       Funciones a las que llama:
*
*       + ordenacion_shell: Utilizada para ordenar una serie de vectores en
*                           orden creciente. Para ello se utiliza el algoritmo
*                           Shell de ordenacion.
*
*       + sqrt: Calcula la raiz cuadrada de su argumento.
*
*       + fabs: Calcula el valor absoluto de su argumento.
*

********************************************************/
int Mvd_punto_central(
               float * datos,
               float *resultados,
               long int anchura,
               long int altura,
               int tamano_ventana,
               int tipo_distancia,
               int l_mvd,
               int k_mvd);




/*! *****************************************************
    \brief Detector de bordes de Shiozaki

    \param datos       Vector que contiene la información de la imagen en color BGR
    \param resultados  Vector que va a contener al imagen realzada generada por el dectector de bordes
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la iamgen
*********************************************************/
void Shiozaki (float *datos, float *resultados, long int anchura, long int altura);




/*! *****************************************************
    \brief Detector de bordes de Pietikainen

    \param datos       Vector que contiene la información de la imagen en color BGR
    \param resultados  Vector que va a contener al imagen realzada generada por el dectector de bordes
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la iamgen
*********************************************************/
void Pietikainen (float *datos, float *resultados, long int anchura, long int altura);

#endif // EDGE_H
