#pragma once

#include "Load3DModel/Src/LMLogicService/Entity/Mesh/Mesh.h"
#include "Load3DModel/Src/LMCommon/Load3DModel_global.h" //此为其他模块包含此头文件时可以索引的目录

class LOAD3DMODEL_EXPORT Gridline: public QObject {
    Q_OBJECT

public:
    Gridline(QObject* parent = 0);
    Gridline(const Gridline& gridline);
    ~Gridline();

    void dumpObjectInfo(int level = 0);
    void dumpObjectTree(int level = 0);

    QPair<float, float> xRange() const;
    QPair<float, float> yRange() const;
    QPair<float, float> zRange() const;
    float xStride() const;
    float yStride() const;
    float zStride() const;
    QVector3D color() const;
    Mesh* marker();

public slots:
    void reset();
    void setXArguments(QVector3D xargs);
    void setYArguments(QVector3D yargs);
    void setZArguments(QVector3D zargs);
    void setColor(QVector3D color);

signals:
    void xArgumentsChanged(QVector3D xargs);
    void yArgumentsChanged(QVector3D yargs);
    void zArgumentsChanged(QVector3D zargs);
    void colorChanged(QVector3D color);

private:
    QPair<float, float> m_xRange, m_yRange, m_zRange;
    float m_xStride, m_yStride, m_zStride;
    QVector3D m_color;
    Mesh* m_marker;

    void update();
};
