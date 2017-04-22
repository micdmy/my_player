#-------------------------------------------------
#
# Project created by QtCreator 2017-02-24T15:30:39
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = my_player
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH +=  "/usr/local/include/taglib"
LIBS += -ltag
LIBS += -lz
#LIBS += -L/lib/x86_64-linux-gnu/ -libz.so
SOURCES += main.cpp\
        mainwindow.cpp \
    medialibrary.cpp \
    programpaths.cpp \
    errgui.cpp \
    librarydirectoriesdialog.cpp \
    directorieslistmodel.cpp \
    songinfo.cpp \
    songsinlibrary.cpp \
    pathscanner.cpp \
    stringlistdialog.cpp \
    songsinlibrarysortfilter.cpp \
    searchframe.cpp \
    onetagtablemodel.cpp \
    onetagsortfilter.cpp

HEADERS  += mainwindow.h \
    medialibrary.h \
    programpaths.h \
    errgui.h \
    librarydirectoriesdialog.h \
    directorieslistmodel.h \
    songinfo.h \
    songsinlibrary.h \
    pathscanner.h \
    stringlistdialog.h \
    songsinlibrarysortfilter.h \
    searchframe.h \
    onetagtablemodel.h \
    onetagsortfilter.h

FORMS    += mainwindow.ui \
    librarydirectoriesdialog.ui \
    stringlistdialog.ui \
    searchframe.ui
