#ifndef FACE_DETECTION_PLUGIN_H
#define FACE_DETECTION_PLUGIN_H

#include "face_detection_plugin_global.h"
#include "CvPluginInterface.h"

class FACE_DETECTION_PLUGIN_EXPORT Face_detection_plugin
        : public QObject, public CvPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.life.cvplugininterface")
    Q_INTERFACES(CvPluginInterface)

public:
    Face_detection_plugin();
    ~Face_detection_plugin();

    QString description();
    void processImage(const cv::Mat &inputImage, cv::Mat &outputImage, std::vector<cv::Rect> &object);
};

#endif // FACE_DETECTION_PLUGIN_H
