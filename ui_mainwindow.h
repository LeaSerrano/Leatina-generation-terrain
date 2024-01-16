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
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget_affichage_terrain;
    QPushButton *pushButton_reload;
    QPushButton *button_save_map;
    QPushButton *button_open_map;
    QPushButton *pushButton_mode_FPS;
    QLabel *label_barre_haut;
    QLabel *label_titre;
    QFrame *frame_pen;
    QLabel *label_param_pen;
    QLabel *label_penSizeIMG;
    QDial *dial_penSize;
    QLabel *label_penSize;
    QPushButton *button_undo;
    QPushButton *button_redo;
    QLabel *label_newHeightValue;
    QSlider *verticalSlider_newHeightValue;
    QLabel *label_p255;
    QLabel *label_0;
    QLabel *label_m255;
    QFrame *frame_perlin;
    QLabel *label_fond_carte;
    QLabel *label_perlinNoise;
    QPushButton *button_show_map;
    QFrame *frame_param_mesh;
    QLabel *label_param_mesh;
    QLabel *label_resolution;
    QSlider *horizontalSlider_resolution;
    QLabel *label_heightRange;
    QSlider *horizontalSlider_heightRange;
    QPushButton *button_show_param_mesh;
    QFrame *frame_controls;
    QLabel *label_controls;
    QLabel *label_q;
    QLabel *label_s;
    QLabel *label_d;
    QLabel *label_z;
    QLabel *label_gauche;
    QLabel *label_bas;
    QLabel *label_droite;
    QLabel *label_haut;
    QPushButton *button_show_controls;
    QPushButton *button_show_erosion;
    QFrame *frame_erosion;
    QLabel *label_erosion;
    QLabel *label_nbRaindrops;
    QLabel *label_nbIteErosion;
    QSpinBox *spinBox_nbRaindrops;
    QSpinBox *spinBox_nbIteErosion;
    QPushButton *pushButton_erosion;
    QLabel *label_impact;
    QSpinBox *spinBox_impact;
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
        pushButton_reload = new QPushButton(centralwidget);
        pushButton_reload->setObjectName(QString::fromUtf8("pushButton_reload"));
        pushButton_reload->setGeometry(QRect(535, 0, 200, 59));
        QFont font;
        font.setFamily(QString::fromUtf8("Liberation Sans Narrow"));
        font.setPointSize(11);
        font.setBold(true);
        pushButton_reload->setFont(font);
        pushButton_reload->setStyleSheet(QString::fromUtf8("QPushButton { background-color: rgb(52, 78, 65); color: white; border-radius: 0px;}\n"
"QPushButton:hover { background-color: lightcoral;  color: white; border-radius: 0px;}"));
        button_save_map = new QPushButton(centralwidget);
        button_save_map->setObjectName(QString::fromUtf8("button_save_map"));
        button_save_map->setGeometry(QRect(735, 0, 150, 59));
        button_save_map->setFont(font);
        button_save_map->setStyleSheet(QString::fromUtf8("QPushButton { background-color: rgb(52, 78, 65); border-radius: 0px; color : white;}\n"
"QPushButton:hover { background-color: lightcoral; border-radius: 0px;}"));
        button_open_map = new QPushButton(centralwidget);
        button_open_map->setObjectName(QString::fromUtf8("button_open_map"));
        button_open_map->setGeometry(QRect(400, 0, 135, 59));
        button_open_map->setFont(font);
        button_open_map->setStyleSheet(QString::fromUtf8("QPushButton { background-color: rgb(52, 78, 65); border-radius: 0px; color : white;}\n"
"QPushButton:hover { background-color: lightcoral; border-radius: 0px;}"));
        pushButton_mode_FPS = new QPushButton(centralwidget);
        pushButton_mode_FPS->setObjectName(QString::fromUtf8("pushButton_mode_FPS"));
        pushButton_mode_FPS->setGeometry(QRect(1770, 0, 150, 59));
        pushButton_mode_FPS->setFont(font);
        pushButton_mode_FPS->setStyleSheet(QString::fromUtf8("QPushButton { background-color: rgb(52, 78, 65); border-radius: 0px; color : white;}\n"
"QPushButton:hover { background-color: lightcoral; border-radius: 0px;}"));
        label_barre_haut = new QLabel(centralwidget);
        label_barre_haut->setObjectName(QString::fromUtf8("label_barre_haut"));
        label_barre_haut->setGeometry(QRect(0, 0, 1920, 60));
        label_barre_haut->setStyleSheet(QString::fromUtf8("background-color: rgb(52, 78, 65);\n"
"border-bottom: 1px solid black;"));
        label_titre = new QLabel(centralwidget);
        label_titre->setObjectName(QString::fromUtf8("label_titre"));
        label_titre->setGeometry(QRect(0, 0, 400, 60));
        QFont font1;
        font1.setFamily(QString::fromUtf8("URW Gothic L"));
        font1.setPointSize(20);
        font1.setBold(false);
        label_titre->setFont(font1);
        label_titre->setStyleSheet(QString::fromUtf8("color : white;"));
        label_titre->setAlignment(Qt::AlignCenter);
        label_titre->setWordWrap(false);
        label_titre->setIndent(0);
        frame_pen = new QFrame(centralwidget);
        frame_pen->setObjectName(QString::fromUtf8("frame_pen"));
        frame_pen->setGeometry(QRect(35, 80, 260, 180));
        frame_pen->setFrameShape(QFrame::StyledPanel);
        frame_pen->setFrameShadow(QFrame::Raised);
        label_param_pen = new QLabel(frame_pen);
        label_param_pen->setObjectName(QString::fromUtf8("label_param_pen"));
        label_param_pen->setGeometry(QRect(0, 0, 260, 180));
        label_param_pen->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255,255);\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(193, 223, 196, 255), stop:1 rgba(222, 236, 221, 255));\n"
