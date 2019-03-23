#-------------------------------------------------
#
# Project created by QtCreator 2017-07-11T21:15:16
#
#-------------------------------------------------


QT       += core gui
QT += webkitwidgets
QT += webkit
QT += network
QT +=sql
CONFIG += console
QMAKE_CXXFLAGS += -std=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CarServer
TEMPLATE = app

INCLUDEPATH+=D:\FILE\opencv\include\opencv \
D:\FILE\opencv\include\opencv2 \
D:\FILE\opencv\include

LIBS += -L D:/FILE/opencv/x86/mingw/lib/libopencv_*.a


SOURCES += main.cpp\
    server.cpp \
    socketthread.cpp \
    query.cpp \
    widget.cpp \
    distinguish.cpp \
    login.cpp \
    parent.cpp \
    core/chars_identify.cpp \
    core/chars_recognise.cpp \
    core/chars_segment.cpp \
    core/core_func.cpp \
    core/feature.cpp \
    core/helper.cpp \
    core/lbp.cpp \
    core/mser2.cpp \
    core/params.cpp \
    core/plate_detect.cpp \
    core/plate_judge.cpp \
    core/plate_locate.cpp \
    core/plate_recognize.cpp \
    core/xmlParser.cpp \
    trainandutil/util/kv.cpp \
    trainandutil/util/program_options.cpp \
    trainandutil/util/util.cpp

HEADERS  += \
    server.h \
    socketthread.h \
    db.h \
    query.h \
    widget.h \
    distinguish.h \
    ccheckboxheaderview.h \
    myhelper.h \
    login.h \
    parent.h \
    include/api.hpp \
    include/character.hpp \
    include/chars_identify.h \
    include/chars_recognise.h \
    include/chars_segment.h \
    include/config.h \
    include/core_func.h \
    include/erfilter.hpp \
    include/feature.h \
    include/helper.hpp \
    include/lbp.hpp \
    include/mser2.hpp \
    include/params.h \
    include/plate.hpp \
    include/plate_detect.h \
    include/plate_judge.h \
    include/plate_locate.h \
    include/plate_recognize.h \
    include/version.h \
    include/xmlParser.h \
    util/kv.h \
    util/program_options.h \
    util/switch.hpp \
    util/util.h \
    include/easypr.h

FORMS    += \
    distinguish.ui \
    query.ui \
    widget.ui \
    login.ui \
    parent.ui

RESOURCES += \
    1.qrc
