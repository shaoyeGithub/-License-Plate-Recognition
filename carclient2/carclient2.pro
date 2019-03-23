#-------------------------------------------------
#
# Project created by QtCreator 2017-07-17T12:18:26
#
#-------------------------------------------------

QT       += core gui
QT    +=network
QT += webkitwidgets
QT += webkit
CONFIG  += qaxcontainer
QT += multimedia multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = carclient2
TEMPLATE = app


SOURCES += main.cpp\
        sendpicturewidget.cpp \
    socket.cpp \
    login.cpp \
    table2excel.cpp

HEADERS  += sendpicturewidget.h \
    ccheckboxheaderview.h \
    socket.h \
    login.h \
    myhelper.h \
    table2excel.h

FORMS    += sendpicturewidget.ui \
    login.ui

RESOURCES += \
    1.qrc
