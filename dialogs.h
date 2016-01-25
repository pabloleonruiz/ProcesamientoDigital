#ifndef DIALOGS_H
#define DIALOGS_H


#include <QDialog>
#include <QWidget>
#include <iostream>
#include <sstream>
#include <string>


#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

#include "assistant.h"
#include "mainwindow.h"
#include "subwindow.h"


using namespace cv;
using namespace std;

QT_BEGIN_NAMESPACE
class QLabel;
class QSpinBox;
class QDoubleSpinBox;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QGridLayout;
class QGroupBox;
class QComboBox;
QT_END_NAMESPACE



/***********************************************/
/***  INICIO CLASE DIALOGO NORMALIZAR        ***/
/***********************************************/

class Dialogo_Normalizar : public QDialog
{
    Q_OBJECT

public:
    Dialogo_Normalizar(QWidget *parent = 0);
    ~Dialogo_Normalizar();

public slots:
    void okPulsado();
    int resultado();

private:
    QLabel *text;
    QSpinBox *valor;
    QPushButton *ok;
    QHBoxLayout *datos, *botones;
    QVBoxLayout *total;

    int operador;
};


/*!
DETECTORES
*/

/***********************************************/
/***  INICIO CLASE DIALOGO DETECTOR LEE COK  ***/
/***********************************************/

class Dialogo_Lee_Cok : public QDialog
{
    Q_OBJECT

public:
    Dialogo_Lee_Cok(QWidget *parent = 0);
    ~Dialogo_Lee_Cok();

public slots:
    void okPulsado();
    int resultado();

private:
    QLabel *text;
    QSpinBox *valor;
    QPushButton *ok;
    QHBoxLayout *datos, *botones;
    QVBoxLayout *total;

    int operador;
};




/*************************************************/
/*** INICIO CLASE DIALOGO DETECTOR DIRECCIONAL ***/
/*************************************************/

class Dialogo_Direccional : public QDialog
{
    Q_OBJECT

public:
    Dialogo_Direccional(QWidget *parent = 0);
    ~Dialogo_Direccional();

public slots:
    void okPulsado();
    int resultado();

private:
    QLabel *text, *textDesc;
    QSpinBox *valor;
    QPushButton *ok;

    QHBoxLayout *datos, *botones;
    QVBoxLayout *casos, *total;

    int operador;
};




/**************************************************/
/***  INICIO CLASE DIALOGO DETECTOR DV y DV-HV  ***/
/**************************************************/

class Dialogo_Dv : public QDialog
{
    Q_OBJECT

public:
    Dialogo_Dv(QString &titulo, int *d, float a, QWidget *parent = 0);
    ~Dialogo_Dv();

public slots:
    void okPulsado();
    int* resultado_datos();
    float resultado_alfa();

private:
    QLabel *text, *text1, *text2, *text3;
    QLabel *textDesc, *textDesc1, *textDesc2, *textDesc3;
    QSpinBox *valor, *valor1, *valor3;
    QDoubleSpinBox *valor2;
    QPushButton *ok;

    QGroupBox *ventana, *filtro, *alfaDialog, *distancia;

    QHBoxLayout *dato1, *dato3, *dato5, *dato7, *botones;
    QVBoxLayout *dato2, *dato4, *dato6, *dato8, *total;

    QGridLayout *grid;

    bool opc;
    int datos[3];
    float alfa;

};




/*****************************************************/
/*CLASE DIALOGO DETECTOR MVD (PARA LAS DOS VERSIONES)*/
/*****************************************************/

class Dialogo_Mvd : public QDialog
{
    Q_OBJECT

public:
    Dialogo_Mvd(QString &titulo, int *d, QWidget *parent = 0);
    ~Dialogo_Mvd();

public slots:
    void okPulsado();
    int* resultado_datos();

private:
    QLabel *text, *text1, *text2, *text3;
    QLabel *textDesc, *textDesc1, *textDesc2, *textDesc3;
    QSpinBox *valor, *valor1, *valor2, *valor3;
    QPushButton *ok;

