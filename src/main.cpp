#include <QCoreApplication>
#include <QImage>
#include <QApplication>
#include <QDesktopWidget>
#include <QSurfaceFormat>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDebug>
#include <QDir>

#include <QToolBar>
#include "MyViewer.h"

#include "glwidget.h"
#include "mainwindow.h"

int main( int argc , char** argv )
{
    //Ex de base
    QApplication app( argc , argv );

    //Code de base dans la base de code
    MyViewer * viewer = new MyViewer;

    QMainWindow * mainWindow = new QMainWindow;
    QToolBar * toolBar = new QToolBar;
    toolBar->setIconSize(QSize(35,35));
    toolBar->setAutoFillBackground(true);
    toolBar->setStyleSheet("QToolBar { background: white; }");

    //toolbar
    //viewer->add_actions_to_toolBar(toolBar);
    //mainWindow->addToolBar(toolBar);

    mainWindow->setCentralWidget(viewer);

    QObject::connect( viewer , SIGNAL(windowTitleUpdated(QString)) , mainWindow , SLOT(setWindowTitle(QString)) );
    viewer->updateTitle("myProject");

    mainWindow->setWindowIcon(QIcon("img/icons/icon.png"));
    mainWindow->show();

    return app.exec();
}
