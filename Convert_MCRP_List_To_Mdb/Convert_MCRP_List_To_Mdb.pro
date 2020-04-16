#-------------------------------------------------
#
# Project created by QtCreator 2020-03-15T18:26:29
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Convert_MCRP_List_To_Mdb
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    parameter.cpp \
    parsingmanager.cpp

HEADERS  += mainwindow.h \
    parameter.h \
    parsingmanager.h

FORMS    += mainwindow.ui
