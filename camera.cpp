#include "camera.h"

Camera::Camera(QObject* parent) : QObject(parent)
{
    capture = new cv::VideoCapture();
    cv::String faceCascadeFilename = "/home/hoff/swdev/opencv_tut/opencv/haarcascade_frontalface_default.xml";
    cv::String eyeCascadeFilename = "/home/hoff/swdev/opencv_tut/opencv/haarcascade_eye.xml";

    loadFiles(faceCascadeFilename, eyeCascadeFilename);
	
}

Camera::~Camera()
{
    capture->~VideoCapture();
}

QImage Camera::convertToQImage(cv::Mat frame)
{
    QImage qtImage;
    if( frame.channels() == 3 )
    {
        qtImage = QImage((const unsigned char*)(frame.data),
                          frame.cols, frame.rows,
                          frame.step, QImage::Format_RGB888).rgbSwapped();
    }

    else if( frame.channels() == 1)
    {
        qtImage = QImage((const unsigned char*)(frame.data),
                          frame.cols, frame.rows,
                          frame.step, QImage::Format_Indexed8);
    }

    // Note: implicit return of empty QImage if channels != 1 or 3
    return qtImage;
}

void Camera::loadFiles(cv::String faceCascadeFilename,
                       cv::String eyeCascadeFilename)
{
    // TODO: Add in a try catch statement here
    if( !faceCascade.load( faceCascadeFilename ) )
    {
        std::cout << "Error Loading" << faceCascadeFilename << std::endl;
    }

    if( !eyeCascade.load( eyeCascadeFilename ) )
    {
        std::cout << "Error Loading" << eyeCascadeFilename << std::endl;
    }
}

void Camera::runSlot()
{
    // TODO: want to be able to select this
    capture->open(cameraIndex_);
    if( capture->isOpened() )
	{
		while( true )
        {
            capture->read(frame);
			if( !frame.empty() )
			{
				detectAndDisplay( frame );
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

void Camera::cameraIndexSlot(int index)
{
    cameraIndex_ = index;
}

void Camera::detectAndDisplay( cv::Mat frame )
{
    std::vector<cv::Rect> faces;
    // Calculate the camera size and set the size to 1/8 of screen height
    faceCascade.detectMultiScale(frame, faces, 1.1, 3, 0,
                          cv::Size(frame.cols/8, frame.rows/8),
                          cv::Size(frame.cols, frame.rows));
    //-- Detect face
	for( size_t i = 0; i < faces.size(); i++)
    {
        rectangle(frame, faces[i], cv::Scalar( 255, 0, 255 ));
        /*
        cv::Point center( faces[i].x + faces[i].width*0.5,
				  faces[i].y + faces[i].height*0.5);

		ellipse( frame, center, 
             cv::Size( faces[i].width*0.5, faces[i].height*0.5 ),
             0, 0, 360, cv::Scalar( 255, 0, 255 ), 4, 8, 0);

        cv::Mat faceROI = frameGray( faces[i] );
        std::vector<cv::Rect> eyes;

		//-- In each face, detect eyes
        eyeCascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(30, 30) );

		for( size_t j = 0; j < eyes.size(); j++)
		{
            cv::Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5,
					  faces[i].y + eyes[j].y + eyes[j].height*0.5 );
			int radius = cvRound( (eyes[j].width + eyes[j].height) *0.25);
            circle( frame, center, radius, cv::Scalar( 255, 0, 0 ), 4, 8, 0);
        }
        */

    }
    QImage image = convertToQImage(frame);
    emit imageSignal(&image);
}
