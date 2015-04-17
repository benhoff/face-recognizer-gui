#include "convertor.h"

convertor::convertor(QObject *parent) : QObject(parent)
{

    cv::String faceCascadeFilename = "/home/hoff/swdev/opencv_tut/opencv/haarcascade_frontalface_default.xml";
    cv::String eyeCascadeFilename = "/home/hoff/swdev/opencv_tut/opencv/haarcascade_eye.xml";

    loadFiles(faceCascadeFilename, eyeCascadeFilename);
}

void convertor::loadFiles(cv::String faceCascadeFilename,
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
convertor::~convertor() : QObject(parent), processAll_(true)
{

}

void convertor::process_frame(const cv::Mat &frame)
{
    if (processAll_)
        process(frame);
    else
        queue(frame);
}

void convertor::setProcessAll(bool all)
{
    processAll_ = all;
}

void convertor::process(cv::Mat frame)
{
    cv::resize(frame, frame, cv::Size(), 0.3, 0.3, cv::INTER_AREA);

    // Add in facial recognition logic here
    cv::cvtColor(frame, frame, CV_BGR2RGB);

    std::vector<cv::Rect> faces;
    // Calculate the camera size and set the size to 1/8 of screen height
    faceCascade.detectMultiScale(frame, faces, 1.1, 3, 0,
                          cv::Size(frame.cols/8, frame.rows/8),
                          cv::Size(frame.cols, frame.rows));
    //-- Detect face
    for( size_t i = 0; i < faces.size(); i++)
    {
        rectangle(*frame, (*faces)[i], cv::Scalar( 255, 0, 255 ));
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
    const QImage image(frame.data, frame.cols, frame.rows, frame.step,
                     QImage::Format_RGB888, &matDeleter, new cv::Mat(frame));
    Q_ASSERT(image.constBits() == frame.data);
    emit image_signal(image);
}
void convertor::timerEvent(QTimerEvent *ev)
{
    if (ev->timerId() != timer_.timerId())
        return;
    process(frame_);
    frame_.release();
    timer_.stop();
}

void convertor::queue(const cv::Mat &frame)
{
    if (!frame.empty())
        qDebug() << "Converter dropped frame !";

    frame_ = frame;
    if (!timer_.isActive())
        timer_.start(0, this);
}


void convertor::matDeleter(void *mat)
{
    delete static_cast<cv::Mat*>(mat);
}

