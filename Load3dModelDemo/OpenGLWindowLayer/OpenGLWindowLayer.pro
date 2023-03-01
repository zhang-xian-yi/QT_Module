QT += core gui opengl
TARGET = OpenGLWinLayer
TEMPLATE = lib
greaterThan(QT_MAJOR_VERSION,4): QT += widgets
#导出宏定义
DEFINES = OPENGLWINDOWLAYER_LIBRARY
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
INCLUDEPATH += Src/OWLogicService/Entity
INCLUDEPATH += Src/OWLogicService/Light
INCLUDEPATH += Src/OWLogicService/OpenGLEntity
INCLUDEPATH += Src/OWLogicService/Services
INCLUDEPATH += Src/OWLogicService/TransformAxis

#第三方库依赖的头文件搜索路径
INCLUDEPATH += VendorLib/include

#资源文件
RESOURCES += OWRes.qrc
#第三方库连接
LIBS += -lopengl32
LIBS += -L$$PWD/VendorLib/libs -lassimp-vc142-mt
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

#外部 .h
HEADERS += \
    Src/ExtStruct.h \
    Src/ILoad3D.h \
    Src/IOpenGLWin.h \
    Src/OpenGLWindowLayer_global.h \
    Src/OpenGLWinLayerrFactory.h \


#外部 .cpp
SOURCES += \
    Src/OpenGLWinLayerrFactory.cpp \


#内部 .h
HEADERS += \
    Src/OWCommon/PCH.h \
    Src/OWCommon/GlobalData.h \
    Src/OWCommon/ExtendMath.h \
    Src/OWMControl/OpenGLWinLayerControl.h \
    Src/OWLogicService/OpenGLWindowsLayerService.h \
    Src/OWLogicService/Entity/AbstractEntity.h \
    Src/OWLogicService/Entity/Camera/Camera.h \
    Src/OWLogicService/Entity/Gridline/Gridline.h \
    Src/OWLogicService/Entity/Material/Material.h \
    Src/OWLogicService/Entity/Mesh/Mesh.h \
    Src/OWLogicService/Entity/Model/Model.h \
    Src/OWLogicService/Entity/Model/ModelExporter.h \
    Src/OWLogicService/Entity/Model/ModelLoader.h \
    Src/OWLogicService/Entity/Scene/Scene.h \
    Src/OWLogicService/Entity/Scene/SceneLoader.h \
    Src/OWLogicService/Entity/Scene/SceneSaver.h \
    Src/OWLogicService/Entity/Texture/Texture.h \
    Src/OWLogicService/Entity/Texture/TextureLoader.h \
    Src/OWLogicService/Entity/Vertex/Vertex.h \
    Src/OWLogicService/Light/AbstractLight.h \
    Src/OWLogicService/Light/AmbientLight/AmbientLight.h \
    Src/OWLogicService/Light/SpotLight/SpotLight.h \
    Src/OWLogicService/Light/DirectionalLight/DirectionalLight.h \
    Src/OWLogicService/Light/PointLight/PointLight.h \
    Src/OWLogicService/TransformAxis/AbstractGizmo.h \
    Src/OWLogicService/TransformAxis/TransformGizmo.h \
    Src/OWLogicService/TransformAxis/Rotate/RotateGizmo.h \
    Src/OWLogicService/TransformAxis/Scale/ScaleGizmo.h \
    Src/OWLogicService/TransformAxis/Postion/TranslateGizmo.h \
    Src/OWLogicService/Services/OpenGLWindow.h \
    Src/OWLogicService/Services/OpenGLRenderer.h \
    Src/OWLogicService/OpenGLEntity/Material/OpenGLMaterial.h \
    Src/OWLogicService/OpenGLEntity/Mesh/OpenGLMesh.h \
    Src/OWLogicService/OpenGLEntity/Scene/OpenGLScene.h \
    Src/OWLogicService/OpenGLEntity/Texture/OpenGLTexture.h \
    Src/OWLogicService/OpenGLEntity/OpenGLUniformBufferObject.h \


#内部 .cpp
SOURCES += \
    Src/OWCommon/GlobalData.cpp \
    Src/OWCommon/ExtendMath.cpp \
    Src/OWMControl/OpenGLWinLayerControl.cpp \
    Src/OWLogicService/OpenGLWindowsLayerService.cpp \
    Src/OWLogicService/Entity/AbstractEntity.cpp \
    Src/OWLogicService/Entity/Camera/Camera.cpp \
    Src/OWLogicService/Entity/Gridline/Gridline.cpp \
    Src/OWLogicService/Entity/Material/Material.cpp \
    Src/OWLogicService/Entity/Mesh/Mesh.cpp \
    Src/OWLogicService/Entity/Model/Model.cpp \
    Src/OWLogicService/Entity/Model/ModelExporter.cpp \
    Src/OWLogicService/Entity/Model/ModelLoader.cpp \
    Src/OWLogicService/Entity/Scene/Scene.cpp \
    Src/OWLogicService/Entity/Scene/SceneLoader.cpp \
    Src/OWLogicService/Entity/Scene/SceneSaver.cpp \
    Src/OWLogicService/Entity/Texture/Texture.cpp \
    Src/OWLogicService/Entity/Texture/TextureLoader.cpp \
    Src/OWLogicService/Entity/Vertex/Vertex.cpp \
    Src/OWLogicService/Light/AbstractLight.cpp \
    Src/OWLogicService/Light/AmbientLight/AmbientLight.cpp \
    Src/OWLogicService/Light/SpotLight/SpotLight.cpp \
    Src/OWLogicService/Light/DirectionalLight/DirectionalLight.cpp \
    Src/OWLogicService/Light/PointLight/PointLight.cpp \
    Src/OWLogicService/TransformAxis/AbstractGizmo.cpp \
    Src/OWLogicService/TransformAxis/TransformGizmo.cpp \
    Src/OWLogicService/TransformAxis/Rotate/RotateGizmo.cpp \
    Src/OWLogicService/TransformAxis/Scale/ScaleGizmo.cpp \
    Src/OWLogicService/TransformAxis/Postion/TranslateGizmo.cpp \
    Src/OWLogicService/Services/OpenGLWindow.cpp \
    Src/OWLogicService/Services/OpenGLRenderer.cpp \
    Src/OWLogicService/OpenGLEntity/Material/OpenGLMaterial.cpp \
    Src/OWLogicService/OpenGLEntity/Mesh/OpenGLMesh.cpp \
    Src/OWLogicService/OpenGLEntity/Scene/OpenGLScene.cpp \
    Src/OWLogicService/OpenGLEntity/Texture/OpenGLTexture.cpp \
    Src/OWLogicService/OpenGLEntity/OpenGLUniformBufferObject.cpp \

