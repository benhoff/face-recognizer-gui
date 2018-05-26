#include "gui/imageviewer.h"

void ImageViewer::set_image(const QImage &img)
{
    if (!image_.isNull())
        qDebug() << "Viewer dropped frame!";
    image_ = img;
    if (image_.size() != size())
        setFixedSize(image_.size());
    update();

}
