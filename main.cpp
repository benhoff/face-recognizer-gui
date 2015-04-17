#include <QApplication>
#include <opencv2/opencv.hpp>
#include "mainwindow.h"

using namespace std;

/** @function main */
int main( int argc, char* argv[] )
{
    qRegisterMetaType<cv::Mat>();
	QApplication app(argc, argv);
    MainWindow window;
    window.show();
	return app.exec();
}
