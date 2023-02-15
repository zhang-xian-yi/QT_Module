#pragma once

#include "AbstractEntity.h"
#include "Vertex/Vertex.h"
#include "Material/Material.h"

class ModelLoader;

class Mesh: public AbstractEntity {
    Q_OBJECT

public:
    enum MeshType {
        Triangle = 0,
        Line = 1,
        Point = 2
    };

    Mesh(QObject * parent = 0);
    Mesh(MeshType meshType, QObject * parent = 0);
    Mesh(const Mesh& mesh);
    ~Mesh();

    void dumpObjectInfo(int level = 0) override;
    void dumpObjectTree(int level = 0) override;

    bool isGizmo() const override;
    bool isLight() const override;
    bool isMesh() const override;
    bool isModel() const override;

    QVector3D centerOfMass() const;
    float mass() const;

    MeshType meshType() const;
    const QVector<Vertex> & vertices() const;
    const QVector<uint32_t> & indices() const;
    QSharedPointer<Material> material() const;

    static QSharedPointer<Mesh> merge(QSharedPointer<Mesh> mesh1, QSharedPointer<Mesh> mesh2);

public slots:
    void setMeshType(MeshType meshType);
    void setGeometry(const QVector<Vertex>& vertices, const QVector<uint32_t>& indices);
    bool setMaterial(QSharedPointer<Material> newMaterial);
    void reverseNormals();
    void reverseTangents();
    void reverseBitangents();

signals:
    void meshTypeChanged(int meshType);
    void geometryChanged(const QVector<Vertex>& vertices, const QVector<uint32_t>& indices);
    void materialChanged(QSharedPointer<Material> material);//材质随时会发生变化也无需释放

protected:
    void childEvent(QChildEvent *event) override;

protected:
    MeshType m_meshType;
    QVector<Vertex> m_vertices;
    QVector<uint32_t> m_indices;
    QSharedPointer<Material> m_material;

    friend ModelLoader;//友元类 此类可以访问本类对象的私有成员
};

QDataStream &operator>>(QDataStream &in, Mesh::MeshType& meshType);
