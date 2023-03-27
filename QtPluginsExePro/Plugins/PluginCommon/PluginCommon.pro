QT -= gui

TARGET = PluginCommon
TEMPLATE = lib
DEFINES += PLUGINCOMMON_LIBRARY

include(../PluginFramework.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


#原文件
SOURCES += \
    IBasePlugin.cpp

HEADERS += \
    PluginCommon_global.h \
    IBasePlugin.h
