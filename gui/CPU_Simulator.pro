#-------------------------------------------------
#
# Project created by QtCreator 2015-11-27T03:42:07
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CPU_Simulator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    WBack.cpp \
    Parser.cpp \
    Memory.cpp \
    Fetch.cpp \
    Execute.cpp \
    Decode.cpp \
    CPU.cpp

HEADERS  += mainwindow.h \
    WBack.h \
    Parser.h \
    Memory.h \
    Fetch.h \
    Execute.h \
    Decode.h \
    CPU.h

FORMS    += mainwindow.ui
