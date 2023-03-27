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
OutTempDir = $$PWD/../OutputDir/Temp
OutBinDir = $$PWD/../OutputDir/ExecuteBin
OutDirName = Plugins

#中文乱码
msvc
{
    QMAKE_CFLAGS += -source-charset:utf-8
    QMAKE_CXXFLAGS += -source-charset:utf-8
    QMAKE_CXXFLAGS += -execution-charset:utf-8
}

#输出路径
DESTDIR = $${OutBinDir}/$${OutDirName}/$${TARGET}/

#debug 配置
CONFIG(debug) {
    MOC_DIR = $${OutTempDir}/debug/$${OutDirName}/$${TARGET}
    OBJECTS_DIR = $${OutTempDir}/debug/$${OutDirName}/$${TARGET}
    RCC_DIR = $${OutTempDir}/debug/$${OutDirName}/$${TARGET}
    UI_DIR = $${OutTempDir}/debug/$${OutDirName}/$${TARGET}
}
#release 配置
CONFIG(release) {
    MOC_DIR = $${OutTempDir}/release/$${OutDirName}/$${TARGET}
    OBJECTS_DIR = $${OutTempDir}/release/$${OutDirName}/$${TARGET}
    RCC_DIR = $${OutTempDir}/release/$${OutDirName}/$${TARGET}
    UI_DIR = $${OutTempDir}/release/$${OutDirName}/$${TARGET}
}
