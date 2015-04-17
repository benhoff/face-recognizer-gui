#ifndef CONVERTOR_H
#define CONVERTOR_H

#include <QObject>
#include <QBasicTimer>
#include <QDebug>
#include <opencv2/opencv.hpp>

class Convertor : public QObject
{
    Q_OBJECT
    QBasicTimer timer_;
    cvMat frame_;
    bool processAll_;
    static void matDeleter(void* mat);
    void queue(const cv::Mat & frame);
    void process(cv::Mat frame);
    void timerEvent(QTimerEvent* ev);
    void loadFiles(cv::String faceCascadeFilename, cv::String eyesCascadeFilename);
    cv::CascadeClassifier faceCascade;
    cv::CascadeClassifier eyeCascade;

public:
    explicit convertor(QObject *parent = 0);
    void setProcessAll(bool all);
    ~convertor();

signals:
    void image_signal(const QImage&);

public slots:
    void process_frame(const cv::Mat& frame);
};

#endif // CONVERTOR_H
