#-------------------------------------------------
#
# Project created by QtCreator 2015-08-02T09:46:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = noteBook
TEMPLATE = app


SOURCES += main.cpp\
        notebook.cpp \
    aboutdialog.cpp

HEADERS  += notebook.h \
    aboutdialog.h

RESOURCES += \
    images.qrc

FORMS += \
    aboutdialog.ui