"border: 1px solid black;"));
        label_penSizeIMG = new QLabel(frame_pen);
        label_penSizeIMG->setObjectName(QString::fromUtf8("label_penSizeIMG"));
        label_penSizeIMG->setGeometry(QRect(25, 60, 100, 100));
        label_penSizeIMG->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border : 1px solid black;\n"
""));
        dial_penSize = new QDial(frame_pen);
        dial_penSize->setObjectName(QString::fromUtf8("dial_penSize"));
        dial_penSize->setGeometry(QRect(100, 130, 50, 50));
        dial_penSize->setMinimum(10);
        dial_penSize->setMaximum(100);
        dial_penSize->setSingleStep(10);
        dial_penSize->setValue(10);
        dial_penSize->setSliderPosition(10);
        dial_penSize->setOrientation(Qt::Horizontal);
        dial_penSize->setInvertedAppearance(false);
        dial_penSize->setWrapping(false);
        dial_penSize->setNotchesVisible(true);
        label_penSize = new QLabel(frame_pen);
        label_penSize->setObjectName(QString::fromUtf8("label_penSize"));
        label_penSize->setGeometry(QRect(20, 30, 111, 40));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Liberation Sans Narrow"));
        font2.setPointSize(11);
        label_penSize->setFont(font2);
        label_penSize->setAlignment(Qt::AlignCenter);
        button_undo = new QPushButton(frame_pen);
        button_undo->setObjectName(QString::fromUtf8("button_undo"));
        button_undo->setGeometry(QRect(170, 10, 20, 20));
        button_undo->setStyleSheet(QString::fromUtf8("QPushButton { background-color: white; border-radius: 10px;}\n"
"QPushButton:hover { background-color: lightcoral; border-radius: 10px;}"));
        button_redo = new QPushButton(frame_pen);
        button_redo->setObjectName(QString::fromUtf8("button_redo"));
        button_redo->setGeometry(QRect(200, 10, 20, 20));
        button_redo->setStyleSheet(QString::fromUtf8("QPushButton { background-color: white; border-radius: 10px;}\n"
"QPushButton:hover { background-color: lightgreen; border-radius: 10px;}"));
        label_newHeightValue = new QLabel(frame_pen);
        label_newHeightValue->setObjectName(QString::fromUtf8("label_newHeightValue"));
        label_newHeightValue->setGeometry(QRect(140, 30, 100, 40));
        label_newHeightValue->setFont(font2);
        label_newHeightValue->setAlignment(Qt::AlignCenter);
        verticalSlider_newHeightValue = new QSlider(frame_pen);
        verticalSlider_newHeightValue->setObjectName(QString::fromUtf8("verticalSlider_newHeightValue"));
        verticalSlider_newHeightValue->setGeometry(QRect(200, 60, 16, 100));
        verticalSlider_newHeightValue->setMinimum(-255);
        verticalSlider_newHeightValue->setMaximum(255);
        verticalSlider_newHeightValue->setOrientation(Qt::Vertical);
        verticalSlider_newHeightValue->setTickPosition(QSlider::TicksBelow);
        verticalSlider_newHeightValue->setTickInterval(50);
        label_p255 = new QLabel(frame_pen);
        label_p255->setObjectName(QString::fromUtf8("label_p255"));
        label_p255->setGeometry(QRect(220, 50, 40, 40));
        label_p255->setFont(font2);
        label_p255->setAlignment(Qt::AlignCenter);
        label_0 = new QLabel(frame_pen);
        label_0->setObjectName(QString::fromUtf8("label_0"));
        label_0->setGeometry(QRect(220, 90, 40, 40));
        label_0->setFont(font2);
        label_0->setAlignment(Qt::AlignCenter);
        label_m255 = new QLabel(frame_pen);
        label_m255->setObjectName(QString::fromUtf8("label_m255"));
        label_m255->setGeometry(QRect(220, 130, 40, 40));
        label_m255->setFont(font2);
        label_m255->setAlignment(Qt::AlignCenter);
        frame_perlin = new QFrame(centralwidget);
        frame_perlin->setObjectName(QString::fromUtf8("frame_perlin"));
        frame_perlin->setGeometry(QRect(35, 280, 540, 580));
        frame_perlin->setFrameShape(QFrame::StyledPanel);
        frame_perlin->setFrameShadow(QFrame::Raised);
        label_fond_carte = new QLabel(frame_perlin);
        label_fond_carte->setObjectName(QString::fromUtf8("label_fond_carte"));
        label_fond_carte->setGeometry(QRect(0, 0, 540, 580));
        label_fond_carte->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255,255);\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(193, 223, 196, 255), stop:1 rgba(222, 236, 221, 255));\n"
