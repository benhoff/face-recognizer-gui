#include <QApplication>
#include <QObject>
#include <QVBoxLayout>
#include <QPushButton>

#include <iostream>
#include <stdio.h>

#include "CVOpenGLWidget.h"
#include "thisGarbage.h"

using namespace std;

/** @function main */
int main( int argc, char* argv[] )
{
	QApplication app(argc, argv);
	QWidget layoutWidget();

	CVOpenGLWidget openGLWidget(layoutWidget);
	
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(openGLWidget);
	
	QPushButton *runButton = new QPushButton('Run');

	layout->addWidget(runButton);
	
	layoutWidget.setLayout(layout);

	Camera camera();
	QObject::connect(&camera, SIGNAL(imageSignal(cv::Mat)), 
					 &widget, SLOT(ShowImage(cv::Mat));

	QObject::connect(runButton, SIGNAL(clicked()), 
					 &camera, SLOT(runSlot()));

	layoutWidget.show();

	return app.exec();
}
