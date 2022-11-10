#include "QFaceRecognition.h"
#include <QDebug>
#include <QDir>
#include <QDirIterator>

QFaceRecognition::QFaceRecognition(QObject *parent, int mode)
    : QObject{parent}
{
    if(!face_cascade.load(FACE_CASCADE))
    {
        CONSOLE << "Load face cascade failed";
    }
    //create algorithm eigenface recognizer
    m_model = cv::face::EigenFaceRecognizer::create();
    if (mode == 1){
      m_model->read(EIGEN_FACE);
    }
}

QFaceRecognition::~QFaceRecognition()
{
}

cv::Mat QFaceRecognition::dectectFace(cv::Mat frame)
{
    std::vector<cv::Rect> faces;
    cv::Mat frame_gray;
    cv::Mat crop;
    cv::Mat res;
    cv::Mat gray;

    cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(frame_gray, frame_gray);

    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

    cv::Rect roi_b;
    cv::Rect roi_c;

    size_t ic = 0;
    int ac = 0;

    size_t ib = 0;
    int ab = 0;

    for (ic = 0; ic < faces.size(); ic++)

    {
        roi_c.x = faces[ic].x;
        roi_c.y = faces[ic].y;
        roi_c.width = (faces[ic].width);
        roi_c.height = (faces[ic].height);

        ac = roi_c.width * roi_c.height;

        roi_b.x = faces[ib].x;
        roi_b.y = faces[ib].y;
        roi_b.width = (faces[ib].width);
        roi_b.height = (faces[ib].height);

        crop = frame(roi_b);
        resize(crop, res, cv::Size(128, 128), 0, 0,cv::INTER_LINEAR);
        cvtColor(crop, gray, cv::COLOR_BGR2GRAY);
        std::stringstream ssfn;

        ssfn << FACE_IMAGE << m_currentId.toStdString() << m_imageCount << ".jpg";
        std::string save_path = ssfn.str();
        imwrite(save_path, res);
        m_imageCount++;


        cv::Point pt1(faces[ic].x, faces[ic].y);
        cv::Point pt2((faces[ic].x + faces[ic].height), (faces[ic].y + faces[ic].width));
        rectangle(frame, pt1, pt2, cv::Scalar(0, 255, 0), 2, 8, 0);
    }

    if (!crop.empty())
    {
        return crop;
    }
    else
        return frame;
}

void QFaceRecognition::addFace(QString faceName)
{
    // hmm hmm
    // Pending
}

void QFaceRecognition::faceDbRead(std::vector<cv::Mat> &images, std::vector<int> &labels)
{

    QString path = BUILD_DIR + FACE_IMAGE;

    CONSOLE << path;

    QDirIterator directories(path, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

    while(directories.hasNext() )
    {
        QString dirName = directories.next();
        QString labelName = directories.fileName();
        qDebug() << dirName;
        qDebug() << labelName;

        QDir imageDir(dirName);
        imageDir.setNameFilters({"*.png", "*.jpg"});

        QStringList imageLists = imageDir.entryList();

        for (int i = 0; i < imageLists.size(); i++)
        {
            qDebug() << dirName + "/" + imageLists[i];
            images.push_back(cv::imread((dirName + "/" + imageLists[i]).toStdString(), 0));
            labels.push_back(labelName.toInt());
        }

        qDebug() << "=================";
    }
}

void QFaceRecognition::faceTrainer()
{
    std::vector<cv::Mat> images;
    std::vector<int> labels;
    faceDbRead(images, labels);
    CONSOLE << "size of the images is " << images.size();
    CONSOLE << "size of the labels is " << labels.size();
    CONSOLE << "Training begins....";

    //train data
    m_model->train(images, labels);

    m_model->save(EIGEN_FACE);

    CONSOLE << EIGEN_FACE;
    CONSOLE << "Training finished....";

    cv::waitKey(10000);

    updateModel();
}

void QFaceRecognition::recognition(cv::Mat& frame)
{
    int img_width = IMAGE_WIDTH;
    int img_height = IMAGE_HEIGHT;

    QString p_name = "";
    QStringList names;

    std::vector<cv::Rect> faces;
    cv::Mat graySacleFrame;
    cv::Mat original;

    if (!frame.empty()) {

        //clone from original frame
        original = frame.clone();

        //convert image to gray scale and equalize
        cv::cvtColor(original, graySacleFrame, cv::COLOR_BGR2GRAY);
        //equalizeHist(graySacleFrame, graySacleFrame);

        //detect face in gray image
        face_cascade.detectMultiScale(graySacleFrame, faces, 1.1, 3, 0, cv::Size(90, 90));

        //number of faces detected
        // CONSOLE << faces.size() << " faces detected";
        std::string faceset = std::to_string(faces.size());

        int width = 0, height = 0;

        //region of interest
        //cv::Rect roi;

        for (int i = 0; i < faces.size(); i++)
        {
            //region of interest
            cv::Rect face_i = faces[i];

            //crop the roi from grya image
            cv::Mat face = graySacleFrame(face_i);

            //resizing the cropped image to suit to database image sizes
            cv::Mat face_resized;
            cv::resize(face, face_resized, cv::Size(img_width, img_height), 1.0, 1.0, cv::INTER_CUBIC);

            //recognizing what faces detected
            int label = -1;
            double confidence = 0;
            m_model->predict(face_resized, label, confidence);

            CONSOLE << " confidence " << confidence << " Label: " << label;

            p_name = QString::fromStdString(std::to_string(label));
            names.append(p_name);
            
            //drawing green rectagle in recognize face
            rectangle(frame, face_i, CV_RGB(0, 255, 0), 1);
            QString text = p_name;

            int pos_x = std::max(face_i.tl().x - 10, 0);
            int pos_y = std::max(face_i.tl().y - 10, 0);

            //name the person who is in the image
            cv::putText(frame, text.toStdString(), cv::Point(pos_x, pos_y), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, CV_RGB(0, 255, 0), 1.0);
        }

//        cv::putText(frame, "No. of Persons detected: " +std::to_string(faces.size()), cv::Point(30, 90), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, CV_RGB(0, 255, 0), 1.0);
//        cv::imshow("Results", frame);
    }

    emit recognized(names);
}

void QFaceRecognition::updateModel()
{
    m_model->clear();
    m_model->read(EIGEN_FACE);
    CONSOLE << "Model updated ...";
}

















