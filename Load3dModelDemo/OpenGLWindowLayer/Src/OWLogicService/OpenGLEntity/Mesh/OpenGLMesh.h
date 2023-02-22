#pragma once

#include "Mesh/Mesh.h"
#include "Material/OpenGLMaterial.h"

class OpenGLMesh: public QObject {
    Q_OBJECT

public:
    OpenGLMesh(QSharedPointer<Mesh> mesh, QObject* parent = 0);
    ~OpenGLMesh();

    QSharedPointer<Mesh> host() const;

    void create();
    void commit();
    void render(bool pickingPass = false);
    void destroy();

    void setSizeFixed(bool sizeFixed);
    void setPickingID(uint id);

protected:
    void childEvent(QChildEvent *event) override;

private:
    QSharedPointer<Mesh> m_host;
    bool m_sizeFixed;
    uint m_pickingID;

    QOpenGLVertexArrayObject*  m_vao;
    QSharedPointer<QOpenGLBuffer> m_vbo, m_ebo;
    QSharedPointer<OpenGLMaterial> m_openGLMaterial;//弱引用，

    static QSharedPointer<OpenGLUniformBufferObject> m_modelInfo;

private slots:
    void materialChanged(QSharedPointer<Material> material);
    void geometryChanged(const QVector<Vertex>& vertices, const QVector<uint32_t>& indices);
    void hostDestroyed(QObject* host);
};
