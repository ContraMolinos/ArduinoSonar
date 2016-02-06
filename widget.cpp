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

//    outGraph=new QGraphicsScene(this);
//    ui->outDraw->setScene(outGraph);
//    outGraph->setSceneRect(-ui->outDraw->width()/2,-ui->outDraw->height()/2,ui->outDraw->width(),ui->outDraw->height());
//    //ui->outDraw->scale(ui->outDraw->width()/outGraph->width(),ui->outDraw->height()/outGraph->height());
//    tempEllipse=outGraph->addEllipse(-10,-10,20,20);
//    outGraph->addLine(-100,0,100,0);
//    outGraph->addLine(0,-100,0,100);
//    //ui->outDraw->centerOn(0,0);


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
        if(dist<23200)
        {
            //display->update(dist/23200.0,angle);
        }
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
    int angle=strData[0].toInt();
    int distance=strData[1].toInt()/58.3;
    int limit=strData[2].toInt()/58.3;
    display->update(distance,angle,limit);

    //Display the reading in auxiliary edit.
    ui->plainTextEdit->setPlainText(QString::number(angle)+","+QString::number(distance)+","+QString::number(limit));
    ui->plainTextEdit->moveCursor(QTextCursor::End);
}
