#ifndef QFACERECOGNITION_H
#define QFACERECOGNITION_H

#include <QObject>
#include <QString>
#include <QStringList>

#include <iostream>
#include <dirent.h>
#include <fstream>
#include <sstream>

#include <opencv2/core/core.hpp>
#include <opencv2/core.hpp>
#include <opencv2/face.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/opencv.hpp>

#include "AppConstants.h"


class QFaceRecognition : public QObject
{
    Q_OBJECT
public:
    explicit QFaceRecognition(QObject *parent = nullptr, int mode = 1);
    ~QFaceRecognition();

    cv::Mat dectectFace(cv::Mat frame);
    void addFace(QString faceName);
    void faceDbRead(std::vector<cv::Mat>& image, std::vector<int>& labels);
    void faceTrainer();
    void recognition(cv::Mat& frame);

signals:
    void recognized(QStringList& names);

public slots:
    void updateModel();

private:
    cv::CascadeClassifier face_cascade;
    cv::Ptr<cv::face::EigenFaceRecognizer> m_model;
    QString m_currentId;
    int m_imageCount;
    int flag;
};

#endif // QFACERECOGNITION_H
