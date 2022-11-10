#ifndef QFACEINFOR_H
#define QFACEINFOR_H

#include <QObject>
#include <QString>

class QFaceInfor
{
public:
    QFaceInfor();
    QFaceInfor(QString name, QString rfid, QString type);
    QFaceInfor(int id, QString name, QString rfid, QString type);

    int id() const;
    QString name() const;
    QString rfid() const;
    QString type() const;
    QString currentPosition() const;

    void setId(int id);
    void setName(QString name);
    void setRFID(QString rfid);
    void setType(QString type);
    void setCurrentPosition(QString position);

    QFaceInfor operator= (QFaceInfor face)
    {
        QFaceInfor _face;
        _face.setId(face.id());
        _face.setName(face.name());
        _face.setRFID(face.rfid());
        _face.setType(face.type());
        return _face;
    }

signals:

private:
    int m_id;
    QString m_name;
    QString m_rfid;
    QString m_type;
    QString m_currentWardrobePosition;
};

#endif // QFACEINFOR_H
