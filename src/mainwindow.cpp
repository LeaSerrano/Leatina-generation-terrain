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

    //this->setStyleSheet("background-color: rgb(52, 78, 65);");

    ui->statusbar->hide();

    // AFFICHAGE DU TERRAIN
    ui->widget_affichage_terrain->setGeometry(0, 0, width(), height());
    ui->widget_affichage_terrain->lower();
    viewer = new MyViewer();
    viewer->saveCameraInFile("initCam.txt");
    viewer->setParent(ui->widget_affichage_terrain);
    viewer->setGeometry(ui->widget_affichage_terrain->geometry());

    // CFG APPARENCE BOUTONS/BARRES

    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect;
    shadowEffect->setBlurRadius(10);
    shadowEffect->setColor(QColor(0, 0, 0, 200)); // Couleur de l'ombre et opacité
    shadowEffect->setOffset(10,10);

    ui->label_barre_haut->setGraphicsEffect(shadowEffect);
    ui->label_fond_carte->setGraphicsEffect(shadowEffect);

    // Barre carte Perlin------------------------------------------------------------------------------------------------
    QLabel *barre = new QLabel();
    barre->setParent(ui->label_fond_carte);
    barre->setStyleSheet("background-color: white;");
    barre->setGeometry(0,0,ui->frame_perlin->width(), 40);

    QFont URWFont("URW Gothic L",11);
    QLabel *textebarre = new QLabel();
    textebarre->setParent(barre);
    textebarre->setText("Carte du bruit de perlin");
    textebarre->setStyleSheet("background-color: rgb(52, 78, 65); border: none; color: white;");
    textebarre->setGeometry(0,0,ui->frame_perlin->width(), 40);
    textebarre->setContentsMargins(15, 10, 10, 10);
    textebarre->setFont(URWFont);

    QPushButton *fermercarte = new QPushButton();
    fermercarte->setParent(barre);
    fermercarte->setGeometry(barre->width()-30, 10, 20,20);
    fermercarte->setStyleSheet("QPushButton {background-color: rgb(200, 88, 88); border: none; border-radius: 10px;} "
                               "QPushButton:hover {background-color: lightcoral; border: none; border-radius: 10px;} ");
    fermercarte->setIcon(QIcon("./icons/fermer.png"));
    QObject::connect(fermercarte, &QPushButton::clicked, this, [=]() {
        hideCarte(true);
    });
    hideCarte(true);

    // Bouton affichage carte
    ui->button_show_map->setIcon(QIcon("./icons/visible_w.png"));
    QObject::connect(ui->button_show_map, &QPushButton::clicked, this, [=]() {
        hideCarte(false);
    });

    // Bouton affichage paramètres pinceau
    QFont Libe("Liberation Sans Narrow",11);
    QPushButton *boutonParam = new QPushButton();
    boutonParam->setParent(barre);
    boutonParam->setGeometry(ui->frame_perlin->width()-180,10, 140, 20);
    boutonParam->setStyleSheet("QPushButton {background-color: rgb(102, 128, 115); border: none; border-radius: 10px;} "
                               "QPushButton:hover {background-color: rgb(122, 148, 135); border: none; border-radius: 10px;} ");
    boutonParam->setText("Paramètres pinceau");
    boutonParam->setFont(Libe);
    boutonParam->setIcon(QIcon("./icons/editer.png"));
    QObject::connect(boutonParam, &QPushButton::clicked, this, [=]() {
        isHidden = !isHidden;
        hideParam(isHidden);
    });

    // Bouton affichage marqueur pour setup localisation FPS
    QPushButton *boutonMarqueur = new QPushButton();
    boutonMarqueur->setParent(barre);
    boutonMarqueur->setGeometry(190,10, 20, 20);
    boutonMarqueur->setStyleSheet("QPushButton {background-color: rgb(102, 128, 115); border: none; border-radius: 10px;} "
                               "QPushButton:hover {background-color: rgb(255, 0, 0); border: none; border-radius: 10px;} "
                               "QPushButton:checked {background-color: rgb(255, 0, 0); border: none; border-radius: 10px;} ");
    boutonMarqueur->setIcon(QIcon("./icons/marqueur.png"));
    boutonMarqueur->setCheckable(true);
    QObject::connect(boutonMarqueur, &QPushButton::clicked, this, [=]() {
        isMarqueurMode = !isMarqueurMode;
        if(!isMarqueurMode){
            ui->label_perlinNoise->setPixmap(QPixmap::fromImage(editedImage));
            boutonMarqueur->setChecked(false);
            viewer->isMarkerOn = false;
            viewer->update();
        } else {
            mergeImages(editedImage, markedImage);
            boutonMarqueur->setChecked(true);
            viewer->isMarkerOn = true;
            viewer->update();
        }
    });

    // Barre paramètres pinceau-------------------------------------------------------------------------------------------
    QLabel *barreParam = new QLabel();
    barreParam->setParent(ui->label_param_pen);
    barreParam->setStyleSheet("background-color: white;");
    barreParam->setGeometry(0,0,ui->frame_pen->width(), 40);

    QLabel *textebarreParam = new QLabel();
    textebarreParam->setParent(barreParam);
    textebarreParam->setText("Paramètres pinceau");
    textebarreParam->setStyleSheet("background-color: rgb(52, 78, 65); border: none; color: white;");
    textebarreParam->setGeometry(0,0,ui->frame_pen->width(), 40);
    textebarreParam->setContentsMargins(15, 10, 10, 10);
    textebarreParam->setFont(URWFont);

    QPushButton *fermerParam = new QPushButton();
    fermerParam->setParent(barreParam);
    fermerParam->setGeometry(textebarreParam->width()-30, 10, 20,20);
    fermerParam->setStyleSheet("QPushButton {background-color: rgb(200, 88, 88); border: none; border-radius: 10px;} "
                               "QPushButton:hover {background-color: lightcoral; border: none; border-radius: 10px;} ");
    fermerParam->setIcon(QIcon("./icons/fermer.png"));
    QObject::connect(fermerParam, &QPushButton::clicked, this, [=]() {
        hideParam(true);
        isHidden = true;
    });

    // Barre paramètres mesh (A DROITE)-------------------------------------------------------------------------------------
    QLabel *barreParamMesh = new QLabel();
    barreParamMesh->setParent(ui->label_param_mesh);
    barreParamMesh->setStyleSheet("background-color: white;");
    barreParamMesh->setGeometry(0,0,ui->frame_param_mesh->width(), 40);

    QLabel *textebarreParamMesh = new QLabel();
    textebarreParamMesh->setParent(barreParamMesh);
    textebarreParamMesh->setText("Paramètres du maillage de la carte");
    textebarreParamMesh->setStyleSheet("background-color: rgb(52, 78, 65); border: none; color: white;");
    textebarreParamMesh->setGeometry(0,0,ui->frame_param_mesh->width(), 40);
    textebarreParamMesh->setContentsMargins(15, 10, 10, 10);
    textebarreParamMesh->setFont(URWFont);

    QPushButton *fermerParamMesh = new QPushButton();
    fermerParamMesh->setParent(barreParamMesh);
    fermerParamMesh->setGeometry(barreParamMesh->width()-30, 10, 20,20);
    fermerParamMesh->setStyleSheet("QPushButton {background-color: rgb(200, 88, 88); border: none; border-radius: 10px;} "
                               "QPushButton:hover {background-color: lightcoral; border: none; border-radius: 10px;} ");
    fermerParamMesh->setIcon(QIcon("./icons/fermer.png"));
    QObject::connect(fermerParamMesh, &QPushButton::clicked, this, [=]() {
        hideParamMesh(true);
    });
    hideParamMesh(true);

    ui->button_show_param_mesh->setIcon(QIcon("./icons/grid_w.png"));
    QObject::connect(ui->button_show_param_mesh, &QPushButton::clicked, this, [=]() {
        hideParamMesh(false);
    });

    // Barre voir contrôles (A DROITE)-------------------------------------------------------------------------------------
    QLabel *barreControles = new QLabel();
    barreControles->setParent(ui->label_controls);
    barreControles->setStyleSheet("background-color: white;");
    barreControles->setGeometry(0,0,ui->frame_controls->width(), 40);

    QLabel *textebarreControles = new QLabel();
    textebarreControles->setParent(barreControles);
    textebarreControles->setText("Contrôles clavier");
    textebarreControles->setStyleSheet("background-color: rgb(52, 78, 65); border: none; color: white;");
    textebarreControles->setGeometry(0,0,ui->frame_controls->width(), 40);
    textebarreControles->setContentsMargins(15, 10, 10, 10);
    textebarreControles->setFont(URWFont);

    QPushButton *fermerControles = new QPushButton();
    fermerControles->setParent(barreControles);
    fermerControles->setGeometry(barreControles->width()-30, 10, 20,20);
    fermerControles->setStyleSheet("QPushButton {background-color: rgb(200, 88, 88); border: none; border-radius: 10px;} "
                                   "QPushButton:hover {background-color: lightcoral; border: none; border-radius: 10px;} ");
    fermerControles->setIcon(QIcon("./icons/fermer.png"));
    QObject::connect(fermerControles, &QPushButton::clicked, this, [=]() {
        hideControles(true);
    });
    hideControles(false);

    ui->button_show_controls->setIcon(QIcon("./icons/clavier_w.png"));
    QObject::connect(ui->button_show_controls, &QPushButton::clicked, this, [=]() {
        hideControles(false);
    });

    ui->label_z->setStyleSheet(toucheOff);
    ui->label_q->setStyleSheet(toucheOff);
    ui->label_s->setStyleSheet(toucheOff);
    ui->label_d->setStyleSheet(toucheOff);

    //Barre fenêtre Erosion (A DROITE)-------------------------------------------------------------
    QLabel *barreErosion = new QLabel();
    barreErosion->setParent(ui->label_erosion);
    barreErosion->setStyleSheet("background-color: white;");
    barreErosion->setGeometry(0,0,ui->frame_erosion->width(), 40);

    QLabel *textebarreErosion = new QLabel();
    textebarreErosion->setParent(barreErosion);
    textebarreErosion->setText("Erosion par gouttes d'eau du terrain");
    textebarreErosion->setStyleSheet("background-color: rgb(52, 78, 65); border: none; color: white;");
    textebarreErosion->setGeometry(0,0,ui->frame_erosion->width(), 40);
    textebarreErosion->setContentsMargins(15, 10, 10, 10);
    textebarreErosion->setFont(URWFont);

    QPushButton *fermerErosion = new QPushButton();
    fermerErosion->setParent(barreErosion);
    fermerErosion->setGeometry(barreErosion->width()-30, 10, 20,20);
    fermerErosion->setStyleSheet("QPushButton {background-color: rgb(200, 88, 88); border: none; border-radius: 10px;} "
                                   "QPushButton:hover {background-color: lightcoral; border: none; border-radius: 10px;} ");
    fermerErosion->setIcon(QIcon("./icons/fermer.png"));
    QObject::connect(fermerErosion, &QPushButton::clicked, this, [=]() {
        hideErosion(true);
    });
    hideErosion(true);

    ui->button_show_erosion->setIcon(QIcon("./icons/erosion_w.png"));
    QObject::connect(ui->button_show_erosion, &QPushButton::clicked, this, [=]() {
        hideErosion(false);
    });

    ui->spinBox_nbRaindrops->setMinimum(50);
    ui->spinBox_nbRaindrops->setMaximum(150);
    ui->spinBox_nbRaindrops->setValue(viewer->terrainMesh.nbRainDrops);
    connect(ui->spinBox_nbRaindrops, SIGNAL(valueChanged(int)), this, SLOT(onSpinBox_nbRaindropsChanged()));


    ui->spinBox_nbIteErosion->setMinimum(20);
    ui->spinBox_nbIteErosion->setMaximum(100);
    ui->spinBox_nbIteErosion->setValue(viewer->terrainMesh.nbErosionIterations);
    connect(ui->spinBox_nbIteErosion, SIGNAL(valueChanged(int)), this, SLOT(onSpinBox_nbIteErosionChanged()));

    ui->spinBox_impact->setMinimum(10);
    ui->spinBox_impact->setMaximum(40);
    ui->spinBox_impact->setValue(viewer->terrainMesh.intensiteImpact);
    connect(ui->spinBox_impact, SIGNAL(valueChanged(int)), this, SLOT(onSpinBox_impactChanged()));

    QObject::connect(ui->pushButton_erosion, &QPushButton::clicked, this, [=]() {
        viewer->terrainMesh.simulateHydraulicErosion(viewer->terrainMesh.nbRainDrops);
        editedImage = viewer->terrainMesh.perlinNoise->ImgPerlin.copy();
        editedImage.convertToFormat(QImage::Format_ARGB32);
        ui->label_perlinNoise->setPixmap(QPixmap::fromImage(editedImage));
        updateMesh(editedImage);
        //viewer->terrainMesh.perlinNoise->ImgPerlin.save("test.png");
    });

    //-----------------------------------------------------------------------------------------------

    //UNDO ET REDO
    ui->button_undo->setText("");
    ui->button_undo->setIcon(QIcon("./icons/undo.png"));

    ui->button_redo->setText("");
    ui->button_redo->setIcon(QIcon("./icons/forward.png"));

    // BOUTONS SAVE/OPEN CARTE
    //Sauvegarde CARTE
    ui->button_save_map->setIcon(QIcon("./icons/download_w.png"));
    QObject::connect(ui->button_save_map, &QPushButton::clicked, this, [=]() {
        downloadMap(viewer->terrainMesh.getMap());
    });

    //Ouverture CARTE
    ui->button_open_map->setIcon(QIcon("./icons/upload_w.png"));
    QObject::connect(ui->button_open_map, &QPushButton::clicked, this, [=]() {
        uploadMap();
    });

    // BOUTON MODE FPS
    ui->pushButton_mode_FPS->setIcon(QIcon("./icons/360_w.png"));
    QObject::connect(ui->pushButton_mode_FPS, SIGNAL(clicked()), this, SLOT(changerVuePremierePersonne()));

    // CFG SLIDER RESOLUTION
    ui->horizontalSlider_resolution->setValue(viewer->terrainMesh.resolution);
    ui->horizontalSlider_resolution->setMinimum(10);
    ui->horizontalSlider_resolution->setMaximum(180);
    QObject::connect(ui->horizontalSlider_resolution, SIGNAL(sliderReleased()), this, SLOT(onResolutionSliderReleased()));

    // CFG SLIDER HAUTEUR
    ui->horizontalSlider_heightRange->setValue(viewer->terrainMesh.heightRange);
    ui->horizontalSlider_heightRange->setMinimum(10);
    ui->horizontalSlider_heightRange->setMaximum(180);
    QObject::connect(ui->horizontalSlider_heightRange, SIGNAL(sliderReleased()), this, SLOT(onHeightRangeSliderReleased()));

    // CFG GENERER NOUVELLE CARTE
    ui->pushButton_reload->setIcon(QIcon("./icons/regen.png"));
    //ui->pushButton_reload->setStyleSheet("background-color : white");
    QObject::connect(ui->pushButton_reload, SIGNAL(clicked()), this, SLOT(onReloadButtonClicked()));    

    //----- CFG IMAGES CARTE -----//
    //Image originale
    originalImage = QImage("perlinNoise.png");

    editedImage = originalImage.copy();
    editedImage = editedImage.convertToFormat(QImage::Format_ARGB32);

    markedImage = originalImage.copy();
    markedImage = markedImage.convertToFormat(QImage::Format_ARGB32);
    markedImage.fill(Qt::transparent);

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
    penSize = 10;
    ui->dial_penSize->setValue(penSize);
    ui->label_penSize->setText("Taille pinceau : " + QString::number(penSize));
    updatePreviewPenSize(penSize);
    QObject::connect(ui->dial_penSize, &QDial::valueChanged, this, [=](){
        penSize = ui->dial_penSize->value();
        ui->label_penSize->setText("Taille pinceau : " + QString::number(penSize));
        updatePreviewPenSize(penSize);
    });

    //Hauteur de la nouvelle valeur de hauteur (pinceau)
    newHeightValue = -10;
    ui->verticalSlider_newHeightValue->setValue(newHeightValue);
    ui->label_newHeightValue->setText("Hauteur : " + QString::number(newHeightValue));
    QObject::connect(ui->verticalSlider_newHeightValue, &QSlider::valueChanged, this, [=]() {
        newHeightValue = ui->verticalSlider_newHeightValue->value();
        ui->label_newHeightValue->setText("Hauteur : " + QString::number(newHeightValue));
    });

    //Position initiale du marqueur
    //updateMarker((viewer->camPosX/4.)*512., (viewer->camPosZ/4.)*512.);
    viewer->moveMarkerMeshRelativeToTerrain(viewer->camPosX, viewer->getThisPositionHeight(viewer->camPosX,viewer->camPosZ), viewer->camPosZ);

    //ui->widget_affichage_terrain->installEventFilter(this);

    // FIN INITIALISATION
    combinePathsImages(pathsImages);
    setFocusPolicy(Qt::StrongFocus);
    viewer->setFocus();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateMarker(int x, int y){
    markedImage.fill(Qt::transparent);

    QPainter previewPainter(&markedImage);
    QPen previewPen;
    previewPen.setColor(Qt::red);
    previewPen.setWidth(12);
    previewPen.setJoinStyle(Qt::RoundJoin);
    previewPen.setCapStyle(Qt::RoundCap);
    previewPainter.setPen(previewPen);
    previewPainter.drawPoint(QPoint(x,y));
}

