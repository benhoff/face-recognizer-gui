#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QCamera>
#include <QCameraInfo>
#include "centralwidget.h"

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
    void set_camera(const QCameraInfo &camera_info);
    void set_camera_action(QAction *camera_action);
    void _setup_camera_devices();

    QScopedPointer<QCamera> _camera;
    QAction* face_cascade_;
    QMenu* cascade_file_menu;
    CentralWidget *_central_widget;
};

#endif // MAINWINDOW_H
