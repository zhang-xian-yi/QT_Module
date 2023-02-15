#pragma once

#include "Mesh/Mesh.h"

class Model: public AbstractEntity {
    Q_OBJECT

public:
    Model(QObject * parent = 0);
    Model(const Model& model);
    ~Model();

    bool addChildMesh(QSharedPointer<Mesh> mesh);
    bool addChildModel(QSharedPointer<Model> model);

    bool removeChildMesh(QObject* mesh, bool recursive);
    bool removeChildModel(QObject* model, bool recursive);

    void dumpObjectInfo(int level = 0) override;
    void dumpObjectTree(int level = 0) override;

    bool isGizmo() const override;
    bool isLight() const override;
    bool isMesh() const override;
    bool isModel() const override;

    QVector3D centerOfMass() const;
    float mass() const;

    QSharedPointer<Mesh> assemble() const;

    const QVector<QSharedPointer<Mesh>> & childMeshes() const;
    const QVector<QSharedPointer<Model>> & childModels() const;

public slots:
    void reverseNormals();
    void reverseTangents();
    void reverseBitangents();

signals:
    void childMeshAdded(QSharedPointer<Mesh> mesh);
    void childMeshRemoved(QObject* object);
    void childModelAdded(QSharedPointer<Model> model);
    void childModelRemoved(QObject* object);

protected:
    void childEvent(QChildEvent *event) override;

private:
    QVector<QSharedPointer<Mesh>> m_childMeshes;
    QVector<QSharedPointer<Model>> m_childModels;
};
