#-------------------------------------------------
#
# Project created by QtCreator 2013-10-29T09:55:49
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql

TARGET = DB_KURS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dbworker.cpp \
    tablewidget.cpp

HEADERS  += mainwindow.h \
    dbworker.h \
    tablewidget.h

FORMS    += mainwindow.ui \
    tablewidget.ui
