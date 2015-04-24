#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H

#include <QObject>
#include <QBasicTimer>
#include <QTimerEvent>
#include <QDebug>
#include <QImage>
#include <opencv2/opencv.hpp>

class FaceDetector : public QObject
{
    Q_OBJECT

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
    explicit FaceDetector(QObject *parent = 0);
    void setProcessAll(bool all);
    ~FaceDetector();

signals:
    void image_signal(const QImage&);

public slots:
    void processFrame(const cv::Mat& frame);
};

FaceDetector::FaceDetector(QObject *parent ) : QObject(parent), processAll_(true)
{
    // TODO: STOP HARD CODING THIS!
    cv::String faceCascadeFilename = "/home/hoff/swdev/opencv_tut/opencv/haarcascade_frontalface_default.xml";
    cv::String eyeCascadeFilename = "/home/hoff/swdev/opencv_tut/opencv/haarcascade_eye.xml";

    loadFiles(faceCascadeFilename, eyeCascadeFilename);
}
#endif // FACEDETECTOR_H
