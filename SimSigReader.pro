#-------------------------------------------------
#
# Project created by QtCreator 2016-01-23T14:54:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimSigReader
TEMPLATE = app
RC_ICONS = images/Lancifolium.ico


SOURCES += main.cpp\
        widget.cpp \
    SgfLancifolium.cpp \
    GnCalculate.cpp \
    GnNode.cpp

HEADERS  += widget.h \
    SgfLancifolium.h \
    GnCalculate.h \
    GnNode.h

FORMS    += widget.ui

DISTFILES +=

RESOURCES += \
    sim.qrc
