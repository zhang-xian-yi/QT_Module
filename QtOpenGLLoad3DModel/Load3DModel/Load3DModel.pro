QT      += core opengl

TARGET = Load3DModel
TEMPLATE = lib
DEFINES += LOAD3DMODEL_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#输出目录
DESTDIR=$$PWD/../OutputDir/ExecuteBin/
#资源路径
RESOURCES += $$PWD/resources.qrc

#项目根路径
INCLUDEPATH += $$PWD/../
INCLUDEPATH += $$PWD/VendorLib/Include
DEPENDPATH += $$PWD/VendorLib/Libs
LIBPATH += $$PWD/VendorLib/Libs

win32 {
    LIBS += -lopengl32
    LIBS += -lassimp-vc142-mt
    #RC_ICONS = resources/icons/AppIcon.ico
}

#预编译头文件
CONFIG += precompiled_header
PRECOMPILED_HEADER =  \
        $$PWD/Src/LMCommon/precompile.h

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


SOURCES += \
    Src/LMCommon/LMGlobalData.cpp \
    Src/LMLogicService/Load3DModelService.cpp \
    Src/LMMControl/LMServiceControl.cpp \
    Src/LoadModelFactory.cpp \

SOURCES += \
    Src/LMCommon/ExtendMath.cpp \
    Src/LMLogicService/Entity/AbstractEntity.cpp \
    Src/LMLogicService/Entity/Camera/Camera.cpp \
    Src/LMLogicService/Entity/Gridline/Gridline.cpp \
    Src/LMLogicService/Entity/Material/Material.cpp \
    Src/LMLogicService/Entity/Mesh/Mesh.cpp \
    Src/LMLogicService/Entity/Model/Model.cpp \
    Src/LMLogicService/Entity/Model/ModelExporter.cpp \
    Src/LMLogicService/Entity/Model/ModelLoader.cpp \
    Src/LMLogicService/Entity/Scene/Scene.cpp \
    Src/LMLogicService/Entity/Scene/SceneLoader.cpp \
    Src/LMLogicService/Entity/Scene/SceneSaver.cpp \
    Src/LMLogicService/Entity/Texture/Texture.cpp \
    Src/LMLogicService/Entity/Texture/TextureLoader.cpp \
    Src/LMLogicService/Entity/Vertex/Vertex.cpp \
    Src/LMLogicService/Light/AbstractLight.cpp \
    Src/LMLogicService/Light/AmbientLight.cpp \
    Src/LMLogicService/Light/SpotLight.cpp \
    Src/LMLogicService/Light/PointLight.cpp \
    Src/LMLogicService/Light/DirectionalLight.cpp \
    Src/LMLogicService/TransformAxis/AbstractGizmo.cpp \
    Src/LMLogicService/TransformAxis/RotateGizmo.cpp \
    Src/LMLogicService/TransformAxis/ScaleGizmo.cpp \
    Src/LMLogicService/TransformAxis/TransformGizmo.cpp \
    Src/LMLogicService/TransformAxis/TranslateGizmo.cpp \

HEADERS += \
    Src/LMCommon/LMGlobalData.h \
    Src/LMCommon/MacroDefine.h \
    Src/LMCommon/Load3DModel_global.h \
    Src/LMCommon/precompile.h \
    Src/LMLogicService/Load3DModelService.h \
    Src/LMMControl/LMServiceControl.h \
    Src/ILoadModel.h \
    Src/LoadModelFactory.h \

HEADERS += \
    Src/LMCommon/ExtendMath.h \
    Src/LMLogicService/Entity/AbstractEntity.h \
    Src/LMLogicService/Entity/Camera/Camera.h \
    Src/LMLogicService/Entity/Gridline/Gridline.h \
    Src/LMLogicService/Entity/Material/Material.h \
    Src/LMLogicService/Entity/Mesh/Mesh.h \
    Src/LMLogicService/Entity/Model/Model.h \
    Src/LMLogicService/Entity/Model/ModelExporter.h \
    Src/LMLogicService/Entity/Model/ModelLoader.h \
    Src/LMLogicService/Entity/Scene/Scene.h \
    Src/LMLogicService/Entity/Scene/SceneLoader.h \
    Src/LMLogicService/Entity/Scene/SceneSaver.h \
    Src/LMLogicService/Entity/Texture/Texture.h \
    Src/LMLogicService/Entity/Texture/TextureLoader.h \
    Src/LMLogicService/Entity/Vertex/Vertex.h \
    Src/LMLogicService/Light/AbstractLight.h \
    Src/LMLogicService/Light/AmbientLight.h \
    Src/LMLogicService/Light/SpotLight.h \
    Src/LMLogicService/Light/PointLight.h \
    Src/LMLogicService/Light/DirectionalLight.h \
    Src/LMLogicService/TransformAxis/AbstractGizmo.h \
    Src/LMLogicService/TransformAxis/RotateGizmo.h \
    Src/LMLogicService/TransformAxis/ScaleGizmo.h \
    Src/LMLogicService/TransformAxis/TransformGizmo.h \
    Src/LMLogicService/TransformAxis/TranslateGizmo.h \