    QGroupBox *ventana, *distancia, *mediana, *borde;

    QHBoxLayout *dato1, *dato3, *dato5, *dato7, *botones;
    QVBoxLayout *dato2, *dato4, *dato6, *dato8, *total;

    QGridLayout *grid;

    int datos[4];

};





/*!
UMBRALIZADORES
*/

/*******************************************/
/***  INICIO CLASE DIALOGO UMBR. MANUAL  ***/
/*******************************************/

class Dialogo_Umbr_Manual : public QDialog
{
    Q_OBJECT

public:
    Dialogo_Umbr_Manual(QWidget *parent = 0);
    ~Dialogo_Umbr_Manual();

public slots:
    void okPulsado();
    float resultado();

private:
    QLabel *text;
    QDoubleSpinBox *valor;
    QPushButton *ok;
    QHBoxLayout *datos, *botones;
    QVBoxLayout *total;

    float operador;
};




/***********************************************/
/***  INICIO CLASE DIALOGO UMBR. PORCENTUAL  ***/
/***********************************************/

class Dialogo_Umbr_Porcentual : public QDialog
{
    Q_OBJECT

public:
    Dialogo_Umbr_Porcentual(QWidget *parent = 0);
    ~Dialogo_Umbr_Porcentual();

public slots:
    void okPulsado();
    float resultado();

private:
    QLabel *text;
    QDoubleSpinBox *valor;
    QPushButton *ok;
    QHBoxLayout *datos, *botones;
    QVBoxLayout *total;

    float operador;
};




/******************************************/
/***  INICIO CLASE DIALOGO HISTERESIS   ***/
/******************************************/

class Dialogo_Histeresis : public QDialog
{
    Q_OBJECT

public:
    Dialogo_Histeresis(QWidget *parent = 0);
    ~Dialogo_Histeresis();

public slots:
    void okPulsado();
    float resultado_mayor();
    float resultado_menor();

private:
    QLabel *text, *text1;
    QDoubleSpinBox *valor, *valor1;
    QPushButton *ok;
    QHBoxLayout *datos, *datos1, *botones;
    QVBoxLayout *total;
    QGroupBox *mayorGrupo, *menorGrupo;

    float mayor, menor, aux_mayor, aux_menor;
};



/******************************************/
/***  INICIO CLASE DIALOGO LINEAR       ***/
/******************************************/

class Dialogo_Linear : public QDialog
{
    Q_OBJECT

public:
    Dialogo_Linear(QWidget *parent = 0);
    ~Dialogo_Linear();

public slots:
    void okPulsado();
    double resultado_mayor();
    double resultado_menor();
    double resultado_inicial();
    bool resultado_recortar();
    float resultado_pendiente();

private:
    QLabel *text, *text1, *text2, *text3;
    QDoubleSpinBox *valor3;
    QSpinBox   *valor, *valor1, *valor2;
    QPushButton *ok;
    QHBoxLayout *datos, *datos1,*datos2,*datos3, *botones;
    QVBoxLayout *total;
    QGroupBox *mayorGrupo, *menorGrupo, *inicioGrupo, *pendienteGrupo;
    QCheckBox *recortar;

    double  mayor, menor, aux_mayor, aux_menor, inicio, inicial;
    float pendiente, pend;
    bool rec;
};

/*!
INICIO CLASE DIALOGO GENERAL
*/

class Dialogo_General : public QDialog
{
    Q_OBJECT

public:
    Dialogo_General(QString &umbral, QString &umbral1, QWidget *parent = 0);
    ~Dialogo_General();

public slots:
    void okPulsado();

private:
    QLabel *text;
    QPushButton *ok;
    QHBoxLayout *texto, *boton;
    QVBoxLayout *total;
};


/***********************************************/
/***  INICIO CLASE DIALOGO HISTOGRAM SLIDE   ***/
/***********************************************/

