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
    editedImage = editedImage.convertToFormat(QImage::Format_ARGB32);

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
    penSize = 3;
    ui->dial_penSize->setValue(penSize);
    ui->label_penSize->setText(QString::number(penSize));
    QObject::connect(ui->dial_penSize, &QDial::valueChanged, this, [=](){
        penSize = ui->dial_penSize->value();
        ui->label_penSize->setText(QString::number(penSize));
        currentPath->setPathPen_width(penSize);
    });

    //Hauteur de la nouvelle valeur de hauteur
    newHeightValue = -10;
    ui->verticalSlider_newHeightValue->setValue(newHeightValue);
    ui->label_newHeightValue->setText(QString::number(newHeightValue));
    QObject::connect(ui->verticalSlider_newHeightValue, &QSlider::valueChanged, this, [=]() {
        newHeightValue = ui->verticalSlider_newHeightValue->value();
        ui->label_newHeightValue->setText(QString::number(newHeightValue));
    });

    //Sauvegarde terrain
    QObject::connect(ui->button_save_map, &QPushButton::clicked, this, [=]() {
        downloadMap(viewer->terrainMesh.getMap());
    });

    //Ouverture terrain
    QObject::connect(ui->button_open_map, &QPushButton::clicked, this, [=]() {
        uploadMap();
    });

    combinePathsImages(pathsImages);
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
    editedImage = editedImage.convertToFormat(QImage::Format_ARGB32);

    //currentPath.clear();
    undoPaths.clear();
    redoPaths.clear();

    pathsImages.clear();
    combinePathsImages(pathsImages);
    updateMesh(combinedImage);

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

                    currentPath = new Path();
                    currentPath->setHeightValue(newHeightValue);
                    currentPath->setPathPen_width(penSize);
                    currentPath->startDrawingPath(mouseEvent);

                    undoPaths.append(currentPath);
                    redoPaths.clear();
                }
            } else if (event->type() == QEvent::MouseMove && isLeftButtonPressed) {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

                currentPath->drawingPath(mouseEvent, editedImage); //Appel editedImage  : juste pour la taille img
                //editedImage = currentPath->getPathImage().copy();

                //Affichage Image résultat + Image tracé rouge
                update_label_perlinNoise(combinedImage, currentPath->getLayerImage());

            } else if (event->type() == QEvent::MouseButtonRelease) {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
                if (mouseEvent->button() == Qt::LeftButton) {
                    isLeftButtonPressed = false;

                    currentPath->setPixelsPath();
                    currentPath->addModification(editedImage); //Appel editedImage : récup couleur de base

                    //Ajout du tracé dans la liste
                    pathsImages.append(currentPath->renderPathImage);

                    //Génération image combinée des tracés
                    combinePathsImages(pathsImages);

                    editedImage = combinedImage.copy();
                    updateMesh(editedImage);

                    // editedImage.save("edited.png");
                    // combinedImage.save("combined.png");

                    //Affichage du tracé rouge
                    //update_label_perlinNoise(editedImage, currentPath->getLayerImage());

                    currentPath->endDrawingPath();
                }
            }
        }
    viewer->setFocus();
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::update_label_perlinNoise(QImage editedImage, QImage layerImage){
    QImage combinedImage(editedImage.size(), QImage::Format_ARGB32);
    combinedImage.fill(Qt::transparent); // Initialise l'image avec un fond transparent
    QPainter cpainter(&combinedImage);

    cpainter.drawImage(0, 0, editedImage);
    cpainter.drawImage(0, 0, layerImage);
    cpainter.end();

    ui->label_perlinNoise->setPixmap(QPixmap::fromImage(combinedImage));
}

void MainWindow::combinePathsImages(QList<QImage> pathsImages){
    combinedImage = QImage(originalImage.size(), QImage::Format_ARGB32);
    combinedImage.fill(Qt::transparent);

    QPainter cpainter(&combinedImage);
    QImage copy_originalImage = originalImage.copy();
    copy_originalImage = copy_originalImage.convertToFormat(QImage::Format_ARGB32);
    cpainter.drawImage(0, 0, copy_originalImage);
    for (const QImage& pathImage : pathsImages){
        cpainter.drawImage(0, 0, pathImage);
    }
    cpainter.end();


    ui->label_perlinNoise->setPixmap(QPixmap::fromImage(combinedImage));
}


// Enlever le tracé
void MainWindow::undoDrawingPath() {
    if (!undoPaths.isEmpty()) {
        //Enlever le tracé du currentPath
        //currentPath->removeModification(editedImage);
        //editedImage = currentPath->getPathImage().copy();

        pathsImages.removeLast();
        combinePathsImages(pathsImages);
        editedImage = combinedImage.copy();
        updateMesh(editedImage);

        //Ajouter à redo
        redoPaths.append(currentPath);

        //Mettre à jour le currentPath par le "précédent"
        currentPath = undoPaths.takeLast();
    }
}

// Refaire le tracé
void MainWindow::redoDrawingPath() {
    if (!redoPaths.isEmpty()) {

        //Mettre à jour le currentPath par le "suivant"
        currentPath = redoPaths.takeLast();

        //Ajouter à undo
        undoPaths.append(currentPath);

        //Remettre le tracé dans la liste des tracés
        pathsImages.append(currentPath->renderPathImage);
        currentPath->addModification(editedImage);

        combinePathsImages(pathsImages);
        editedImage = combinedImage.copy();
        updateMesh(editedImage);
    }
}

// Actualiser le maillage
void MainWindow::updateMesh(QImage image){
    viewer->terrainMesh.perlinNoise->ImgPerlin = image;
    viewer->terrainMesh.generateMesh();

    viewer->setFocus();
    ui->widget_affichage_terrain->setFocus();
}

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
