QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LoginPlugin

TEMPLATE = lib
DEFINES += LOGINPLUGIN_LIBRARY

include(../PluginFramework.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    LoginWidget.cpp

HEADERS += \
    LoginWidget.h

FORMS += \
    LoginWidget.ui


