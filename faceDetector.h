#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H

#include <QObject>
#include <QBasicTimer>
#include <QTimerEvent>
#include <QDebug>
#include <QImage>
#include <QString>
#include <opencv2/opencv.hpp>

class FaceDetector : public QObject
{
    Q_OBJECT
    QString facecascade_filename_;
    QString eyecascade_filename_;
    QBasicTimer timer_;
    cv::Mat frame_;
    bool processAll_;
    cv::CascadeClassifier faceCascade;
    cv::CascadeClassifier eyeCascade;

    void process(cv::Mat frame);
    void loadFiles(cv::String faceCascadeFilename, cv::String eyesCascadeFilename);
    void queue(const cv::Mat & frame);
    void timerEvent(QTimerEvent* ev);
    static void matDeleter(void* mat);

public:
    FaceDetector(QObject *parent=0) : QObject(parent), processAll_(true)
    {
        facecascade_filename_ = "/home/hoff/swdev/opencv_tut/opencv/haarcascade_frontalface_default.xml";
        eyecascade_filename_ = "/home/hoff/swdev/opencv_tut/opencv/haarcascade_eye.xml";

        loadFiles(facecascade_filename_.toStdString().c_str(),
                  eyecascade_filename_.toStdString().c_str());
    }
    void setProcessAll(bool all);
    ~FaceDetector();

signals:
    void image_signal(const QImage&);

public slots:
    void processFrame(const cv::Mat& frame);
    void facecascade_filename(QString filename);
};

#endif // FACEDETECTOR_H
