#ifndef HISTWINDOW_H
#define HISTWINDOW_H

#include "mainwindow.h"


#ifndef QT_NO_PRINTER
#include <QPrinter>
#endif



class histwindow: public QMainWindow
{
    Q_OBJECT

public:
    histwindow(const QString &fileName);
    histwindow(const QString &fileName, const Mat &resultadoImg);
    histwindow(const QString &fileName, const Mat &resultadoImg, float umbral);
    histwindow(const QString &fileName, const Mat &resultadoImg, float umbral_mayor, float umbral_menor);

private slots:
    void save();
    void print();
    void histAux();

private:

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void savefile(const QString &titulo, Mat &imagen);

    Mat histoColorCalc(int histSize);
    Mat histoRealzadaCalc(int histSize);
    Mat histoUmbralCalc(int histSize, float umbral);
    Mat histoUmbralCalc(int histSize, float umbral_mayor, float umbral_menor);



    Mat Img;
    Mat hist;
    int numIntColor;
    float Umbral,Umbral_mayor,Umbral_menor;
    int control;
    bool dc;
    QString filename,salida;

    QComboBox *myComboBox;

    QCheckBox *umbralCheck;

    QMenu *fileMenu;
    QToolBar *fileToolBar;
    QToolBar *viewToolBar;

    QAction *saveAct;
    QAction *printAct;
    QAction *exitAct;

    QLabel *imageLabel;
    QScrollArea *scrollArea;


#ifndef QT_NO_PRINTER
    QPrinter printer;
#endif

};
#endif // HISTWINDOW_H
