#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), maxFileNr(4)
{

//Icono de la aplicación
    setWindowIcon(QIcon(":/images/histogram.png"));
//Se inicializa la ventana
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);
//Se crean los componentes de la ventana
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    this->resize(800,600);

//Se muestra maximizada la aplicación
    this->showMaximized();

}

//Funciones para cargar la imagen
void MainWindow::open()
{
        QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "",tr("Images (*.png *.xpm *.jpg *.gif)"));
            if (!filePath.isEmpty())
                loadFile(filePath);
}



bool MainWindow::loadFile(const QString &fileName)
{
//Abre una ventana nueva si ya se ha cargado una imagen antes
    if(window==1)
    {
        MainWindow *other = new MainWindow;
        other->show();
        other->loadFile(fileName);
        other->showNormal();
        other->resize(800,600);
        return true;
    }

    QImage image(fileName);

     if (image.isNull())
     {
             QMessageBox::information(this,"Error",tr("No se puede cargar %1.").arg(QDir::toNativeSeparators(fileName)));

        setWindowFilePath(QString());
        imageLabel->setPixmap(QPixmap());
        imageLabel->adjustSize();
        return false;
    }

    if (image.isGrayscale())
    {
        normalizarAct->setEnabled(true);
        manualAct->setEnabled(true);
        porcentualAct->setEnabled(true);
        histeresisAct->setEnabled(true);
        otsuAct->setEnabled(true);
        rosinAct->setEnabled(true);
        rosinNorAct->setEnabled(true);
        rosinNorAcuAct->setEnabled(true);
        proxiAct->setEnabled(true);
        proxiAcuAct->setEnabled(true);
        distAct->setEnabled(true);
        distAcuAct->setEnabled(true);
        menorAct->setEnabled(true);
        menorAcuAct->setEnabled(true);
        adapAct->setEnabled(true);
        adapAcuAct->setEnabled(true);
        semiAct->setEnabled(true);
        semiAcuAct->setEnabled(true);
        colorMapAct->setEnabled(true);
    }
    else
    {
        leecockAct->setEnabled(true);
        scharcanskiAct->setEnabled(true);
        dvAct->setEnabled(true);
        dvhdAct->setEnabled(true);
        mvdagreAct->setEnabled(true);
        mvdcentralAct->setEnabled(true);
        shiozakiAct->setEnabled(true);
        pietiAct->setEnabled(true);
    }

    imageLabel->setPixmap(QPixmap::fromImage(image));

    scaleFactor = 1.0;

    printAct->setEnabled(true);
    fitToWindowAct->setEnabled(true);
    histogramAct->setEnabled(true);

    lineargrayAct->setEnabled(true);
    slideAct->setEnabled(true);
    shrinkAct->setEnabled(true);
    stretchAct->setEnabled(true);
    adaptiveAct->setEnabled(true);
    highpassAct->setEnabled(true);
    highFrequencyAct->setEnabled(true);
    moravecAct->setEnabled(true);
    homomorphicAct->setEnabled(true);
    unsharpAct->setEnabled(true);
    sharpeningAct->setEnabled(true);
    meanFilterAct->setEnabled(true);
    medianFilterAct->setEnabled(true);
    gaussFilterAct->setEnabled(true);
    kuwaharaAct->setEnabled(true);

    updateActions();

    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();

   adjustForCurrentFile(fileName);

   setWindowFilePath(fileName);

   statusBar()->showMessage(tr("Imagen cargada"));

    window=1;
    return true;
}

//Crea la ventana helpwindow (Manual de contenidos)
void MainWindow::contents()
{
   helpwindow *other = new helpwindow;
   other->show();
}


void MainWindow::about()
{
   QMessageBox::about(this, tr("Acerca de la aplicación"),
            tr("La <b>aplicación</b> muestra distintos tipos de procesamiento digital de imagenes ..."));
}


//Crea la venta histwindow (Histograma de la imagen)
void MainWindow::histogram()
{
    histwindow *other = new histwindow(currentFilePath);
    other->show();
}


