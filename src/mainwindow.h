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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QImage>
#include <QPainter>
#include <QPainterPath>
#include <QStack>
#include <QLabel>
#include <QRandomGenerator>
#include <QGraphicsDropShadowEffect>
#include <QKeyEvent>
#include "MyViewer.h"
#include "path.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QList<QPen> pathPens;



private slots:
    void onResolutionSliderReleased();
    void onHeightRangeSliderReleased();
    void onReloadButtonClicked();

    //Concerne le tracé
    void undoDrawingPath();
    void redoDrawingPath();

    //Sauvegarde carte
    void downloadMap(QImage image);

    //Ouvrir carte
    void uploadMap();

    void changerVuePremierePersonne();

    //preview tracé pinceau
    void updatePreviewPenSize(int penSize);

    //update marqueur
    void updateMarker(int x, int y);

    void hideParamMesh(bool hide);
    void hideParam(bool hide);
    void hideCarte(bool hide);
    void hideControles(bool hide);
    void hideErosion(bool hide);

    void onSpinBox_nbRaindropsChanged();
    void onSpinBox_nbIteErosionChanged();
    void onSpinBox_impactChanged();

private:
    Ui::MainWindow *ui;
    //QWidget* defaultCentralWidget;
    QLabel *backgroundWidget;
    MyViewer* viewer;
    bool isLeftButtonPressed;

    //Image originale
    QImage originalImage;

    //Image modifiée
    QImage editedImage;

    //Image combinée (image qui regroupe tous les tracés)
    QList<QImage> pathsImages; //regroupe toutes les calques
    QImage combinedImage;

    //Image du marqueur
    QImage markedImage;

    Path* currentPath;

    QList<Path*> undoPaths;
    QList<Path*> redoPaths;

    int newHeightValue;

    int penSize;

    bool isHidden = true;

    bool isMarqueurMode = false;

    QString toucheOn = "background-color : white;\nborder : 1px solid;\nborder-radius : 10px;";
    QString toucheOff = "background-color : gray;\nborder : 1px solid;\nborder-radius : 10px;";

protected:
    bool eventFilter(QObject *obj, QEvent *event);

    void updateMesh(QImage image);

    void update_label_perlinNoise(QImage editedImage, QImage layerImage);
    void combinePathsImages(QList<QImage> pathsImages);

    void mergeImages(QImage img1, QImage img2);

};

#endif // MAINWINDOW_H
