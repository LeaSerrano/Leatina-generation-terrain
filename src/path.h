#ifndef PATH_H
#define PATH_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QDebug>


class Path
{
public:
    Path();
    void startDrawingPath(QMouseEvent *mouseEvent);
    void drawingPath(QMouseEvent *mouseEvent, QImage editedImage);
    void endDrawingPath();

private:
    QPainterPath path;
    QPointF startPoint;

    //Param stylo
    QPen pathPen;
    int widthPen = 3;
    int HeightValue = 0;

    //calque
    QList<QPoint> pixelsPath; //pixels du tracé rouge
    QImage layerImage; //image du calque

    QImage pathImage; //image originale + tracé


protected:

    void setPixelsPath();
    void addModification(QImage editedImage);
    void removeModification(QImage editedImage);

    void setPathPen_width(int size);
    QImage getPathImage();

};

#endif // PATH_H
