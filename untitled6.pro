#-------------------------------------------------
#
# Project created by QtCreator 2017-06-17T12:01:55
#
#-------------------------------------------------

QT       += core gui
QT += axcontainer
QT += webkitwidgets
QT += printsupport
CONFIG += axserver    # for an ActiveX server component
CONFIG += axcontainer
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled6
TEMPLATE = app
CONFIG += C++14
QMAKE_CXXFLAGS += -std=c++14

SOURCES += main.cpp\
        mainwindow.cpp \
    pdfc.cpp

HEADERS  += mainwindow.h \
    drop.h \
    pdfc.h

FORMS    += mainwindow.ui
