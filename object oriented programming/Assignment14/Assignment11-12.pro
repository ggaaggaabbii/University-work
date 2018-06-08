#-------------------------------------------------
#
# Project created by QtCreator 2018-05-11T14:10:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Assignment11-12
TEMPLATE = app
CONFIG += c++17

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
        main.cpp \
        mainwindow.cpp\
        src/Movie.cpp \
        src/uiAdmin.cpp \
        src/Repository.cpp \
        src/Controller.cpp \
        src/WatchList.cpp \
        src/uiUser.cpp \
        src/FileRepo.cpp \
        src/Validator.cpp \
        src/CustomException.cpp \
        src/CSVWatchlist.cpp \
        src/HTMLWatchlist.cpp \
        src/SQLRepo.cpp \
        src/SelectionWindow.cpp \
        src/UiAdmin.cpp \
        src/UiUser.cpp \
    src/UndoCtrl.cpp \
    src/Operation.cpp \
    src/AddOp.cpp \
    src/DelOp.cpp \
    src/UpdateOp.cpp \
    src/CostomModel.cpp \
    src/Img.cpp

HEADERS += \
        mainwindow.h\
        include/Movie.h \
        include/uiAdmin.h \
        include/Repository.h \
        include/Controller.h \
        include/WatchList.h \
        include/uiUser.h \
        include/FileRepo.h \
        include/Validator.h \
        include/CustomException.h \
        include/CSVWatchlist.h \
        include/HTMLWatchlist.h \
        include/SQLRepo.h \
        include/SelectionWindow.h \
        include/UiAdmin.h \
        include/UiUser.h \
    include/UndoCtrl.h \
    include/Operation.h \
    include/AddOp.h \
    include/DelOp.h \
    include/UpdateOp.h \
    include/CostomModel.h \
    include/Img.h


FORMS += \
        mainwindow.ui

LIBS += -L/ -lsqlite3
