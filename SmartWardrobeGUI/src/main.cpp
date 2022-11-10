#include "MainWindow.h"
#include "AppConstants.h"
#include "QCameraCapture.h"
#include "QFaceRecognition.h"
#include "QDataHandler.h"

#include <QApplication>
#include <opencv2/core.hpp>
#include <QStringList>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<cv::Mat>("cv::Mat");
    MainWindow w;
//    w.showFullScreen();
    w.show();

//    QFaceRecognition face(nullptr, 0);
//    face.faceTrainer();

    return a.exec();
}
