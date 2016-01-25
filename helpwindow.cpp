#include "helpwindow.h"

helpwindow::helpwindow()
{
    view = new QWebView(this);
    view->setBackgroundRole(QPalette::Base);
    view->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    view->load(QUrl::fromLocalFile(QApplication::applicationDirPath() + "/ayuda/index.htm"));

    setCentralWidget(view);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    this->resize(800,600);

    setWindowTitle("Manual de contenidos");
}


void helpwindow::about()
{
   QMessageBox::about(this, tr("Acerca del manual"),
            tr("El <b>manual</b> muestra los algoritmos usados en la aplicación y como funciona."));
}


void helpwindow::createActions()
{

    exitAct = new QAction(tr("Cerrar &Manual"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Cierra la ventana del manual"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));



    aboutAct = new QAction(tr("Sobre el &Manual"), this);
    aboutAct->setStatusTip(tr("Muestra la información del manual de contenido"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void helpwindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Archivo"));
    fileMenu->addAction(exitAct);


    viewMenu = menuBar()->addMenu(tr("&Navegación"));
    viewMenu->addAction(view->pageAction(QWebPage::Back));
    viewMenu->addAction(view->pageAction(QWebPage::Forward));
    viewMenu->addAction(view->pageAction(QWebPage::Reload));
    viewMenu->addAction(view->pageAction(QWebPage::Stop));



    helpMenu = menuBar()->addMenu(tr("&Ayuda"));
    helpMenu->addAction(aboutAct);
}


void helpwindow::createToolBars()
{
    viewToolBar = addToolBar(tr("Navegación"));
    viewToolBar->addAction(view->pageAction(QWebPage::Back));
    viewToolBar->addAction(view->pageAction(QWebPage::Forward));
    viewToolBar->addAction(view->pageAction(QWebPage::Reload));
    viewToolBar->addAction(view->pageAction(QWebPage::Stop));

}

void helpwindow::createStatusBar()
{
    statusBar()->showMessage(tr("Listo"));
}


void helpwindow::readSettings()
{
    QSettings settings("Proyecto", "Prototipo");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    move(pos);
    resize(size);
}


void helpwindow::writeSettings()
{
    QSettings settings("Proyecto", "Prototipo");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}


