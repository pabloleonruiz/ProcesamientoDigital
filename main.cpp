#include <QApplication>
#include <QTextCodec>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(application);
    // Configuración: acentuación, etc.
    QTextCodec *linuxCodec=QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(linuxCodec);
    QTextCodec::setCodecForCStrings(linuxCodec);
    QTextCodec::setCodecForLocale(linuxCodec);
    QApplication app(argc, argv);
    app.setOrganizationName("Pablo");
    app.setApplicationName("Procesamiento digital de imagenes");
    MainWindow mainWin;

    mainWin.show();
    return app.exec();
}
