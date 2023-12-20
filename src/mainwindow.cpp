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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), isLeftButtonPressed(false) {
    ui->setupUi(this);
    setWindowTitle("Leatina Generation Terrain");

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

    //Image originale
    originalImage = QImage("perlinNoise.png");

    editedImage = originalImage.copy();

    //ui->label_perlinNoise->setPixmap(pixmap);
    ui->label_perlinNoise->setMouseTracking(true);
    ui->label_perlinNoise->installEventFilter(this);
    int coin_x = ui->label_perlinNoise->geometry().x();
    int coin_y = ui->label_perlinNoise->geometry().y();
    ui->label_perlinNoise->setGeometry(coin_x, coin_y, editedImage.width(), editedImage.height());
    ui->label_perlinNoise->setPixmap(QPixmap::fromImage(editedImage));

    //concerne le tracé
    QObject::connect(ui->button_undo, &QPushButton::clicked, this, &MainWindow::undoDrawingPath);
    QObject::connect(ui->button_redo, &QPushButton::clicked, this, &MainWindow::redoDrawingPath);

    //Pinceau
    //pathPen.setColor(Qt::white);
    //pathPen.setWidth(3);
    //pathPen.setJoinStyle(Qt::RoundJoin);

    //Hauteur de la nouvelle valeur de hauteur
    newHeightValue = -10;
    ui->verticalSlider_newHeightValue->setValue(newHeightValue);
    QObject::connect(ui->verticalSlider_newHeightValue, &QSlider::valueChanged, this, [=]() {
        newHeightValue = ui->verticalSlider_newHeightValue->value();
        ui->label_newHeightValue->setText(QString::number(newHeightValue));
    });

    QObject::connect(ui->button_save_map, &QPushButton::clicked, this, [=]() {
        downloadMap(viewer->terrainMesh.getMap());
    });

    QObject::connect(ui->button_open_map, &QPushButton::clicked, this, [=]() {
        uploadMap();
    });

    viewer->setFocus();

}

MainWindow::~MainWindow() {
    delete ui;
}

// Modifier résolution
void MainWindow::onResolutionSliderReleased() {
    int value = ui->horizontalSlider_resolution->value();

    qDebug() << "resolution : " << value;

    viewer->terrainMesh.resolution = value;
    viewer->terrainMesh.generateMesh();

    viewer->setFocus();
}

// Modifier étendue (range)
void MainWindow::onHeightRangeSliderReleased() {
    int value = ui->horizontalSlider_heightRange->value();
    viewer->terrainMesh.heightRange = value;
    viewer->terrainMesh.generateMesh();

    viewer->setFocus();
}


// Regénérer carte + maillage
void MainWindow::onReloadButtonClicked() {
    viewer->terrainMesh.perlinNoiseCreated = false;
    viewer->terrainMesh.generateMesh();

    originalImage = QImage("perlinNoise.png");
    //ui->label_perlinNoise->setPixmap(QPixmap::fromImage(originalImage));
    editedImage = originalImage.copy();

    //currentPath.clear();
    previousPaths.clear();
    redoPaths.clear();

    ui->label_perlinNoise->setPixmap(QPixmap::fromImage(editedImage));

    viewer->setFocus();
}

// Permet de savoir si la souris est en train de faire un clic gauche + mouvement dans le label de la carte
bool MainWindow::eventFilter(QObject *obj, QEvent *event){
    if (obj == ui->label_perlinNoise) {
            if (event->type() == QEvent::MouseButtonPress) {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
                if (mouseEvent->button() == Qt::LeftButton) {
                    isLeftButtonPressed = true;
                    //_startPoint = mouseEvent->localPos();

                    //point de départ tracé
                    //_currentPath.moveTo(startPoint);

                    //
                    currentPath = new Path();
                    currentPath->startDrawingPath(mouseEvent);

                    previousPaths.append(currentPath);
                    redoPaths.clear();
                }
            } else if (event->type() == QEvent::MouseMove && isLeftButtonPressed) {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
                //drawingPath(mouseEvent);
                currentPath->drawingPath(mouseEvent, editedImage);
                qDebug() << "tracé ?";
            } else if (event->type() == QEvent::MouseButtonRelease) {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
                if (mouseEvent->button() == Qt::LeftButton) {
                    isLeftButtonPressed = false;
                    //currentPath = QPainterPath();
                    //_startPoint = QPointF();
                    //getPixelsFromPath(layerImage);
                   // getPixelsFromPath(redPixels);
                    currentPath->endDrawingPath();
                }
            }
        }

        return QMainWindow::eventFilter(obj, event);
}

// // Enlever le tracé
// void MainWindow::undoDrawingPath() {
//     if (!previousPaths.isEmpty()) {
//         redoPaths.push(currentPath);
//         currentPath = previousPaths.pop();
//         updateDrawingPath();
//     }
// }

// // Refaire le tracé
// void MainWindow::redoDrawingPath() {
//     if (!redoPaths.isEmpty()) {
//         previousPaths.push(currentPath);
//         currentPath = redoPaths.pop();
//         updateDrawingPath();
//     }
// }