class Dialogo_Slide : public QDialog
{
    Q_OBJECT

public:
    Dialogo_Slide(QWidget *parent = 0);
    ~Dialogo_Slide();

public slots:
    void okPulsado();
    int resultado();

private:
    QLabel *text;
    QSpinBox *valor;
    QPushButton *ok;
    QHBoxLayout *datos, *botones;
    QVBoxLayout *total;

    int operador;
};

/*************************************************/
/***   INICIO CLASE DIALOGO HISTOGRAM SHRINK  ***/
/*************************************************/
class Dialogo_Shrink : public QDialog
{
    Q_OBJECT

public:
    Dialogo_Shrink(QWidget *parent = 0);
    ~Dialogo_Shrink();

public slots:
    void okPulsado();
    float resultado_mayor();
    float resultado_menor();

private:
    QLabel *text, *text1;
    QDoubleSpinBox *valor, *valor1;
    QPushButton *ok;
    QHBoxLayout *datos, *datos1, *botones;
    QVBoxLayout *total;
    QGroupBox *mayorGrupo, *menorGrupo;

    float mayor, menor, aux_mayor, aux_menor;
};

/*************************************************/
/***   INICIO CLASE DIALOGO HISTOGRAM STRETCH  ***/
/*************************************************/
class Dialogo_Stretch : public QDialog
{
    Q_OBJECT

public:
    Dialogo_Stretch(QWidget *parent = 0);
    ~Dialogo_Stretch();

public slots:
    void okPulsado();
    float resultado_mayor();
    float resultado_menor();
    float resultado_bajo();
    float resultado_alto();


private:
    QLabel *text, *text1, *text2, *text3;
    QDoubleSpinBox *valor, *valor1, *valor2, *valor3;
    QPushButton *ok;
    QHBoxLayout *datos, *datos1, *datos2, *datos3, *botones;
    QVBoxLayout *total;
    QGroupBox *mayorGrupo, *menorGrupo, *menorClip,*mayorClip;

    float mayor, menor, aux_mayor, aux_menor, low_clip, high_clip,bajo,alto;
};

/*************************************************/
/***   INICIO CLASE DIALOGO ADAPTATIVE CONTRAST **/
/*************************************************/
class Dialogo_Adaptative : public QDialog
{
    Q_OBJECT

public:
    Dialogo_Adaptative(QWidget *parent = 0);
    ~Dialogo_Adaptative();

public slots:
    void okPulsado();
    float resultado_k1();
    float resultado_k2();
    float resultado_size();
    float resultado_min();
    float resultado_max();


private:
    QLabel *text, *text1, *text2, *text3, *text4;
    QDoubleSpinBox *valor, *valor1, *valor3, *valor4;
    QSpinBox *valor2;
    QPushButton *ok;
    QHBoxLayout *datos, *datos1, *datos2, *datos3, *datos4, *botones;
    QVBoxLayout *total;
    QGroupBox *k1Grupo, *k2Grupo, *sizeGrupo,*minGrupo,*maxGrupo;

    float k1, k2, min, max;
    int size;
};


/**************************************/
/*** INICIO CLASE DIALOGO COLORMAP  ***/
/**************************************/

class Dialogo_ColorMap : public QDialog
{
    Q_OBJECT

public:
    Dialogo_ColorMap(QWidget *parent = 0);
    ~Dialogo_ColorMap();

public slots:
    void okPulsado();
    int resultado();

private:
    QLabel *text, *textDesc;
    QSpinBox *valor;
    QPushButton *ok;

    QHBoxLayout *datos, *botones;
    QVBoxLayout *casos, *total;

    int operador;
};


/*******************************************************/
/***  INICIO CLASE DIALOGO HIGH FREQUENCY EMPHASIS   ***/
/*******************************************************/

