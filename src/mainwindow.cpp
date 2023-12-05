/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow), isLeftButtonPressed(false) {
    ui->setupUi(this);

    viewer = new MyViewer();

    viewer->setParent(ui->widget_affichage_terrain);
    viewer->setGeometry(ui->widget_affichage_terrain->geometry());

    ui->horizontalSlider_resolution->setValue(viewer->terrainMesh.resolution);
    ui->horizontalSlider_resolution->setMinimum(10);
    ui->horizontalSlider_resolution->setMaximum(300);
    QObject::connect(ui->horizontalSlider_resolution, SIGNAL(sliderReleased()), this, SLOT(onResolutionSliderReleased()));

    ui->horizontalSlider_heightRange->setValue(viewer->terrainMesh.heightRange);
    ui->horizontalSlider_heightRange->setMinimum(10);
    ui->horizontalSlider_heightRange->setMaximum(180);
    QObject::connect(ui->horizontalSlider_heightRange, SIGNAL(sliderReleased()), this, SLOT(onHeightRangeSliderReleased()));

    ui->pushButton_reload->setIcon(QIcon("./icons/reload_icon_black.png"));
    ui->pushButton_reload->setStyleSheet("background-color : white");
    QObject::connect(ui->pushButton_reload, SIGNAL(clicked()), this, SLOT(onReloadButtonClicked()));

    //QPixmap pixmap("perlinNoise.png");
    QImage originalImage("perlinNoise.png");
    editedImage = originalImage.copy();

    //ui->label_perlinNoise->setPixmap(pixmap);
    ui->label_perlinNoise->setMouseTracking(true);
    ui->label_perlinNoise->installEventFilter(this);
    int coin_x = ui->label_perlinNoise->geometry().x();
    int coin_y = ui->label_perlinNoise->geometry().y();
    ui->label_perlinNoise->setGeometry(coin_x, coin_y, editedImage.width(), editedImage.height());
    ui->label_perlinNoise->setPixmap(QPixmap::fromImage(editedImage));

    QObject::connect(ui->button_undo, &QPushButton::clicked, this, &MainWindow::undoDrawingPath);
    QObject::connect(ui->button_redo, &QPushButton::clicked, this, &MainWindow::redoDrawingPath);


    viewer->setFocus();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onResolutionSliderReleased() {
    int value = ui->horizontalSlider_resolution->value();

    qDebug() << "resolution : " << value;

    viewer->terrainMesh.resolution = value;
    viewer->terrainMesh.generateMesh();

    viewer->setFocus();
}

void MainWindow::onHeightRangeSliderReleased() {
    int value = ui->horizontalSlider_heightRange->value();
    viewer->terrainMesh.heightRange = value;
    viewer->terrainMesh.generateMesh();

    viewer->setFocus();
}

void MainWindow::onReloadButtonClicked() {
    viewer->terrainMesh.perlinNoiseCreated = false;
    viewer->terrainMesh.generateMesh();

    viewer->setFocus();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event){
    if (obj == ui->label_perlinNoise) {
            if (event->type() == QEvent::MouseButtonPress) {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
                if (mouseEvent->button() == Qt::LeftButton) {
                    isLeftButtonPressed = true;
                    startPoint = mouseEvent->localPos();

                    //point de départ tracé
                    currentPath.moveTo(startPoint);

                    previousPaths.push(currentPath);
                    redoPaths.clear();
                }
            } else if (event->type() == QEvent::MouseMove && isLeftButtonPressed) {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
                //drawingPath(static_cast<QMouseEvent*>(event));
                drawingPath(mouseEvent);
            } else if (event->type() == QEvent::MouseButtonRelease) {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
                if (mouseEvent->button() == Qt::LeftButton) {
                    isLeftButtonPressed = false;
                    //currentPath = QPainterPath();
                    startPoint = QPointF();
                }
            }
        }
        return QMainWindow::eventFilter(obj, event);
}

void MainWindow::undoDrawingPath() {
    if (!previousPaths.isEmpty()) {
        redoPaths.push(currentPath);
        currentPath = previousPaths.pop();
        updateDrawingPath();
    }
}

void MainWindow::redoDrawingPath() {
    if (!redoPaths.isEmpty()) {
        previousPaths.push(currentPath);
        currentPath = redoPaths.pop();
        updateDrawingPath();
    }
}

void MainWindow::updateDrawingPath() {
    QImage tempImage(editedImage.size(), QImage::Format_ARGB32);
    tempImage.fill(Qt::transparent);

    QPainter painter(&tempImage);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawImage(0, 0, editedImage);
    painter.setPen(QPen(Qt::white, 1));
    painter.drawPath(currentPath);
    painter.end();

    ui->label_perlinNoise->setPixmap(QPixmap::fromImage(tempImage));

}

void MainWindow::drawingPath(QMouseEvent* mouseEvent)
{
    QPointF mousePos = mouseEvent->localPos();

    // Ajout point au tracé
    currentPath.lineTo(mousePos);

    // Actualiser l'affichage de l'image
    int coin_x = ui->label_perlinNoise->geometry().x();
    int coin_y = ui->label_perlinNoise->geometry().y();
    ui->label_perlinNoise->setGeometry(coin_x, coin_y, editedImage.width(), editedImage.height());

    // Création image temporaire pour dessiner le tracé
    QImage tempImage(editedImage.size(), QImage::Format_ARGB32);
    tempImage.fill(Qt::transparent);

    // Dessiner tracé sur image temporaire
    QPainter painter(&tempImage);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawImage(0, 0, editedImage);
    painter.setPen(QPen(Qt::white, 1));
    painter.drawPath(currentPath);
    painter.end();

    // Afficher l'image temporaire sur le QLabel
    ui->label_perlinNoise->setPixmap(QPixmap::fromImage(tempImage));
}

