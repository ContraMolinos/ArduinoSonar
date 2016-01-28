#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include "arducomm.h"
#include <QSerialPortInfo>
#include <QPaintEvent>
#include <QPainter>

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
    void on_portBox_currentIndexChanged(const QString &arg1);
    void printTest();

private:
    Ui::Widget *ui;
    QSerialPortInfo *portInfo;
    arduComm *arduPort;
protected:
    //void paintEvent(QPaintEvent *e);
};

#endif // WIDGET_H