// Enlever le tracé
void MainWindow::undoDrawingPath() {
    if (!previousPaths.isEmpty()) {
        redoPaths.append(currentPath);
        currentPath = previousPaths.takeLast();
        //updateDrawingPath();
    }
}

// Refaire le tracé
void MainWindow::redoDrawingPath() {
    if (!redoPaths.isEmpty()) {
        previousPaths.append(currentPath);
        currentPath = redoPaths.takeLast();
        //updateDrawingPath();
    }
}


// Actualiser le maillage
void MainWindow::updateMesh(QImage image){
    viewer->terrainMesh.perlinNoise->ImgPerlin = image;
    viewer->terrainMesh.generateMesh();

    viewer->setFocus();
    ui->widget_affichage_terrain->setFocus();
}

// Actualiser le tracé
// void MainWindow::updateDrawingPath() {
//     QImage layerImage(editedImage.size(), QImage::Format_ARGB32);
//     layerImage.fill(Qt::transparent);

//     QPainter painter(&layerImage);
//     painter.setRenderHint(QPainter::Antialiasing, true);
//     painter.drawImage(0, 0, editedImage);
//     painter.setPen(pathPen);
//     painter.drawPath(currentPath);
//     painter.end();

//     ui->label_perlinNoise->setPixmap(QPixmap::fromImage(layerImage));
//     updateMesh(layerImage);
// }


// void MainWindow::drawingPath(QMouseEvent* mouseEvent)
// {
//     QPointF mousePos = mouseEvent->localPos();

//     // Ajout point au tracé
//     currentPath.lineTo(mousePos);

//     // Actualiser l'affichage de l'image
//     int coin_x = ui->label_perlinNoise->geometry().x();
//     int coin_y = ui->label_perlinNoise->geometry().y();
//     ui->label_perlinNoise->setGeometry(coin_x, coin_y, editedImage.width(), editedImage.height());

//     // Création image temporaire pour dessiner le tracé
//     //QImage layerImage(editedImage.size(), QImage::Format_ARGB32);
//     //layerImage = QImage(editedImage.size(), QImage::Format_ARGB32);
//     layerImage = QImage(editedImage.size(), editedImage.format());
//     layerImage.fill(Qt::transparent);

//     // Dessiner tracé sur image temporaire
//     QPainter painter(&layerImage);
//     painter.setRenderHint(QPainter::Antialiasing, true);
//     painter.drawImage(0, 0, layerImage);
//     pathPen.setColor(Qt::red);
//     pathPen.setJoinStyle(Qt::RoundJoin);
//     painter.setPen(pathPen);
//     painter.drawPath(currentPath);
//     painter.end();

//     QList<QPoint> redPixels;
//     for (int y = 0; y < layerImage.height(); ++y) {
//         for (int x = 0; x < layerImage.width(); ++x) {
//             QColor pixelLayerValue = layerImage.pixel(x, y);

//             // Vérifier si le pixel appartient au tracé rouge
//             if (pixelLayerValue == Qt::red) {
//                 // Ajouter les coordonnées du pixel à la liste
//                 redPixels.append(QPoint(x, y));
//                 //qDebug() << "X:" << x << ", Y:" << y;
//             }
//         }
//     }

//     getPixelsFromPath(redPixels);

//     //QPainterPathStroker stroker;
//     //stroker.setWidth(pathPen.width()); // Définir la largeur du trait (à ajuster selon vos besoins)
//     //QPainterPath outline = stroker.createStroke(currentPath);

//     // Récupérer les points du chemin résultant

//     // QList<QPointF> points;
//     // for (int i = 0; i < currentPath.elementCount(); ++i) {
//     //     QPointF point = currentPath.elementAt(i);
//     //     points.append(point);
//     // }

//     // // Afficher les positions x, y des points
//     // for (const QPointF& point : points) {
//     //     int x = static_cast<int>(point.x());
//     //     int y = static_cast<int>(point.y());
//     //     qDebug() << "X:" << x << ", Y:" << y;
//     //     QColor editedPixelColor = editedImage.pixelColor(x, y);

//     //     int red = qBound(0, editedPixelColor.red() + newHeightValue, 255);
//     //     int green = qBound(0, editedPixelColor.green() + newHeightValue, 255);
//     //     int blue = qBound(0, editedPixelColor.blue() + newHeightValue, 255);

//     //     editedImage.setPixel(x, y, QColor(red, green, blue).rgb());
//     // }

//     //getPixelsFromPath(currentPath);

//     // Afficher l'image temporaire sur le QLabel
//     //ui->label_perlinNoise->setPixmap(QPixmap::fromImage(layerImage));
//     //ui->label_perlinNoise->setPixmap(QPixmap::fromImage(editedImage));

//     QImage combinedImage(editedImage.size(), editedImage.format());
//     combinedImage.fill(Qt::transparent); // Initialise l'image avec un fond transparent

//     QPainter cpainter(&combinedImage);
//     cpainter.drawImage(0, 0, editedImage);
//     //cpainter.drawImage(0, 0, layerImage);
//     cpainter.end();

