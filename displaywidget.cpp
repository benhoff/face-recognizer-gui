#include "displaywidget.h"

DisplayWidget::DisplayWidget(QWidget *parent) : QWidget(parent)
{
    QStringList cameraOptions;
    cameraOptions << "0" << "1" << "2" << "3" << "4" << "5" << "6";
    QComboBox* cameraComboBox = new QComboBox;
    cameraComboBox->addItems(cameraOptions);

    QHBoxLayout* horizontalLayout = new QHBoxLayout();
    QPushButton *runButton = new QPushButton("run", this);
    QPushButton *fileSelector = new QPushButton("select file");
    horizontalLayout->addWidget(cameraComboBox);
    horizontalLayout->addWidget(fileSelector);
    horizontalLayout->addWidget(runButton);

    QVBoxLayout *layout = new QVBoxLayout;
    CVOpenGLWidget* openGLWidget = new CVOpenGLWidget(this);
    QRadioButton *sourceSelector = new QRadioButton("Stream from video camera", this);
    sourceSelector->setDown(true);

    layout->addWidget(openGLWidget);
    layout->addLayout(horizontalLayout);
    layout->addWidget(sourceSelector);

    setLayout(layout);

    Camera* camera = new Camera(this);

    QObject::connect(camera, SIGNAL(imageSignal(QImage*)),
                     openGLWidget, SLOT(ImageSlot(QImage*)));

    // TODO: Add in slot to turn off camera, or something
    QObject::connect(runButton, SIGNAL(clicked()),
                     camera, SLOT(runSlot()));

    QObject::connect(cameraComboBox, SIGNAL(currentIndexChanged(int)),
                     camera, SLOT(cameraIndexSlot(int)));

    QObject::connect(fileSelector, SIGNAL(clicked()),
                     this,	SLOT(openFileDialog()));

    QObject::connect(sourceSelector, SIGNAL(toggled(bool)),
                     camera, SLOT(usingVideoCameraSlot(bool)));

    QObject::connect(this, SIGNAL(videoFileNameSignal(QString)),
                     camera, SLOT(videoFileNameSlot(QString)));
}

DisplayWidget::~DisplayWidget()
{

}

void DisplayWidget::openFileDialog()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Video"));
    emit videoFileNameSignal(filename);
}