"border: 1px solid black;"));
        label_perlinNoise = new QLabel(frame_perlin);
        label_perlinNoise->setObjectName(QString::fromUtf8("label_perlinNoise"));
        label_perlinNoise->setGeometry(QRect(15, 55, 512, 512));
        label_perlinNoise->setStyleSheet(QString::fromUtf8("background-color :rgb(92, 115, 84);\n"
"border: 1px solid black;"));
        button_show_map = new QPushButton(centralwidget);
        button_show_map->setObjectName(QString::fromUtf8("button_show_map"));
        button_show_map->setGeometry(QRect(885, 0, 125, 59));
        button_show_map->setFont(font);
        button_show_map->setStyleSheet(QString::fromUtf8("QPushButton { background-color: rgb(52, 78, 65); border-radius: 0px; color : white;}\n"
"QPushButton:hover { background-color: lightcoral; border-radius: 0px;}"));
        frame_param_mesh = new QFrame(centralwidget);
        frame_param_mesh->setObjectName(QString::fromUtf8("frame_param_mesh"));
        frame_param_mesh->setGeometry(QRect(1345, 80, 540, 100));
        frame_param_mesh->setFrameShape(QFrame::StyledPanel);
        frame_param_mesh->setFrameShadow(QFrame::Raised);
        label_param_mesh = new QLabel(frame_param_mesh);
        label_param_mesh->setObjectName(QString::fromUtf8("label_param_mesh"));
        label_param_mesh->setGeometry(QRect(0, 0, 540, 100));
        label_param_mesh->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255,255);\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(193, 223, 196, 255), stop:1 rgba(222, 236, 221, 255));\n"
