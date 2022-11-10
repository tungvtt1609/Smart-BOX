#ifndef QDATAHANDLER_H
#define QDATAHANDLER_H

#include <QObject>
#include <QtCore/QtGlobal>
#include <QtSerialPort/QSerialPort>

// Connect with Arduino, read and extract information
class QDataHandler : public QObject
{
    Q_OBJECT
public:
    QDataHandler();
    ~QDataHandler();

public slots:
    void openSerialPort();
    void closeSerialPort();
    void writeData(const QByteArray &data);
private slots:

    void readData();

    void handleError(QSerialPort::SerialPortError error);

signals:
    void dataReady(QString& data);

private:
    QSerialPort *m_serial;

};

#endif // QDATAHANDLER_H
