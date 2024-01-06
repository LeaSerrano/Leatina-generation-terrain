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
    QLabel *label_barre_haut;
    QLabel *label_fond_carte;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_titre;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1920, 1020);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget_affichage_terrain = new QWidget(centralwidget);
        widget_affichage_terrain->setObjectName(QString::fromUtf8("widget_affichage_terrain"));
        widget_affichage_terrain->setGeometry(QRect(610, 160, 700, 700));
        widget_affichage_terrain->setStyleSheet(QString::fromUtf8("background-color:rgb(36, 31, 49);"));
        horizontalSlider_resolution = new QSlider(centralwidget);
        horizontalSlider_resolution->setObjectName(QString::fromUtf8("horizontalSlider_resolution"));
        horizontalSlider_resolution->setGeometry(QRect(1350, 10, 160, 16));
        horizontalSlider_resolution->setOrientation(Qt::Horizontal);
        label_resolution = new QLabel(centralwidget);
        label_resolution->setObjectName(QString::fromUtf8("label_resolution"));
        label_resolution->setGeometry(QRect(1260, 10, 91, 25));
        horizontalSlider_heightRange = new QSlider(centralwidget);
        horizontalSlider_heightRange->setObjectName(QString::fromUtf8("horizontalSlider_heightRange"));
        horizontalSlider_heightRange->setGeometry(QRect(1650, 10, 160, 16));
        horizontalSlider_heightRange->setOrientation(Qt::Horizontal);
        label_heightRange = new QLabel(centralwidget);
        label_heightRange->setObjectName(QString::fromUtf8("label_heightRange"));
        label_heightRange->setGeometry(QRect(1520, 10, 141, 25));
        pushButton_reload = new QPushButton(centralwidget);
        pushButton_reload->setObjectName(QString::fromUtf8("pushButton_reload"));
        pushButton_reload->setGeometry(QRect(735, 10, 40, 40));
        pushButton_reload->setStyleSheet(QString::fromUtf8("QPushButton { background-color: white; border-radius: 20px;}\n"
"QPushButton:hover { background-color: lightcoral; border-radius: 20px;}"));
        label_perlinNoise = new QLabel(centralwidget);
        label_perlinNoise->setObjectName(QString::fromUtf8("label_perlinNoise"));
        label_perlinNoise->setGeometry(QRect(49, 335, 512, 512));
        label_perlinNoise->setStyleSheet(QString::fromUtf8("background-color :rgb(92, 115, 84);\n"
"border: 1px solid black;"));
        button_undo = new QPushButton(centralwidget);
        button_undo->setObjectName(QString::fromUtf8("button_undo"));
        button_undo->setGeometry(QRect(1210, 100, 89, 25));
        button_redo = new QPushButton(centralwidget);
        button_redo->setObjectName(QString::fromUtf8("button_redo"));
        button_redo->setGeometry(QRect(1300, 100, 89, 25));
        button_save_map = new QPushButton(centralwidget);
        button_save_map->setObjectName(QString::fromUtf8("button_save_map"));
        button_save_map->setGeometry(QRect(580, 10, 151, 40));
        QFont font;
        font.setFamily(QString::fromUtf8("Liberation Sans Narrow"));
        font.setPointSize(11);
        font.setBold(true);
        button_save_map->setFont(font);
        button_save_map->setStyleSheet(QString::fromUtf8("QPushButton { background-color: white; border-radius: 7px;}\n"
"QPushButton:hover { background-color: lightcoral; border-radius: 7px;}"));
        button_open_map = new QPushButton(centralwidget);
        button_open_map->setObjectName(QString::fromUtf8("button_open_map"));
        button_open_map->setGeometry(QRect(450, 10, 125, 40));
        button_open_map->setFont(font);
        button_open_map->setStyleSheet(QString::fromUtf8("QPushButton { background-color: white; border-radius: 7px;}\n"
"QPushButton:hover { background-color: lightcoral; border-radius: 7px;}"));
        verticalSlider_newHeightValue = new QSlider(centralwidget);
        verticalSlider_newHeightValue->setObjectName(QString::fromUtf8("verticalSlider_newHeightValue"));
        verticalSlider_newHeightValue->setGeometry(QRect(470, 170, 16, 160));
        verticalSlider_newHeightValue->setMinimum(-255);
        verticalSlider_newHeightValue->setMaximum(255);
        verticalSlider_newHeightValue->setOrientation(Qt::Vertical);
        verticalSlider_newHeightValue->setTickPosition(QSlider::TicksBelow);
        verticalSlider_newHeightValue->setTickInterval(50);
        label_newHeightValue = new QLabel(centralwidget);
        label_newHeightValue->setObjectName(QString::fromUtf8("label_newHeightValue"));
        label_newHeightValue->setGeometry(QRect(390, 170, 71, 17));
        label_newHeightValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        dial_penSize = new QDial(centralwidget);
        dial_penSize->setObjectName(QString::fromUtf8("dial_penSize"));
        dial_penSize->setGeometry(QRect(1140, 550, 50, 64));
        dial_penSize->setMinimum(10);
        dial_penSize->setMaximum(100);
        dial_penSize->setSingleStep(10);
        dial_penSize->setValue(10);
        dial_penSize->setSliderPosition(10);
        dial_penSize->setOrientation(Qt::Horizontal);
        dial_penSize->setInvertedAppearance(false);
        dial_penSize->setWrapping(false);
        dial_penSize->setNotchesVisible(true);
        label_penSize = new QLabel(centralwidget);
        label_penSize->setObjectName(QString::fromUtf8("label_penSize"));
        label_penSize->setGeometry(QRect(1150, 520, 67, 17));
        pushButton_mode_FPS = new QPushButton(centralwidget);
        pushButton_mode_FPS->setObjectName(QString::fromUtf8("pushButton_mode_FPS"));
        pushButton_mode_FPS->setGeometry(QRect(1810, 20, 89, 25));
        label_barre_haut = new QLabel(centralwidget);
        label_barre_haut->setObjectName(QString::fromUtf8("label_barre_haut"));
        label_barre_haut->setGeometry(QRect(0, 0, 1920, 60));
        label_barre_haut->setStyleSheet(QString::fromUtf8("background-color: rgb(52, 78, 65);\n"
"border-bottom: 1px solid black;"));
        label_fond_carte = new QLabel(centralwidget);
        label_fond_carte->setObjectName(QString::fromUtf8("label_fond_carte"));
        label_fond_carte->setGeometry(QRect(35, 280, 540, 580));
        label_fond_carte->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255,255);\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(193, 223, 196, 255), stop:1 rgba(222, 236, 221, 255));\n"