void MainWindow::createActions()
{
//Acciones principales de la ventana
    openAct = new QAction(QIcon(":/images/open.png"), tr("&Abrir..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Abre una imagen existente"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    QAction* recentFileAction = 0;
        for(int i = 0; i < maxFileNr; i++){
            recentFileAction = new QAction(this);
            recentFileAction->setVisible(false);
            QObject::connect(recentFileAction, SIGNAL(triggered()),
                                         this, SLOT(openRecent()));
            recentFileActionList.append(recentFileAction);
        }

    printAct = new QAction(tr("&Imprimir..."), this);
    printAct->setShortcut(tr("Ctrl+P"));
    printAct->setEnabled(false);
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));


    closeAct = new QAction(tr("&Cerrar Ventana"), this);
    closeAct->setShortcut(tr("Ctrl+W"));
    closeAct->setStatusTip(tr("Cierra esta ventana"));
    connect(closeAct, SIGNAL(triggered()), this, SLOT(close()));

    exitAct = new QAction(tr("&Salir"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Salir de la aplicación"));
    connect(exitAct, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
//Histograma
    histogramAct = new QAction(QIcon(":/images/histogram.png"), tr("&Histograma"), this);
    histogramAct->setShortcut(tr("Ctrl+H"));
    histogramAct->setEnabled(false);
    histogramAct->setStatusTip(tr("Muestra el histograma de la imagen seleccionada"));
    connect(histogramAct, SIGNAL(triggered()), this, SLOT(histogram()));

//Normalizar
    normalizarAct = new QAction(tr("Normalizar imagen"), this);
    normalizarAct->setShortcut(tr("Ctrl+N"));
    normalizarAct->setEnabled(false);
    normalizarAct->setStatusTip(tr("Normaliza la imagen"));
    connect(normalizarAct, SIGNAL(triggered()), this, SLOT(normalizar()));

//Acciones del visor de ventana
    zoomInAct = new QAction(QIcon(":/images/zoom_in.png"), tr("Aumentar &Zoom (25%)"), this);
    zoomInAct->setShortcut(tr("Ctrl++"));
    zoomInAct->setEnabled(false);
    zoomInAct->setStatusTip(tr("Aumenta el zoom un 25% de la imagen seleccionada"));
    connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

    zoomOutAct = new QAction(QIcon(":/images/zoom_out.png"), tr("Disminuir &Zoom (25%)"), this);
    zoomOutAct->setShortcut(tr("Ctrl+-"));
    zoomOutAct->setEnabled(false);
    zoomOutAct->setStatusTip(tr("Disminuye el zoom un 25% de la imagen seleccionada"));
    connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));

    normalSizeAct = new QAction(tr("Tamaño &Original"), this);
    normalSizeAct->setShortcut(tr("Ctrl+S"));
    normalSizeAct->setEnabled(false);
    connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));

    fitToWindowAct = new QAction(QIcon(":/images/zoom_best_fit.png"), tr("Ajustar a &Pantalla"), this);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setCheckable(true);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));
    fitToWindowAct->setStatusTip(tr("Ajusta la imagen a la pantalla"));
    connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));

//Detección de bordes
    leecockAct = new QAction(tr("Algoritmo &Lee y Cock"), this);
    leecockAct->setEnabled(false);
    connect(leecockAct, SIGNAL(triggered()), this, SLOT(leecock()));

    scharcanskiAct = new QAction(tr("&Scharcanski-Venetsanopoulos"), this);
    scharcanskiAct->setEnabled(false);
    connect(scharcanskiAct, SIGNAL(triggered()), this, SLOT(scharcanski()));

    dvAct = new QAction(tr("&Dv"), this);
    dvAct->setEnabled(false);
    connect(dvAct, SIGNAL(triggered()), this, SLOT(dv()));

    dvhdAct = new QAction(tr("&Dv-Hv"), this);
    dvhdAct->setEnabled(false);
    connect(dvhdAct, SIGNAL(triggered()), this, SLOT(dvhd()));

    mvdagreAct = new QAction(tr("&Mvd agregadas mutuas"), this);
    mvdagreAct->setEnabled(false);
    connect(mvdagreAct, SIGNAL(triggered()), this, SLOT(mvdagre()));

    mvdcentralAct = new QAction(tr("&Mvd punto central"), this);
    mvdcentralAct->setEnabled(false);
    connect(mvdcentralAct, SIGNAL(triggered()), this, SLOT(mvdcentral()));

    shiozakiAct = new QAction(tr("&Shiozaki"), this);
    shiozakiAct->setEnabled(false);
    connect(shiozakiAct, SIGNAL(triggered()), this, SLOT(shiozaki()));

    pietiAct = new QAction(tr("&Pietikäinen-Rosenfeld"), this);
    pietiAct->setEnabled(false);
    connect(pietiAct, SIGNAL(triggered()), this, SLOT(pieti()));