"border: 1px solid black;"));
        label_resolution = new QLabel(frame_param_mesh);
        label_resolution->setObjectName(QString::fromUtf8("label_resolution"));
        label_resolution->setGeometry(QRect(0, 40, 90, 60));
        label_resolution->setFont(font2);
        label_resolution->setAlignment(Qt::AlignCenter);
        horizontalSlider_resolution = new QSlider(frame_param_mesh);
        horizontalSlider_resolution->setObjectName(QString::fromUtf8("horizontalSlider_resolution"));
        horizontalSlider_resolution->setGeometry(QRect(90, 40, 150, 60));
        horizontalSlider_resolution->setOrientation(Qt::Horizontal);
        label_heightRange = new QLabel(frame_param_mesh);
        label_heightRange->setObjectName(QString::fromUtf8("label_heightRange"));
        label_heightRange->setGeometry(QRect(240, 40, 141, 60));
        label_heightRange->setFont(font2);
        label_heightRange->setAlignment(Qt::AlignCenter);
        horizontalSlider_heightRange = new QSlider(frame_param_mesh);
        horizontalSlider_heightRange->setObjectName(QString::fromUtf8("horizontalSlider_heightRange"));
        horizontalSlider_heightRange->setGeometry(QRect(380, 40, 150, 60));
        horizontalSlider_heightRange->setOrientation(Qt::Horizontal);
        button_show_param_mesh = new QPushButton(centralwidget);
        button_show_param_mesh->setObjectName(QString::fromUtf8("button_show_param_mesh"));
        button_show_param_mesh->setGeometry(QRect(1530, 0, 240, 59));
        button_show_param_mesh->setFont(font);
        button_show_param_mesh->setStyleSheet(QString::fromUtf8("QPushButton { background-color: rgb(52, 78, 65); border-radius: 0px; color : white;}\n"
"QPushButton:hover { background-color: lightcoral; border-radius: 0px;}"));
        frame_controls = new QFrame(centralwidget);
        frame_controls->setObjectName(QString::fromUtf8("frame_controls"));
        frame_controls->setGeometry(QRect(1345, 760, 540, 200));
        frame_controls->setFrameShape(QFrame::StyledPanel);
        frame_controls->setFrameShadow(QFrame::Raised);
        label_controls = new QLabel(frame_controls);
        label_controls->setObjectName(QString::fromUtf8("label_controls"));
        label_controls->setGeometry(QRect(0, 0, 540, 200));
        label_controls->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255,255);\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(193, 223, 196, 255), stop:1 rgba(222, 236, 221, 255));\n"
