#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //Create port.
    arduPort=new arduComm();

    // Find available ports and populate Combo Box.
    portInfo=new QSerialPortInfo();
    foreach(const QSerialPortInfo &pI, portInfo->availablePorts())
    {
        ui->portBox->addItem(pI.portName());
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_portBox_currentIndexChanged(const QString &arg1)
{
    arduPort->openPort(ui->portBox->currentText(),QSerialPort::ReadOnly,QSerialPort::Baud9600);

    connect(arduPort,SIGNAL(readyRead()),this,SLOT(printTest()));
}

void Widget::printTest()
{
    arduPort->readPort();
    QString text(arduPort->getBuffer()->data());
    ui->plainTextEdit->setPlainText(text);
    ui->plainTextEdit->moveCursor(QTextCursor::End);
}
