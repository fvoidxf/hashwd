#-------------------------------------------------
#
# Project created by QtCreator 2019-08-25T14:55:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qlife
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += "C:\Program Files (x86)\Visual Leak Detector\include"

LIBS += "C:\Program Files (x86)\Visual Leak Detector\lib\Win64\vld.lib"

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        cell.cpp \
        cellitem.cpp \
        dynmodel.cpp \
        field.cpp \
        fieldscene.cpp \
        fieldthread.cpp \
        fieldview.cpp \
        main.cpp \
        mainwindow.cpp \
        workarea.cpp \
		config.cpp

HEADERS += \
        cell.h \
        cellitem.h \
        dynmodel.h \
        field.h \
        fieldscene.h \
        fieldthread.h \
        fieldview.h \
        mainwindow.h \
        workarea.h \
		config.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