"border: 1px solid black;"));
        label_q = new QLabel(frame_controls);
        label_q->setObjectName(QString::fromUtf8("label_q"));
        label_q->setGeometry(QRect(20, 125, 64, 64));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Liberation Sans Narrow"));
        font3.setPointSize(25);
        label_q->setFont(font3);
        label_q->setStyleSheet(QString::fromUtf8("background-color : white;\n"
"border : 1px solid;\n"
"border-radius : 10px;"));
        label_q->setAlignment(Qt::AlignCenter);
        label_s = new QLabel(frame_controls);
        label_s->setObjectName(QString::fromUtf8("label_s"));
        label_s->setGeometry(QRect(90, 125, 64, 64));
        label_s->setFont(font3);
        label_s->setStyleSheet(QString::fromUtf8("background-color : white;\n"
"border : 1px solid;\n"
"border-radius : 10px;"));
        label_s->setAlignment(Qt::AlignCenter);
        label_d = new QLabel(frame_controls);
        label_d->setObjectName(QString::fromUtf8("label_d"));
        label_d->setGeometry(QRect(160, 125, 64, 64));
        label_d->setFont(font3);
        label_d->setStyleSheet(QString::fromUtf8("background-color : white;\n"
"border : 1px solid;\n"
"border-radius : 10px;"));
        label_d->setAlignment(Qt::AlignCenter);
        label_z = new QLabel(frame_controls);
        label_z->setObjectName(QString::fromUtf8("label_z"));
        label_z->setGeometry(QRect(90, 55, 64, 64));
        label_z->setFont(font3);
        label_z->setStyleSheet(QString::fromUtf8("background-color : white;\n"
"border : 1px solid;\n"
"border-radius : 10px;"));
        label_z->setAlignment(Qt::AlignCenter);
        label_gauche = new QLabel(frame_controls);
        label_gauche->setObjectName(QString::fromUtf8("label_gauche"));
        label_gauche->setGeometry(QRect(456, 125, 64, 64));
        QFont font4;
        font4.setPointSize(25);
        label_gauche->setFont(font4);
        label_gauche->setStyleSheet(QString::fromUtf8("background-color : white;\n"
"border : 1px solid;\n"
"border-radius : 10px;"));
        label_gauche->setAlignment(Qt::AlignCenter);
        label_bas = new QLabel(frame_controls);
        label_bas->setObjectName(QString::fromUtf8("label_bas"));
        label_bas->setGeometry(QRect(386, 125, 64, 64));
        label_bas->setFont(font4);
        label_bas->setStyleSheet(QString::fromUtf8("background-color : white;\n"
"border : 1px solid;\n"
"border-radius : 10px;"));
        label_bas->setAlignment(Qt::AlignCenter);
        label_droite = new QLabel(frame_controls);
        label_droite->setObjectName(QString::fromUtf8("label_droite"));
        label_droite->setGeometry(QRect(316, 125, 64, 64));
        label_droite->setFont(font4);
        label_droite->setStyleSheet(QString::fromUtf8("background-color : white;\n"
"border : 1px solid;\n"
"border-radius : 10px;"));
        label_droite->setAlignment(Qt::AlignCenter);
        label_haut = new QLabel(frame_controls);
        label_haut->setObjectName(QString::fromUtf8("label_haut"));
        label_haut->setGeometry(QRect(386, 55, 64, 64));
        label_haut->setFont(font4);
        label_haut->setStyleSheet(QString::fromUtf8("background-color : white;\n"
"border : 1px solid;\n"
"border-radius : 10px;"));
        label_haut->setAlignment(Qt::AlignCenter);
        button_show_controls = new QPushButton(centralwidget);
        button_show_controls->setObjectName(QString::fromUtf8("button_show_controls"));
        button_show_controls->setGeometry(QRect(1360, 0, 170, 59));
        button_show_controls->setFont(font);
        button_show_controls->setStyleSheet(QString::fromUtf8("QPushButton { background-color: rgb(52, 78, 65); border-radius: 0px; color : white;}\n"
"QPushButton:hover { background-color: lightcoral; border-radius: 0px;}"));
        button_show_erosion = new QPushButton(centralwidget);
        button_show_erosion->setObjectName(QString::fromUtf8("button_show_erosion"));
        button_show_erosion->setGeometry(QRect(1010, 0, 125, 59));
        button_show_erosion->setFont(font);
        button_show_erosion->setStyleSheet(QString::fromUtf8("QPushButton { background-color: rgb(52, 78, 65); border-radius: 0px; color : white;}\n"
"QPushButton:hover { background-color: lightcoral; border-radius: 0px;}"));
        frame_erosion = new QFrame(centralwidget);
        frame_erosion->setObjectName(QString::fromUtf8("frame_erosion"));
        frame_erosion->setGeometry(QRect(1345, 200, 540, 150));
        frame_erosion->setFrameShape(QFrame::StyledPanel);
        frame_erosion->setFrameShadow(QFrame::Raised);
        label_erosion = new QLabel(frame_erosion);
        label_erosion->setObjectName(QString::fromUtf8("label_erosion"));
        label_erosion->setGeometry(QRect(0, 0, 540, 150));
        label_erosion->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255,255);\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(193, 223, 196, 255), stop:1 rgba(222, 236, 221, 255));\n"
