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
#include "image_ppm.h"

#include "perlinNoise.cpp"

int main( int argc , char** argv )
{
    QApplication app( argc , argv );

    //Code de base dans la base de code
    /*MyViewer * viewer = new MyViewer;

    QMainWindow * mainWindow = new QMainWindow;
    QToolBar * toolBar = new QToolBar;
    toolBar->setIconSize(QSize(35,35));
    toolBar->setAutoFillBackground(true);
    toolBar->setStyleSheet("QToolBar { background: white; }");
    viewer->add_actions_to_toolBar(toolBar);

    mainWindow->addToolBar(toolBar);

    mainWindow->setCentralWidget(viewer);

    QObject::connect( viewer , SIGNAL(windowTitleUpdated(QString)) , mainWindow , SLOT(setWindowTitle(QString)) );
    viewer->updateTitle("myProject");

    mainWindow->setWindowIcon(QIcon("img/icons/icon.png"));
    mainWindow->show();

    return app.exec();*/

    //Carte de bruit de Perlin
    int nH = 512, nW = 512, nTaille;
    char cNomImg[250];
    std::string perlinNoiseImage = "perlinNoise.pgm";
    strcpy(cNomImg, perlinNoiseImage.c_str());

    OCTET *ImgOut;

    nTaille = nH * nW;
    allocation_tableau(ImgOut, OCTET, nTaille);

    int octaves = 6;
    double frequency = 0.9;
    double persistence = 0.5;

    int seed = generateRandomSeed();

    for (int i = 0; i < nH; ++i) {
        for (int j = 0; j < nW; ++j) {

            double x = static_cast<double>(i) / nW;
            double y = static_cast<double>(j) / nH;

            double perlin = perlinNoise(octaves, frequency, persistence, x, y, seed) * 255;

            if (x < nW / 4) {
                perlin -= 25;
            } else if (x >= 3 * nW / 4) {
                perlin += 25;
            }

            if (perlin > 255) {
                perlin = 255;
            }
            else if (perlin < 0) {
                perlin = 0;
            }

            ImgOut[i*nW + j] = perlin;
        }
    }

    ecrire_image_pgm(cNomImg, ImgOut, nH, nW);
    free(ImgOut);

    QCoreApplication::setApplicationName("Leatina-generation-terrain");
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption multipleSampleOption("multisample", "Multisampling");
    parser.addOption(multipleSampleOption);
    QCommandLineOption coreProfileOption("coreprofile", "Use core profile");
    parser.addOption(coreProfileOption);
    QCommandLineOption transparentOption("transparent", "Transparent window");
    parser.addOption(transparentOption);

    parser.process(app);

    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
    if (parser.isSet(multipleSampleOption))
        fmt.setSamples(4);
    if (parser.isSet(coreProfileOption)) {
        fmt.setVersion(3, 2);
        fmt.setProfile(QSurfaceFormat::CoreProfile);
    }
    QSurfaceFormat::setDefaultFormat(fmt);

    MainWindow mainWindow;

    GLWidget::setTransparent(parser.isSet(transparentOption));
    if (GLWidget::isTransparent()) {
        mainWindow.setAttribute(Qt::WA_TranslucentBackground);
        mainWindow.setAttribute(Qt::WA_NoSystemBackground, false);
    }
    mainWindow.resize(mainWindow.sizeHint());
    int desktopArea = QApplication::desktop()->width() *
                      QApplication::desktop()->height();
    int widgetArea = mainWindow.width() * mainWindow.height();
    if (((float)widgetArea / (float)desktopArea) < 0.75f)
        mainWindow.show();
    else
        mainWindow.showMaximized();
    return app.exec();
}
