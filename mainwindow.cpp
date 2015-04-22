#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    DisplayWidget* display = new DisplayWidget(this);

    setCentralWidget(display);
}

MainWindow::~MainWindow()
{
}

