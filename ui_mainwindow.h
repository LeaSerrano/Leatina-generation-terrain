/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget_affichage_terrain;
    QSlider *horizontalSlider_resolution;
    QLabel *label_resolution;
    QSlider *horizontalSlider_heightRange;
    QLabel *label_heightRange;
    QPushButton *pushButton_reload;
    QLabel *label_perlinNoise;
    QPushButton *button_undo;
    QPushButton *button_redo;
    QPushButton *button_save_map;
    QPushButton *button_open_map;
    QSlider *verticalSlider_newHeightValue;
    QLabel *label_newHeightValue;
    QDial *dial_penSize;
    QLabel *label_penSize;
    QPushButton *pushButton_mode_FPS;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(868, 735);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget_affichage_terrain = new QWidget(centralwidget);
        widget_affichage_terrain->setObjectName(QString::fromUtf8("widget_affichage_terrain"));
        widget_affichage_terrain->setGeometry(QRect(0, 0, 661, 441));
        horizontalSlider_resolution = new QSlider(centralwidget);
        horizontalSlider_resolution->setObjectName(QString::fromUtf8("horizontalSlider_resolution"));
        horizontalSlider_resolution->setGeometry(QRect(680, 140, 160, 16));
        horizontalSlider_resolution->setOrientation(Qt::Horizontal);
        label_resolution = new QLabel(centralwidget);
        label_resolution->setObjectName(QString::fromUtf8("label_resolution"));
        label_resolution->setGeometry(QRect(680, 100, 91, 25));
        horizontalSlider_heightRange = new QSlider(centralwidget);
        horizontalSlider_heightRange->setObjectName(QString::fromUtf8("horizontalSlider_heightRange"));
        horizontalSlider_heightRange->setGeometry(QRect(680, 290, 160, 16));
        horizontalSlider_heightRange->setOrientation(Qt::Horizontal);
        label_heightRange = new QLabel(centralwidget);
        label_heightRange->setObjectName(QString::fromUtf8("label_heightRange"));
        label_heightRange->setGeometry(QRect(680, 250, 141, 25));
        pushButton_reload = new QPushButton(centralwidget);
        pushButton_reload->setObjectName(QString::fromUtf8("pushButton_reload"));
        pushButton_reload->setGeometry(QRect(660, 0, 28, 28));
        label_perlinNoise = new QLabel(centralwidget);
        label_perlinNoise->setObjectName(QString::fromUtf8("label_perlinNoise"));
        label_perlinNoise->setGeometry(QRect(0, 440, 300, 300));
        button_undo = new QPushButton(centralwidget);
        button_undo->setObjectName(QString::fromUtf8("button_undo"));
        button_undo->setGeometry(QRect(340, 450, 89, 25));
        button_redo = new QPushButton(centralwidget);
        button_redo->setObjectName(QString::fromUtf8("button_redo"));
        button_redo->setGeometry(QRect(340, 480, 89, 25));
        button_save_map = new QPushButton(centralwidget);
        button_save_map->setObjectName(QString::fromUtf8("button_save_map"));
        button_save_map->setGeometry(QRect(340, 550, 89, 25));
        button_open_map = new QPushButton(centralwidget);
        button_open_map->setObjectName(QString::fromUtf8("button_open_map"));
        button_open_map->setGeometry(QRect(340, 520, 89, 25));
        verticalSlider_newHeightValue = new QSlider(centralwidget);
        verticalSlider_newHeightValue->setObjectName(QString::fromUtf8("verticalSlider_newHeightValue"));
        verticalSlider_newHeightValue->setGeometry(QRect(520, 450, 16, 160));
        verticalSlider_newHeightValue->setMinimum(-255);
        verticalSlider_newHeightValue->setMaximum(255);
        verticalSlider_newHeightValue->setOrientation(Qt::Vertical);
        verticalSlider_newHeightValue->setTickPosition(QSlider::TicksAbove);
        verticalSlider_newHeightValue->setTickInterval(50);
        label_newHeightValue = new QLabel(centralwidget);
        label_newHeightValue->setObjectName(QString::fromUtf8("label_newHeightValue"));
        label_newHeightValue->setGeometry(QRect(570, 470, 71, 17));
        dial_penSize = new QDial(centralwidget);
        dial_penSize->setObjectName(QString::fromUtf8("dial_penSize"));
        dial_penSize->setGeometry(QRect(650, 500, 50, 64));
        dial_penSize->setMinimum(1);
        dial_penSize->setMaximum(10);
        dial_penSize->setSliderPosition(3);
        dial_penSize->setOrientation(Qt::Horizontal);
        dial_penSize->setInvertedAppearance(false);
        dial_penSize->setWrapping(false);
        dial_penSize->setNotchesVisible(true);
        label_penSize = new QLabel(centralwidget);
        label_penSize->setObjectName(QString::fromUtf8("label_penSize"));
        label_penSize->setGeometry(QRect(640, 470, 67, 17));
        pushButton_mode_FPS = new QPushButton(centralwidget);
        pushButton_mode_FPS->setObjectName(QString::fromUtf8("pushButton_mode_FPS"));
        pushButton_mode_FPS->setGeometry(QRect(740, 650, 89, 25));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 868, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_resolution->setText(QCoreApplication::translate("MainWindow", "Resolution : ", nullptr));
        label_heightRange->setText(QCoreApplication::translate("MainWindow", "Plage de hauteurs : ", nullptr));
        pushButton_reload->setText(QString());
        label_perlinNoise->setText(QString());
        button_undo->setText(QCoreApplication::translate("MainWindow", "undo", nullptr));
        button_redo->setText(QCoreApplication::translate("MainWindow", "redo", nullptr));
        button_save_map->setText(QCoreApplication::translate("MainWindow", "sauvegarder carte", nullptr));
        button_open_map->setText(QCoreApplication::translate("MainWindow", "ouvrir carte", nullptr));
        label_newHeightValue->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_penSize->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        pushButton_mode_FPS->setText(QCoreApplication::translate("MainWindow", "FPS", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
