#-------------------------------------------------
#
# Project created by QtCreator 2017-11-26T18:59:51
#
#-------------------------------------------------

QT       += network network websockets
QT       -= gui

INCLUDEPATH += src
DEPENDPATH += src

TARGET = ew-node
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/node.cpp \
        src/nodeipc.cpp \
        src/nodews.cpp \
        src/types.cpp \
        src/etherlog.cpp \
        src/gethlog.cpp \
        src/helpers.cpp \
        src/ethereum/bigint.cpp \
        src/ethereum/tx.cpp

HEADERS += \
        src/node.h \
        src/nodeipc.h \
        src/nodews.h \
        src/types.h \
        src/etherlog.h \
        src/gethlog.h \
        src/helpers.h \
        src/ethereum/keccak.h \
        src/ethereum/bigint.h \
        src/ethereum/tx.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
