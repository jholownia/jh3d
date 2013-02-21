#-------------------------------------------------
#
# Project created by QtCreator 2013-02-20T17:13:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jh3d
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    matrix.cpp \
    quad.cpp \
    renderarea.cpp

HEADERS  += mainwindow.h \
    point.h \
    matrix.h \
    quad.h \
    renderarea.h

FORMS    += mainwindow.ui