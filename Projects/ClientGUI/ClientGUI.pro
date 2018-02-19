#-------------------------------------------------
#
# Project created by QtCreator 2017-12-09T18:02:55
#
#-------------------------------------------------

QT       += core gui
QT       += core
QT       += network
QT       += widgets
QT       += core websockets
QT       += gamepad

CONFIG 	   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClientGUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += /usr/local/include/opencv

LIBS += -L/usr/local/lib -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_photo -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_cvv -lopencv_dpm -lopencv_face -lopencv_freetype -lopencv_fuzzy -lopencv_img_hash -lopencv_line_descriptor -lopencv_optflow -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_dnn -lopencv_plot -lopencv_xfeatures2d -lopencv_shape -lopencv_video -lopencv_ml -lopencv_ximgproc -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_flann -lopencv_xobjdetect -lopencv_imgcodecs -lopencv_objdetect -lopencv_xphoto -lopencv_imgproc -lopencv_core

LIBS       += -lVLCQtCore -lVLCQtWidgets
# Edit below for custom library location
INCLUDEPATH += /home/maumrtn/Downloads/vlc-2.2.8/include
LIBS       += -L/home/maumrtn/Downloads/vlc-2.2.8/lib -lVLCQtCore -lVLCQtWidgets



SOURCES += \
        main.cpp \
        mainwindow.cpp \
    arrowpad.cpp \
    ledindicator.cpp \
    qledindicator.cpp \
    clientsocket.cpp \
    clientsocket2.cpp \
    gauge.cpp \
    gamepadmonitor.cpp \
    settings.cpp

HEADERS += \
        mainwindow.h \
    arrowpad.h \
    ledindicator.h \
    qledindicator.h \
    clientsocket.h \
    cvimagewidget.h \
    clientsocket2.h \
    cvimagewidget.h \
    gauge.h \
    gamepadmonitor.h \
    settings.h

FORMS += \
        mainwindow.ui \
    settings.ui
