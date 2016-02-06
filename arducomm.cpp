#include "arducomm.h"
#include <QDebug>

arduComm::arduComm(QObject *parent):QObject(parent)
{
    portPointer=new QSerialPort(this);
    portOpen=false;

    //Initialize buffer.
    buffer=new QByteArray();
}

arduComm::~arduComm()
{
    delete buffer;
    closePort();
}

//Open the port. Mode can be read, write or readwrite. Baud rate is 9600 by default.
//All other parameters are fixed.
bool arduComm::openPort(QString portName,QSerialPort::OpenMode mode, QSerialPort::BaudRate br)
{
    closePort();

    portPointer->setPortName(portName);
    try
    {
        portPointer->open(mode);
        portOpen=true;
    }catch(...)
    {
        portOpen=false;
        QMessageBox::warning(NULL,"Port error","Couldn't open the port.");
        return false;
    }
    portPointer->setBaudRate(br);
    portPointer->setDataBits(db);
    portPointer->setParity(parity);
    portPointer->setStopBits(stopBits);
    portPointer->setFlowControl(fcontrol);

    connect(portPointer,SIGNAL(readyRead()),this,SLOT(ready()));
    return true;
}

bool arduComm::closePort()
{
    if(portOpen)
    {
        portPointer->close();
        return true;
    }
    return false;
}

//Default version of readPort that stores the information within the class.
int arduComm::readPort()
{
    return arduComm::readPort(arduComm::buffer);
}

//Read the serial port and store it in the variable pointed by buffer.
int arduComm::readPort(QByteArray *buf)
{
    buf->clear();    //Empty buffer.

    if(portOpen)
    {
        int nAvail=portPointer->bytesAvailable();
        if(!portPointer->canReadLine())
        {
            return -1;
        }  //Not possible to read a line.
       // qDebug()<<nAvail<<" bytes available";
        if(nAvail<1)
            throw "No data in port.";
        //Every line should be a different set of data.
        //if(portPointer->canReadLine())
            buf->append(portPointer->readLine());
        //qDebug()<<"Read "<<*buf;
        return buf->length();
    }

    return -1;
}

const QByteArray *arduComm::getBuffer()
{
    return buffer;
}

/**
 * @brief arduComm::isPortReady Checking whether a full line is awaiting to be read in the port buffer
 * @return Yes or no.
 */
bool arduComm::isPortReady()
{
    return portPointer->canReadLine();
}

/**
 * @brief arduComm::ready   This slot links the port's readyRead signal with the outside of the class.
 */
void arduComm::ready()
{
    emit readyRead();
}

