#include "DECube.h"

DECube::DECube()
{
    m_pIndexBuf = QSharedPointer<QOpenGLBuffer>(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer));
}

DECube::~DECube()
{

}

void DECube::Draw(QSharedPointer<QOpenGLShaderProgram> program)
{
    //提交gpu数据
    this->m_pIndexBuf->bind();
    this->m_pIndexBuf->allocate(m_indexVect.constData(), m_indexVect.size() * sizeof(GLuint));
    this->m_pIndexBuf->setUsagePattern(QOpenGLBuffer::StaticDraw);

    //绘制
    glDrawElements(GL_QUADS, m_indexVect.size(), GL_UNSIGNED_INT, 0);

    this->m_pIndexBuf->release();
}

//此方法会在initialGL方法中执行create
void DECube::SetRendererData(QVector<FEVertex> &allVertexArr, QVector<GLuint>& indexArr)
{
    m_indexVect.clear();//每次清空
    //顶点缓冲区创建
    this->m_pIndexBuf->create();

    FEVertex* pV0,*pV1,*pV2,*pV3;
    //face1
    GLuint meshRealIndex = 0;
    //顶点索引从1 开始，内存地址从0开始，所以真实index 需要减去1
    meshRealIndex = indexArr.at(0) - 1 ;
    m_indexVect.append(meshRealIndex);
    pV0 = &allVertexArr[meshRealIndex];//add by light director
    meshRealIndex = indexArr.at(1) - 1 ;
    m_indexVect.append(meshRealIndex);
    pV1 = &allVertexArr[meshRealIndex];//add by light director
    meshRealIndex = indexArr.at(2) - 1 ;
    m_indexVect.append(meshRealIndex);
    pV2 = &allVertexArr[meshRealIndex];//add by light director
    meshRealIndex = indexArr.at(3) - 1 ;
    m_indexVect.append(meshRealIndex);
    pV3 = &allVertexArr[meshRealIndex];//add by light director
    ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
    //face2
    meshRealIndex = indexArr.at(4) - 1 ;
    m_indexVect.append(meshRealIndex);
    pV0 = &allVertexArr[meshRealIndex];//add by light director
    meshRealIndex = indexArr.at(5) - 1 ;
    m_indexVect.append(meshRealIndex);
    pV1 = &allVertexArr[meshRealIndex];//add by light director
    meshRealIndex = indexArr.at(6) - 1 ;
    m_indexVect.append(meshRealIndex);
    pV2 = &allVertexArr[meshRealIndex];//add by light director
    meshRealIndex = indexArr.at(7) - 1 ;
    m_indexVect.append(meshRealIndex);
    pV3 = &allVertexArr[meshRealIndex];//add by light director
    ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
    //face3
    meshRealIndex = indexArr.at(2) - 1 ;
    m_indexVect.append(meshRealIndex);
    pV0 = &allVertexArr[meshRealIndex];//add by light director
    meshRealIndex = indexArr.at(7) - 1 ;
    m_indexVect.append(meshRealIndex);
    pV1 = &allVertexArr[meshRealIndex];//add by light director
    meshRealIndex = indexArr.at(6) - 1 ;
    m_indexVect.append(meshRealIndex);
    pV2 = &allVertexArr[meshRealIndex];//add by light director
    meshRealIndex = indexArr.at(1) - 1 ;
    m_indexVect.append(meshRealIndex);
    pV3 = &allVertexArr[meshRealIndex];//add by light director
    ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
    //face4
    meshRealIndex = indexArr.at(3) - 1 ;
    m_indexVect.append(meshRealIndex);
    pV0 = &allVertexArr[meshRealIndex];//add by light director
    meshRealIndex = indexArr.at(4) - 1 ;
    m_indexVect.append(meshRealIndex);
    pV1 = &allVertexArr[meshRealIndex];//add by light director
    meshRealIndex = indexArr.at(5) - 1 ;
    m_indexVect.append(meshRealIndex);
    pV2 = &allVertexArr[meshRealIndex];//add by light director
    meshRealIndex = indexArr.at(0) - 1 ;
    m_indexVect.append(meshRealIndex);
    pV3 = &allVertexArr[meshRealIndex];//add by light director
    ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
    //face5
    meshRealIndex = indexArr.at(3) - 1 ;
    m_indexVect.append(meshRealIndex);
    pV0 = &allVertexArr[meshRealIndex];//add by light director
    meshRealIndex = indexArr.at(2) - 1 ;
    m_indexVect.append(meshRealIndex);
    pV1 = &allVertexArr[meshRealIndex];//add by light director
    meshRealIndex = indexArr.at(7) - 1 ;
    m_indexVect.append(meshRealIndex);
    pV2 = &allVertexArr[meshRealIndex];//add by light director
    meshRealIndex = indexArr.at(4) - 1 ;
    m_indexVect.append(meshRealIndex);
    pV3 = &allVertexArr[meshRealIndex];//add by light director
    ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
    //face6
    meshRealIndex = indexArr.at(0) - 1 ;
    m_indexVect.append(meshRealIndex);
    pV0 = &allVertexArr[meshRealIndex];//add by light director
    meshRealIndex = indexArr.at(1) - 1 ;
    m_indexVect.append(meshRealIndex);
    pV1 = &allVertexArr[meshRealIndex];//add by light director
    meshRealIndex = indexArr.at(5) - 1 ;
    m_indexVect.append(meshRealIndex);
    pV2 = &allVertexArr[meshRealIndex];//add by light director
    meshRealIndex = indexArr.at(6) - 1 ;
    m_indexVect.append(meshRealIndex);
    pV3 = &allVertexArr[meshRealIndex];//add by light director
    ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
}

void DECube::ComputeNormal(FEVertex &v0, FEVertex &v1, FEVertex &v2, FEVertex &v3)
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

void DECube::AssignVertexNormal(FEVertex &vert, QVector3D normal)
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
