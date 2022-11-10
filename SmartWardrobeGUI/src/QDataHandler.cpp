#include "QDataHandler.h"
#include "AppConstants.h"

#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QString>

QDataHandler::QDataHandler()
{
    m_serial = new QSerialPort(this);
    connect(m_serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));


    connect(m_serial, &QSerialPort::readyRead, this, &QDataHandler::readData);
}

QDataHandler::~QDataHandler()
{

}

void QDataHandler::openSerialPort()
{
    QSerialPortInfo portToUse;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QString s = QObject::tr("Port:") + info.portName() + "\n"
                    + QObject::tr("Location:") + info.systemLocation() + "\n"
                    + QObject::tr("Description:") + info.description() + "\n"
                    + QObject::tr("Manufacturer:") + info.manufacturer() + "\n"
                    + QObject::tr("Serial number:") + info.serialNumber() + "\n"
                    + QObject::tr("Vendor Identifier:") + (info.hasVendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString()) + "\n"
                    + QObject::tr("Product Identifier:") + (info.hasProductIdentifier() ? QString::number(info.productIdentifier(), 16) : QString()) + "\n"
                    + QObject::tr("Busy:") + (info.isBusy() ? QObject::tr("Yes") : QObject::tr("No")) + "\n";

        if(!info.isBusy() && (info.description().contains("1a86") || info.manufacturer().contains("1a86")))
            portToUse = info;
        CONSOLE << s;
    }

    if(portToUse.isNull() || !portToUse.isValid())
    {
        CONSOLE << "port is not valid:" << portToUse.portName();
        return;
    }

    // Enumerate the serial port
    // Find one that sounds like Arduino, or the highest one on the list
    // Open it if it isn't busy

    m_serial->setPortName(portToUse.portName());
    m_serial->setBaudRate(QSerialPort::Baud9600);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);
    if (m_serial->open(QIODevice::ReadWrite)) {
        CONSOLE << "Connected to" << portToUse.description() << "on" << portToUse.portName();
    } else {
        qCritical() << "Serial Port error:" << m_serial->errorString();

        CONSOLE << tr("Open error");
    }
}

void QDataHandler::closeSerialPort()
{
    m_serial->close();
    CONSOLE << tr("Disconnected");
}

void QDataHandler::writeData(const QByteArray &data)
{
    CONSOLE<< data;
    m_serial->write(data+ "\n");
}

void QDataHandler::readData()
{
    QByteArray data = m_serial->readLine();
    CONSOLE << "UART:" << data;

    QString _data = QString(data);
    emit dataReady(_data);
}

void QDataHandler::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        qCritical() << "Serial Port error:" << m_serial->errorString();
        closeSerialPort();
    }
}
