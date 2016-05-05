#-------------------------------------------------
#
# Project created by QtCreator 2016-03-04T00:23:47
#
#-------------------------------------------------

QT 	  += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtLancifolium
TEMPLATE = app
RC_ICONS = images/Lancifolium.ico

SUBDIRS = Lancifolium \
    QtLancifolium


SOURCES += main.cpp\
    QtLancifolium/Formatting.cpp \
    QtLancifolium/QtLancifolium.cpp \
    QtLancifolium/QtWithoutForm.cpp \
    Lancifolium/DevLancifolium.cpp \
    Lancifolium/GnCalculate.cpp \
    Lancifolium/GnNode.cpp \
    Lancifolium/MovLancifolium.cpp \
    Lancifolium/UniLancifolium.cpp

HEADERS  += \
    Lancifolium/DevLancifolium.h \
    Lancifolium/FunLancifolium.h \
    Lancifolium/GnCalculate.h \
    Lancifolium/GnNode.h \
    Lancifolium/MovLancifolium.h \
    Lancifolium/UniLancifolium.h \
    QtLancifolium/Formatting.h \
    QtLancifolium/QtLancifolium.h \
    QtLancifolium/QtWithoutForm.h \
    QtLancifolium/testing.h


FORMS

RESOURCES += \
    images.qrc

DISTFILES += \
    README.md \
    CHANGELOG \
    formula.sgf \
    tmp.sgf
