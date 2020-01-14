#-------------------------------------------------
#
# Project created by QtCreator 2019-10-09T15:40:10
#
#-------------------------------------------------

QT       += core gui network
QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InstantMessaging
TEMPLATE = app


SOURCES += main.cpp\
    login.cpp \
    interface.cpp \
    zhuce.cpp

HEADERS  += \
    login.h \
    interface.h \
    connection.h \
    zhuce.h

FORMS    += \
    login.ui \
    interface.ui \
    zhuce.ui

RESOURCES += \
    image.qrc \
    image.qrc
