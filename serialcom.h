#ifndef SERIALCOM_H
#define SERIALCOM_H

#include <QSerialPort>
#include <QObject>
#include <QDebug>



class SerialCom : public QObject
{
    Q_OBJECT
public:
    SerialCom();
    virtual ~SerialCom();
    void serialPortOpen(QString comName, int baudrate);
    bool getConnectionStatus();
    void closeSerialPort();

public slots:
    void openSerialPortSlot(QString comName, int baudrate);
    void readFromSerialPort();
    bool getConnectionStatusSlot();
    void closeSerialPortSlot();
signals:
    QString getSerialData(QString data);

private:
    QSerialPort *serialPort;
};

#endif // SERIALCOM_H