//Umbralización
    manualAct = new QAction(tr("&Manual"), this);
    manualAct->setEnabled(false);
    connect(manualAct, SIGNAL(triggered()), this, SLOT(manual()));

    porcentualAct = new QAction(tr("&Porcentual"), this);
    porcentualAct->setEnabled(false);
    connect(porcentualAct, SIGNAL(triggered()), this, SLOT(porcentual()));

    histeresisAct = new QAction(tr("&Histéresis"), this);
    histeresisAct->setEnabled(false);
    connect(histeresisAct, SIGNAL(triggered()), this, SLOT(histeresis()));

    otsuAct = new QAction(tr("&Otsu"), this);
    otsuAct->setEnabled(false);
    connect(otsuAct, SIGNAL(triggered()), this, SLOT(otsu()));

    rosinAct = new QAction(tr("&Rosin"), this);
    rosinAct->setEnabled(false);
    connect(rosinAct, SIGNAL(triggered()), this, SLOT(rosin()));

    rosinNorAct = new QAction(tr("&Rosin normalizado"), this);
    rosinNorAct->setEnabled(false);
    connect(rosinNorAct, SIGNAL(triggered()), this, SLOT(rosinNor()));

    rosinNorAcuAct = new QAction(tr("&Rosin normalizado acumulado inverso"), this);
    rosinNorAcuAct->setEnabled(false);
    connect(rosinNorAcuAct, SIGNAL(triggered()), this, SLOT(rosinNorAcu()));

    proxiAct = new QAction(tr("&Próxim. (max/N,0.0)"), this);
    proxiAct->setEnabled(false);
    connect(proxiAct, SIGNAL(triggered()), this, SLOT(proxi()));

    proxiAcuAct = new QAction(tr("&Próxim. (max/N,0.0) acumulado inverso"), this);
    proxiAcuAct->setEnabled(false);
    connect(proxiAcuAct, SIGNAL(triggered()), this, SLOT(proxiAcu()));

    distAct = new QAction(tr("&Más dist. (1.0,1.0)"), this);
    distAct->setEnabled(false);
    connect(distAct, SIGNAL(triggered()), this, SLOT(dist()));

    distAcuAct = new QAction(tr("&Más dist. (1.0,1.0) acumulado inverso"), this);
    distAcuAct->setEnabled(false);
    connect(distAcuAct, SIGNAL(triggered()), this, SLOT(distAcu()));

    menorAct = new QAction(tr("&Menor dist. diagonal"), this);
    menorAct->setEnabled(false);
    connect(menorAct, SIGNAL(triggered()), this, SLOT(menor()));

    menorAcuAct = new QAction(tr("&Menor dist. diagonal acumulado inverso"), this);
    menorAcuAct->setEnabled(false);
    connect(menorAcuAct, SIGNAL(triggered()), this, SLOT(menorAcu()));

    adapAct = new QAction(tr("&Adaptativo"), this);
    adapAct->setEnabled(false);
    connect(adapAct, SIGNAL(triggered()), this, SLOT(adap()));

    adapAcuAct = new QAction(tr("&Adaptativo acumulado inverso"), this);
    adapAcuAct->setEnabled(false);
    connect(adapAcuAct, SIGNAL(triggered()), this, SLOT(adapAcu()));

    semiAct = new QAction(tr("&Semi-adaptativo"), this);
    semiAct->setEnabled(false);
    connect(semiAct, SIGNAL(triggered()), this, SLOT(semi()));

    semiAcuAct = new QAction(tr("&Semi-adaptativo acumulado inverso"), this);
    semiAcuAct->setEnabled(false);
    connect(semiAcuAct, SIGNAL(triggered()), this, SLOT(semiAcu()));

