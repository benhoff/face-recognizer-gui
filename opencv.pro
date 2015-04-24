#-------------------------------------------------
#
# Project created by QtCreator 2015-03-25T18:15:50
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
TARGET = opencv
TEMPLATE = app
INCLUDEPATH += /usr/include/opencv
LIBS += -L/lib -I/usr/include/opencv -lopencv_calib3d -lopencv_core -lopencv_cudaarithm -lopencv_cudabgsegm -lopencv_cudacodec -lopencv_cudafeatures2d -lopencv_cudafilters -lopencv_cudaimgproc -lopencv_cudalegacy -lopencv_cudaobjdetect -lopencv_cudaoptflow -lopencv_cudastereo -lopencv_cudawarping -lopencv_cudev -lopencv_features2d -lopencv_flann -lopencv_hal -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videoio -lopencv_videostab

SOURCES += main.cpp \
    mainwindow.cpp \
    CVOpenGLWidget.cpp \
    camera.cpp \
    displaywidget.cpp \
    faceDetector.cpp

HEADERS += CVOpenGLWidget.h \
    mainwindow.h \
    camera.h \
    displaywidget.h \
    faceDetector.h
