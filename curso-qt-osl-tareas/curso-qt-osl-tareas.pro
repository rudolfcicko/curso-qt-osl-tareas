#-------------------------------------------------
#
# Project created by QtCreator 2014-02-28T22:49:48
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = curso-qt-osl-tareas-exe
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp \
    creadortareas.cpp

HEADERS  += \
    dbconnection.h \
    mainwindow.h \
    creadortareas.h

FORMS += \
    mainwindow.ui \
    creadortareas.ui