//Modificación escala de gris
    lineargrayAct = new QAction(tr("&Linear gray level modification (Mapping equation)"), this);
    lineargrayAct->setEnabled(false);
    connect(lineargrayAct, SIGNAL(triggered()), this, SLOT(lineargray()));

    slideAct = new QAction(tr("&Histogram slide"), this);
    slideAct->setEnabled(false);
    connect(slideAct, SIGNAL(triggered()), this, SLOT(slide()));

    shrinkAct = new QAction(tr("&Histogram shrink"), this);
    shrinkAct->setEnabled(false);
    connect(shrinkAct, SIGNAL(triggered()), this, SLOT(shrink()));

    stretchAct = new QAction(tr("&Histogram stretch"), this);
    stretchAct->setEnabled(false);
    connect(stretchAct, SIGNAL(triggered()), this, SLOT(stretch()));

    adaptiveAct = new QAction(tr("&Adaptive contrast filter"), this);
    adaptiveAct->setEnabled(false);
    connect(adaptiveAct, SIGNAL(triggered()), this, SLOT(adaptive()));

    colorMapAct = new QAction(tr("&ColorMap"), this);
    colorMapAct->setEnabled(false);
    connect(colorMapAct, SIGNAL(triggered()), this, SLOT(colorMap()));

//Nitidez
    highpassAct = new QAction(tr("&Highpass Filtering"), this);
    highpassAct->setEnabled(false);
    connect(highpassAct, SIGNAL(triggered()), this, SLOT(highpass()));

    highFrequencyAct = new QAction(tr("&High Frequency Emphasis"), this);
    highFrequencyAct->setEnabled(false);
    connect(highFrequencyAct, SIGNAL(triggered()), this, SLOT(highFrequency()));

    moravecAct = new QAction(tr("&Moravec Filter (Directional Difference Filters)"), this);
    moravecAct->setEnabled(false);
    connect(moravecAct, SIGNAL(triggered()), this, SLOT(moravec()));

    homomorphicAct = new QAction(tr("&Homomorphic Filtering"), this);
    homomorphicAct->setEnabled(false);
    connect(homomorphicAct, SIGNAL(triggered()), this, SLOT(homomorphic()));

    unsharpAct = new QAction(tr("&Unsharp Masking"), this);
    unsharpAct->setEnabled(false);
    connect(unsharpAct, SIGNAL(triggered()), this, SLOT(unsharp()));

    sharpeningAct = new QAction(tr("&Sharpening Algorithm"), this);
    sharpeningAct->setEnabled(false);
    connect(sharpeningAct, SIGNAL(triggered()), this, SLOT(sharpening()));

//Suavizado
    meanFilterAct = new QAction(tr("&Mean Filter"), this);
    meanFilterAct->setEnabled(false);
    connect(meanFilterAct, SIGNAL(triggered()), this, SLOT(meanFilter()));

    medianFilterAct = new QAction(tr("&Median Filter"), this);
    medianFilterAct->setEnabled(false);
    connect(medianFilterAct, SIGNAL(triggered()), this, SLOT(medianFilter()));

    gaussFilterAct = new QAction(tr("&Gaussian Filter"), this);
    gaussFilterAct->setEnabled(false);
    connect(gaussFilterAct, SIGNAL(triggered()), this, SLOT(gaussFilter()));

    kuwaharaAct = new QAction(tr("&Kuwahara Filter (Nonlinear Filtering)"), this);
    kuwaharaAct->setEnabled(false);
    connect(kuwaharaAct, SIGNAL(triggered()), this, SLOT(kuwahara()));