class Dialogo_High : public QDialog
{
    Q_OBJECT

public:
    Dialogo_High(QWidget *parent = 0);
    ~Dialogo_High();

public slots:
    void okPulsado();
    int resultado_size();
    bool resultado_dc();
    int resultado_cutoff();
    float resultado_alfa();
    int resultado_order();

private:
    QLabel *text, *text1, *text2, *text3;
    QDoubleSpinBox *valor3;
    QSpinBox   *valor, *valor1, *valor2;
    QPushButton *ok;
    QHBoxLayout *datos, *datos1,*datos2,*datos3, *botones;
    QVBoxLayout *total;
    QGroupBox *sizeGrupo, *dcGrupo, *cutoffGrupo, *alfaGrupo, *orderGrupo;
    QCheckBox *recortar;

    float alfa;
    bool dc;
    int cutoff, size, order;
};

/*****************************************/
/***  INICIO CLASE DIALOGO MORAVEC     ***/
/*****************************************/

class Dialogo_Moravec : public QDialog
{
    Q_OBJECT

public:
    Dialogo_Moravec(QWidget *parent = 0);
    ~Dialogo_Moravec();

public slots:
    void okPulsado();
    float resultado();

private:
    QLabel *text;
    QDoubleSpinBox *valor;
    QPushButton *ok;
    QHBoxLayout *datos, *botones;
    QVBoxLayout *total;

    float operador;
};

/****************************************/
/***  INICIO CLASE DIALOGO SMOOTH     ***/
/****************************************/

class Dialogo_Smooth : public QDialog
{
    Q_OBJECT

public:
    Dialogo_Smooth(QWidget *parent = 0);
    ~Dialogo_Smooth();

public slots:
    void okPulsado();
    int resultado();

private:
    QLabel *text;
    QSpinBox *valor;
    QPushButton *ok;
    QHBoxLayout *datos, *botones;
    QVBoxLayout *total;

    int operador;
};

/****************************************/
/***  INICIO CLASE DIALOGO KUWAHARA   ***/
/****************************************/

class Dialogo_Kuwahara : public QDialog
{
    Q_OBJECT

public:
    Dialogo_Kuwahara(QWidget *parent = 0);
    ~Dialogo_Kuwahara();

public slots:
    void okPulsado();
    int resultado();

private:
    QLabel *text;
    QSpinBox *valor;
    QPushButton *ok;
    QHBoxLayout *datos, *botones;
    QVBoxLayout *total;

    int operador;
};

/********************************************/
/***   INICIO CLASE DIALOGO HOMOMORPHIC   ***/
/********************************************/
class Dialogo_Homomorphic : public QDialog
{
    Q_OBJECT

public:
    Dialogo_Homomorphic(QWidget *parent = 0);
    ~Dialogo_Homomorphic();

public slots:
    void okPulsado();
    float resultado_upper();
    float resultado_lower();
    int resultado_cutoff();



private:
    QLabel *text, *text1, *text2;
    QDoubleSpinBox *valor, *valor1;
    QSpinBox *valor2;
    QPushButton *ok;
    QHBoxLayout *datos, *datos1, *datos2, *botones;
    QVBoxLayout *total;
    QGroupBox *upperGrupo, *lowerGrupo, *cutoffGrupo;

    float upper,lower;
    int cutoff;
};

/***************************************/
/***   INICIO CLASE DIALOGO UNSHARP  ***/
/***************************************/
class Dialogo_Unsharp : public QDialog
{
    Q_OBJECT

public:
    Dialogo_Unsharp(QWidget *parent = 0);
    ~Dialogo_Unsharp();

public slots:
    void okPulsado();
    int resultado_mayor();
    int resultado_menor();
    float resultado_bajo();
    float resultado_alto();


private:
    QLabel *text, *text1, *text2, *text3;
    QDoubleSpinBox *valor2, *valor3;
    QSpinBox *valor,*valor1;
    QPushButton *ok;
    QHBoxLayout *datos, *datos1, *datos2, *datos3, *botones;
    QVBoxLayout *total;
    QGroupBox *mayorGrupo, *menorGrupo, *menorClip,*mayorClip;

    float bajo,alto;
    int mayor, menor;
};

#endif // DIALOGS_H
