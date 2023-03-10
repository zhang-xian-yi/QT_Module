#include "FEModel.h"

FEModel::FEModel()
{
    //构造顶点缓冲区
    m_pVertexBuf = QSharedPointer<QOpenGLBuffer>(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer));
}

//此函数在OpenGL 初始化方法执行
void FEModel::CreateBuffer()
{
    m_pVertexBuf->create();

    //遍历所有的网格体（绘制单元并创建对应缓冲去）
    foreach (FEMesh mesh, meshVect)
    {
        mesh.CreateBuffer(this->verticesVect);
    }
}

void FEModel::DrawModel(QSharedPointer<QOpenGLShaderProgram> program)
{
    // 完成初始化渲染数据 - 将CPU数据设置到GPU缓存中
    this->m_pVertexBuf->bind();
    this->m_pVertexBuf->allocate(this->verticesVect.constData(), verticesVect.size() * sizeof(FEVertex));
    this->m_pVertexBuf->setUsagePattern(QOpenGLBuffer::StaticDraw);

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

    //遍历所有的网格体（绘制单元并创建对应缓冲去）
    foreach (FEMesh mesh, meshVect)
    {
        mesh.Draw(program);
    }

    this->m_pVertexBuf->release();
}