void MainWindow::updatePreviewPenSize(int penSize){
    QPixmap previewPixmap(ui->label_penSizeIMG->size());
    previewPixmap.fill(Qt::white);

    QPainter previewPainter(&previewPixmap);

    int squareSize = 10; // Taille du carré
    int numRows = 100 / squareSize;
    int numCols = 100 / squareSize;

    for (int row = 0; row < numRows; ++row){
        for (int col = 0; col < numCols; ++col){
            if ((row + col) % 2 == 0){
                previewPainter.fillRect(col * squareSize, row * squareSize, squareSize, squareSize, QColor(220, 220, 220));
            }else{
                previewPainter.fillRect(col * squareSize, row * squareSize, squareSize, squareSize, Qt::white);
            }
        }
    }

    QPen previewPen;
    previewPen.setColor(QColor("lightcoral"));
    previewPen.setWidth(penSize);
    previewPen.setJoinStyle(Qt::RoundJoin);
    previewPen.setCapStyle(Qt::RoundCap);
    //QPainter previewPainter(&previewPixmap);
    previewPainter.setPen(previewPen);
    previewPainter.drawPoint(QPoint(50,50));
    ui->label_penSizeIMG->setPixmap(previewPixmap);
}

void MainWindow::hideParamMesh(bool hide){
    if(!hide){
        ui->frame_param_mesh->show();
        ui->button_show_param_mesh->hide();

    }else{
        ui->frame_param_mesh->hide();
        ui->button_show_param_mesh->show();
    }
}

