#-------------------------------------------------
#
# Project created by QtCreator 2014-12-11T14:50:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SkypeBot
TEMPLATE = app
QT += axcontainer
QT += xml

SOURCES += main.cpp\
        mainwindow.cpp \
    skype.cpp \
    Clog.cpp \
    dialogchats.cpp

HEADERS  += mainwindow.h \
    skype.h \
    Clog.h \
    dialogchats.h

FORMS    += mainwindow.ui \
    dialogchats.ui

RESOURCES += \
    resources.qrc


RC_FILE = resources.rc
