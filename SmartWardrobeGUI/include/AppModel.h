#ifndef APPMODEL_H
#define APPMODEL_H

#include <QObject>
#include <QPixmap>
#include <memory.h>
#include <QStringList>

#include "WardrobeDB.h"
#include "QDataHandler.h"
#include "QFaceRecognition.h"
#include "QFaceInfor.h"

class AppModel : public QObject
{
    Q_OBJECT

    Q_ENUMS(APP_STATE)

public:

    enum APP_STATE {
        NONE_STATE,
        CHECKING_STATE, // when received signal havePerson() => change to QCameraWidget => open camera + checking
        CHECKING_DONE_STATE, // when checking done => have face infor => change to QFaceInforWidget
        NO_CHECKING_STATE, // when face dont have in DB or no person before machine => change to QWardrobeWidget
        ADD_FACE_STATE, // when update face_db (pending state)
        SLOT_UPDATE, // when recived signal wardrobeUpdate() => change to QWardrobeWidget and wait to wardobeUpdateDone() => update UI
        END_STATE,
    };

    explicit AppModel(QObject *parent = nullptr);

    bool addSlot(QString position, QString rfid);
    bool removeSlot(QString position);
    void addFace(QString& name, QString& rfid);
    void writeRecord(QString& rfid, QString& position, int state);

    void findFaceInfor(QString faceId, QFaceInfor& faceInfor);
    QString findSlot(QString rfid);

    WardrobeDB* m_database;
    QDataHandler* m_handler;
    QFaceRecognition* m_faceRecognition;

signals:
    void getSlotDone(QString position);
    void slotUpdate(); // update UI signal
    void wardrobeUpdate();
    void wardrobeUpdateDone();
    void imageReady(QPixmap pixmap);
    void sendIndex(QString index);
    void havePerson();  // start camera widget
    void noPerson();    // close camera widget and switch to wardrobe widget
    void recognitionDone(); // change to QFaceInforWidget
    void slotNotifyUI(QString position);
    void idRecognizedNotify(QString faceId);
    void stateChanged();
    void rfidReceived(QString rfid);
    void doorClose();

public slots:
    void processImage(cv::Mat frame);
    void extractData(QString& data);
    void checkFace(QStringList& faceId);
    void setState(APP_STATE state);

public:
    APP_STATE m_state;
    QFaceInfor m_currentFace;
    bool doorState;
};

#endif // APPMODEL_H
