#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QApplication>
#include <QWebView>
#include <QPrintDialog>


#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>


using namespace cv;


#include <iostream>
#include <sstream>
#include <string>


#ifndef QT_NO_PRINTER
#include <QPrinter>
#endif

#include "helpwindow.h"
#include "imageconverter.h"
#include "dialogs.h"
#include "histwindow.h"
#include "mainwindow.h"
#include "enhancement.h"
#include "edge.h"
#include "thresholding.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QLabel;
class QScrollArea;
class QScrollBar;
class QWebView;
class Dialogo_Normalizar;
class Dialogo_Lee_Cok;
class Dialogo_Direccional;
class Dialogo_Dv;
class Dialogo_Mvd;
class Dialogo_Umbr_Manual;
class Dialogo_Umbr_Porcentual;
class Dialogo_Histeresis;
class Dialogo_General;
class Dialogo_Linear;
class Dialogo_Slide;
class Dialogo_Shrink;
class Dialogo_Stretch;
class Dialogo_Adaptative;
class Dialogo_ColorMap;
class Dialogo_High;
class Dialogo_Moravec;
class Dialogo_Smooth;
class Dialogo_Kuwahara;
class Dialogo_Homomorphic;
class Dialogo_Unsharp;
QT_END_NAMESPACE


class subwindow: public QMainWindow
{
    Q_OBJECT

public:
    subwindow( const QString &fileName, const QString &algoritName);
    subwindow(const QString &fileName, const QString &algoritName, const Mat &imagen);

private slots:
    void print();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    void contents();
    void about();

    void histogram();
    void normalizar2();
    void save();
    void leecock();
    void scharcanski();
    void dv();
    void dvhd();
    void mvdagre();
    void mvdcentral();
    void shiozaki();
    void pieti();

    void manual();
    void porcentual();
    void histeresis();
    void otsu();
    void rosin();
    void rosinNor();
    void rosinNorAcu();
    void proxi();
    void proxiAcu();
    void dist();
    void distAcu();
    void menor();
    void menorAcu();
    void adap();
    void adapAcu();
    void semi();
    void semiAcu();

    void lineargray();
    void slide();
    void shrink();
    void stretch();
    void adaptive();
    void colorMap();

    void highpass();
    void highFrequency();
    void moravec();
    void homomorphic();
    void unsharp();
    void sharpening();

    void meanFilter();
    void medianFilter();
    void gaussFilter();
    void kuwahara();

private:
    void init();
    void activategray();
    void activateColor();
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    void adjustForCurrentFile(const QString& filePath);
    void savefile(const QString &titulo, Mat &imagen);
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor;
    QString currentFilePath;
    QString algoritmo;
    QString filename;
    QString salida;
    QString nombreDetector;

    Mat Img;
    Mat resultadoImg;
    float *result;

    int op_LeeCok, op_Direccional;
    int *datos_Dv, *datos_Hv;
    float alfa_Dv, alfa_Hv;
    int *datos_Mvd_Am, *datos_Mvd_Pc;
    float umbral, umbral_mayor, umbral_menor;
    float porcentaje;
    float umbralOtsu;
    float umbralRosin;
    float  slope;
    double start, end, inicial;

    //Datos obtenidos de los métodos normalizados
    float result_rosin_norm;
    float *result_prox;
    float result_dist;
    float result_diag;
    float *result_adap;
    float *result_semi;

    Dialogo_Normalizar *dialogo13;
    //Dialogos detectores
    Dialogo_Lee_Cok *dialogo1;
    Dialogo_Direccional *dialogo2;
    Dialogo_Dv *dialogo3;
    Dialogo_Mvd *dialogo4;

    //Dialogos umbralizadores
    Dialogo_Umbr_Manual *dialogo5;
    Dialogo_Umbr_Porcentual *dialogo6;
    Dialogo_Histeresis *dialogo7;
    Dialogo_General *dialogo8;

    //Dialogos realce
    Dialogo_Linear *dialogo9;
    Dialogo_Slide *dialogo10;
    Dialogo_Shrink *dialogo11;
    Dialogo_Stretch *dialogo12;
    Dialogo_Adaptative *dialogo14;
    Dialogo_ColorMap *dialogo15;
    Dialogo_High *dialogo16;
    Dialogo_Moravec *dialogo17;
    Dialogo_Smooth *dialogo18;
    Dialogo_Kuwahara *dialogo19;
    Dialogo_Homomorphic *dialogo20;
    Dialogo_Unsharp *dialogo21;


#ifndef QT_NO_PRINTER
    QPrinter printer;
#endif

    QMenu *fileMenu;
    QMenu* recentFilesMenu;
    QMenu *viewMenu;
    QMenu *enhancementMenu;
    QMenu *subenhancementMenu;
    QMenu *subenhancementMenu2;
    QMenu *subenhancementMenu3;
    QMenu *subenhancementMenu4;

    QMenu *thresholdingMenu;
    QMenu *helpMenu;
    QToolBar *fileToolBar;
    QToolBar *viewToolBar;

    QAction *saveAct;
    QAction *closeAct;
    QAction *exitAct;
    QAction *printAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;

    QAction *histogramAct;
    QAction *normalizarAct;


//Acciones detector de bordes
    QAction *leecockAct;
    QAction *scharcanskiAct;
    QAction *dvAct;
    QAction *dvhdAct;
    QAction *mvdagreAct;
    QAction *mvdcentralAct;
    QAction *shiozakiAct;
    QAction *pietiAct;

//Acciones umbralización
    QAction *manualAct;
    QAction *porcentualAct;
    QAction *histeresisAct;
    QAction *otsuAct;
    QAction *rosinAct;
    QAction *rosinNorAct;
    QAction *rosinNorAcuAct;
    QAction *proxiAct;
    QAction *proxiAcuAct;
    QAction *distAct;
    QAction *distAcuAct;
    QAction *menorAct;
    QAction *menorAcuAct;
    QAction *adapAct;
    QAction *adapAcuAct;
    QAction *semiAct;
    QAction *semiAcuAct;

//Acciones modificación escala de gris
    QAction *lineargrayAct;
    QAction *slideAct;
    QAction *shrinkAct;
    QAction *stretchAct;
    QAction *adaptiveAct;
    QAction *colorMapAct;

//Acciones nitidez
    QAction *highpassAct;
    QAction *highFrequencyAct;
    QAction *moravecAct;
    QAction *homomorphicAct;
    QAction *unsharpAct;
    QAction *sharpeningAct;

//Acciones suavizado
    QAction *meanFilterAct;
    QAction *medianFilterAct;
    QAction *gaussFilterAct;
    QAction *kuwaharaAct;

    QAction *aboutAct;
    QAction *contentsAct;

    QAction *separatorAct;

};


#endif // SUBWINDOW_H
