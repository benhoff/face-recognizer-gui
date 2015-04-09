#include "CVOpenGLWidget.h"

CVOpenGLWidget::CVOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

    sceneChanged_ = false;
    backgroundColor_ = QColor::fromRgb(150, 150, 150);

    imageRatio_ = 4.0f/3.0f;

    rng_ = cv::RNG(12345);
}

void CVOpenGLWidget::initializeGL()
{
    //makeCurrent();
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// Render the openGL scene
void CVOpenGLWidget::paintGL()
{
    if( !sceneChanged_ )
        return;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderImage();

    sceneChanged_ = false;
}

void CVOpenGLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, (GLint)width, (GLint)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, width, 0, height, 0, 1); // To draw image in the center of the area

    glMatrixMode(GL_MODELVIEW);

    // Scaled Image sizes
    resizedImageHeight_ = width/imageRatio_;
    resizedImageWidth_ = width;

    if( resizedImageHeight_ > height)
    {
        resizedImageWidth_ = height * imageRatio_;
        resizedImageHeight_ = height;
    }

    emit imageSizeChanged( resizedImageWidth_, resizedImageHeight_ );

    positionX_ = (width - resizedImageWidth_)/2;
    positionY_ = (height - resizedImageHeight_)/2;

    sceneChanged_ = true;
    paintGL();
}

void CVOpenGLWidget::updateScene()
{
    if( sceneChanged_ && this->isVisible() )
        renderImage();
}

void CVOpenGLWidget::renderImage()
{
    makeCurrent();
    glClear(GL_COLOR_BUFFER_BIT);

    if (!qtImage.isNull())
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
                image = qtImage.scaled(QSize(resizedImageWidth_,
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

bool CVOpenGLWidget::ImageSlot(QImage* image )
{
    imageRatio_ = (float) image->height()/(float)image->width();

    // TODO: Do not use QGLWidget functions, class is depriciated
    qtImage = QGLWidget::convertToGLFormat(*image);

    sceneChanged_ = true;

    paintGL();
    return true;
}
