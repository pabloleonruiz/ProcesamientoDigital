#include "histwindow.h"

histwindow::histwindow(const QString &fileName)
{
    filename=fileName;
    Img = cv::imread(fileName.toStdString(), -1);
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);

    dc=FALSE;
    control=0;

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    QFileInfo ruta(filename);
    salida = ruta.baseName();
    salida.append("_");
    salida.append("Histograma");

    Umbral=0;
    Umbral_mayor=0;
    Umbral_menor=0;
    histAux();

    imageLabel->resize(1 * imageLabel->pixmap()->size());

    setWindowFilePath(salida);
}

histwindow::histwindow(const QString &fileName, const Mat &resultadoImg)
{
    Img=resultadoImg;
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);

    dc=FALSE;
    control=0;
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    Umbral=0;
    Umbral_mayor=0;
    Umbral_menor=0;

    histAux();

    imageLabel->resize(1 * imageLabel->pixmap()->size());

    salida = fileName;
    salida.append("_");
    salida.append("Histograma");
    setWindowFilePath(salida);
}

histwindow::histwindow(const QString &fileName, const Mat &resultadoImg, float umbral)
{
    Img=resultadoImg;
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);
control=1;
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    Umbral_mayor=0;
    Umbral_menor=0;
    Umbral=umbral;

    histAux();

    imageLabel->resize(1 * imageLabel->pixmap()->size());

    salida = fileName;
    salida.append("_");
    salida.append("Histograma");
    setWindowFilePath(salida);
}

histwindow::histwindow(const QString &fileName, const Mat &resultadoImg, float umbral_mayor, float umbral_menor)
{
    Img=resultadoImg;
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);
control=1;
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    Umbral=0;
    Umbral_mayor=umbral_mayor;
    Umbral_menor=umbral_menor;

    histAux();

    imageLabel->resize(1 * imageLabel->pixmap()->size());

    salida = fileName;
    salida.append("_");
    salida.append("Histograma");
    setWindowFilePath(salida);
}

void histwindow::createActions()
{
    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Guardar"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Guarda el histograma al disco"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    printAct = new QAction(tr("&Imprimir..."), this);
    printAct->setShortcut(tr("Ctrl+P"));
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));

    exitAct = new QAction(tr("Cerrar &Ventana"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Cierra la ventana"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));


}

void histwindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Archivo"));
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

}


void histwindow::createToolBars()
{
    fileToolBar = addToolBar(tr("Archivo"));
    fileToolBar->addAction(saveAct);
    viewToolBar = addToolBar(tr("Ver"));
    QLabel *text = new QLabel(tr("Nº Intervalos:"));
    viewToolBar->addWidget(text);

    myComboBox = new QComboBox();
    myComboBox->setStyleSheet("font-size: 14px;");
    myComboBox->addItem(tr("256"));
    myComboBox->addItem(tr("128"));
    myComboBox->addItem(tr("64"));
    myComboBox->addItem(tr("32"));
    myComboBox->addItem(tr("16"));
    myComboBox->addItem(tr("8"));
    viewToolBar->addWidget(myComboBox);

    connect(myComboBox, SIGNAL(activated(int)), this, SLOT(histAux()));

if(control==1)
{
    umbralCheck= new QCheckBox(tr("Mostrar umbral"));
    umbralCheck->setLayoutDirection(Qt::RightToLeft);
    viewToolBar->addWidget(umbralCheck);
    connect(umbralCheck, SIGNAL(clicked(bool)), this, SLOT(histAux()));
}

}

void histwindow::createStatusBar()
{
    statusBar()->showMessage(tr("Listo"));
}


void histwindow::print()
{
    Q_ASSERT(imageLabel->pixmap());
#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
    QPrintDialog dialog(&printer, this);
    if (dialog.exec()) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = imageLabel->pixmap()->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(imageLabel->pixmap()->rect());
        painter.drawPixmap(0, 0, *imageLabel->pixmap());
    }
#endif
}


//Función auxiliar para dibujar hitograma
void histwindow::histAux()
{

    hist.release();

    int index = myComboBox->currentIndex();
    switch (index) {
    case 0:
        numIntColor=256;
        break;
    case 1:
        numIntColor=128;
        break;
    case 2:
        numIntColor=64;
        break;
    case 3:
        numIntColor=32;
        break;
    case 4:
        numIntColor=16;
        break;
    case 5:
        numIntColor=8;
        break;
    default:
        numIntColor=256;
        break;
    }

    if( Umbral_mayor!=0 ||  Umbral_menor!=0 || Umbral!=0)
    {
    Qt::CheckState state1;
    state1 = umbralCheck->checkState();

    if(state1==Qt::Checked)
        dc=TRUE;
    else
        dc=FALSE;

    }
   if(Img.channels()>1)
   {
    hist = histoColorCalc(numIntColor);
    }
    else
   {
       if(Umbral_mayor!=0 || Umbral_menor!=0)
           hist = histoUmbralCalc(numIntColor,Umbral_mayor,Umbral_menor);

       if(Umbral!=0)
           hist = histoUmbralCalc(numIntColor,Umbral);

        if(Umbral==0 && Umbral_mayor==0 && Umbral_menor==0)
          hist=histoRealzadaCalc(numIntColor);
   }
    imageLabel->setPixmap(ASM::cvMatToQPixmap(hist));
}



