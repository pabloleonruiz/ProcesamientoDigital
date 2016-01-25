#include "assistant.h"


/*! ***************************************
    \brief Umbralizador manual

    \param datos       Vector que contiene la información de la imagen realzada
    \param resultados  Vector que va a contener al imagen umbralizada generada
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la imagen
    \param umbral      Indica el umbral seleccionado
*******************************************/
void Manual (float *datos, float *resultados, long int anchura, long int altura, float umbral);




/*! ****************************************
    \brief Umbralizador porcentual

    \param datos       Vector que contiene la información de la imagen realzada
    \param resultados  Vector que va a contener al imagen umbralizada generada
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la imagen
    \param porc        Indica el porcentaje seleccionado
********************************************/
void Porcentual (float *datos, float *resultados, long int anchura, long int altura, float porc);




/*! *****************************************
    \brief Umbralizador por Histéresis

    \param datos         Vector que contiene la información de la imagen realzada
    \param resultados    Vector que va a contener al imagen umbralizada generada
    \param anchura	     Anchura de la imagen
    \param altura	     Altura de la imagen
    \param umbral_mayor  Contiene el umbral mayor seleccionado
    \param umbral_menor  Contiene el umbral menor seleccionado
*********************************************/
void Histeresis (float *datos, float *resultados, long int anchura, long int altura, float umbral_mayor, float umbral_menor);




/*! ******************************************
    \brief Umbralizador Otsu

    \param datos       Vector que contiene la información de la imagen realzada
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la immgen
**********************************************/
float Otsu(float *datos, long int anchura, long int altura);





///////////////////////////////////////////////////
//////               NUEVOS                   /////
///////////////////////////////////////////////////

/*! ******************************************
    \brief Normalizador (1,1) brillo-densidad

    \param datos       Vector que contiene la información de la imagen realzada
    \param f           Vector que va a contener las densidades de cada valor de brillo
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la immgen
**********************************************/
void Normalizar1_1 (float *datos, float *f, long int anchura, long int altura);




/*! ******************************************
    \brief Umbralizador Proximidad al punto (max/N,0.0)

    \param datos       Vector que contiene la información de la imagen realzada
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la immgen
**********************************************/
float* Proximidad (float *datos, long int anchura, long int altura);




/*! *******************************************
    \brief Umbralizador Más distancia al punto (1.0,1.0)

    \param datos       Vector que contiene la información de la imagen realzada
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la immgen
***********************************************/
float Distante (float *datos, long int anchura, long int altura);




/*! ********************************************
    \brief Umbralizador Menor distancia bajo la diagonal

    \param datos       Vector que contiene la información de la imagen realzada
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la immgen
************************************************/
float Diagonal (float *datos, long int anchura, long int altura);




/*! ********************************************
    \brief Umbralizador Adaptativo

    \param datos       Vector que contiene la información de la imagen realzada
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la immgen
************************************************/
float* Adaptativo (float *datos, long int anchura, long int altura);




/*! *********************************************
    \brief Umbralizador Semi-adaptativo

    \param datos       Vector que contiene la información de la imagen realzada
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la immgen
*************************************************/
float* Semi_adaptativo (float *datos, long int anchura, long int altura);




/*! *********************************************
    \brief Umbralizador Rosin normalizado

    \param datos       Vector que contiene la información de la imagen realzada
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la immgen
*************************************************/
float Rosin_normalizado (float *datos, long int anchura, long int altura);




/*! *********************************************
    \brief Umbralizador Rosin

    \param datos       Vector que contiene la información de la imagen realzada
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la immgen
*************************************************/
int Rosin (float *datos, long int anchura, long int altura);





///////////////////////////////////////////////////
//////       ACUMULATIVOS E INVERSOS          /////
///////////////////////////////////////////////////

/*! *********************************************
    \brief Umbralizador Proximidad al punto (max/N,0.0) acumulado inverso normalizado

    \param datos       Vector que contiene la información de la imagen realzada
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la immgen
*************************************************/
float* Proximidad_Acumulado_Inverso (float *datos, long int anchura, long int altura);




/*! **********************************************
    \brief Umbralizador Más distancia al punto (1.0,1.0) acumulado inverso normalizado

    \param datos       Vector que contiene la información de la imagen realzada
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la immgen
**************************************************/
float Distante_Acumulado_Inverso (float *datos, long int anchura, long int altura);




/*! ************************************************
    \brief Umbralizador Menor distancia bajo la diagonal acumulado inverso normalizado

    \param datos       Vector que contiene la información de la imagen realzada
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la immgen
****************************************************/
float Diagonal_Acumulado_Inverso  (float *datos, long int anchura, long int altura);




/*! *************************************************
    \brief Umbralizador Adaptativo acumulado inverso normalizado

    \param datos       Vector que contiene la información de la imagen realzada
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la immgen
*****************************************************/
float* Adaptativo_Acumulado_Inverso (float *datos, long int anchura, long int altura);




/*! **************************************************
    \brief Umbralizador Semi-adaptativo acumulado inverso normalizado

    \param datos       Vector que contiene la información de la imagen realzada
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la immgen
******************************************************/
float* Semi_adaptativo_Acumulado_Inverso (float *datos, long int anchura, long int altura);




/*! **************************************************
    \brief Umbralizador Rosin normalizado acumulado inverso normalizado

    \param datos       Vector que contiene la información de la imagen realzada
    \param anchura	   Anchura de la imagen
    \param altura	   Altura de la immgen
******************************************************/
float Rosin_normalizado_Acumulado_Inverso (float *datos, long int anchura, long int altura);






/*! **************************************************
    \brief Transforma el histograma para que sea acumulativo inverso y normalizado

    \param f       Vector que contiene la información del histograma
******************************************************/
void Transformar_Acumulado_Inverso_Normalizado(float *f);


