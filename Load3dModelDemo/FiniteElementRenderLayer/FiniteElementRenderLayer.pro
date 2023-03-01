QT -= gui

TEMPLATE = lib
greaterThan(QT_MAJOR_VERSION,4): QT += widgets
#导出宏定义
DEFINES = FINITEELEMENTRENDERLAYER_LIBRARY
#配置
CONFIG += c++17

#输出路径
DESTDIR = $$PWD/../OutputDir/ExecuteBin
#预编译头文件
PRECOMPILED_HEADER += $$PWD/Src/OWCommon/PCH.h

#头文件包含的搜索路径
#模块外部使用的路径（带模块名的头文件搜索）
INCLUDEPATH += $$PWD/../
#模块内部使用的相对路径
INCLUDEPATH += $$PWD/
#源码中的头文件搜索路径

#第三方库依赖的头文件搜索路径
INCLUDEPATH += $$PWD/VendorLib/include
INCLUDEPATH += $$PWD/3rdPartySrc/
#第三方库连接
LIBS += -lopengl32 -luser32 -lgdi32 -lshell32
#资源
RESOURCES += OWRes.qrc
#中文乱码
win32-msvc* {
    QMAKE_CXXFLAGS += /source-charset:utf-8 /execution-charset:utf-8
}

#debug 配置
CONFIG(debug) {
    DEFINES += DEBUG_VLD
    #debug 内存vld监测
    LIBS += -L$$PWD/VendorLib/libs -lvld
    MOC_DIR = $$PWD/../OutputDir/tmp/debug
    OBJECTS_DIR = $$PWD/../OutputDir/tmp/debug
    RCC_DIR = $$PWD/../OutputDir/tmp/debug
    UI_DIR = $$PWD/../OutputDir/tmp/debug
}
#release 配置
CONFIG(release) {
    MOC_DIR = $$PWD/../OutputDir/tmp/release
    OBJECTS_DIR = $$PWD/../OutputDir/tmp/release
    RCC_DIR = $$PWD/../OutputDir/tmp/release
    UI_DIR = $$PWD/../OutputDir/tmp/release
}

#内部 .h
HEADERS += \
    Src/OWCommon/PCH.h \
    Src/OWCommon/ExtStruct.h \
    Src/OWCommon/GlobalData.h \
    Src/OWLogicService/FERendererLayerService.h \
    Src/OWLogicService/Services/OpenGLWindow.h \
    Src/OWLogicService/Services/CubeGeometry.h \
    Src/OWLogicService/Services/DataParser.h \
    Src/OWMControl/FERendererLayerControl.h


#内部 .cpp
SOURCES += \
    Src/OWCommon/GlobalData.cpp \
    Src/OWCommon/ExtStruct.cpp \
    Src/OWLogicService/FERendererLayerService.cpp \
    Src/OWLogicService/Services/OpenGLWindow.cpp \
    Src/OWLogicService/Services/CubeGeometry.cpp \
    Src/OWLogicService/Services/DataParser.cpp \
    Src/OWMControl/FERendererLayerControl.cpp

#外部 .h
HEADERS += \
    Src/FERendererLayerFactory.h \
    Src/ILoad3D.h \
    Src/IOpenGLWin.h \
    Src/FiniteElementRenderlayer_global.h \


#外部 .cpp
SOURCES += \
    Src/FERendererLayerFactory.cpp
