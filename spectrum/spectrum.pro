#-------------------------------------------------
#
# Project created by QtCreator 2014-05-06T23:23:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = spectrum
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

unix:!macx:!symbian: LIBS += -lasound
