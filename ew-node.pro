#-------------------------------------------------
#
# Project created by QtCreator 2017-11-26T18:59:51
#
#-------------------------------------------------

QT       += network testlib network websockets
QT       -= gui

INCLUDEPATH += ewnode
DEPENDPATH += ewnode

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
        ewnode/node.cpp \
        ewnode/nodeipc.cpp \
        ewnode/nodews.cpp \
        ewnode/types.cpp \
        ewnode/etherlog.cpp \
        ewnode/gethlog.cpp \
        ewnode/helpers.cpp \
        ewnode/ethereum/bigint.cpp \
        ewnode/ethereum/tx.cpp

HEADERS += \
        ewnode/node.h \
        ewnode/nodeipc.h \
        ewnode/nodews.h \
        ewnode/types.h \
        ewnode/etherlog.h \
        ewnode/gethlog.h \
        ewnode/helpers.h \
        ewnode/ethereum/keccak.h \
        ewnode/ethereum/bigint.h \
        ewnode/ethereum/tx.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
