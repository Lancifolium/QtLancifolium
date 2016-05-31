#-------------------------------------------------
#
# Project created by QtCreator 2016-03-04T00:23:47
#
#-------------------------------------------------

QT 	  += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtFormulary
TEMPLATE = app
RC_ICONS = images/Lancifolium.ico

SUBDIRS = Lancifolium \
    QtLancifolium


SOURCES +=\
    QtLancifolium/QtLancifolium.cpp \
    Lancifolium/DevLancifolium.cpp \
    Lancifolium/GnNode.cpp \
    Lancifolium/MovLancifolium.cpp \
    Lancifolium/FileBuff.cpp \
    formain.cpp \
    QtLancifolium/Formula.cpp \
    Lancifolium/FormLancifolium.cpp

HEADERS  += \
    Lancifolium/DevLancifolium.h \
    Lancifolium/FunLancifolium.h \
    Lancifolium/GnNode.h \
    Lancifolium/MovLancifolium.h \
    Lancifolium/FileBuff.h \
    QtLancifolium/Formula.h \
    QtLancifolium/QtLancifolium.h \
    Lancifolium/FormLancifolium.h


FORMS

RESOURCES += \
    images.qrc

DISTFILES += \
    README.md \
    CHANGELOG \
    tmp.sgf
