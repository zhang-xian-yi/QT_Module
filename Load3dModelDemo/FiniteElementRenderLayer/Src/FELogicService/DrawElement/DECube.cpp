#include "DECube.h"

DECube::DECube()
{

}

DECube::~DECube()
{

}

void DECube::Draw(QSharedPointer<QOpenGLShaderProgram> program)
{

}

//此方法会在initialGL方法中执行create
QVector<GLuint>&  DECube::ComputeRendererData(QVector<FEVertex> &allVertexArr, QVector<GLuint>& indexArr)
{
    m_indexVect.clear();

    static FEVertex* pV0,*pV1,*pV2,*pV3;
    //face1  0123
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
    //face2 4567
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
    //face3 2761
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
    //face4 2456
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
    //face5 3274
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
    //face6 0156
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

    return m_indexVect;
}


void DECube::ComputeNormal(FEVertex &v0, FEVertex &v1, FEVertex &v2, FEVertex &v3)
{
    QVector3D firstVec = v1.position- v0.position;
    QVector3D secondVec = v2.position - v0.position;
    //计算两个向量之间的法向量
    QVector3D normal = QVector3D::crossProduct(firstVec, secondVec);
    //法向量单元化
    normal.normalize();

    //赋值法线
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
        vert.normal = (vert.normal + normal) /2 ;
    }
}
