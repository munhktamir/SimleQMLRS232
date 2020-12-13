#include "serialcom.h"

SerialCom::SerialCom()
{
    serialPort = new QSerialPort(this);
}

SerialCom::~SerialCom()
{
    delete this;
}

void SerialCom::serialPortOpen(QString comName, int baudrate)
{
    serialPort->setPortName(comName);
    serialPort->setBaudRate(baudrate);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->open(QIODevice::ReadOnly);
    connect(serialPort, SIGNAL(readyRead()), this, SLOT(readFromSerialPort()));
}

bool SerialCom::getConnectionStatus()
{
    return serialPort->isOpen();
}

void SerialCom::closeSerialPort()
{
    serialPort->close();
}

void SerialCom::openSerialPortSlot(QString comName, int baudrate)
{
    this->serialPortOpen(comName, baudrate);
}

void SerialCom::readFromSerialPort()
{
    if (serialPort->canReadLine())
    {
        QString data = QString::fromLatin1(serialPort->readAll());
        emit getSerialData(data);
    }
}

bool SerialCom::getConnectionStatusSlot()
{
    qDebug() << this->getConnectionStatus();
    return this->getConnectionStatus();
}

void SerialCom::closeSerialPortSlot()
{
    this->closeSerialPort();
}
