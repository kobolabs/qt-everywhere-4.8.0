TEMPLATE = app

DESTDIR     = ../../bin

DEPENDPATH += .
INCLUDEPATH += . ../../src/3rdparty/harfbuzz/src \
                 ../../src/3rdparty/accessplugin
TARGET = qttracereplay

# Input
SOURCES += main.cpp

target.path=$$[QT_INSTALL_BINS]
INSTALLS += target

CONFIG += console
