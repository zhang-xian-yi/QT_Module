TARGET = OpenGLWindowUI
TEMPLATE = lib
#VERSION = 1.0.0

DEFINES += OPENGLWINDOWUI_LIBRARY

QT      += core opengl widgets gui
CONFIG += c++17

#预编译头文件
CONFIG += precompiled_header
PRECOMPILED_HEADER =  \
        $$PWD/Src/OWCommon/precomplie.h

#输出目录
DESTDIR=$$PWD/../OutputDir/ExecuteBin/

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#项目根路径
INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/../
#第三方依赖库

INCLUDEPATH += $$PWD/VendorLib/Include
LIBPATH += $$PWD/VendorLib/Libs
LIBS += -L$$PWD/VendorLib/Libs/ -lglfw3
LIBS += -L$$PWD/VendorLib/Libs/ -lfreeglut
#glfw 依赖第三方库
LIBS += -lopengl32 -lgdi32 -lkernel32 -luser32  -lshell32
#RC_ICONS = resources/icons/AppIcon.ico
#依赖项目库 为输出路径
LIBPATH += DESTDIR=$$PWD/../OutputDir/ExecuteBin/
LIBS += -lLoad3DModel


CONFIG(debug) {
    DEFINES += DEBUG_OUTPUT
    MOC_DIR = $$PWD/../OutputDir/tmp/debug
    OBJECTS_DIR = $$PWD/../OutputDir/tmp/debug
    RCC_DIR = $$PWD/../OutputDir/tmp/debug
    UI_DIR = $$PWD/../OutputDir/tmp/debug
}

CONFIG(release) {
    MOC_DIR = $$PWD/../OutputDir/tmp/release
    OBJECTS_DIR = $$PWD/../OutputDir/tmp/release
    RCC_DIR = $$PWD/../OutputDir/tmp/release
    UI_DIR = $$PWD/../OutputDir/tmp/release
}
#第三方库源代码
HEADERS += \
    Src/3rdLib/glad/glad.h
    Src/3rdLib/glad/khrplatform.h
SOURCES += \
    Src/3rdLib/glad/glad.c
#工厂源代码
HEADERS += \
    Src/OWCommon/OWGlobalData.h \
    Src/OWCommon/MacroDefine.h \
    Src/OWCommon/precomplie.h \
    Src/IOpenGLWin.h \
    Src/OpenGLWinFactory.h \
    Src/OWCommon/OpenGLWindowUI_global.h \
    Src/OWLogicService/OpenGLWindowUI.h \
    Src/OWLogicService/Services/QtOpenGLWindow.h \
    Src/OWLogicService/Services/FPSCounter.h \
    Src/OWLogicService/Services/OpenGLRenderer.h \
    Src/OWLogicService/OpenGLEntity/OpenGLUniformBufferObject.h \
    Src/OWLogicService/OpenGLEntity/OpenGLMaterial.h \
    Src/OWLogicService/OpenGLEntity/OpenGLMesh.h \
    Src/OWLogicService/OpenGLEntity/OpenGLScene.h \
    Src/OWLogicService/OpenGLEntity/OpenGLTexture.h \
    Src/OWMControl/OpenGLWinControl.h \

SOURCES += \
    Src/OWCommon/OWGlobalData.cpp \
    Src/OpenGLWinFactory.cpp \
    Src/OWLogicService/OpenGLWindowUI.cpp \
    Src/OWLogicService/Services/QtOpenGLWindow.cpp \
    Src/OWLogicService/Services/FPSCounter.cpp \
    Src/OWLogicService/Services/OpenGLRenderer.cpp \
    Src/OWLogicService/OpenGLEntity/OpenGLUniformBufferObject.cpp \
    Src/OWLogicService/OpenGLEntity/OpenGLMaterial.cpp \
    Src/OWLogicService/OpenGLEntity/OpenGLMesh.cpp \
    Src/OWLogicService/OpenGLEntity/OpenGLScene.cpp \
    Src/OWLogicService/OpenGLEntity/OpenGLTexture.cpp \
    Src/OWMControl/OpenGLWinControl.cpp \

