#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QThread convertorThread, cameraThread;

    Camera* camera = new Camera(this);
    Convertor* convertor = new Convertor(this);

    convertor->setProcessAll(false);

    captureThread.start();
    cameraThread.start();

    camera->moveToThread(cameraThread);
    convertor->moveToThread(convertorThread);

    // START HERE ---------------------------------!!!!
    convertor->connect(camera, SIGNAL(matReady(cv::Mat)), SLOT(processFrame(cv::Mat)));

    DisplayWidget* display = new DisplayWidget(this);
    setCentralWidget(display);
}

MainWindow::~MainWindow()
{
}

