QT += core gui network opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGLWinLayer
TEMPLATE = lib
#导出洪
DEFINES += OPENGLWINDOWLAYER_LIBRARY
#参数
#VERSION = 1.0.0
DEFINES += \
    QT_DEPRECATED_WARNINGS \

#APP_VERSION=\\\"v$${VERSION}\\\"

#模块外部使用的路径（带模块名的头文件搜索）
INCLUDEPATH += $$PWD/../
#模块内部使用的相对路径
INCLUDEPATH += $$PWD/
#配置
CONFIG += c++17
DESTDIR = $$PWD/../OutputDir/ExecuteBin

PRECOMPILED_HEADER += \
                    $$PWD/Src/OWCommon/PCH.h

HEADERS += \
    Src/ILoad3D.h \
    Src/OWCommon/PCH.h \
    Src/OWCommon/MacroDefine.h \
    Src/OWCommon/OpenGLWindowLayer_global.h \
    Src/IOpenGLWin.h \
    Src/OpenGLWinLayerrFactory.h \
    Src/OWMControl/OpenGLWinLayerControl.h \

SOURCES += \
    Src/OWMControl/OpenGLWinLayerControl.cpp \
    Src/OpenGLWinLayerrFactory.cpp \


INCLUDEPATH += \
    Src/OWLogicService/Entity \
    Src/OWLogicService/Light \
    Src/OWLogicService/OpenGLEntity \
    Src/OWLogicService/Services \
    Src/OWLogicService/TransformAxis \
    Src/OWLogicService/UI \
    VendorLib/include

RESOURCES += OWRes.qrc

LIBS += -lopengl32
LIBS += -L$$PWD/VendorLib/libs -lassimp-vc142-mt

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

HEADERS += \
    Src/OWCommon/extmath.h \
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
    Src/OWLogicService/OpenGLWindowsLayerService.h \

SOURCES += \
    Src/OWCommon/extmath.cpp \
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
    Src/OWLogicService/OpenGLWindowsLayerService.cpp \

