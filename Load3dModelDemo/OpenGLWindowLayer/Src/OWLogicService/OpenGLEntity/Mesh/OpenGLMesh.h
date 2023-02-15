#pragma once

#include "Mesh/Mesh.h"
#include "Material/OpenGLMaterial.h"

class OpenGLMesh: public QObject {
    Q_OBJECT

public:
    OpenGLMesh(Mesh* mesh, QObject* parent = 0);
    ~OpenGLMesh();

    Mesh* host() const;

    void create();
    void commit();
    void render(bool pickingPass = false);
    void destroy();

    void setSizeFixed(bool sizeFixed);
    void setPickingID(uint id);

protected:
    void childEvent(QChildEvent *event) override;

private:
    Mesh* m_host;
    bool m_sizeFixed;
    uint m_pickingID;

    QOpenGLVertexArrayObject * m_vao;
    QOpenGLBuffer* m_vbo, *m_ebo;
    OpenGLMaterial* m_openGLMaterial;//矩阵随时更新,但是不做释放

    static OpenGLUniformBufferObject *m_modelInfo;

private slots:
    void materialChanged(Material* material);
    void geometryChanged(const QVector<Vertex>& vertices, const QVector<uint32_t>& indices);
    void hostDestroyed(QObject* host);
};
