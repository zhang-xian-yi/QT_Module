TARGET = MainAPP
QT    += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#模块外部使用的路径（带模块名的头文件搜索）
INCLUDEPATH += $$PWD/../

HEADERS += \
    mainwindow.h

SOURCES += \
    main.cpp \
    mainwindow.cpp

FORMS += \
    mainwindow.ui

#中文乱码
win32-msvc* {
    QMAKE_CXXFLAGS += /source-charset:utf-8 /execution-charset:utf-8
}

#输出目录
DESTDIR=$$PWD/../OutputDir/ExecuteBin/
CONFIG(debug) {
    DEFINES += DEBUG_OUTPUT
    MOC_DIR = $$PWD/../OutputDir/tmp/debug/MainAPP
    OBJECTS_DIR = $$PWD/../OutputDir/tmp/debug/MainAPP
    RCC_DIR = $$PWD/../OutputDir/tmp/debug/MainAPP
    UI_DIR = $$PWD/../OutputDir/tmp/debug/MainAPP
}

CONFIG(release) {
    MOC_DIR = $$PWD/../OutputDir/tmp/release/MainAPP
    OBJECTS_DIR = $$PWD/../OutputDir/tmp/release/MainAPP
    RCC_DIR = $$PWD/../OutputDir/tmp/release/MainAPP
    UI_DIR = $$PWD/../OutputDir/tmp/release/MainAPP
}

#项目根路径
INCLUDEPATH += $$PWD/../
#依赖项目库 为输出路径
LIBPATH += $$PWD/../OutputDir/ExecuteBin/
LIBS += -lOpenGLWinLayer
LIBS += -lFiniteElementRenderLayer


