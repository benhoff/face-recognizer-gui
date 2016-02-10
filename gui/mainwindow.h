#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include "gui/displaywidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void face_cascade_filename_signal(QString casacde_filename);

private slots:
    void change_face_cascade();

private:
    QAction* face_cascade_;
    QMenu* cascade_file_menu;
};

#endif // MAINWINDOW_H
