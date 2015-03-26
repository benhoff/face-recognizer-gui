#include <QOpenGlWidget>
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
	bool show_image( cv::Mat image); /// used to set the image to be viewed

	cv::CascadeClassifier face_cascade;
	cv::CascadeClassifier eyes_cascade;

	QImage qt_image; /// Qt image to be rendered
	cv::Mat original_image; /// original OpenCv image to be shown

private:
	int _resized_image_height;
	int _resized_image_widgth;
	float _image_ratio;

	int _position_x;
	int _position_y;

	RNG _rng;
	bool _scene_changed;
	QColor _background_color;
};
