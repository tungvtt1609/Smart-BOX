#include "MainWindow.h"
#include "QDataHandler.h"
#include "AppConstants.h"

#include "ui_mainwindow.h"

#include <QDebug>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/images/data/res/nurses.png"));

    m_model = new AppModel();

    m_cameraWidget = new QCameraWidget(nullptr, m_model);
    m_wardrobeWidget = new QWardrobeWidget(nullptr, m_model);
    m_faceInforWidget = new QFaceInforWidget(nullptr, m_model);
    m_stackWidget = new QStackedWidget();

    m_stackWidget->addWidget(m_cameraWidget);
    m_stackWidget->addWidget(m_wardrobeWidget);
    m_stackWidget->addWidget(m_faceInforWidget);

    m_stackWidget->setCurrentWidget(m_wardrobeWidget);

    setCentralWidget(m_stackWidget);

    connect(m_model, &AppModel::slotUpdate, m_wardrobeWidget, &QWardrobeWidget::updateUI);

//    connect(m_model, &AppModel::havePerson, this, [this] {
//        CONSOLE << "Start Person checking";
//        m_stackWidget->setCurrentWidget(m_cameraWidget);
//        m_model->setState(AppModel::APP_STATE::CHECKING_STATE);
//        if (!m_cameraWidget->getCameraState()){
//            m_cameraWidget->startWidget();
//        }
//    });

    // Need check APP_STATE before emit this signal
//    connect(m_model, &AppModel::noPerson, this, [this] {
//        CONSOLE << "Stop Person checking";
//        m_model->setState(AppModel::APP_STATE::NO_CHECKING_STATE);
//        m_stackWidget->setCurrentWidget(m_wardrobeWidget);
//        // m_cameraWidget->stopWidget();
//    });

//    connect(m_model, &AppModel::recognitionDone, this, [this] {
//        CONSOLE << "Checking done";
//        m_model->setState(AppModel::APP_STATE::CHECKING_DONE_STATE);
//        m_faceInforWidget->loadFaceInfor1();
//        m_stackWidget->setCurrentWidget(m_faceInforWidget);
//        // m_cameraWidget->stopWidget();
//    });

//    connect(m_model, &AppModel::doorClose, this, [this] {
//        CONSOLE << "Return no checking state";
//        m_model->setState(AppModel::APP_STATE::NO_CHECKING_STATE);
//        m_stackWidget->setCurrentWidget(m_wardrobeWidget);
//    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << event->key();

    if(event->key() == Qt::Key_Q)
    {
        m_stackWidget->setCurrentWidget(m_wardrobeWidget);
    }
    else if(event->key() == Qt::Key_W)
    {
        m_stackWidget->setCurrentWidget(m_cameraWidget);
        if (!m_cameraWidget->getCameraState()){
            m_cameraWidget->startWidget();
        }
    }
    else if (event->key() == Qt::Key_E)
    {
        m_faceInforWidget->loadFaceInfor1();
        m_stackWidget->setCurrentWidget(m_faceInforWidget);
    }
    else if (event->key() == Qt::Key_R)
    {
        m_faceInforWidget->loadFaceInfor2();
        m_stackWidget->setCurrentWidget(m_faceInforWidget);
    }
    else if (event->key() == Qt::Key_T)
    {
        m_faceInforWidget->loadFaceInfor3();
        m_stackWidget->setCurrentWidget(m_faceInforWidget);
    }
    else if (event->key() == Qt::Key_Y)
    {
        m_faceInforWidget->loadFaceInfor4();
        m_stackWidget->setCurrentWidget(m_faceInforWidget);
    }
    else if (event->key() == Qt::Key_1)
    {
        // LED 1 ON
        // Slot A_1
        QByteArray opendoor = "d:1";
        QByteArray getslot = QString("A_1").toUtf8();
        m_model->m_handler->writeData(opendoor + getslot);
    }
    else if (event->key() == Qt::Key_2)
    {
        // LED 2 ON
        // Slot A_2
        QByteArray opendoor = "d:1";
        QByteArray getslot = QString("A_2").toUtf8();
        m_model->m_handler->writeData(opendoor + getslot);
    }
    else if (event->key() == Qt::Key_3)
    {
        // LED 3 ON
        // Slot A_3
        QByteArray opendoor = "d:1";
        QByteArray getslot = QString("A_3").toUtf8();
        m_model->m_handler->writeData(opendoor + getslot);
    }
    else if (event->key() == Qt::Key_4)
    {
        // LED 4 ON
        // Slot A_4
        QByteArray opendoor = "d:1";
        QByteArray getslot = QString("A_4").toUtf8();
        m_model->m_handler->writeData(opendoor + getslot);
    }
    else if (event->key() == Qt::Key_5)
    {
        // Open door (Staff)
        QByteArray opendoor = "d:1";
        m_model->m_handler->writeData(opendoor);
    }
    else if (event->key() == Qt::Key_A)
    {
        // Update slot 1
        m_model->addSlot("A_1", "");
    }
    else if (event->key() == Qt::Key_S)
    {
        // Update slot 2
        m_model->addSlot("A_2", "");
    }

    else if (event->key() == Qt::Key_D)
    {
        // Update slot 3
        m_model->addSlot("A_3", "");
    }

    else if (event->key() == Qt::Key_F)
    {
        // Update slot 4
        m_model->addSlot("A_4", "");
    }
    else if (event->key() == Qt::Key_G)
    {
        // Remove slot 1
        m_model->removeSlot("A_1");
    }
    else if (event->key() == Qt::Key_H)
    {
        // Remove slot 2
        m_model->removeSlot("A_2");
    }

    else if (event->key() == Qt::Key_J)
    {
        // Remove slot 3
        m_model->removeSlot("A_3");
    }

    else if (event->key() == Qt::Key_K)
    {
        // Remove slot 4
        m_model->removeSlot("A_4");
    }

}















