#include "face_detection_plugin.h"

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

Face_detection_plugin::Face_detection_plugin()
{
}

Face_detection_plugin::~Face_detection_plugin()
{

}

QString Face_detection_plugin::description()
{
    return "This is face detection plugin";
}

void Face_detection_plugin::processImage(const cv::Mat &inputImage, cv::Mat &outputImage, std::vector<cv::Rect> &object)
{
    cv::CascadeClassifier cascade;
    std::vector<cv::Rect> faces;
    cv::Mat img = inputImage.clone();
    outputImage = inputImage.clone();

    double scale = 1;

    cascade.load("./data/haarcascade_frontalcatface.xml");

    cv::Mat gray, smallImg;

    // Convert to Gray Scale
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    double fx = 1 / scale;

    // Resize
    cv::resize(gray, smallImg, cv::Size(), fx, fx, cv::INTER_LINEAR);
    cv::equalizeHist(smallImg, smallImg);

    // Detect faces
    cascade.detectMultiScale(smallImg, faces, 1.1, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

    for( size_t i = 0; i < faces.size(); i++)
    {
        cv::Rect r = faces[i];
        cv::rectangle(outputImage, r, cv::Scalar( 255, 0, 255 ), 4);
    }

}