void MainWindow::hideParam(bool hide){
    if(!hide){
        ui->frame_pen->show();
    }else{
        ui->frame_pen->hide();
    }
}

void MainWindow::hideCarte(bool hide){
    if(!hide){
        ui->frame_perlin->show();
        ui->button_show_map->hide();
    }else{
        ui->frame_perlin->hide();
        ui->button_show_map->show();
        ui->frame_pen->hide();
    }
}

void MainWindow::hideControles(bool hide){
    if(!hide){
        ui->frame_controls->show();
        ui->button_show_controls->hide();
    }else{
        ui->frame_controls->hide();
        ui->button_show_controls->show();

    }
}

void MainWindow::hideErosion(bool hide){
    if(!hide){
        ui->frame_erosion->show();
        ui->button_show_erosion->hide();
    }else{
        ui->frame_erosion->hide();
        ui->button_show_erosion->show();

    }
}

void MainWindow::onSpinBox_nbRaindropsChanged(){
    viewer->terrainMesh.nbRainDrops = ui->spinBox_nbRaindrops->value();
    //qDebug() << viewer->terrainMesh.nbRainDrops;
}

void MainWindow::onSpinBox_nbIteErosionChanged(){
    viewer->terrainMesh.nbErosionIterations = ui->spinBox_nbIteErosion->value();
}

