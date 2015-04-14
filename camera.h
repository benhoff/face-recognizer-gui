#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include <QObject>
#include <stdio.h>
#include <iostream>
#include <QImage>

class Camera : public QObject
{
Q_OBJECT
public:
    Camera(QObject* parent = 0);
    ~Camera();
    cv::VideoCapture* capture;
    cv::Mat frame;

    void detectAndDisplay( cv::Mat frame );

    QImage convertToQImage( cv::Mat frame );

    cv::CascadeClassifier faceCascade;
    cv::CascadeClassifier eyeCascade;

public slots:
    void runSlot();
    void cameraIndexSlot(int index);
    void videoFileNameSlot(QString fileName);
    void usingVideoCameraSlot(bool value);

signals:
    void imageSignal(QImage* image);

protected:
    void loadFiles(cv::String faceCascadeFilename, cv::String eyesCascadeFilename);

private:
    bool usingVideoCamera_;
    int cameraIndex_;
    cv::String videoFileName_;
};
