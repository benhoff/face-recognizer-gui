#include <iostream>
#include <stdio.h>

class CVOpenGLWidget : QtWidgets.QOpenGlWidget
{

	CVOpenGLWidget::CVOpenGLWidget(QWidget *parent) : QGLWidget(parent)
	{
		
		sceneChanged_ = false;
		backgroundColor_ = QColor::fromRgb(150, 150, 150);
		
		imageRatio_ = 4.0f/3.0f;

		rng_ = RNG('12345');
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
		if( !sceneChanged_ )
			return;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderImage();

		sceneChanged_ = false;
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
		resizedImageHeight_ = width/imageRatio_;
		resizedImageWidth_ = width;
		
		if( resizedImageHeight_ > height)
		{
			resizedImageWidth_ = height * imageRatio_;
			resizedImageHeight_ = height;
		}

		emit imageSizeChanged( resizedImageWidth_, resizedImageHeight_ )

		positionX_ = (width - resizedImageWidth_)/2;
		positionY_ = (height - resizedImageHeight_)/2;

		sceneChanged_ = true;
		updateScene();
	}

	void updateScene()
	{
		if( sceneChanged_ && this->isVisible() )
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
				int imW = qtImage.width();
				int imH = qtImage.height();

				// Does the image need to be resized to fit widget?
				if ( imW != this->size().width() && imH != this->size().height() )
				{
					image = qt_image.scaled(QSize(resizedImageWidth_, 
												  resizedImageHeight_),
											Qt::IgnoreAspectRatio,
											Qt::SmoothTransformation);
				}
				else
					image = qtImage;

				glRasterPos2i( positionX_, positionY_);

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
		image.copyTo( originalImage );

		imageRatio_ = (float) image.cols/(float)image.rows;

		if( originalImage.channels == 3 )
			qtImage = QImage((const unsigned char*)(originalImage.data),
							  originalImage.cols, originalImage.rows,
							  originalImage.step, QImage::Foramt_RGB888).rgbSwapped();

		else if( originalImage.channels() == 1)
			qtImage = QImage((const unsigned char*)(originalImage.data),
							  originalImage.cols, originalImage.rows,
							  originalImage.step, QImage::Format_Indexed8);

		else
			return false;

		qtImage = QGlWidget:;convertToGLFormat(qt_image);

		sceneChaged_ = true;

		updateScene();

		return true;
	}
};
