#ifndef ARDUCOMM_H
#define ARDUCOMM_H

/** This class is meant to handle the communication
 * with arduino. In principle, it is meant to be used
 * only with the ultrasound detector.
*/

#include <QMessageBox>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class arduComm: public QObject
{
    Q_OBJECT
public:
    arduComm(QObject *parent=0);
    ~arduComm();
    //arduComm(QString portName,QWidget *parent);
    bool openPort(QString portName,QSerialPort::OpenMode mode, QSerialPort::BaudRate br=QSerialPort::Baud9600);
    int readPort(QByteArray *buffer);  //This version of readPort is meant to write on a outside array.
    int readPort();   //This version is meant to be used to write in the internal buffer.
    const QByteArray* getBuffer();
    bool isPortReady();
    bool closePort();
public slots:
    void ready();
signals:
    void readyRead();

private:
    QSerialPort *portPointer;
    bool portOpen;     //To be set with the status of isOpen().
    const QSerialPort::DataBits db=QSerialPort::Data8;                  //These are
    const QSerialPort::Parity parity=QSerialPort::NoParity;             //fixed values
    const QSerialPort::StopBits stopBits=QSerialPort::OneStop;          //for
    const QSerialPort::FlowControl fcontrol=QSerialPort::NoFlowControl;    //Arduino.
    QSerialPort::BaudRate baudRate;
    QSerialPort::OpenMode openMode;
    QByteArray *buffer;

    quint8 bufferSize; //TODO Determine buffer size.
};

#endif // ARDUCOMM_H
