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
    MyViewer* viewer = new MyViewer;

    TerrainMesh tm;

    //QMainWindow* mainWindow = new QMainWindow;
    MainWindow* mainWindow = new MainWindow;

    /*QSpinBox* resolutionSpinBox = new QSpinBox;
    resolutionSpinBox->setFixedSize(100, 30);
    resolutionSpinBox->setMaximum(100);
    resolutionSpinBox->setValue(tm.resolution);
    //QObject::connect(resolutionSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), &tm, [&tm](int valeur){
    //    tm.heightRange = valeur;
    //});

    QLabel* resolutionLabel = new QLabel;
    resolutionLabel->setText("Résolution : ");

    QSpinBox* heightRangeSpinBox = new QSpinBox;
    heightRangeSpinBox->setFixedSize(100, 30);
    heightRangeSpinBox->setMaximum(100);
    heightRangeSpinBox->setValue(tm.heightRange);
    //QObject::connect(comboBox, SIGNAL(currentIndexChanged(const QString&)), viewer, SLOT(onComboBoxIndexChanged(const QString&)));

    QLabel* heightRangeLabel = new QLabel;
    heightRangeLabel->setText("Plage de hauteurs : ");


    QWidget* parametresWidget = new QWidget;
    QVBoxLayout* comboBoxLayout = new QVBoxLayout;
    comboBoxLayout->setMargin(0);
    comboBoxLayout->setContentsMargins(QMargins(0,0,0,0));
    comboBoxLayout->setSpacing(0);
    comboBoxLayout->addWidget(resolutionLabel, 0, Qt::AlignTop);
    comboBoxLayout->addWidget(resolutionSpinBox, 0, Qt::AlignTop);
    comboBoxLayout->addWidget(heightRangeLabel, 0, Qt::AlignTop);
    comboBoxLayout->addWidget(heightRangeSpinBox, 0, Qt::AlignTop);

    parametresWidget->setLayout(comboBoxLayout);


    QDockWidget* dockWidget = new QDockWidget(" ", mainWindow);
    dockWidget->setWidget(parametresWidget);

    dockWidget->setFixedWidth(150);

    dockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);

    mainWindow->addDockWidget(Qt::RightDockWidgetArea, dockWidget);

    mainWindow->setCentralWidget(viewer);

    QObject::connect(viewer, SIGNAL(windowTitleUpdated(QString)), mainWindow, SLOT(setWindowTitle(QString)));
    viewer->updateTitle("myProject");

    mainWindow->setWindowIcon(QIcon("img/icons/icon.png"));*/
    mainWindow->show();
    //viewer->setFocus();

    return app.exec();
}
