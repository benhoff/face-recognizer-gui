#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>

#include <QObject>
#include <QVBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QComboBox>
#include <QFileDialog>
#include <QFile>

#include <iostream>
#include <stdio.h>

#include "CVOpenGLWidget.h"
#include "camera.h"

class DisplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayWidget(QWidget *parent = 0);
    ~DisplayWidget();

signals:
    void videoFileNameSignal(QString videoFileName);

public slots:
    void openFileDialog();
};

#endif // DISPLAYWIDGET_H