//     // Affichez l'image combinée dans le QLabel
//     ui->label_perlinNoise->setPixmap(QPixmap::fromImage(combinedImage));

//     // Actualisation du maillage
//     updateMesh(editedImage);


// }

// void MainWindow::getPixelsFromPath(QList<QPoint> redPixels)
// {
//     //QImage rgbImage = editedImage.convertToFormat(QImage::Format_RGB32);

//     for (const QPoint& pixel : redPixels){
//         qDebug() << editedImage.format();
//         //qDebug() << rgbImage.format();
//         int x = pixel.x();
//         int y = pixel.y();

//         qDebug() << "Pixel > X:" << x << ", Y:" << y;

//         // QRgb rgbPixelColor = rgbImage.pixel(x, y);

//         // int grayValue = qGray(rgbPixelColor);
//         // int newGrayValue = qBound(0, grayValue + newHeightValue, 255);

//         // rgbImage.setPixel(x, y, qRgb(newGrayValue, newGrayValue, newGrayValue));

//         QRgb editedPixelColor = editedImage.pixel(x, y);

//         int grayValue = qGray(editedPixelColor);
//         qDebug() << grayValue;

//         int newGrayValue = qBound(0, grayValue + newHeightValue, 255);

//         qDebug() << newGrayValue;

//         //editedImage.setPixel(x, y, newGrayValue);
//         editedImage.setPixel(x, y, qRgb(newGrayValue, newGrayValue, newGrayValue));

//         QImage rgbImage = editedImage.convertToFormat(QImage::Format_RGB32);

//         ui->label_perlinNoise->setPixmap(QPixmap::fromImage(rgbImage));

//         //ui->label_perlinNoise->setPixmap(QPixmap::fromImage(editedImage));
//     }
//     // QPainterPathStroker stroker;
//     // stroker.setWidth(pathPen.width()); // Définir la largeur du trait (à ajuster selon vos besoins)
//     // QPainterPath outline = stroker.createStroke(currentPath);

//     // // Récupérer les points du chemin résultant
//     // QList<QPointF> points;
//     // for (int i = 0; i < outline.elementCount(); ++i) {
//     //     QPointF point = outline.elementAt(i);
//     //     points.append(point);
//     // }

//     // // Afficher les positions x, y des points
//     // for (const QPointF& point : points) {
//     //     int x = static_cast<int>(point.x());
//     //     int y = static_cast<int>(point.y());
//     //     qDebug() << "X:" << x << ", Y:" << y;
//     //     QColor editedPixelColor = editedImage.pixelColor(x, y);

//     //     int red = qBound(0, editedPixelColor.red() + newHeightValue, 255);
//     //     int green = qBound(0, editedPixelColor.green() + newHeightValue, 255);
//     //     int blue = qBound(0, editedPixelColor.blue() + newHeightValue, 255);

//     //     editedImage.setPixel(x, y, QColor(red, green, blue).rgb());

//     //}

//     // // Accéder aux pixels de l'image
//     // for (int y = 0; y < image.height(); ++y)
//     // {
//     //     for (int x = 0; x < image.width(); ++x)
//     //     {
//     //         QPointF point(x, y);

//     //         // Vérifier si le point est sur le tracé du chemin et n'est pas à l'intérieur du tracé
//     //         //if (currentPath)
//     //         //{
//     //             // Appliquer la transformation de couleur à l'image éditée
//     //             QColor editedPixelColor = editedImage.pixelColor(x, y);

//     //             int red = qBound(0, editedPixelColor.red() + newHeightValue, 255);
//     //             int green = qBound(0, editedPixelColor.green() + newHeightValue, 255);
//     //             int blue = qBound(0, editedPixelColor.blue() + newHeightValue, 255);

//     //             // Appliquer la nouvelle couleur avec la luminosité ajustée à l'image éditée
//     //             editedImage.setPixel(x, y, QColor(red, green, blue).rgb());
//     //         //}
//     //     }
//     // }
// }

void MainWindow::downloadMap(QImage image){
    // Boîte de dialogue pour save la carte
    QString filePath = QFileDialog::getSaveFileName(this, tr("Enregistrer une carte"), QDir::homePath(), tr("Images (*.png)"));

    if (filePath.isEmpty()){
        return;
    }

    if (!filePath.toLower().endsWith(".png")) {
        filePath += ".png";
    }

    if(image.save(filePath, "png")){
        qDebug() << "L'image de la carte a bien été sauvergardée ici : " << filePath;
    }else{
        qDebug() << "Erreur lors de la sauvegarde de l'image de la carte.";
    }
}

void MainWindow::uploadMap(){
    QString filePath = QFileDialog::getOpenFileName(this, tr("Ouvrir une carte"), QDir::homePath(), tr("Images (*.png)"));

    if (filePath.isEmpty()){
        return;
    }else{

    }

    originalImage = QImage(filePath);
    ui->label_perlinNoise->setPixmap(QPixmap::fromImage(originalImage));
    updateMesh(originalImage);
    viewer->setFocus();

}
