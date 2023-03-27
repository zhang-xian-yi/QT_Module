#平台配置
win32
{
    CONFIG += c++17
}

unix:!macx
{
    QMAKE_CXXFLAGS += -std=c++17
}


#输出目录
OutTempDir = $$PWD/OutputDir/Temp
OutBinDir = $$PWD/OutputDir/ExecuteBin

#中文乱码
msvc
{
    QMAKE_CFLAGS += -source-charset:utf-8
    QMAKE_CXXFLAGS += -source-charset:utf-8
    QMAKE_CXXFLAGS += -execution-charset:utf-8
}

#输出路径
DESTDIR = $${OutBinDir}/

#debug 配置
CONFIG(debug) {
    MOC_DIR = $${OutTempDir}/debug/$${TARGET}
    OBJECTS_DIR = $${OutTempDir}/debug/$${TARGET}
    RCC_DIR = $${OutTempDir}/debug/$${TARGET}
    UI_DIR = $${OutTempDir}/debug/$${TARGET}
}
#release 配置
CONFIG(release) {
    MOC_DIR = $${OutTempDir}/release/$${TARGET}
    OBJECTS_DIR = $${OutTempDir}/release/$${TARGET}
    RCC_DIR = $${OutTempDir}/release/$${TARGET}
    UI_DIR = $${OutTempDir}/release/$${TARGET}
}