void MainWindow::onSpinBox_impactChanged(){
    viewer->terrainMesh.intensiteImpact = ui->spinBox_impact->value();
    qDebug() << viewer->terrainMesh.intensiteImpact;
}

// Modifier résolution
void MainWindow::onResolutionSliderReleased() {
    int value = ui->horizontalSlider_resolution->value();

    //qDebug() << "resolution : " << value;

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
    viewer->loadTextures();
    viewer->camPosX = QRandomGenerator::global()->generateDouble();
    viewer->camPosZ = QRandomGenerator::global()->generateDouble();

    originalImage = QImage("perlinNoise.png");
    editedImage = originalImage.copy();
    editedImage = editedImage.convertToFormat(QImage::Format_ARGB32);

    undoPaths.clear();
    redoPaths.clear();

    pathsImages.clear();
    combinePathsImages(pathsImages);
    updateMesh(combinedImage);

    ui->label_perlinNoise->setPixmap(QPixmap::fromImage(editedImage));

    //Marqueur reset
    //updateMarker((viewer->camPosX/4.)*512., (viewer->camPosZ/4.)*512.);
    viewer->moveMarkerMeshRelativeToTerrain(viewer->camPosX, viewer->getThisPositionHeight(viewer->camPosX,viewer->camPosZ), viewer->camPosZ);

    viewer->setFocus();
}

