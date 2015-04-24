#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>

#include <QObject>
#include <QVBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QComboBox>
#include <QFileDialog>
#include <QThread>

#include <iostream>
#include <stdio.h>

#include "CVOpenGLWidget.h"
#include "camera.h"
#include "faceDetector.h"

class DisplayWidget : public QWidget
{
    Q_OBJECT
public:
    CVOpenGLWidget* openGLWidget_;
    explicit DisplayWidget(QWidget *parent = 0);
    ~DisplayWidget();

signals:
    void videoFileNameSignal(QString videoFileName);
    void facecascade_name_signal(QString filename);

public slots:
    void openFileDialog();
    void change_face_cascade_filename(QString filename);

private:
    FaceDetector* faceDector_;
    Camera* camera_;
    QThread faceDetectThread_;
    QThread cameraThread_;
};

#endif // DISPLAYWIDGET_H
