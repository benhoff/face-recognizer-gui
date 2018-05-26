#include "mainwindow.h"

#include <QActionGroup>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    face_cascade_ = new QAction("Change Face Cascade", this);
    this->connect(face_cascade_, SIGNAL(triggered()), SLOT(change_face_cascade()));

    cascade_file_menu = this->menuBar()->addMenu(tr("File"));
    cascade_file_menu->addAction(face_cascade_);

    _central_widget = new CentralWidget(this);
    setCentralWidget(_central_widget);

    connect(this, &MainWindow::face_cascade_filename_signal, _central_widget, &CentralWidget::change_face_cascade_filename);
}

void MainWindow::change_face_cascade()
{
    QString filename = QFileDialog::getOpenFileName(this, 
		    				    tr("HaarCascade Filename"));

    emit face_cascade_filename_signal(filename);
}


MainWindow::~MainWindow()
{
}


void MainWindow::_setup_camera_devices()
{
    QActionGroup *camera_group = new QActionGroup(this);
    const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    QMenuBar* menu_bar = menuBar();
    QMenu *device_menu = menu_bar->addMenu("Devices");

    for (const QCameraInfo &camera_info: cameras)
    {
        QAction *camera_action = new QAction(camera_info.description(), camera_group);
        camera_action->setCheckable(true);
        camera_action->setData(QVariant::fromValue(camera_info));
        if (camera_info == QCameraInfo::defaultCamera())
            camera_action->setChecked(true);
        device_menu->addAction(camera_action);
    }

    connect(camera_group, &QActionGroup::triggered, this, &MainWindow::set_camera_action);
}
