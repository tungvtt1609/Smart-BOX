#ifndef QCAMERAWIDGET_H
#define QCAMERAWIDGET_H

#include <QWidget>
#include <QThread>
#include "AppModel.h"
#include "QCameraCapture.h"

namespace Ui {
class QCameraWidget;
}

class QCameraWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QCameraWidget(QWidget *parent = nullptr, AppModel *model = nullptr);
    ~QCameraWidget();

    void startWidget();
    void stopWidget();
    bool getCameraState();

public slots:
    void openCamera();
    void closeCamera();

private:
    Ui::QCameraWidget *ui;
    AppModel* m_model;
    QCameraCapture* m_camera;
    bool m_camera_state;
};

#endif // QCAMERAWIDGET_H
