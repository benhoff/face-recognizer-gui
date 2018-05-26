#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include <QObject>
#include <QScopedPointer>
#include <QTimerEvent>
#include <stdio.h>
#include <iostream>
#include <QImage>
#include <QBasicTimer>
#include <QDebug>

class Camera : public QObject
{
    Q_OBJECT
    QScopedPointer<cv::VideoCapture> videoCapture_;
    QBasicTimer timer_;
    bool run_;
    bool usingVideoCamera_;
    int cameraIndex_;
    cv::String videoFileName_;

public:
    Camera(int camera_index=0, QObject* parent=0) : QObject(parent)
    {
        cameraIndex_ = camera_index;
        usingVideoCamera_ = true;
    }

    ~Camera();
    QImage convertToQImage( cv::Mat frame );


public slots:
    void runSlot();
    void cameraIndexSlot(int index);
    void videoFileNameSlot(QString fileName);
    void usingVideoCameraSlot(bool value);
    void stopped();

signals:
    void started();
    void matReady(const cv::Mat &);

private:
    void timerEvent(QTimerEvent * ev);
};
