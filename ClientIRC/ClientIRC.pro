#-------------------------------------------------
#
# Project created by QtCreator 2016-01-13T08:34:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClientIRC
TEMPLATE = app


SOURCES += main.cpp\
        mainclientwindow.cpp \
    pickserverdialog.cpp \
    client.cpp \
    connection.cpp \
    logindialog.cpp \
    message.cpp

HEADERS  += mainclientwindow.h \
    pickserverdialog.h \
    client.h \
    connection.h \
    logindialog.h \
    message.h

FORMS    += mainclientwindow.ui \
    pickserverdialog.ui \
    logindialog.ui
