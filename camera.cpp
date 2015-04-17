#include "camera.h"

Camera::Camera(QObject* parent) : QObject(parent)
{
    capture = new cv::VideoCapture();
    usingVideoCamera_ = true;
    frame_ = new cv::Mat
}

Camera::~Camera()
{
}

void Camera::runSlot()
{
    // TODO: clean up. Would be nice not to have nested `if` statements
    if (!videoCapture_)
        if (usingVideoCamera_)
            videoCapture_.reset(new cv::VideoCapture(cameraIndex_));
        else
            videoCapture_.reset(new cv::VideoCapture(videoFileName_));
    if (videoCapture_->isOpened())
    {
       timer_.start(0, this);
       emit started();
    }
}

void Camera::stopped()
{
    timer_.stop();
}

void Camera::timerEvent(QTimeEvent *ev)
{
    if (ev->timerId() != timer_.timerId())
        return;
    cv::Mat frame;
    if (videoCapture_->read(frame)) // Blocks until a new frame is ready
    {
        timer_.stop();
        return
    }
    emit matReady(frame);
}

void Camera::usingVideoCameraSlot(bool value)
{
    usingVideoCamera_ = value;
}

void Camera::cameraIndexSlot(int index)
{
    cameraIndex_ = index;
}

void Camera::videoFileNameSlot(QString fileName)
{
    videoFileName_ = fileName.toStdString().c_str();
}

void Camera::detectAndDisplay( QScopedPoint<cv::Mat> frame )
{
    const QImage image(frame->data, frame->cols, frame->rows, frame->step,
                       QImage::Format_RGB888, matDeleter, frame.take());
    emit imageSignal(&image);
    cv::waitKey(30);
}
