#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include "subwindow.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QLabel;
class QScrollArea;
class QScrollBar;
class QWebView;
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private slots:
    void open();
    void openRecent();
    bool loadFile(const QString &);
    void print();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    void contents();
    void about();
    void histogram();
    void normalizar();

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
    void updateRecentActionList();

    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor;
    const int maxFileNr;
    int window;
    QString currentFilePath;



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

    QAction *openAct;
    QList<QAction*> recentFileActionList;

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

#endif