//Manual de ayuda
    contentsAct = new QAction(tr("Manual de &contenidos"), this);
    contentsAct->setStatusTip(tr("Muestra el manual de la aplicación"));
    contentsAct->setShortcut(tr("F1"));
    connect(contentsAct, SIGNAL(triggered()), this, SLOT(contents()));

    aboutAct = new QAction(tr("Sobre la &aplicación"), this);
    aboutAct->setStatusTip(tr("Muestra información sobre la aplicación"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

//Se crea la barra de menu
void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("Archivo"));
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();

//Archivos recientes
    recentFilesMenu = fileMenu->addMenu(tr("Recientes"));
        for(int i = 0; i < maxFileNr; i++)
            recentFilesMenu->addAction(recentFileActionList.at(i));
    updateRecentActionList();
    fileMenu->addSeparator();

    fileMenu->addAction(printAct);
    fileMenu->addSeparator();

    fileMenu->addAction(closeAct);
    fileMenu->addAction(exitAct);

    viewMenu = menuBar()->addMenu(tr("Ver"));
    viewMenu->addAction(histogramAct);
    menuBar()->addSeparator();
    viewMenu->addAction(zoomInAct);
    viewMenu->addAction(zoomOutAct);
    viewMenu->addAction(normalSizeAct);
    viewMenu->addSeparator();
    viewMenu->addAction(fitToWindowAct);
    menuBar()->addSeparator();
    viewMenu->addAction(normalizarAct);


    enhancementMenu = menuBar()->addMenu(tr("Realce"));
    subenhancementMenu=enhancementMenu->addMenu(tr("Detector de Bordes"));
    subenhancementMenu->addAction(leecockAct);
    subenhancementMenu->addAction(scharcanskiAct);
    subenhancementMenu->addAction(dvAct);
    subenhancementMenu->addAction(dvhdAct);
    subenhancementMenu->addAction(mvdagreAct);
    subenhancementMenu->addAction(mvdcentralAct);
    subenhancementMenu->addAction(shiozakiAct);
    subenhancementMenu->addAction(pietiAct);

    subenhancementMenu2=enhancementMenu->addMenu(tr("Modificación escala de Gris"));
    subenhancementMenu2->addAction(lineargrayAct);
    subenhancementMenu2->addAction(slideAct);
    subenhancementMenu2->addAction(shrinkAct);
    subenhancementMenu2->addAction(stretchAct);
    subenhancementMenu2->addAction(adaptiveAct);
    subenhancementMenu2->addAction(colorMapAct);


    subenhancementMenu3=enhancementMenu->addMenu(tr("Nitidez de la imagen"));
    subenhancementMenu3->addAction(highpassAct);
    subenhancementMenu3->addAction(highFrequencyAct);
    subenhancementMenu3->addAction(moravecAct);
    subenhancementMenu3->addAction(homomorphicAct);
    subenhancementMenu3->addAction(unsharpAct);
    subenhancementMenu3->addAction(sharpeningAct);


    subenhancementMenu4=enhancementMenu->addMenu(tr("Suavizado de la imagen"));
    subenhancementMenu4->addAction(meanFilterAct);
    subenhancementMenu4->addAction(medianFilterAct);
    subenhancementMenu4->addAction(gaussFilterAct);
    subenhancementMenu4->addAction(kuwaharaAct);



    menuBar()->addSeparator();

    thresholdingMenu= menuBar()->addMenu(tr("&Umbralización"));
    thresholdingMenu->addAction(manualAct);
    thresholdingMenu->addAction(porcentualAct);
    thresholdingMenu->addAction(histeresisAct);
    thresholdingMenu->addAction(otsuAct);
    thresholdingMenu->addSeparator();
    thresholdingMenu->addAction(rosinAct);
    thresholdingMenu->addAction(rosinNorAct);
    thresholdingMenu->addAction(rosinNorAcuAct);
    thresholdingMenu->addSeparator();
    thresholdingMenu->addAction(proxiAct);
    thresholdingMenu->addAction(proxiAcuAct);
    thresholdingMenu->addSeparator();
    thresholdingMenu->addAction(distAct);
    thresholdingMenu->addAction(distAcuAct);
    thresholdingMenu->addSeparator();
    thresholdingMenu->addAction(menorAct);
    thresholdingMenu->addAction(menorAcuAct);
    thresholdingMenu->addSeparator();
    thresholdingMenu->addAction(adapAct);
    thresholdingMenu->addAction(adapAcuAct);
    thresholdingMenu->addSeparator();
    thresholdingMenu->addAction(semiAct);
    thresholdingMenu->addAction(semiAcuAct);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Ayuda"));
    helpMenu->addAction(contentsAct);
    helpMenu->addAction(aboutAct);
}