"border: 1px solid black;"));
        label_nbRaindrops = new QLabel(frame_erosion);
        label_nbRaindrops->setObjectName(QString::fromUtf8("label_nbRaindrops"));
        label_nbRaindrops->setGeometry(QRect(0, 40, 130, 60));
        label_nbRaindrops->setFont(font2);
        label_nbRaindrops->setAlignment(Qt::AlignCenter);
        label_nbIteErosion = new QLabel(frame_erosion);
        label_nbIteErosion->setObjectName(QString::fromUtf8("label_nbIteErosion"));
        label_nbIteErosion->setGeometry(QRect(185, 40, 120, 60));
        label_nbIteErosion->setFont(font2);
        label_nbIteErosion->setAlignment(Qt::AlignCenter);
        spinBox_nbRaindrops = new QSpinBox(frame_erosion);
        spinBox_nbRaindrops->setObjectName(QString::fromUtf8("spinBox_nbRaindrops"));
        spinBox_nbRaindrops->setGeometry(QRect(130, 50, 50, 40));
        spinBox_nbIteErosion = new QSpinBox(frame_erosion);
        spinBox_nbIteErosion->setObjectName(QString::fromUtf8("spinBox_nbIteErosion"));
        spinBox_nbIteErosion->setGeometry(QRect(305, 50, 50, 40));
        pushButton_erosion = new QPushButton(frame_erosion);
        pushButton_erosion->setObjectName(QString::fromUtf8("pushButton_erosion"));
        pushButton_erosion->setGeometry(QRect(220, 100, 100, 40));
        pushButton_erosion->setFont(font2);
        label_impact = new QLabel(frame_erosion);
        label_impact->setObjectName(QString::fromUtf8("label_impact"));
        label_impact->setGeometry(QRect(365, 40, 100, 60));
        label_impact->setFont(font2);
        label_impact->setAlignment(Qt::AlignCenter);
        spinBox_impact = new QSpinBox(frame_erosion);
        spinBox_impact->setObjectName(QString::fromUtf8("spinBox_impact"));
        spinBox_impact->setGeometry(QRect(475, 50, 50, 40));
        MainWindow->setCentralWidget(centralwidget);
        widget_affichage_terrain->raise();
        frame_perlin->raise();
        frame_pen->raise();
        label_barre_haut->raise();
        pushButton_reload->raise();
        button_save_map->raise();
        button_open_map->raise();
        pushButton_mode_FPS->raise();
        label_titre->raise();
        button_show_map->raise();
        frame_param_mesh->raise();
        button_show_param_mesh->raise();
        frame_controls->raise();
        button_show_controls->raise();
        button_show_erosion->raise();
        frame_erosion->raise();
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
        pushButton_reload->setText(QCoreApplication::translate("MainWindow", "G\303\251n\303\251rer une nouvelle carte", nullptr));
        button_save_map->setText(QCoreApplication::translate("MainWindow", "Sauvegarder la carte", nullptr));
        button_open_map->setText(QCoreApplication::translate("MainWindow", "Charger une carte", nullptr));
        pushButton_mode_FPS->setText(QCoreApplication::translate("MainWindow", "Afficher vue FPS", nullptr));
        label_titre->setText(QCoreApplication::translate("MainWindow", "Leatina Generation Terrain", nullptr));
        label_param_pen->setText(QString());
        label_penSizeIMG->setText(QString());
        label_penSize->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Taille pinceau : 0</p></body></html>", nullptr));
        button_undo->setText(QCoreApplication::translate("MainWindow", "undo", nullptr));
        button_redo->setText(QCoreApplication::translate("MainWindow", "redo", nullptr));
        label_newHeightValue->setText(QCoreApplication::translate("MainWindow", "Hauteur : 0", nullptr));
        label_p255->setText(QCoreApplication::translate("MainWindow", "+255", nullptr));
        label_0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_m255->setText(QCoreApplication::translate("MainWindow", "-255", nullptr));
        label_fond_carte->setText(QString());
        label_perlinNoise->setText(QString());
        button_show_map->setText(QCoreApplication::translate("MainWindow", "Afficher la carte", nullptr));
        label_param_mesh->setText(QString());
        label_resolution->setText(QCoreApplication::translate("MainWindow", "R\303\251solution : ", nullptr));
        label_heightRange->setText(QCoreApplication::translate("MainWindow", "Plage de hauteurs : ", nullptr));
        button_show_param_mesh->setText(QCoreApplication::translate("MainWindow", "Afficher les param\303\250tres du maillage", nullptr));
        label_controls->setText(QString());
        label_q->setText(QCoreApplication::translate("MainWindow", "Q", nullptr));
        label_s->setText(QCoreApplication::translate("MainWindow", "S", nullptr));
        label_d->setText(QCoreApplication::translate("MainWindow", "D", nullptr));
        label_z->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        label_gauche->setText(QCoreApplication::translate("MainWindow", "\342\206\222", nullptr));
        label_bas->setText(QCoreApplication::translate("MainWindow", "\342\206\223", nullptr));
        label_droite->setText(QCoreApplication::translate("MainWindow", "\342\206\220", nullptr));
        label_haut->setText(QCoreApplication::translate("MainWindow", "\342\206\221", nullptr));
        button_show_controls->setText(QCoreApplication::translate("MainWindow", "Afficher les contr\303\264les", nullptr));
        button_show_erosion->setText(QCoreApplication::translate("MainWindow", "Eroder la carte", nullptr));
        label_erosion->setText(QString());
        label_nbRaindrops->setText(QCoreApplication::translate("MainWindow", "Nombre de gouttes :", nullptr));
        label_nbIteErosion->setText(QCoreApplication::translate("MainWindow", "Longueur \303\251rosion :", nullptr));
        pushButton_erosion->setText(QCoreApplication::translate("MainWindow", "Eroder", nullptr));
        label_impact->setText(QCoreApplication::translate("MainWindow", "Intensit\303\251 impact :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
