#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QWebView>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QWebView;
QT_END_NAMESPACE

class helpwindow: public QMainWindow
{
    Q_OBJECT

public:
    helpwindow();


private slots:
    void about();


private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();

    QWebView *view;


    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
    QToolBar *fileToolBar;
    QToolBar *viewToolBar;
    QAction *exitAct;
    QAction *aboutAct;
};


#endif // HELPWINDOW_H
