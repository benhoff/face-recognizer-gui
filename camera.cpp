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
    run_ = true;
    // TODO: want to be able to select this
    if (usingVideoCamera_)
        capture->open(cameraIndex_);
    else
        capture->open(videoFileName_);

    if( capture->isOpened() )
	{
        while( run_ )
        {
            capture->read(frame_);
            if( !frame_.empty() )
            {
                // This is going to become an emit signal to our convertor class
                //detectAndDisplay( frame );
			}
			else
			{
				std::cout << "No captured frame -- Break!" << std::endl;
				break;
			}

            int c = cv::waitKey(10);
			if( (char)c == 'c') 
			{ 
                break;
                std::cout << "Break!";
			}
		}
	}
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
