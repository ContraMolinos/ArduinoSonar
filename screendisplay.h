#ifndef SCREENDISPLAY_H
#define SCREENDISPLAY_H

/**
 * @brief The ScreenDisplay class
 * Class inherited from QGraphicsItem to draw the
 * screen of the sonar.
 */

#include <QGraphicsItem>
#include <QPainter>

#define PI 3.14159265

class ScreenDisplay:public QGraphicsItem
{
public:
    ScreenDisplay(qreal width,qreal height);
    QRectF boundingRect() const;
    void setScale(qreal scale);
    //Overriding paint.
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal width,height;
    qreal zFactor=0.8;
    QPoint center;
    qreal scale=100;
    const int nArcs=5;

    QPoint ang2point(QPoint cen, qreal angle, qreal r);
};

#endif // SCREENDISPLAY_H