//Se crea la barra de herramientas
void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("Archivo"));
    fileToolBar->addAction(openAct);

    viewToolBar = addToolBar(tr("Ver"));
    viewToolBar->addAction(histogramAct);
    viewToolBar->addAction(zoomInAct);
    viewToolBar->addAction(zoomOutAct);
    viewToolBar->addAction(fitToWindowAct);

}


void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Listo"));
}


void MainWindow::readSettings()
{
    QSettings settings("Proyecto", "Prototipo");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    move(pos);
    resize(size);
}


void MainWindow::writeSettings()
{
    QSettings settings("Proyecto", "Prototipo");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}


//Imprimir imagen
void MainWindow::print()
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

//Funciones visor imagenes
void MainWindow::zoomIn()
{
    scaleImage(1.25);
}


void MainWindow::zoomOut()
{
    scaleImage(0.8);
}


void MainWindow::normalSize()
{
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}


void MainWindow::fitToWindow()
{
    bool fitToWindow = fitToWindowAct->isChecked();
    scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow) {
        normalSize();
    }
    updateActions();
}


void MainWindow::updateActions()
{
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}


void MainWindow::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
}


void MainWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

//Funciones archivos recientes
void MainWindow::openRecent()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
        loadFile(action->data().toString());
}

void MainWindow::adjustForCurrentFile(const QString &filePath)
{
    currentFilePath = filePath;
    setWindowFilePath(currentFilePath);

    QSettings settings;
    QStringList recentFilePaths = settings.value("recentFiles").toStringList();
    recentFilePaths.removeAll(filePath);
    recentFilePaths.prepend(filePath);
    while (recentFilePaths.size() > maxFileNr)
        recentFilePaths.removeLast();
    settings.setValue("recentFiles", recentFilePaths);

    updateRecentActionList();
}

void MainWindow::updateRecentActionList()
{
    QSettings settings;
    QStringList recentFilePaths =
            settings.value("recentFiles").toStringList();

    int itEnd = 0;
    if(recentFilePaths.size() <= maxFileNr)
        itEnd = recentFilePaths.size();
    else
        itEnd = maxFileNr;

    for (int i = 0; i < itEnd; i++) {
        QString strippedName = QFileInfo(recentFilePaths.at(i)).fileName();
        recentFileActionList.at(i)->setText(strippedName);
        recentFileActionList.at(i)->setData(recentFilePaths.at(i));
        recentFileActionList.at(i)->setVisible(true);
    }

    for (int i = itEnd; i < maxFileNr; i++)
        recentFileActionList.at(i)->setVisible(false);
}

//Funciones detector
void MainWindow::leecock()
{
    subwindow *other = new subwindow(currentFilePath,"Lee-Cok");
    other->show();

}

void MainWindow::scharcanski()
{
    subwindow *other = new subwindow(currentFilePath,"Direccional");
    other->show();
}

void MainWindow::dv()
{
    subwindow *other = new subwindow(currentFilePath,"Dv");
    other->show();
}

void MainWindow::dvhd()
{
    subwindow *other = new subwindow(currentFilePath,"Dv-Hv");
    other->show();
}

void MainWindow::mvdagre()
{
    subwindow *other = new subwindow(currentFilePath,"Mvd-AM");
    other->show();
}

void MainWindow::mvdcentral()
{
    subwindow *other = new subwindow(currentFilePath,"Mvd-PC");
    other->show();
}

void MainWindow::shiozaki()
{
    subwindow *other = new subwindow(currentFilePath,"Shiozaki");
    other->show();
}

void MainWindow::pieti()
{
    subwindow *other = new subwindow(currentFilePath,"Pietikainen");
    other->show();
}

//Funciones umbralización
void MainWindow::manual()
{
    subwindow *other = new subwindow(currentFilePath,"Manual");
    other->show();
}
void MainWindow::porcentual()
{
    subwindow *other = new subwindow(currentFilePath,"Porcentual");
    other->show();
}
void MainWindow::histeresis()
{
    subwindow *other = new subwindow(currentFilePath,"Histeresis");
    other->show();
}
void MainWindow::otsu()
{
    subwindow *other = new subwindow(currentFilePath,"Otsu");
    other->show();
}

