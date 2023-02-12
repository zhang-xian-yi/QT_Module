#pragma once

#include "AbstractLight.h"

#include "Load3DModel/Src/LMCommon/Load3DModel_global.h" //此为其他模块包含此头文件时可以索引的目录

class LOAD3DMODEL_EXPORT DirectionalLight: public AbstractLight {
    Q_OBJECT

public:
    DirectionalLight(QObject* parent = 0);
    DirectionalLight(QVector3D color, QVector3D direction, QObject* parent = 0);
    DirectionalLight(const DirectionalLight& light);
    ~DirectionalLight();

    void dumpObjectInfo(int level = 0) override;
    void dumpObjectTree(int level = 0) override;

    QVector3D direction();

public slots:
    void setDirection(QVector3D direction);

signals:
    void directionChanged(QVector3D direction);

protected:
    QVector3D m_direction;
};
