#include "FEModel.h"

FEModel::FEModel()
{
    //构造顶点缓冲区
    m_pVertexBuf = QSharedPointer<QOpenGLBuffer>(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer));
    m_pIndexBuf = QSharedPointer<QOpenGLBuffer>(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer));
}


void FEModel::Commit()
{
    m_indexVect.clear();

    foreach (FEMesh mesh, meshVect)
    {
        FEVertex* pV0,*pV1,*pV2,*pV3;
        //face1
        GLuint meshRealIndex = 0;
        meshRealIndex = mesh.indexVect.at(0) - 1 ;
        m_indexVect.append(meshRealIndex);
        pV0 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = mesh.indexVect.at(1) - 1 ;
        m_indexVect.append(meshRealIndex);
        pV1 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = mesh.indexVect.at(2) - 1 ;
        m_indexVect.append(meshRealIndex);
        pV2 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = mesh.indexVect.at(3) - 1 ;
        m_indexVect.append(meshRealIndex);
        pV3 = &verticesVect[meshRealIndex];//add by light director
        ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
        //face2
        meshRealIndex = mesh.indexVect.at(4) - 1 ;
        m_indexVect.append(meshRealIndex);
        pV0 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = mesh.indexVect.at(5) - 1 ;
        m_indexVect.append(meshRealIndex);
        pV1 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = mesh.indexVect.at(6) - 1 ;
        m_indexVect.append(meshRealIndex);
        pV2 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = mesh.indexVect.at(7) - 1 ;
        m_indexVect.append(meshRealIndex);
        pV3 = &verticesVect[meshRealIndex];//add by light director
        ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
        //face3
        meshRealIndex = mesh.indexVect.at(2) - 1 ;
        m_indexVect.append(meshRealIndex);
        pV0 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = mesh.indexVect.at(7) - 1 ;
        m_indexVect.append(meshRealIndex);
        pV1 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = mesh.indexVect.at(6) - 1 ;
        m_indexVect.append(meshRealIndex);
        pV2 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = mesh.indexVect.at(1) - 1 ;
        m_indexVect.append(meshRealIndex);
        pV3 = &verticesVect[meshRealIndex];//add by light director
        ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
        //face4
        meshRealIndex = mesh.indexVect.at(3) - 1 ;
        m_indexVect.append(meshRealIndex);
        pV0 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = mesh.indexVect.at(4) - 1 ;
        m_indexVect.append(meshRealIndex);
        pV1 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = mesh.indexVect.at(5) - 1 ;
        m_indexVect.append(meshRealIndex);
        pV2 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = mesh.indexVect.at(0) - 1 ;
        m_indexVect.append(meshRealIndex);
        pV3 = &verticesVect[meshRealIndex];//add by light director
        ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
        //face5
        meshRealIndex = mesh.indexVect.at(3) - 1 ;
        m_indexVect.append(meshRealIndex);
        pV0 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = mesh.indexVect.at(2) - 1 ;
        m_indexVect.append(meshRealIndex);
        pV1 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = mesh.indexVect.at(7) - 1 ;
        m_indexVect.append(meshRealIndex);
        pV2 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = mesh.indexVect.at(4) - 1 ;
        m_indexVect.append(meshRealIndex);
        pV3 = &verticesVect[meshRealIndex];//add by light director
        ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
        //face6
        meshRealIndex = mesh.indexVect.at(0) - 1 ;
        m_indexVect.append(meshRealIndex);
        pV0 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = mesh.indexVect.at(1) - 1 ;
        m_indexVect.append(meshRealIndex);
        pV1 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = mesh.indexVect.at(5) - 1 ;
        m_indexVect.append(meshRealIndex);
        pV2 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = mesh.indexVect.at(6) - 1 ;
        m_indexVect.append(meshRealIndex);
        pV3 = &verticesVect[meshRealIndex];//add by light director
        ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
    }


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

    /*
    //遍历所有的网格体（绘制单元并创建对应缓冲去）
    foreach (FEMesh mesh, meshVect)
    {
        mesh.Draw(program);
    }

    this->m_pVertexBuf->release();
    */

}

void FEModel::ComputeNormal(FEVertex &v0, FEVertex &v1, FEVertex &v2, FEVertex &v3)
{
    QVector3D firstVec = v1.position- v0.position;
    QVector3D secondVec = v2.position - v0.position;
    //计算两个向量之间的法向量
    QVector3D normal = QVector3D::crossProduct(firstVec, secondVec);
    //法向量单元化
    normal.normalize();


    AssignVertexNormal(v0,normal);
    AssignVertexNormal(v1,normal);
    AssignVertexNormal(v2,normal);
    AssignVertexNormal(v3,normal);
}

void FEModel::AssignVertexNormal(FEVertex &vert, QVector3D normal)
{
    static QVector3D compare = {0,0,0};

    if(vert.normal == compare)
    {
        vert.normal = normal;
    }
    else
    {
        vert.normal = (vert.normal + normal) ;
    }
}
