#include "Mesh.h"
#include "AbstractGizmo.h"
#include "AbstractLight.h"
#include "Src/OWCommon/GlobalData.h" //LogLv 引入 dout 引入
Mesh::Mesh(QObject * parent): AbstractEntity(0) {
    m_meshType = Triangle;
    m_material = nullptr;
    setObjectName("Untitled Mesh");
    //setParent(parent);
}

Mesh::Mesh(MeshType _meshType, QObject * parent): AbstractEntity(0) {
    m_meshType = _meshType;
    m_material = nullptr;
    setObjectName("Untitled Mesh");
    //setParent(parent);
}

Mesh::Mesh(const Mesh & mesh): AbstractEntity(mesh) {
    m_meshType = mesh.m_meshType;
    m_vertices = mesh.m_vertices;
    m_indices = mesh.m_indices;
    m_material = QSharedPointer<Material>(new Material(*mesh.m_material));
    setObjectName(mesh.objectName());
}

Mesh::~Mesh() {
    if (logLV >= LOG_LEVEL_INFO)
        dout << "Mesh" << this->objectName() << "is destroyed";
}

// Dump info

void Mesh::dumpObjectInfo(int l) {
    qDebug().nospace() << tab(l) << "Mesh: " << objectName();
    qDebug().nospace() << tab(l + 1) << "Type: " <<
        (m_meshType == Triangle ? "Triangle" : (m_meshType == Line ? "Line" : "Point"));
    qDebug().nospace() << tab(l + 1) << "Visible: " << m_visible;
    qDebug().nospace() << tab(l + 1) << "Position: " << m_position;
    qDebug().nospace() << tab(l + 1) << "Rotation: " << m_rotation;
    qDebug().nospace() << tab(l + 1) << "Scaling:  " << m_scaling;
    qDebug("%s%d vertices, %d indices, %d material",
           tab(l + 1), m_vertices.size(), m_indices.size(), m_material != 0);
}

void Mesh::dumpObjectTree(int l) {
    dumpObjectInfo(l);
    if (m_material)
        m_material->dumpObjectTree(l + 1);
}

bool Mesh::isGizmo() const {
    if (qobject_cast<AbstractGizmo*>(parent())) return true;
    return false;
}

bool Mesh::isLight() const {
    if (qobject_cast<AbstractLight*>(parent())) return true;
    return false;
}

bool Mesh::isMesh() const {
    if (isGizmo()) return false;
    if (isLight()) return false;
    return true;
}

bool Mesh::isModel() const {
    return false;
}

QVector3D Mesh::centerOfMass() const {
    QVector3D centerOfMass;
    float totalMass = 0;
    QMatrix4x4 modelMat = globalModelMatrix();
    for (int i = 0; i < m_indices.size();) {
        QVector3D centroid;
        float mass = 0;
        if (m_meshType == Point) {
            centroid = modelMat * m_vertices[m_indices[i + 0]].position;
            mass = 1.0f;
            i += 1;
        } else if (m_meshType == Line) {
            QVector3D p0 = modelMat * m_vertices[m_indices[i + 0]].position;
            QVector3D p1 = modelMat * m_vertices[m_indices[i + 1]].position;
            centroid = (p0 + p1) / 2;
            mass = p0.distanceToPoint(p1);
            i += 2;
        } else if (m_meshType == Triangle) {
            QVector3D p0 = modelMat * m_vertices[m_indices[i + 0]].position;
            QVector3D p1 = modelMat * m_vertices[m_indices[i + 1]].position;
            QVector3D p2 = modelMat * m_vertices[m_indices[i + 2]].position;
            centroid = (p0 + p1 + p2) / 3;
            mass = QVector3D::crossProduct(p1 - p0, p2 - p0).length() / 2;
            i += 3;
        }
        centerOfMass += centroid * mass;
        totalMass += mass;
    }
    return centerOfMass / totalMass;
}

float Mesh::mass() const {
    float totalMass = 0;
    QMatrix4x4 modelMat = globalModelMatrix();
    for (int i = 0; i < m_indices.size();) {
        if (m_meshType == Point) {
            totalMass += 1.0f;
            i += 1;
        } else if (m_meshType == Line) {
            QVector3D p0 = modelMat * m_vertices[m_indices[i + 0]].position;
            QVector3D p1 = modelMat * m_vertices[m_indices[i + 1]].position;
            totalMass += p0.distanceToPoint(p1);
            i += 2;
        } else if (m_meshType == Triangle) {
            QVector3D p0 = modelMat * m_vertices[m_indices[i + 0]].position;
            QVector3D p1 = modelMat * m_vertices[m_indices[i + 1]].position;
            QVector3D p2 = modelMat * m_vertices[m_indices[i + 2]].position;
            totalMass += QVector3D::crossProduct(p1 - p0, p2 - p0).length() / 2;
            i += 3;
        }
    }
    return totalMass;
}

Mesh::MeshType Mesh::meshType() const {
    return m_meshType;
}

const QVector<Vertex>& Mesh::vertices() const {
    return m_vertices;
}

const QVector<uint32_t>& Mesh::indices() const {
    return m_indices;
}

QSharedPointer<Material> Mesh::material() const{
    return m_material;
}