void MainWindow::rosin()
{
    subwindow *other = new subwindow(currentFilePath,"Rosin");
    other->show();
}
void MainWindow::rosinNor()
{
    subwindow *other = new subwindow(currentFilePath,"Rosin-Normalizado");
    other->show();
}
void MainWindow::rosinNorAcu()
{
    subwindow *other = new subwindow(currentFilePath,"Rosin-Normalizado_Acumulado_Inverso");
    other->show();
}
void MainWindow::proxi()
{
    subwindow *other = new subwindow(currentFilePath,"Proximidad");
    other->show();
}
void MainWindow::proxiAcu()
{
    subwindow *other = new subwindow(currentFilePath,"Proximidad_Acumulado_Inverso");
    other->show();
}
void MainWindow::dist()
{
    subwindow *other = new subwindow(currentFilePath,"Distancia");
    other->show();
}
void MainWindow::distAcu()
{
    subwindow *other = new subwindow(currentFilePath,"Distancia_Acumulado_Inverso");
    other->show();
}
void MainWindow::menor()
{
    subwindow *other = new subwindow(currentFilePath,"Diagonal");
    other->show();
}
void MainWindow::menorAcu()
{
    subwindow *other = new subwindow(currentFilePath,"Diagonal_Acumulado_Inverso");
    other->show();
}
void MainWindow::adap()
{
    subwindow *other = new subwindow(currentFilePath,"Adaptativo");
    other->show();
}
void MainWindow::adapAcu()
{
    subwindow *other = new subwindow(currentFilePath,"Adaptativo_Acumulado_Inverso");
    other->show();
}
void MainWindow::semi()
{
    subwindow *other = new subwindow(currentFilePath,"Semi-adaptativo");
    other->show();
}
void MainWindow::semiAcu()
{
    subwindow *other = new subwindow(currentFilePath,"Semi-adaptativo_Acumulado_Inverso");
    other->show();
}
//Funciones realce
void MainWindow::lineargray()
{
    subwindow *other = new subwindow(currentFilePath,"gray_Level");
    other->show();
}

void MainWindow::slide()
{
    subwindow *other = new subwindow(currentFilePath,"Histogram_Slide");
    other->show();
}

void MainWindow::shrink()
{
    subwindow *other = new subwindow(currentFilePath,"Histogram_Shrink");
    other->show();
}

void MainWindow::stretch()
{
    subwindow *other = new subwindow(currentFilePath,"Histogram_Stretch");
    other->show();
}

void MainWindow::adaptive()
{
    subwindow *other = new subwindow(currentFilePath,"Adaptive_Contrast");
    other->show();
}

void MainWindow::colorMap()
{
    subwindow *other = new subwindow(currentFilePath,"ColorMap");
    other->show();
}

void MainWindow::highpass()
{
    subwindow *other = new subwindow(currentFilePath,"Highpass_Filtering");
    other->show();
}

void MainWindow::highFrequency()
{
    subwindow *other = new subwindow(currentFilePath,"High_Frequency_Emphasis");
    other->show();
}

void MainWindow::moravec()
{
    subwindow *other = new subwindow(currentFilePath,"Moravec_Filter");
    other->show();
}

void MainWindow::homomorphic()
{
    subwindow *other = new subwindow(currentFilePath,"Homomorphic_Filtering");
    other->show();
}

void MainWindow::unsharp()
{
    subwindow *other = new subwindow(currentFilePath,"Unsharp_Masking");
    other->show();
}

void MainWindow::sharpening()
{
    subwindow *other = new subwindow(currentFilePath,"Sharpening");
    other->show();
}

void MainWindow::meanFilter()
{
    subwindow *other = new subwindow(currentFilePath,"Mean_Filter");
    other->show();
}
void MainWindow::medianFilter()
{
    subwindow *other = new subwindow(currentFilePath,"Median_Filter");
    other->show();
}

void MainWindow::gaussFilter()
{
    subwindow *other = new subwindow(currentFilePath,"Gaussian_Filter");
    other->show();
}

void MainWindow::kuwahara()
{
    subwindow *other = new subwindow(currentFilePath,"Kuwahara_Filter");
    other->show();
}

void MainWindow::normalizar()
{
    subwindow *other = new subwindow(currentFilePath,"Normalizar");
    other->show();
}
