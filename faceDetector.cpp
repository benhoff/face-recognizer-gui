#include "faceDetector.h"


void FaceDetector::loadFiles(cv::String faceCascadeFilename,
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
FaceDetector::~FaceDetector()
{

}

void FaceDetector::processFrame(const cv::Mat &frame)
{
    if (processAll_)
        process(frame);
    else
        queue(frame);
}

void FaceDetector::setProcessAll(bool all)
{
    processAll_ = all;
}

void FaceDetector::process(cv::Mat frame)
{
    cv::Mat grey_image;
    cv::cvtColor(frame, grey_image, CV_BGR2GRAY);
    cv::equalizeHist(grey_image, grey_image);

    std::vector<cv::Rect> faces;
    // Calculate the camera size and set the size to 1/8 of screen height
    faceCascade.detectMultiScale(grey_image, faces, 1.1, 2,  0|CV_HAAR_SCALE_IMAGE,
                                 cv::Size(frame.cols/4, frame.rows/4)); // Minimum size of obj
    //-- Draw rectangles around faces
    for( size_t i = 0; i < faces.size(); i++)
    {
        cv::rectangle(frame, faces[i], cv::Scalar( 255, 0, 255 ));
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
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    const QImage image((const unsigned char*)frame.data, frame.cols, frame.rows, frame.step,
                       QImage::Format_RGB888, &matDeleter, new cv::Mat(frame));
    image.rgbSwapped();
    Q_ASSERT(image.constBits() == frame.data);
    emit image_signal(image);
}
void FaceDetector::timerEvent(QTimerEvent *ev)
{
    if (ev->timerId() != timer_.timerId())
        return;
    process(frame_);
    frame_.release();
    timer_.stop();
}

void FaceDetector::queue(const cv::Mat &frame)
{
    if (!frame.empty())
        qDebug() << "Converter dropped frame !";

    frame_ = frame;
    if (!timer_.isActive())
        timer_.start(0, this);
}


void FaceDetector::matDeleter(void *mat)
{
    delete static_cast<cv::Mat*>(mat);
}

void FaceDetector::facecascade_filename(QString filename)
{
    cv::String temp = filename.toStdString().c_str();
    if( !faceCascade.load( temp ) )
    {
        std::cout << "Error Loading" << filename.toStdString() << std::endl;
    }
    facecascade_filename_ = filename;
    // FIXME: Incorrect Implementation
    loadFiles(filename.toStdString().c_str(), filename.toStdString().c_str());
}
