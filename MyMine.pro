#-------------------------------------------------
#
# Project created by QtCreator 2015-10-18T17:14:27
#
#-------------------------------------------------

QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyMine
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    MySql.cpp \
    GameWidget.cpp \
    GameBlock.cpp

HEADERS  += MainWindow.h \
    MySql.h \
    GameBlock.h \
    GameWidget.h

FORMS += \
    dlgGameDiyLevel.ui \
    dlgGameWin.ui

RESOURCES += \
    res.qrc


