#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


class Camera
{
public:
	CvCapture* capture;
	Mat frame;

	Camera();

	void detectAndDisplay( Mat frame );

public slots:
	void runSlot();
public signals:
	void imageSignal();
};
