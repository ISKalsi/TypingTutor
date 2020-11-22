#-------------------------------------------------
#
# Project created by QtCreator 2019-05-29T18:05:59
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = try
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        easy.cpp \
        hard.cpp \
        help.cpp \
        highscore.cpp \
        main.cpp \
        mainwindow.cpp \
        normal.cpp \
        play.cpp \
        practice.cpp

HEADERS += \
        easy.h \
        hard.h \
        help.h \
        highscore.h \
        mainwindow.h \
        normal.h \
        play.h \
        practice.h

FORMS += \
        easy.ui \
        hard.ui \
        help.ui \
        highscore.ui \
        mainwindow.ui \
        normal.ui \
        play.ui \
        practice.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

DISTFILES += \
    highscore/easy_highscore.txt \
    highscore/hard_highscore.txt \
    highscore/medium_highscore.txt \
    highscore/x.txt