Mat histwindow::histoColorCalc(int histSize)
{
     Mat src = Img;

     /// Separate the image in 3 places ( B, G and R )
     vector<Mat> bgr_planes;
     split( src, bgr_planes );

     /// Establish the number of bins
     //int histSize = 256;

     /// Set the ranges ( for B,G,R) )
     float range[] = { 0, 255 } ;
     const float* histRange = { range };

     bool uniform = true; bool accumulate = false;

     Mat b_hist, g_hist, r_hist;

     /// Compute the histograms:
     calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
     calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
     calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

     // Draw the histograms for B, G and R
     int hist_w = 400;
     int hist_h = 170;
     int bin_w = cvRound( (double) hist_w/histSize );

     Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

     /// Normalize the result to [ 0, histImage.rows ]
     normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
     normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
     normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

     /// Draw for each channel
     for( int i = 1; i <= histSize; i++ )
     {
         line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                          Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                          Scalar( 255, 0, 0), 1, 8, 0  );
         line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
                          Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                          Scalar( 0, 255, 0), 1, 8, 0  );
         line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
                          Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                          Scalar( 0, 0, 255), 1, 8, 0  );
     }


     //Pintamos un marco blanco para delimitar el histograma
     line( histImage, Point( 0, 0) ,
                      Point( 0, hist_h-1),
                      Scalar(255,255,255), 1, 8, 0  );

     line( histImage, Point( 0, 0) ,
                      Point( hist_w-1, 0),
                      Scalar(255,255,255), 1, 8, 0  );

     line( histImage, Point( 0, hist_h-1) ,
                      Point( hist_w-1, hist_h-1),
                      Scalar(255,255,255), 1, 8, 0  );

     line( histImage, Point( hist_w-1, 0) ,
                      Point( hist_w-1, hist_h-1),
                      Scalar(255,255,255), 1, 8, 0  );

     return histImage;
}


Mat histwindow::histoRealzadaCalc(int histSize)
{
    Mat src = Img;

     // Establish the number of bins
     //int histSize = 16;

     // Set the ranges ( for B,G,R) )
     float range[] = { 0, 255 } ;
     const float* histRange = { range };

     bool uniform = true; bool accumulate = false;

     Mat b_hist;

     // Compute the histogram:
     calcHist( &src, 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );

     int hist_w = 512;
     int hist_h = 400;
     int bin_w = cvRound( (double) hist_w/histSize );

     Mat histImage( hist_h, hist_w, CV_8UC3, Scalar(0) );

     // Normalize the result to [ 0, histImage.rows ]
     normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

     // Draw for the channel

         // Versión para dibujar el histograma mediante una línea
         for( int i = 1; i <= histSize; i++ )
          {
           line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                            Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                            Scalar(0,255,255), 1, 8, 0  );

          }



     //Pintamos un marco blanco para delimitar el histograma
     line( histImage, Point( 0, 0) ,
                      Point( 0, hist_h-1),
                      Scalar(255,255,255), 1, 8, 0  );

     line( histImage, Point( 0, 0) ,
                      Point( hist_w-1, 0),
                      Scalar(255,255,255), 1, 8, 0  );

     line( histImage, Point( 0, hist_h-1) ,
                      Point( hist_w-1, hist_h-1),
                      Scalar(255,255,255), 1, 8, 0  );

     line( histImage, Point( hist_w-1, 0) ,
                      Point( hist_w-1, hist_h-1),
                      Scalar(255,255,255), 1, 8, 0  );

    return histImage;

}


//Función auxiliar para guardar histograma color
void histwindow::save()
{
  savefile(tr("Guardar histograma color"), hist);
}



