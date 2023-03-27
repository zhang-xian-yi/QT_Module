QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LoggerPlugin

TEMPLATE = lib
DEFINES += LOGGERPLUGIN_LIBRARY

include(../PluginFramework.pri)
