#include "QFaceInfor.h"

QFaceInfor::QFaceInfor()
{

}

QFaceInfor::QFaceInfor(QString name, QString rfid, QString type)
    : m_name(name),
      m_rfid(rfid),
      m_type(type)
{

}

int QFaceInfor::id() const
{
    return m_id;
}

QString QFaceInfor::name() const
{
    return m_name;
}

QString QFaceInfor::rfid() const
{
    return m_rfid;
}

QString QFaceInfor::type() const
{
    return m_type;
}

QString QFaceInfor::currentPosition() const
{
    return m_currentWardrobePosition;
}

void QFaceInfor::setId(int id)
{
    m_id = id;
}

void QFaceInfor::setName(QString name)
{
    m_name = name;
}

void QFaceInfor::setRFID(QString rfid)
{
    m_rfid = rfid;
}

void QFaceInfor::setType(QString type)
{
    m_type = type;
}

void QFaceInfor::setCurrentPosition(QString position)
{
    m_currentWardrobePosition = position;
}