//Función para guardar histograma color
void histwindow::savefile(const QString &titulo, Mat &imagen)
{

     QString escribir;
/*
     QFileInfo ruta(filename);
     salida = ruta.baseName();
*/
     escribir=salida;
     escribir.append("_");
     escribir.append(QString::number(numIntColor));
     escribir.append(".jpg");
     QString fileName = QFileDialog::getSaveFileName(this, titulo, escribir, tr("Image Files (*.jpg *.jpeg)"));
     if (!fileName.isEmpty())
      {
        vector<int> parametros;
        parametros.push_back(CV_IMWRITE_JPEG_QUALITY);
        parametros.push_back(100);
        cv::imwrite(fileName.toStdString(), imagen, parametros);
      }
     else
           return;
}

//Función para dibujar el histograma umbralizada
Mat histwindow::histoUmbralCalc(int histSize, float umbral)
{
    Mat src = Img;

     // Establish the number of bins
     //int histSize = 16;

     // Set the ranges ( for B,G,R) )
     float range[] = { 0, 255 } ;
     const float* histRange = { range };

     bool uniform = true; bool accumulate = false;

     Mat b_hist;

     // Compute the histogram:
     calcHist( &src, 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );

     int hist_w = 512;
     int hist_h = 400;
     int bin_w = cvRound( (double) hist_w/histSize );

     Mat histImage( hist_h, hist_w, CV_8UC3, Scalar(0) );

     // Normalize the result to [ 0, histImage.rows ]
     normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

     // Draw for the channel

         // Versión para dibujar el histograma mediante una línea
         for( int i = 1; i <= histSize; i++ )
          {
           line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                            Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                            Scalar(0,255,255), 1, 8, 0  );

          }



     //Pintamos un marco blanco para delimitar el histograma
     line( histImage, Point( 0, 0) ,
                      Point( 0, hist_h-1),
                      Scalar(255,255,255), 1, 8, 0  );

     line( histImage, Point( 0, 0) ,
                      Point( hist_w-1, 0),
                      Scalar(255,255,255), 1, 8, 0  );

     line( histImage, Point( 0, hist_h-1) ,
                      Point( hist_w-1, hist_h-1),
                      Scalar(255,255,255), 1, 8, 0  );

     line( histImage, Point( hist_w-1, 0) ,
                      Point( hist_w-1, hist_h-1),
                      Scalar(255,255,255), 1, 8, 0  );

             int i = (int)(umbral);

if(dc)
{
             //Se pinta la línea que marca el umbral calculado
             line( histImage, Point( bin_w*(i), hist_h-1)  ,
                              Point( bin_w*(i), 0),
                              Scalar(0,0,255), 1, 8, 0  );
}

return histImage;
}


//Función para dibujar el histograma umbralizada
Mat histwindow::histoUmbralCalc(int histSize, float umbral_mayor, float umbral_menor)
{
    Mat src = Img;

     // Establish the number of bins
     //int histSize = 16;

     // Set the ranges ( for B,G,R) )
     float range[] = { 0, 255 } ;
     const float* histRange = { range };

     bool uniform = true; bool accumulate = false;

     Mat b_hist;

     // Compute the histogram:
     calcHist( &src, 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );

     int hist_w = 512;
     int hist_h = 400;
     int bin_w = cvRound( (double) hist_w/histSize );

     Mat histImage( hist_h, hist_w, CV_8UC3, Scalar(0) );

     // Normalize the result to [ 0, histImage.rows ]
     normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

     // Draw for the channel

         // Versión para dibujar el histograma mediante una línea
         for( int i = 1; i <= histSize; i++ )
          {
           line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                            Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                            Scalar(0,255,255), 1, 8, 0  );

          }



     //Pintamos un marco blanco para delimitar el histograma
     line( histImage, Point( 0, 0) ,
                      Point( 0, hist_h-1),
                      Scalar(255,255,255), 1, 8, 0  );

     line( histImage, Point( 0, 0) ,
                      Point( hist_w-1, 0),
                      Scalar(255,255,255), 1, 8, 0  );

     line( histImage, Point( 0, hist_h-1) ,
                      Point( hist_w-1, hist_h-1),
                      Scalar(255,255,255), 1, 8, 0  );

     line( histImage, Point( hist_w-1, 0) ,
                      Point( hist_w-1, hist_h-1),
                      Scalar(255,255,255), 1, 8, 0  );
if(dc)
{
     int i = (int)(umbral_mayor);
     int j = (int)(umbral_menor);

     //Se pinta la línea que marca el umbral mayor calculado
     line( histImage, Point( bin_w*(i), hist_h-1)  ,
                      Point( bin_w*(i), 0),
                      Scalar(0,0,255), 1, 8, 0  );

     //Se pinta la línea que marca el umbral menor calculado
     line( histImage, Point( bin_w*(j), hist_h-1)  ,
                      Point( bin_w*(j), 0),
                      Scalar(0,0,255), 1, 8, 0  );
}

             return histImage;

}
