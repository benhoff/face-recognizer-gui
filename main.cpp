#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <Qt5/QtCore>
#include <Qt5/QtWidgets>

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;


void detectAndDisplay( Mat frame);

/** Global variable */

String face_cascade_name = "haarcascade_frontalface_default.xml";
String eyes_cascade_name = "haarcascade_eye.xml";

CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;

string window_name = "Capture - Face detection";
RNG rng(12345);

/** @function main */
int main( int argc, const char** argv )
{
	QtWidgets.QApplication app(argc, argv);
	QtWidgets.QMainWindow main_window();
	main_window.show();

	return app.exec()

	CvCapture* capture;
	Mat frame;

	//-- 1. Load the cascades
	if( !face_cascade.load( face_cascade_name ) ){printf("--(!)Error loading\n"); return -1; };
	if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };

	//-- 2. Read the video stream
	//capture = cvCaptureFromFile("/home/hoff/example.flv");
	capture = cvCaptureFromCAM( 0 );
	if( capture )
	{
		while( true )
		{
			frame = cvQueryFrame( capture );
			if( !frame.empty() )
			{
				detectAndDisplay( frame );
			}
			else
			{
				std::cout << "No captured frame -- Break!" << std::endl;
				break;
				
			}

			int c = waitKey(10);
			if( (char)c == 'c') 
			{ 
				break; 
			}

		}
	}
	return 0;
}

void detectAndDisplay( Mat frame )
{
	std::vector<Rect> faces;
	Mat frame_gray;

	cvtColor( frame, frame_gray, CV_BGR2GRAY );
	equalizeHist( frame_gray, frame_gray );

	//-- Detect face
	face_cascade.detectMultiScale( frame_gray, 
				       faces, 1.1, 2, 
				       0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

	for( size_t i = 0; i < faces.size(); i++)
	{
		Point center( faces[i].x + faces[i].width*0.5,
			      faces[i].y + faces[i].height*0.5);

		ellipse( frame, center, 
			 Size( faces[i].width*0.5, faces[i].height*0.5 ),
			 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0);

		Mat faceROI = frame_gray( faces[i] );
		std::vector<Rect> eyes;

		//-- In each face, detect eyes
		eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

		for( size_t j = 0; j < eyes.size(); j++)
		{
			Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, 
				      faces[i].y + eyes[j].y + eyes[j].height*0.5 );
			int radius = cvRound( (eyes[j].width + eyes[j].height) *0.25);
			circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0);
		}

	}
	imshow( window_name, frame );	
}
