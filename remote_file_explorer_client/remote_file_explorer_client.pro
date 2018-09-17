#-------------------------------------------------
#
# Project created by QtCreator 2018-05-25T10:33:52
#
#-------------------------------------------------

QT       += core gui network widgets

TARGET = file_remote_explorer_client
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

DEPENDPATH += . ../remote_file_explorer_library/
INCLUDEPATH += ../remote_file_explorer_library/
LIBS += -L../remote_file_explorer_library -lremote_file_explorer_library

SOURCES += \
    main.cpp \
    stringlistmodel.cpp \
    textpreview.cpp \
    serveraccess.cpp \
    servercommunicationqt.cpp \
    servercommunication.cpp

HEADERS += \
    stringlistmodel.h \
    textpreview.h \
    serveraccess.h \
    servercommunication.h \
    servercommunicationqt.h