// Permet de savoir si la souris est en train de faire un clic gauche + mouvement dans le label de la carte
// Ou touches clavier
bool MainWindow::eventFilter(QObject *obj, QEvent *event){
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    if(obj == ui->label_perlinNoise){
        float x = mouseEvent->pos().x();
        float z = mouseEvent->pos().y();
        float x_div = x/512.;
        float z_div = z/512.;

        //qDebug() << "x " << x;
        //qDebug() << "y " << y;
        //qDebug() << "z " << z;

        float y = viewer->getThisPositionHeight(x_div,z_div);
        if (!isMarqueurMode/* && obj == ui->label_perlinNoise*/) {
            viewer->isPointerOn = true;
            viewer->movePointerMeshRelativeToTerrain(x_div, y, z_div);
            if(x_div == 0 && y == 0 && z_div == 0){
                viewer->isPointerOn = false;
                viewer->update();
            }

            if (event->type() == QEvent::MouseButtonPress) {
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
                currentPath->drawingPath(mouseEvent, editedImage); //Appel editedImage  : juste pour la taille img

                //Affichage Image résultat + Image tracé rouge
                update_label_perlinNoise(combinedImage, currentPath->getLayerImage());

            } else if (event->type() == QEvent::MouseButtonRelease) {
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
        } else if(isMarqueurMode /*&& obj == ui->label_perlinNoise*/){
            viewer->isPointerOn = false;
            if (event->type() == QEvent::MouseButtonPress) {
                if (mouseEvent->button() == Qt::LeftButton) {
                    QColor couleurPixel = editedImage.pixelColor(x,z); // le y de l'img est le z du mesh
                    if(couleurPixel.red() > 15){
                        updateMarker(x,z);
                        mergeImages(editedImage, markedImage);
                        viewer->moveMarkerMeshRelativeToTerrain(x_div,y,z_div);
                        viewer->camPosX = x_div*4;
                        viewer->camPosZ = z_div*4; // Z est le y du mesh
                    }
                }
            }
        }else{
            //viewer->isPointerOn = false;
        }

    }else{ //Hors de la carte
        //viewer->isPointerOn = false;

    }

    //qDebug() << obj;

    // NE MARCHE PAS CAR FAIT PLANTER SI DESSIN SUR PERLIN NOISE
    // if (obj == ui->widget_affichage_terrain) {
    //     QKeyEvent* keyEvent = dynamic_cast<QKeyEvent*>(event);
    //     if (keyEvent) {
    //         // Appeler la fonction keyPressEvent de MyViewer.h
    //         //viewer->keyPressEvent(keyEvent);

    //         // Récupérer la touche pressée
    //         int keyInt = keyEvent->key();
    //         Qt::Key key = static_cast<Qt::Key>(keyInt);
    //         //qDebug() << "Touche pressée dans ui->widget_affichage_terrain : " << key;


    //         if(key == Qt::Key_Right || key == Qt::Key_Left || key == Qt::Key_Up || key == Qt::Key_Down){
    //             //qDebug() << "main " << viewer->camLocked;
    //             if(viewer->camLocked){
    //                 ui->label_droite->setStyleSheet(toucheOff);
    //                 ui->label_gauche->setStyleSheet(toucheOff);
    //             }else{
    //                 ui->label_droite->setStyleSheet(toucheOn);
    //                 ui->label_gauche->setStyleSheet(toucheOn);
    //             }

    //         }

    //         if(key == Qt::Key_Z || key == Qt::Key_Q || key == Qt::Key_S || key == Qt::Key_D){
    //             if(viewer->camLockedFPS){
    //                 ui->label_droite->setStyleSheet(toucheOff);
    //                 ui->label_gauche->setStyleSheet(toucheOff);
    //             }else{
    //                 ui->label_droite->setStyleSheet(toucheOn);
    //                 ui->label_gauche->setStyleSheet(toucheOn);
    //             }
    //         }
    //     }

    // }

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

void MainWindow::mergeImages(QImage img1, QImage img2) {
    QImage mergedImages(img1.size(), QImage::Format_ARGB32);
    mergedImages.fill(Qt::transparent);

    QPainter cpainter(&mergedImages);
    cpainter.drawImage(0, 0, img1);
    cpainter.drawImage(0, 0, img2);
    cpainter.end();

    ui->label_perlinNoise->setPixmap(QPixmap::fromImage(mergedImages));
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
    //qDebug() << "test";

    if (!undoPaths.isEmpty()) {
        //qDebug() << "        undo " << QString::number(undoPaths.count()) << " redo " << QString::number(redoPaths.count());
        //Enlever le tracé dans la liste des tracés
        pathsImages.removeLast();

        //Update de l'image
        combinePathsImages(pathsImages);
        editedImage = combinedImage.copy();
        updateMesh(editedImage);

        //Ajouter à redo
        redoPaths.append(currentPath);

        //Mettre à jour le currentPath par le "précédent"
        currentPath = undoPaths.takeLast();

        //qDebug() << "UNDO => undo " << QString::number(undoPaths.count()) << " redo " << QString::number(redoPaths.count());
    }
}

// Refaire le tracé
void MainWindow::redoDrawingPath() {
    if (!redoPaths.isEmpty()) {
        //qDebug() << "        undo " << QString::number(undoPaths.count()) << " redo " << QString::number(redoPaths.count());

        //Ajouter à undo
        undoPaths.append(currentPath);

        //Remettre le tracé dans la liste des tracés
        pathsImages.append(currentPath->renderPathImage);
        currentPath->addModification(editedImage);

        //Update de l'image
        combinePathsImages(pathsImages);
        editedImage = combinedImage.copy();
        updateMesh(editedImage);

        //Mettre à jour le currentPath par le "suivant"
        currentPath = redoPaths.takeLast();

        //qDebug() << "REDO => undo " << QString::number(undoPaths.count()) << " redo " << QString::number(redoPaths.count());
    }
}

// Actualiser le maillage
void MainWindow::updateMesh(QImage image){
    viewer->terrainMesh.perlinNoise->ImgPerlin = image;
    viewer->terrainMesh.generateMesh();
    viewer->loadTextures();
    viewer->update();

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

    viewer->camPosX = QRandomGenerator::global()->generateDouble();
    viewer->camPosZ = QRandomGenerator::global()->generateDouble();

    originalImage = QImage(filePath);
    ui->label_perlinNoise->setPixmap(QPixmap::fromImage(originalImage));
    editedImage = originalImage.copy();
    editedImage = editedImage.convertToFormat(QImage::Format_ARGB32);

    undoPaths.clear();
    redoPaths.clear();

    pathsImages.clear();
    combinePathsImages(pathsImages);
    updateMesh(combinedImage);

    updateMesh(originalImage);
    viewer->setFocus();
}

void MainWindow::changerVuePremierePersonne() {
    if (viewer->vueActuelle == viewer->VueTerrain) {
        viewer->vueActuelle = viewer->VuePremierePersonne;

        ui->label_droite->setStyleSheet(toucheOn);
        ui->label_gauche->setStyleSheet(toucheOn);
        ui->label_z->setStyleSheet(toucheOn);
        ui->label_q->setStyleSheet(toucheOn);
        ui->label_s->setStyleSheet(toucheOn);
        ui->label_d->setStyleSheet(toucheOn);

        hideCarte(true);
        ui->button_show_map->hide();
        hideParamMesh(true);
        ui->button_show_param_mesh->hide();
        hideErosion(true);
        ui->button_show_erosion->hide();

        ui->pushButton_mode_FPS->setText("Quitter vue FPS");

        viewer->terrainMesh.sizeX = 4.0;
        viewer->terrainMesh.sizeY = 4.0;
        viewer->terrainMesh.sizeZ = 4.0;
        viewer->terrainMesh.generateMesh();

        viewer->draw();

        viewer->setFocus();
    }
    else {
        ui->pushButton_mode_FPS->setText("Afficher vue FPS");
        viewer->vueActuelle = viewer->VueTerrain;

        ui->label_droite->setStyleSheet(toucheOn);
        ui->label_gauche->setStyleSheet(toucheOn);
        ui->label_z->setStyleSheet(toucheOff);
        ui->label_q->setStyleSheet(toucheOff);
        ui->label_s->setStyleSheet(toucheOff);
        ui->label_d->setStyleSheet(toucheOff);

        ui->button_show_map->show();
        ui->button_show_param_mesh->show();
        ui->button_show_erosion->show();

        viewer->openCameraFromFile("initCam.txt");

        viewer->terrainMesh.sizeX = 1.0;
        viewer->terrainMesh.sizeY = 1.0;
        viewer->terrainMesh.sizeZ = 1.0;
        viewer->terrainMesh.generateMesh();

        point3d bbmin(0.0, 0.0, 0.0) , BBmax(1, 1, 1);
        viewer->adjustCamera(bbmin, BBmax);

        viewer->draw();

        viewer->setFocus();
    }

}



