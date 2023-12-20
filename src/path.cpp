#include "path.h"

Path::Path() {
    pathPen.setColor(Qt::red);
    pathPen.setWidth(widthPen);
}

void Path::startDrawingPath(QMouseEvent *mouseEvent){
    startPoint = mouseEvent->localPos();
    path.moveTo(startPoint);
}

void Path::drawingPath(QMouseEvent *mouseEvent, QImage editedImage){
    QPointF mousePos = mouseEvent->localPos();

    //Ajout point au tracé
    path.lineTo(mousePos);

    //Calque trait
    layerImage = QImage(editedImage.size(), QImage::Format_ARGB32);
    layerImage.fill(Qt::transparent);

    //Trait visuel rouge
    QPainter painter(&layerImage);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawImage(0, 0, layerImage);
    painter.setPen(pathPen);
    painter.drawPath(path);
    painter.end();

    //qDebug() << "trace.";
}

void Path::setPixelsPath(){
    for (int y = 0; y < layerImage.height(); ++y) {
        for (int x = 0; x < layerImage.width(); ++x) {
            QColor pixelLayerValue = layerImage.pixel(x, y);

            // Vérifier si le pixel appartient au tracé rouge
            if (pixelLayerValue == Qt::red) {
                // Ajouter les coordonnées du pixel à la liste
                pixelsPath.append(QPoint(x, y));
                //qDebug() << "X:" << x << ", Y:" << y;
            }
        }
    }
}

void Path::addModification(QImage editedImage){
    pathImage = editedImage.copy();
    qDebug() << "là";
    for(const QPoint& pixel : pixelsPath){
        int x = pixel.x();
        int y = pixel.y();

        //Récupération de la couleur d'origine
        QRgb editedPixelColor = pathImage.pixel(x, y);

        int grayValue = qGray(editedPixelColor);
        int newGrayValue = qBound(0, grayValue + heightValue, 255);

        pathImage.setPixel(x, y, qRgb(newGrayValue, newGrayValue, newGrayValue));

        //pathImage = pathImage.convertToFormat(QImage::Format_RGB32);
        qDebug() << "ici";
    }
}

void Path::removeModification(QImage editedImage){
    pathImage = editedImage.copy();
    for(const QPoint& pixel : pixelsPath){
        int x = pixel.x();
        int y = pixel.y();

        //Récupération de la couleur d'origine
        QRgb editedPixelColor = pathImage.pixel(x, y);

        int grayValue = qGray(editedPixelColor);
        int newGrayValue = qBound(0, grayValue - heightValue, 255);

        pathImage.setPixel(x, y, qRgb(newGrayValue, newGrayValue, newGrayValue));

        //pathImage = pathImage.convertToFormat(QImage::Format_RGB32);
    }
}

void Path::endDrawingPath(){
    startPoint = QPointF();
}

void Path::setPathPen_width(int size){
    widthPen = size;
    pathPen.setWidth(widthPen);
}

void Path::setHeightValue(int size){
    heightValue = size;
}

int Path::getHeightValue(){
    return heightValue;
}

QImage Path::getLayerImage(){
    return layerImage;
}

QImage Path::getPathImage(){
    return pathImage;
}

//QImage Path::setPathImage(QImage editedImage){
//    pathImage = editedImage.copy();
//}

