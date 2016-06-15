TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \ 
    DevLancifolium.cpp \
    FileBuff.cpp \
    FormLancifolium.cpp \
    GnNode.cpp \
    main.cpp \
    MovLancifolium.cpp \
    sgfnode.cpp \
    sgftree.cpp

HEADERS += \ 
    DevLancifolium.h \
    FileBuff.h \
    FormLancifolium.h \
    FunLancifolium.h \
    GnNode.h \
    MovLancifolium.h \
    sgf_properties.h \
    sgftree.h
