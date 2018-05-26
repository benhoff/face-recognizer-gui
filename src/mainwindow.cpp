#include "gui/mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    face_cascade_ = new QAction("Change Face Cascade", this);
    this->connect(face_cascade_, SIGNAL(triggered()), SLOT(change_face_cascade()));

    cascade_file_menu = this->menuBar()->addMenu(tr("File"));
    cascade_file_menu->addAction(face_cascade_);

    DisplayWidget* display = new DisplayWidget(this);
    display->connect(this, SIGNAL(face_cascade_filename_signal(QString)),
                     SLOT(change_face_cascade_filename(QString)));

    setCentralWidget(display);
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

