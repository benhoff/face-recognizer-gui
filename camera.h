#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QObject>
#include <stdio.h>
#include <iostream>
class Camera : public QObject
{
public:
    Camera(QObject* parent = 0);

    CvCapture* capture;
    cv::Mat frame;

	void detectAndDisplay( cv::Mat frame );

    cv::CascadeClassifier faceCascade;
    cv::CascadeClassifier eyeCascade;

public slots:
	void runSlot(int cameraNumber);
signals:
    void imageSignal(cv::Mat* matrix);

protected:
    void loadFiles(cv::string faceCascadeFilename, cv::string eyesCascadeFilename);
};
