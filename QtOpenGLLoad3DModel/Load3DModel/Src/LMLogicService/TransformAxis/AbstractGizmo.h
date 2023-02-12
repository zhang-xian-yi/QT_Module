#pragma once

#include "Load3DModel/Src/LMLogicService/Entity/Mesh/Mesh.h"
#include "Load3DModel/Src/LMLogicService/Entity/AbstractEntity.h"
#include "Load3DModel/Src/LMCommon/ExtendMath.h"
#include "Load3DModel/Src/LMCommon/MacroDefine.h"

#include "Load3DModel/Src/LMCommon/Load3DModel_global.h" //此为其他模块包含此头文件时可以索引的目录

class LOAD3DMODEL_EXPORT AbstractGizmo: public AbstractEntity {
    Q_OBJECT

public:
    enum TransformAxis {
        None = 0,
        X = 1,
        Y = 2,
        Z = 3
    };

    AbstractGizmo(QObject* parent = 0);
    ~AbstractGizmo();

    void dumpObjectInfo(int) override {}
    void dumpObjectTree(int) override {}

    bool isGizmo() const override;
    bool isLight() const override;
    bool isMesh() const override;
    bool isModel() const override;

    virtual TransformAxis transformAxis() const;
    virtual QVector<Mesh*>& markers();
    virtual void drag(QPoint from, QPoint to, int scnWidth, int scnHeight, QMatrix4x4 proj, QMatrix4x4 view) = 0;
    virtual void bindTo(AbstractEntity* host);
    virtual void unbind();

public slots:
    virtual void setTransformAxis(TransformAxis axis);
    virtual void setTransformAxis(void* marker);

protected:
    TransformAxis m_axis;
    QVector<Mesh*> m_markers;
    AbstractEntity* m_host;

private slots:
    void hostDestroyed(QObject* host);
};
