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
//#include "mySimpleViewer.h"
#include "MyViewer.h"

#include "glwidget.h"
#include "mainwindow.h"

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
    //viewer->add_actions_to_toolBar(toolBar);

    mainWindow->addToolBar(toolBar);

    mainWindow->setCentralWidget(viewer);

    QObject::connect( viewer , SIGNAL(windowTitleUpdated(QString)) , mainWindow , SLOT(setWindowTitle(QString)) );
    viewer->updateTitle("myProject");

    mainWindow->setWindowIcon(QIcon("img/icons/icon.png"));
    mainWindow->show();

    return app.exec();*/

    /*QApplication application(argc, argv);

    // Create an instance of MyViewer
    MyViewer viewer;

    // Set up the viewer and add actions to the toolbar
    //viewer.init();
    QToolBar *toolBar = new QToolBar();
    viewer.add_actions_to_toolBar(toolBar);

    // Set up the main window
    QMainWindow mainWindow;
    mainWindow.setCentralWidget(&viewer);
    mainWindow.addToolBar(toolBar);

    // Set the window properties
    mainWindow.setWindowTitle("My 3D Viewer");
    mainWindow.setGeometry(100, 100, 800, 600);

    // Show the main window
    mainWindow.show();

    // Open a mesh (you can replace this with your own logic)
    viewer.open_mesh();*/

    /*QMainWindow mainWindow;
    MySimpleViewer *myOpenGLWidget = new MySimpleViewer(&mainWindow);
    mainWindow.setCentralWidget(myOpenGLWidget);

    mainWindow.resize(800, 600);
    mainWindow.show();*/

    // Start the application event loop
    //return application.exec();

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
