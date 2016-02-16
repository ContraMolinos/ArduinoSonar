/**     Arduino Sonar
    FJS. February 2016
  Application to visualize the output of an arduino-based sonar.
  06-02-2016. Version 1.0. First working version.
  07-02-2016. Solved list out of bounds bug.
*/

#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //Create port.
    arduPort=new arduComm(this);

    // Find available ports and populate Combo Box.
    portInfo=new QSerialPortInfo();
    foreach(const QSerialPortInfo &pI, portInfo->availablePorts())
    {
        ui->portBox->addItem(pI.portName());
    }

    //Create output scene
    display=new displaySonar(ui->outDraw,this);
}

Widget::~Widget()
{
    delete portInfo;
    delete ui;
}

void Widget::on_portBox_currentIndexChanged(int idx)
{
    arduPort->openPort(ui->portBox->currentText(),QSerialPort::ReadOnly,QSerialPort::Baud9600);

    connect(arduPort,SIGNAL(readyRead()),this,SLOT(refresh()));
}

/**
 * @brief Widget::printTest Test method. Not to be used outside development.
 */
void Widget::printTest()
{
    if(arduPort->isPortReady())
    {
        arduPort->readPort();
        QString text(arduPort->getBuffer()->data());
        if(!text.contains("->"))    return;
        int dist=text.split("->")[1].toInt();
        int angle=text.split("->")[0].toInt();
        ui->plainTextEdit->setPlainText(QString::number(angle)+","+QString::number(dist));
        ui->plainTextEdit->moveCursor(QTextCursor::End);
    }
}

/**
 * @brief Widget::refresh   Slot to refresh the screen with new data.
 */
void Widget::refresh()
{
    if(!arduPort->isPortReady())    return;     //If there isn't a whole line in the buffer, do nothing.
    arduPort->readPort();
    QString rawData(arduPort->getBuffer()->data());
    if(!rawData.contains("->")) return;     //The "->" string is the separator. If it isn't present, something's wrong.
    QStringList strData=rawData.split("->");
    //qDebug()<<strData.size()<<" "<<strData.count();
    if(strData.size()>2)
    {
        int angle=strData[0].toInt();
        int distance=strData[1].toInt()/58.3;
        int limit=strData[2].toInt();
        display->update(distance,angle,limit);

        //Display the reading in auxiliary edit.
        ui->plainTextEdit->setPlainText(QString::number(angle)+","+QString::number(distance)+","+QString::number(limit));
        ui->plainTextEdit->moveCursor(QTextCursor::End);
    }
}
