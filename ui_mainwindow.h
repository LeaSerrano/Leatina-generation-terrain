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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
