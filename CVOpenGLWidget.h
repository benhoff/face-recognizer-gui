#include <QOpenGLWidget>
#include <QColor>
#include <QImage>
#include <QOpenGLFunctions>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class CVOpenGLWidget : public QOpenGlWidget, protected QOpenGLFunctions
{
public:
	CVOpenGLWidget(QWidget *parent);

	void paintGL(); /// OpenGl Rendering
	void resizeGL(int width, int height); /// Widget Resize Event
	void initializeGL(); ///OpenGL intilizing

	void updateScene(); /// Forces a scene update
	void renderImage(); /// Render image on openGL frame

signals:
	void imageSizeChanged( int out_width, int out_height );

public slots:
	bool ShowImage( cv::Mat image); /// used to set the image to be viewed

	cv::CascadeClassifier face_cascade;
	cv::CascadeClassifier eyes_cascade;

	QImage qtImage; /// Qt image to be rendered
	cv::Mat originalImage; /// original OpenCv image to be shown

private:
	int resizedImageHeight_;
	int resizedImageWidgth_;
	float imageRatio_;

	int positionX_;
	int positionY_;

	RNG rng_;
	bool sceneChanged_;
	QColor backgroundColor_;
};
