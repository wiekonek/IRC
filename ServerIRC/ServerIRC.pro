QT += core
QT -= gui

TARGET = ServerIRC
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp \
    connection.cpp \
    channel.cpp \
    listener.cpp

HEADERS += \
    server.h \
    connection.h \
    channel.h \
    listener.h

