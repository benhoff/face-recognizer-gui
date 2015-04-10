#include <QApplication>
#include <QObject>
#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>

#include <iostream>
#include <stdio.h>

#include "CVOpenGLWidget.h"
#include "camera.h"

using namespace std;

/** @function main */
int main( int argc, char* argv[] )
{
	QApplication app(argc, argv);

    QStringList cameraOptions;
    cameraOptions << "0" << "1" << "2" << "3" << "4" << "5" << "6";
    QComboBox cameraComboBox;
    cameraComboBox.addItems(cameraOptions);

    QHBoxLayout* horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(&cameraComboBox);
    QPushButton *runButton = new QPushButton("run");
    horizontalLayout->addWidget(runButton);

    QVBoxLayout *layout = new QVBoxLayout;
    QWidget layoutWidget;
    CVOpenGLWidget openGLWidget(&layoutWidget);
    layout->addWidget(&openGLWidget);
    layout->addLayout(horizontalLayout);
	
    layoutWidget.setLayout(layout);

    Camera camera;
    QObject::connect(&camera, SIGNAL(imageSignal(QImage*)),
                     &openGLWidget, SLOT(ImageSlot(QImage*)));
	
	
	// TODO: Add in slot to turn off camera, or something
	QObject::connect(runButton, SIGNAL(clicked()), 
					 &camera, SLOT(runSlot()));

    QObject::connect(&cameraComboBox, SIGNAL(currentIndexChanged(int)),
                     &camera, SLOT(cameraIndexSlot(int)));
	layoutWidget.show();

	return app.exec();
}
