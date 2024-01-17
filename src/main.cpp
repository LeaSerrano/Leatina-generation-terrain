#include <QCoreApplication>
#include <QImage>
#include <QApplication>
#include <QDesktopWidget>
#include <QSurfaceFormat>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDebug>
#include <QDir>
#include <QObject>

#include <QToolBar>
#include <QSpinBox>
#include <QDockWidget>
#include <QComboBox>
#include <QLabel>
#include "MyViewer.h"

#include "mainwindow.h"
#include "terrainMesh.h"


int main(int argc, char** argv) {
    QApplication app(argc, argv);

    // Code de base dans la base de code

    MainWindow* mainWindow = new MainWindow;

    mainWindow->show();

    return app.exec();
}
