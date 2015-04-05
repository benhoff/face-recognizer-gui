#pragma once
#include <QOpenGLWidget>
#include <QColor>
#include <QImage>
#include <QOpenGLFunctions>
#include <QGLWidget>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class CVOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    CVOpenGLWidget(QWidget *parent=0);

	void paintGL(); /// OpenGl Rendering
	void resizeGL(int width, int height); /// Widget Resize Event
	void initializeGL(); ///OpenGL intilizing

	void updateScene(); /// Forces a scene update
	void renderImage(); /// Render image on openGL frame

signals:
	void imageSizeChanged( int out_width, int out_height );

public slots:
    bool ImageSlot( cv::Mat image); /// used to set the image to be viewed

	cv::CascadeClassifier face_cascade;
	cv::CascadeClassifier eyes_cascade;

	QImage qtImage; /// Qt image to be rendered
	cv::Mat originalImage; /// original OpenCv image to be shown

private:
	int resizedImageHeight_;
    int resizedImageWidth_;
	float imageRatio_;

	int positionX_;
	int positionY_;

    cv::RNG rng_;
	bool sceneChanged_;
	QColor backgroundColor_;
};
