QT += core gui widgets

CONFIG += c++11
TARGET = opencv
TEMPLATE = app

unix: INCLUDEPATH += /usr/include/opencv2
# Windows users need to add the correct include path! Uncomment below line and fix path!
win32: INCLUDEPATH += C:\opencv\build\include


unix {
    !contains(QT_CONFIG, no-pkg-config) {
            CONFIG += link_pkgconfig
            PKGCONFIG += opencv
    } else {
            LIBS += -lopencv_core -lopencv_imgproc -lopencv_objdetect
    }
}
win32 {
    # Windows users need to correct the lib path! Uncomment below and fix paths!
    # LIBS+= C:\opencv-build\bin\libopencv_core320.dll
    # LIBS+= C:\opencv-build\bin\libopencv_imgproc320.dll
    # LIBS+= C:\opencv-build\bin\libopencv_objdetect320.dll
}

SOURCES += main.cpp \
    mainwindow.cpp \
    camera.cpp \
    faceDetector.cpp \
    gui/imageviewer.cpp \
    centralwidget.cpp

HEADERS += mainwindow.h \
    camera.h \
    faceDetector.h \
    gui/imageviewer.h \
    centralwidget.h
