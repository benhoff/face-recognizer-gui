#include <iostream>
#include <stdio.h>

class CVOpenGLWidget : QtWidgets.QOpenGlWidget
{

	CVOpenGLWidget::CVOpenGLWidget(QWidget *parent) : QGLWidget(parent)
	{
		cv::String face_cascade_filename = "haarcascade_frontalface_default.xml"
		cv::String eyes_cascade_filename = "haarcascade_eye.xml"
		
		if( !face_cascade.load( face_cascade_filename ) )
		{
			printf("--(!)Error loading\n"); 
			return -1;
		}

		if( !eyes_cascade.load( eyes_cascade_filename ) )
		{ 
			printf("--(!)Error loading\n"); 
			return -1; 
		}
		
		_scene_changed = false;
		_background_color = QColor::fromRgb(150, 150, 150);
		
		_image_ratio = 4.0f/3.0f;

		_rng = RNG('12345');
	}

	void initializeGL()
	{
		//makeCurrent();	
		initializeOpenGLFunctions();
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	}

	// Render the openGL scene
	void paintGL()
	{
		makeCurrent();
		if( !_scene_changed )
			return;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderImage();

		_scene_changed = false;
	}

	void resizeGL(int width, int height)
	{
		makeCurrent();
		glViewport(0, 0, (GLint)width, (GLint)height);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0, width, 0, height, 0, 1); // To draw image in the center of the area

		glMatrixMode(GL_MODEL_VIEW);

		// Scaled Image sizes
		_resized_image_height = width/_image_ratio;
		_resized_image_width = width;
		
		if( _resized_image_height > height)
		{
			_resized_image_width = height * _image_ratio;
			_resized_image_height = height;
		}

		emit imageSizeChanged( _resized_image_width, _resized_image_height )

		_position_x = (width - _resized_image_width)/2;
		_position_y = (height - _resized_image_height)/2;

		_scene_changed = true;
		updateScene();
	}

	void updateScene()
	{
		if( _scene_changed && this->isVisible() )
			updateGL();
	}

	void renderImage()
	{
		makeCurrent();
		glClear(GL_COLOR_BUFFER_BIT);

		if (!qt_image.isNull())
		{
			glLoadIdentity();
			QImage image; // the image rendered

			glPushMatrix();
			{
				int imW = qt_image.width();
				int imH = qt_image.height();

				// Does the image need to be resized to fit widget?
				if ( imW != this->size().width() && imH != this->size().height() )
				{
					image = qt_image.scaled(QSize(_resized_image_widght, 
												  _resized_image_height),
											Qt::IgnoreAspectRatio,
											Qt::SmoothTransformation);
				}
				else
					image = qt_image;

				glRasterPos2i( _position_x, _position_y);

				imW = image.width();
				imH = image.height();

				glDrawPixels( imW, imH, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
			}
			glPopMatrix();

			// end
			glFlush();
		}
	}

	bool CVOpenGLWidget( cv::Mat image )
	{
		image.copyTo( original_image );

		_image_ratio = (float) image.cols/(float)image.rows;

		if( original_image.channels == 3 )
			qt_image = QImage((const unsigned char*)(original_image.data),
							  original_image.cols, original_image.rows,
							  original_image.step, QImage::Foramt_RGB888).rgbSwapped();

		else if( original_image.channels() == 1)
			qt_image = QImage((const unsigned char*)(original_image.data),
							  original_image.cols, original_image.rows,
							  original_image.step, QImage::Format_Indexed8);

		else
			return false;

		qt_image = QGlWidget:;convertToGLFormat(qt_image);

		_scene_chaged = true;

		updateScene();

		return true;
	}
};
