#include "displaysonar.h"

/**
 * @brief displaySonar::displaySonar Constructor function. Inherits QObject.
 * @param view  QGraphicsView pointer that will contain the image.
 * @param parent    Pointer to invoquing class.
 */
displaySonar::displaySonar(QGraphicsView *view, QObject *parent) : QObject(parent)
{
    _view=view;
    viewHeight=_view->height();
    viewWidth=_view->width();

    scene=new QGraphicsScene(this);
    _view->setScene(scene);
    sweepLineLenght=0.8*viewWidth/2;
    //Fix the scene size to that of the graphics view.
    scene->setSceneRect(-viewWidth/2,-viewHeight/2,viewWidth,viewHeight);

    //This line will be static.
    screen=new ScreenDisplay(viewWidth,viewHeight);
    scene->addItem(screen);
    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(2);
    //This line will sweep the scanning area.
    sweepLine=scene->addLine(-0.8*viewWidth/2,0.8*viewHeight/2,0,0.8*viewHeight/2,pen);

    //Initialize the hash to contain the list of echoes.
    displayPoints=new QHash<float, QGraphicsEllipseItem*>();
}


displaySonar::~displaySonar()
{
    QList<float> keys=displayPoints->keys();
    qDebug()<<keys.count();
    for(int i=0;i<keys.size();i++)
        removeEcho(keys.at(i));
    delete displayPoints;
    delete screen;
}

/**
 * @brief displaySonar::update  Update the position of the display.
 * @param r Distance as a fraction of the sweeping line lenght.
 * @param alpha Angle of the scanned direction.
 */
void displaySonar::update(float r, float alpha,float limit)
{
    QPoint lineEnd;
    lineEnd=polarToCartesian(0.8*viewWidth/2,alpha);
    //The coordinates need to change the origin from (0,0) to the origin of the beam.
    sweepLine->setLine(-lineEnd.x(),0.8*viewHeight/2-lineEnd.y(),0,0.8*viewHeight/2);

    removeEcho(alpha);
    if(r<limit)   //Something was detected.
            newEcho(r*sweepLineLenght/limit,alpha);
    screen->setScale(limit);
}


/**
 * @brief displaySonar::polarToCartesian. Converts a distance-angle duple into x,y coordinates.
 * @param r Distance.
 * @param alpha Angle.
 * @return QPoint with x,y coordinates.
 */
QPoint displaySonar::polarToCartesian(float r, float alpha)
{
    QPoint p;
    double x,y;

    //Absolute coordinates.
    x=r*cos(PI*alpha/180);
    y=r*sin(PI*alpha/180);
    p.setX(round(x));
    p.setY(round(y));

    return p;
}

/**
 * @brief displaySonar::newEcho Creates a new echo graph pointer at the given angle and distance and adds it
 * to the displayPoints hash.
 * @param r Distance of the echo to the origin.
 * @param alpha Angle of the echo.
 */
void displaySonar::newEcho(float r, float alpha)
{
    QPoint p=polarToCartesian(r,alpha);

    //The coordinates need to change the origin from (0,0) to the origin of the beam.
    QGraphicsEllipseItem *e=scene->addEllipse(-(p.x()+dotRadius),0.8*viewHeight/2-(p.y()+dotRadius),2*dotRadius,2*dotRadius);
    displayPoints->insert(alpha,e);
}

/**
 * @brief displaySonar::removeEcho  Deletes the point corresponding to a given angle from the
 * displayPoints hash.
 * @param alpha Angle to remove.
 */
void displaySonar::removeEcho(float alpha)
{
    if(displayPoints->contains(alpha))
    {
        QGraphicsEllipseItem *e=displayPoints->value(alpha);
        delete e;
        displayPoints->remove(alpha);
    }
}

