#-------------------------------------------------
#
# Project created by QtCreator 2019-10-14T14:42:36
#
#-------------------------------------------------

QT       += core gui network

QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp\
        server.cpp \
    chatdetail.cpp

HEADERS  += server.h \
    connection.h \
    chatdetail.h

FORMS    += server.ui \
    chatdetail.ui
