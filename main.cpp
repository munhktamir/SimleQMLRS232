#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSerialPortInfo>
#include <QtSerialPort>
#include <QQmlContext>
#include "serialcom.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QSerialPortInfo serialPortInfo;
    QList<QSerialPortInfo> ports = serialPortInfo.availablePorts();
    QList<qint32> bauds = serialPortInfo.standardBaudRates();
    QStringList portsName;
    QStringList baudsStr;

    foreach(QSerialPortInfo port, ports)
    {
        portsName.append(port.portName());
    }
    foreach(qint32 baud, bauds)
    {
        baudsStr.append(QString::number(baud));
    }

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    SerialCom serialComm;
    context->setContextProperty("SerialCommInstance", &serialComm);
    context->setContextProperty("portsName", QVariant::fromValue(portsName));
    context->setContextProperty("baudRates", QVariant::fromValue(baudsStr));

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;




    return app.exec();
}
