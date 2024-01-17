#ifndef PATH_H
#define PATH_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QDebug>
#include <QtGui>
//#include "./extern/opencv2/opencv.hpp"

class Path
{
public:
    Path();
    void startDrawingPath(QMouseEvent *mouseEvent);
    void drawingPath(QMouseEvent *mouseEvent, QImage image);
    void endDrawingPath();
    void addModification(QImage image);

    QImage getLayerImage();
    QImage getPathImage();

    QImage setPathImage(QImage image);

    void setHeightValue(int size);
    int getHeightValue();
    void setPixelsPath();
    void setPathPen_width(int size);

    QImage renderPathImage; //image tracée (tracé prend les bonnes couleurs modifiées)

    QImage getRenderPathImage();

    int blurSize();

private:
    QPainterPath path;
    QPointF startPoint;

    //Param stylo
    QPen pathPen;
    int widthPen = 3;
    int heightValue = 0;

    //calque
    QList<QPoint> pixelsPath; //pixels du tracé rouge
    QImage layerImage; //image du calque (tracé rouge)



};

#endif // PATH_H
