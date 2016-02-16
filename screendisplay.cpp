
#include "screendisplay.h"
#include <QDebug>

ScreenDisplay::ScreenDisplay(qreal width, qreal height): width(width), height(height)
{
    center=QPoint(0,zFactor*height/2);
}

/**
 * @brief ScreenDisplay::boundingRect   Returns the outer boundaries.
 * @return
 */
QRectF ScreenDisplay::boundingRect() const
{
    //return QRectF(-width/2,-height/2,width,height);
    return QRectF(-zFactor*width/2,-zFactor*(width-height)/2,zFactor*width,zFactor*width);
}

void ScreenDisplay::setScale(qreal scale)
{
    this->scale=scale;
}

void ScreenDisplay::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec=boundingRect();
    QSizeF recSize=rec.size();
    painter->drawLine(-zFactor*width/2,zFactor*height/2,zFactor*width/2,zFactor*height/2);  //Base line.

    //Draw distance marks.
    painter->drawText(QPoint(0,zFactor*height/2+15),"0");
    for(int i=0;i<nArcs;i++)
    {
        float s=i*(1.0/nArcs);
        rec.setX((-zFactor*width/2)+s*zFactor*width/2);
        rec.setY((-zFactor*(width-height)/2)+s*zFactor*width/2);
        rec.setSize(recSize*(1-s));
        painter->drawArc(rec,0,180*16);
        painter->drawText(rec.topLeft()+QPoint(0,rec.height()/2+15),QString::number((nArcs-i)*(scale/nArcs)));
    }

    //Draw direction marks.
    painter->drawText(QPoint(-0.9*width/2,zFactor*height/2),"0º");
    for(int i=0;i<5;i++)
    {
        QPoint p=ang2point(center,(180/6)*(i+1),zFactor*width/2);
        painter->drawLine(center,p);
        p=ang2point(center,(180/6)*(i+0.9),(1.15-0.03*i)*zFactor*width/2);
        painter->drawText(p,QString::number((180/6)*(i+1))+"º");
    }
    painter->drawText(QPoint(0.85*width/2,zFactor*height/2),"180º");

}

QPoint ScreenDisplay::ang2point(QPoint cen, qreal angle,qreal r)
{
    return center-QPoint(r*cos(PI*angle/180),r*sin(PI*angle/180));
}

