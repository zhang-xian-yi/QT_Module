#include "CubeGeometry.h"

CubeGeometry* CubeGeometry::m_pStatInstance = nullptr;
QMutex CubeGeometry::m_oMutex;

CubeGeometry::CubeGeometry():QOpenGLFunctions()
    , indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();
    this->arrayBuf.create();
    this->indexBuf.create();

    this->m_nVertexCount = 0;
    this->m_strRenderElementName = "";
}

CubeGeometry::~CubeGeometry()
{
    this->arrayBuf.destroy();
    this->indexBuf.destroy();
}

void CubeGeometry::drawCubeGeometry(QSharedPointer<QOpenGLShaderProgram> program)
{
    this->arrayBuf.bind();
    this->indexBuf.bind();

    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vPos = program->attributeLocation("vPosition");
    program->enableAttributeArray(vPos);
    program->setAttributeBuffer(vPos, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int aColor = program->attributeLocation("aColor");
    program->enableAttributeArray(aColor);
    program->setAttributeBuffer(aColor, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for normal
    offset += sizeof(QVector3D);
    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int aNormal = program->attributeLocation("aNormal");
    program->enableAttributeArray(aNormal);
    program->setAttributeBuffer(aNormal, GL_FLOAT, offset, 3, sizeof(VertexData));
    auto f =QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
    f->glDrawElements(GL_QUADS, indicesQuad.size(), GL_UNSIGNED_INT, 0);
}

void CubeGeometry::UpdateCubeGeometry(QSharedPointer<FEModel> m_pModel)
{
    // 设置渲染数据
    this->SetRenderData(m_pModel->verticesVect,m_pModel->meshVect);
    // 完成初始化渲染数据 - 将CPU数据设置到GPU缓存中
    this->InitCompleteCubeGeometry();
}

void CubeGeometry::SetRenderData(QVector<QSharedPointer<FEVertex>>& vertexArr,QVector<QSharedPointer<FEMesh>>& meshArr)
{

    foreach (QSharedPointer<FEVertex> pQuadPoint, vertexArr)
    {
        VertexData tmp;
        tmp.position = pQuadPoint->position;
        tmp.color = QVector3D(0/255.0, 181/255.0, 0/255.0);
        // 遍历所有顶点
        verticesVect.append(tmp); // 默认模型颜色为银灰色
    }

    foreach (QSharedPointer<FEMesh> pMesh, meshArr)
    {
        VertexData* pV0,*pV1,*pV2,*pV3;
        //face1
        GLuint meshRealIndex = 0;
        meshRealIndex = pMesh->indexVect.at(0) - 1 + m_nVertexCount;
        indicesQuad.append(meshRealIndex);
        pV0 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = pMesh->indexVect.at(1) - 1 + m_nVertexCount;
        indicesQuad.append(meshRealIndex);
        pV1 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = pMesh->indexVect.at(2) - 1 + m_nVertexCount;
        indicesQuad.append(meshRealIndex);
        pV2 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = pMesh->indexVect.at(3) - 1 + m_nVertexCount;
        indicesQuad.append(meshRealIndex);
        pV3 = &verticesVect[meshRealIndex];//add by light director
        ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
        //face2
        meshRealIndex = pMesh->indexVect.at(4) - 1 + m_nVertexCount;
        indicesQuad.append(meshRealIndex);
        pV0 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = pMesh->indexVect.at(5) - 1 + m_nVertexCount;
        indicesQuad.append(meshRealIndex);
        pV1 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = pMesh->indexVect.at(6) - 1 + m_nVertexCount;
        indicesQuad.append(meshRealIndex);
        pV2 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = pMesh->indexVect.at(7) - 1 + m_nVertexCount;
        indicesQuad.append(meshRealIndex);
        pV3 = &verticesVect[meshRealIndex];//add by light director
        ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
        //face3
        meshRealIndex = pMesh->indexVect.at(2) - 1 + m_nVertexCount;
        indicesQuad.append(meshRealIndex);
        pV0 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = pMesh->indexVect.at(7) - 1 + m_nVertexCount;
        indicesQuad.append(meshRealIndex);
        pV1 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = pMesh->indexVect.at(6) - 1 + m_nVertexCount;
        indicesQuad.append(meshRealIndex);
        pV2 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = pMesh->indexVect.at(1) - 1 + m_nVertexCount;
        indicesQuad.append(meshRealIndex);
        pV3 = &verticesVect[meshRealIndex];//add by light director
        ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
        //face4
        meshRealIndex = pMesh->indexVect.at(3) - 1 + m_nVertexCount;
        indicesQuad.append(meshRealIndex);
        pV0 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = pMesh->indexVect.at(4) - 1 + m_nVertexCount;
        indicesQuad.append(meshRealIndex);
        pV1 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = pMesh->indexVect.at(5) - 1 + m_nVertexCount;
        indicesQuad.append(meshRealIndex);
        pV2 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = pMesh->indexVect.at(0) - 1 + m_nVertexCount;
        indicesQuad.append(meshRealIndex);
        pV3 = &verticesVect[meshRealIndex];//add by light director
        ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
        //face5
        meshRealIndex = pMesh->indexVect.at(3) - 1 + m_nVertexCount;
        indicesQuad.append(meshRealIndex);
        pV0 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = pMesh->indexVect.at(2) - 1 + m_nVertexCount;
        indicesQuad.append(meshRealIndex);
        pV1 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = pMesh->indexVect.at(7) - 1 + m_nVertexCount;
        indicesQuad.append(meshRealIndex);
        pV2 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = pMesh->indexVect.at(4) - 1 + m_nVertexCount;
        indicesQuad.append(meshRealIndex);
        pV3 = &verticesVect[meshRealIndex];//add by light director
        ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
        //face6
        meshRealIndex = pMesh->indexVect.at(0) - 1 + m_nVertexCount;
        indicesQuad.append(meshRealIndex);
        pV0 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = pMesh->indexVect.at(1) - 1 + m_nVertexCount;
        indicesQuad.append(meshRealIndex);
        pV1 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = pMesh->indexVect.at(5) - 1 + m_nVertexCount;
        indicesQuad.append(meshRealIndex);
        pV2 = &verticesVect[meshRealIndex];//add by light director
        meshRealIndex = pMesh->indexVect.at(6) - 1 + m_nVertexCount;
        indicesQuad.append(meshRealIndex);
        pV3 = &verticesVect[meshRealIndex];//add by light director
        ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
    }
    this->m_nVertexCount += vertexArr.size();
}

void CubeGeometry::InitCompleteCubeGeometry()
{
    this->arrayBuf.bind();
    this->arrayBuf.allocate(verticesVect.constData(), m_nVertexCount * sizeof(VertexData));
    this->arrayBuf.setUsagePattern(QOpenGLBuffer::StaticDraw);

    this->indexBuf.bind();
    this->indexBuf.allocate(indicesQuad.constData(), indicesQuad.size() * sizeof(GLuint));
    this->indexBuf.setUsagePattern(QOpenGLBuffer::StaticDraw);

    this->m_nVertexCount = 0;
}

void CubeGeometry::ReleaseRenderData()
{
    this->verticesVect.clear();
    this->indicesQuad.clear();

    this->arrayBuf.release();
    this->indexBuf.release();

    this->m_strRenderElementName = "";
}

CubeGeometry *CubeGeometry::GetInstance()
{
    m_oMutex.lock();
    if (nullptr == m_pStatInstance)
    {
        m_pStatInstance = new CubeGeometry();
    }
    m_oMutex.unlock();
    return m_pStatInstance;
}

//计算四个点决定的平面的法向量
void CubeGeometry::ComputeNormal(VertexData &v0, VertexData &v1, VertexData &v2, VertexData &v3)
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


void CubeGeometry::AssignVertexNormal(VertexData &vert,QVector3D normal)
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