QSharedPointer<Mesh> Mesh::merge(QSharedPointer<Mesh> mesh1, QSharedPointer<Mesh>  mesh2) {
    if (mesh1 == nullptr && mesh2 == nullptr)
    {
        return nullptr;
    }
    else if (mesh1 == nullptr || mesh2 == nullptr)
    {
        if (mesh1 == nullptr)
        {
            mesh1 = mesh2;
        }
        QSharedPointer<Mesh> mergedMesh = QSharedPointer<Mesh>(new Mesh(mesh1->meshType()));
        mergedMesh->setObjectName(mesh1->objectName());
        mergedMesh->setMaterial(QSharedPointer<Material>(new Material(*mesh1->material())));
        for (int i = 0; i < mesh1->m_vertices.size(); i++)
        {
            mergedMesh->m_vertices.push_back(mesh1->globalModelMatrix() * mesh1->m_vertices[i]);
        }
        mergedMesh->m_indices = mesh1->m_indices;
        return mergedMesh;
    }

    if (mesh1->meshType() != mesh2->meshType())
    {
        if (logLV >= LOG_LEVEL_ERROR)
            dout << "Failed to merge" << mesh1->objectName() << "and" << mesh2->objectName() << ": type not match";
        return nullptr;
    }

    if (logLV >= LOG_LEVEL_INFO)
    {
        dout << "Merging" << mesh1->objectName() << "and" << mesh2->objectName();
    }

    QSharedPointer<Mesh> mergedMesh = QSharedPointer<Mesh>(new Mesh(mesh1->meshType()));
    mergedMesh->setObjectName(mesh1->objectName() + mesh2->objectName());
    mergedMesh->setMaterial(QSharedPointer<Material>(new Material));

    for (int i = 0; i < mesh1->m_vertices.size(); i++)
    {
        mergedMesh->m_vertices.push_back(mesh1->globalModelMatrix() * mesh1->m_vertices[i]);
    }

    for (int i = 0; i < mesh2->m_vertices.size(); i++)
    {
        mergedMesh->m_vertices.push_back(mesh2->globalModelMatrix() * mesh2->m_vertices[i]);
    }

    mergedMesh->m_indices = mesh1->m_indices;
    for (int i = 0; i < mesh2->m_indices.size(); i++)
    {
        mergedMesh->m_indices.push_back(mesh2->m_indices[i] + mesh1->m_vertices.size());
    }

    return mergedMesh;
}

void Mesh::setMeshType(MeshType meshType) {
    if (m_meshType != meshType) {
        m_meshType = meshType;
        if (logLV >= LOG_LEVEL_INFO)
            dout << "The type of mesh" << this->objectName() << "is set to"
                 << (m_meshType == Triangle ? "Triangle" : (m_meshType == Line ? "Line" : "Point"));
        meshTypeChanged(m_meshType);
    }
}

void Mesh::setGeometry(const QVector<Vertex>& vertices, const QVector<uint32_t>& indices) {
    if (m_vertices != vertices || m_indices != indices) {
        m_vertices = vertices;
        m_indices = indices;
        geometryChanged(m_vertices, m_indices);
    }
}

bool Mesh::setMaterial(QSharedPointer<Material> material) {
    if (m_material == material) return false;

    
    if (!m_material.isNull()) {
        m_material.clear();
    }
    

    if (!material.isNull())
    {
        m_material = material;
        //m_material->setParent(this);
        if (logLV >= LOG_LEVEL_INFO)
            dout << "Material" << material->objectName() << "is assigned to mesh" << objectName();
    }

    materialChanged(m_material);
    return true;
}

void Mesh::reverseNormals() {
    for (int i = 0; i < m_vertices.size(); i++)
        m_vertices[i].normal = -m_vertices[i].normal;
    if (logLV >= LOG_LEVEL_INFO)
        dout << "Normals of" << this->objectName() << "is reversed";
    geometryChanged(m_vertices, m_indices);
}

void Mesh::reverseTangents() {
    for (int i = 0; i < m_vertices.size(); i++)
        m_vertices[i].tangent = -m_vertices[i].tangent;
    if (logLV >= LOG_LEVEL_INFO)
        dout << "Tangents of" << this->objectName() << "is reversed";
    geometryChanged(m_vertices, m_indices);
}

void Mesh::reverseBitangents() {
    for (int i = 0; i < m_vertices.size(); i++)
        m_vertices[i].bitangent = -m_vertices[i].bitangent;
    if (logLV >= LOG_LEVEL_INFO)
        dout << "Bitangents of" << this->objectName() << "is reversed";
    geometryChanged(m_vertices, m_indices);
}

void Mesh::childEvent(QChildEvent * e) {
    if (e->added())
    {
        if (Material* material = qobject_cast<Material*>(e->child()))
        {
            setMaterial(QSharedPointer<Material>(material));
        }
    }
    else if (e->removed())
    {
        if (e->child() == m_material)
        {
            m_material = nullptr;
            materialChanged(0);
        }
    }
}

QDataStream & operator>>(QDataStream & in, Mesh::MeshType & meshType) {
    qint32 t;
    in >> t;
    if (t == 0)
        meshType = Mesh::Triangle;
    else if (t == 1)
        meshType = Mesh::Line;
    else
        meshType = Mesh::Point;
    return in;
}
