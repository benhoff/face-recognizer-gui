#include <QApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <QDebug>
#include "mainwindow.h"

Q_DECLARE_METATYPE(cv::Mat)
/** @function main */
int main( int argc, char* argv[] )
{
    qRegisterMetaType<cv::Mat>();
    //qDebug() << cv::cuda::getCudaEnbledDeviceCount();
	QApplication app(argc, argv);
    MainWindow window;
    window.show();
	return app.exec();
}
