#-------------------------------------------------
#
# Project created by QtCreator 2015-02-18T08:21:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = mvcPong
TEMPLATE = app


SOURCES += main.cpp\
    pongtext.cpp \
    pongpart.cpp \
    pongmember.cpp \
    pongmodel.cpp \
    pongview.cpp \
    pongcontroller.cpp \
    ponggame.cpp \
	pongclient.cpp \

HEADERS  += \
    pongtext.h \
    pongpart.h \
    pongmember.h \
    pongmodel.h \
    pongview.h \
    pongcontroller.h \
    ponggame.h \
	pongclient.h \

FORMS    +=

RESOURCES += \
    res.qrc
