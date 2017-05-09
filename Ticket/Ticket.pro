#-------------------------------------------------
#
# Project created by QtCreator 2017-05-04T20:26:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ticket
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


SOURCES += main.cpp\
        mainwindow.cpp \
    test.cpp \
    logindialog.cpp \
    userdialog.cpp \
    buyquerydialog.cpp \
    myticketdialog.cpp \
    buydialog.cpp \
    refunddialog.cpp \
    infodialog.cpp \
    utility.cpp \
    managerdialog.cpp \
    addtraindialog.cpp \
    deltraindialog.cpp \
    querytraindialog.cpp \
    prequerytraindialog.cpp

HEADERS  += \
    account.hpp \
    log.hpp \
    railway.hpp \
    ticket.hpp \
    train.hpp \
    lib/exceptions.hpp \
    lib/lib.hpp \
    lib/map.hpp \
    lib/set.hpp \
    lib/shared_ptr.hpp \
    lib/time.hpp \
    lib/utility.hpp \
    lib/vector.hpp \
    mainwindow.hpp \
    logindialog.h \
    userdialog.h \
    buyquerydialog.h \
    myticketdialog.h \
    buydialog.h \
    refunddialog.h \
    infodialog.h \
    managerdialog.h \
    addtraindialog.h \
    deltraindialog.h \
    querytraindialog.h \
    prequerytraindialog.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    userdialog.ui \
    buyquerydialog.ui \
    myticketdialog.ui \
    buydialog.ui \
    refunddialog.ui \
    infodialog.ui \
    managerdialog.ui \
    addtraindialog.ui \
    deltraindialog.ui \
    querytraindialog.ui \
    prequerytraindialog.ui

DISTFILES +=