"border: 1px solid black;"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(490, 160, 31, 31));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(490, 300, 31, 31));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(490, 230, 31, 40));
        label_titre = new QLabel(centralwidget);
        label_titre->setObjectName(QString::fromUtf8("label_titre"));
        label_titre->setGeometry(QRect(0, 0, 400, 60));
        QFont font1;
        font1.setFamily(QString::fromUtf8("URW Gothic"));
        font1.setPointSize(20);
        font1.setBold(false);
        label_titre->setFont(font1);
        label_titre->setStyleSheet(QString::fromUtf8("color : white;"));
        label_titre->setAlignment(Qt::AlignCenter);
        label_titre->setWordWrap(false);
        label_titre->setIndent(0);
        MainWindow->setCentralWidget(centralwidget);
        widget_affichage_terrain->raise();
        label_fond_carte->raise();
        label_barre_haut->raise();
        horizontalSlider_resolution->raise();
        label_resolution->raise();
        horizontalSlider_heightRange->raise();
        label_heightRange->raise();
        pushButton_reload->raise();
        label_perlinNoise->raise();
        button_undo->raise();
        button_redo->raise();
        button_save_map->raise();
        button_open_map->raise();
        verticalSlider_newHeightValue->raise();
        label_newHeightValue->raise();
        dial_penSize->raise();
        label_penSize->raise();
        pushButton_mode_FPS->raise();
        label->raise();
        label_2->raise();
        label_3->raise();
        label_titre->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1920, 22));
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
        button_save_map->setText(QCoreApplication::translate("MainWindow", "sauvegarder la carte", nullptr));
        button_open_map->setText(QCoreApplication::translate("MainWindow", "ouvrir une carte", nullptr));
        label_newHeightValue->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_penSize->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        pushButton_mode_FPS->setText(QCoreApplication::translate("MainWindow", "entrer mode FPS", nullptr));
        label_fond_carte->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "255", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "-255", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_titre->setText(QCoreApplication::translate("MainWindow", "Leatina Generation Terrain", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
