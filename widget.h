#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QMessageBox>
#include "arducomm.h"
#include "displaysonar.h"
#include <QSerialPortInfo>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_portBox_currentIndexChanged(int idx);
    void printTest();
    void refresh();

private:
    Ui::Widget *ui;
    QSerialPortInfo *portInfo;
    arduComm *arduPort;
    QGraphicsScene *outGraph;
    QGraphicsEllipseItem *tempEllipse;
    displaySonar *display;

};

#endif // WIDGET_H
