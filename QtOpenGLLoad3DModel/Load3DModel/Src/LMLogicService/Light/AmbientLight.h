#pragma once

#include "AbstractLight.h"

#include "Load3DModel/Src/LMCommon/Load3DModel_global.h" //此为其他模块包含此头文件时可以索引的目录

class LOAD3DMODEL_EXPORT AmbientLight: public AbstractLight {
    Q_OBJECT

public:
    AmbientLight(QObject* parent = 0);
    AmbientLight(QVector3D color, QObject* parent = 0);
    AmbientLight(const AmbientLight& light);
    ~AmbientLight();

    void dumpObjectInfo(int level = 0) override;
    void dumpObjectTree(int level = 0) override;
};
