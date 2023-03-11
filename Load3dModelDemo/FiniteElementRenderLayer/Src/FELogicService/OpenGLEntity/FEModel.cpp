#include "FEModel.h"

FEModel::FEModel()
{
    m_vao = QSharedPointer<QOpenGLVertexArrayObject>(new QOpenGLVertexArrayObject());
    //构造顶点缓冲区
    m_pVertexBuf = QSharedPointer<QOpenGLBuffer>(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer));
    m_pIndexBuf = QSharedPointer<QOpenGLBuffer>(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer));
}


void FEModel::Commit()
{
    m_indexVect.clear();

    //遍历所有的索引
    foreach (FEMesh mesh, meshVect)
    {
        //添加索引缓冲
        m_indexVect.append(mesh.Compute(verticesVect));
    }

    //顶点数组绑定对象
    m_vao->create();
    m_vao->bind();
    // 完成初始化渲染数据 - 将CPU数据设置到GPU缓存中
    m_pVertexBuf->create();
    m_pVertexBuf->bind();
    m_pVertexBuf->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_pVertexBuf->allocate(verticesVect.constData(), verticesVect.size() * sizeof(FEVertex));
    m_pVertexBuf->release();

    m_pIndexBuf->create();
    m_pIndexBuf->bind();
    m_pIndexBuf->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_pIndexBuf->allocate(m_indexVect.constData(), m_indexVect.size() * sizeof(GLuint));
    m_pIndexBuf->release();

    m_vao->release();//用完释放
}

void FEModel::DrawModel(QSharedPointer<QOpenGLShaderProgram> program)
{
    m_pVertexBuf->bind();
    m_pIndexBuf->bind();

    quintptr offset = 0;
    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vPos = program->attributeLocation("vPosition");
    program->enableAttributeArray(vPos);
    program->setAttributeBuffer(vPos, GL_FLOAT, offset, 3, sizeof(FEVertex));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int aColor = program->attributeLocation("aColor");
    program->enableAttributeArray(aColor);
    program->setAttributeBuffer(aColor, GL_FLOAT, offset, 3, sizeof(FEVertex));

    // Offset for normal
    offset += sizeof(QVector3D);
    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int aNormal = program->attributeLocation("aNormal");
    program->enableAttributeArray(aNormal);
    program->setAttributeBuffer(aNormal, GL_FLOAT, offset, 3, sizeof(FEVertex));

    //绘制
    glDrawElements(GL_QUADS, m_indexVect.size(), GL_UNSIGNED_INT, 0);

    m_pIndexBuf->release();
    m_pVertexBuf->release();
}
