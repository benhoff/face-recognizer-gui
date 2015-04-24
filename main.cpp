#include <QApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/cuda_types.hpp>
#include <opencv2/core/cuda.inl.hpp>
#include <QDebug>
#include "mainwindow.h"

Q_DECLARE_METATYPE(cv::Mat)
/** @function main */
int main( int argc, char* argv[] )
{
    qRegisterMetaType<cv::Mat>();
    qDebug() << cv::cuda::getCudaEnabledDeviceCount();
	QApplication app(argc, argv);
    MainWindow window;
    window.show();
	return app.exec();
}
