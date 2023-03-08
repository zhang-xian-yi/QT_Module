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
PRECOMPILED_HEADER += $$PWD/Src/FECommon/PCH.h

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
    MOC_DIR = $$PWD/../OutputDir/tmp/debug/FiniteElementRendererLayer
    OBJECTS_DIR = $$PWD/../OutputDir/tmp/debug/FiniteElementRendererLayer
    RCC_DIR = $$PWD/../OutputDir/tmp/debug/FiniteElementRendererLayer
    UI_DIR = $$PWD/../OutputDir/tmp/debug/FiniteElementRendererLayer
}
#release 配置
CONFIG(release) {
    MOC_DIR = $$PWD/../OutputDir/tmp/release/FiniteElementRendererLayer
    OBJECTS_DIR = $$PWD/../OutputDir/tmp/release/FiniteElementRendererLayer
    RCC_DIR = $$PWD/../OutputDir/tmp/release/FiniteElementRendererLayer
    UI_DIR = $$PWD/../OutputDir/tmp/release/FiniteElementRendererLayer
}

#内部 .h
HEADERS += \
    Src/FECommon/PCH.h \
    Src/FECommon/GlobalData.h \
    Src/FELogicService/OpenGLEntity/CameraView.h \
    Src/FELogicService/OpenGLEntity/FEMesh.h \
    Src/FELogicService/OpenGLEntity/FEModel.h \
    Src/FELogicService/OpenGLEntity/FEVertex.h \
    Src/FELogicService/OpenGLEntity/Material.h \
    Src/FELogicService/Services/ConvertOpenGLData.h \
    Src/FELogicService/Services/FEFileParser.h \
    Src/FEMControl/FERendererLayerControl.h \
    Src/FELogicService/FERendererLayerService.h \
    Src/FELogicService/Services/OpenGLWindow.h \
    Src/FELogicService/Services/CubeGeometry.h \
    Src/FELogicService/DataEntity/FEFileData.h



#内部 .cpp
SOURCES += \
    Src/FECommon/GlobalData.cpp \
    Src/FELogicService/OpenGLEntity/CameraView.cpp \
    Src/FELogicService/OpenGLEntity/FEMesh.cpp \
    Src/FELogicService/OpenGLEntity/FEModel.cpp \
    Src/FELogicService/OpenGLEntity/FEVertex.cpp \
    Src/FELogicService/OpenGLEntity/Material.cpp \
    Src/FELogicService/Services/ConvertOpenGLData.cpp \
    Src/FELogicService/Services/FEFileParser.cpp \
    Src/FEMControl/FERendererLayerControl.cpp \
    Src/FELogicService/FERendererLayerService.cpp \
    Src/FELogicService/Services/OpenGLWindow.cpp \
    Src/FELogicService/Services/CubeGeometry.cpp \
    Src/FELogicService/DataEntity/FEFileData.cpp \



#外部 .h
HEADERS += \
    Src/FERendererLayerFactory.h \
    Src/ILoad3D.h \
    Src/IOpenGLWin.h \
    Src/FiniteElementRenderlayer_global.h \


#外部 .cpp
SOURCES += \
    Src/FERendererLayerFactory.cpp
