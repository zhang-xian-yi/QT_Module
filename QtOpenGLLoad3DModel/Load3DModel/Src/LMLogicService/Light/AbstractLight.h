#pragma once

#include "Load3DModel/Src/LMLogicService/Entity/Mesh/Mesh.h"
#include "Load3DModel/Src/LMCommon/ExtendMath.h"
#include "Load3DModel/Src/LMCommon/MacroDefine.h"

#include "Load3DModel/Src/LMCommon/Load3DModel_global.h" //此为其他模块包含此头文件时可以索引的目录

class LOAD3DMODEL_EXPORT AbstractLight: public QObject {
    Q_OBJECT

public:
    AbstractLight();
    AbstractLight(QVector3D color);
    AbstractLight(const AbstractLight& light);
    ~AbstractLight();

    virtual void dumpObjectInfo(int level = 0) = 0;
    virtual void dumpObjectTree(int level = 0) = 0;

    QVector3D color();
    bool enabled();
    float intensity();
    virtual Mesh* marker() const;

public slots:
    virtual void setColor(QVector3D color);
    virtual void setEnabled(bool enabled);
    virtual void setIntensity(float intensity);

signals:
    void colorChanged(QVector3D color);
    void enabledChanged(bool enabled);
    void intensityChanged(float intensity);

protected:
    QVector3D m_color;
    bool m_enabled;
    float m_intensity;
};
