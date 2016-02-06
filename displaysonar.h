#ifndef DISPLAYSONAR_H
#define DISPLAYSONAR_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QPoint>
#include <QHash>
#include <QDebug>

#define PI 3.14159265

/**
 * Class to manage the sonar-like representation of the data retrieved from
 * Arduino with the SR04 ultrasound module.
 */

class displaySonar : public QObject
{
    Q_OBJECT
public:
    displaySonar(QGraphicsView *view, QObject *parent);
    void update(float r, float alpha, float limit);
    ~displaySonar();

private:
    QGraphicsView *_view;
    int viewWidth, viewHeight;
    QGraphicsScene *scene;
    float angleStep;    //Angle interval between two consecutive readings.
    double maxDist=23200;
    float sweepLineLenght;  //Length of the sweeping line in the graph.
    QGraphicsLineItem *baseLine;
    QGraphicsLineItem *sweepLine;
   // QPen *pen;
    QHash<float, QGraphicsEllipseItem*> *displayPoints;   //It is mean to contain a hash of pairs (angle,point) when an echo is received.
    int dotRadius=3;

    QGraphicsEllipseItem temp;


    QPoint polarToCartesian(float r, float alpha);
    void *newEcho(float r, float alpha);
    void removeEcho(float alpha);

signals:

public slots:
};

#endif // DISPLAYSONAR_H
