include(gtest_dependency.pri)
include(remote_file_explorer_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG += qt
QT += core network

HEADERS += \
        tst_maintest.h

SOURCES += \
        main.cpp
