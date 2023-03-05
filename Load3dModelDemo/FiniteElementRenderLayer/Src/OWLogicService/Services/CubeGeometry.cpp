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
}

CubeGeometry::~CubeGeometry()
{
    this->arrayBuf.destroy();
    this->indexBuf.destroy();
}

void CubeGeometry::drawCubeGeometry(QOpenGLShaderProgram *program)
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
    glDrawElements(GL_QUADS, indicesQuad.size(), GL_UNSIGNED_INT, 0);
}

void CubeGeometry::SetRenderData(QVector<InVertex> &vectexArr, QVector<InFaceIndex> &indexArray)
{
    foreach (InVertex quadPoint, vectexArr)
    {
        VertexData tmp;
        tmp.position = QVector3D(quadPoint.PostionXYZ.one, quadPoint.PostionXYZ.two, quadPoint.PostionXYZ.three);
        tmp.color = QVector3D(0.0f, 1.0f, 0.0f);
        verticesVect.append(tmp);
    }
    foreach (InFaceIndex meshIdxVec, indexArray)
    {
        VertexData* pV0,*pV1,*pV2,*pV3;
        if (meshIdxVec.IndexsArray.size() == 8) // 0123 4567
        { // 六面体
            //face1
            GLuint meshRealIndex = meshIdxVec.IndexsArray.at(0) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV0 = &verticesVect[meshRealIndex];//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(1) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV1 = &verticesVect[meshRealIndex];//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(2) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV2 = &verticesVect[meshRealIndex];//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(3) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV3 = &verticesVect[meshRealIndex];//add by light director
            ComputeNormal(*pV0,*pV1,*pV2,*pV3,FaceDirect::FRONT);//计算四个点锁确定平面的法向量
            //face2
            meshRealIndex = meshIdxVec.IndexsArray.at(4) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV0 = &verticesVect[meshRealIndex];//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(5) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV1 = &verticesVect[meshRealIndex];//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(6) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV2 = &verticesVect[meshRealIndex];//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(7) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV3 = &verticesVect[meshRealIndex];//add by light director
            ComputeNormal(*pV0,*pV1,*pV2,*pV3,FaceDirect::BACK);//计算四个点锁确定平面的法向量
            //face3
            meshRealIndex = meshIdxVec.IndexsArray.at(2) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV0 = &verticesVect[meshRealIndex];//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(7) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV1 = &verticesVect[meshRealIndex];//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(6) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV2 = &verticesVect[meshRealIndex];//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(1) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV3 = &verticesVect[meshRealIndex];//add by light director
            ComputeNormal(*pV0,*pV1,*pV2,*pV3,FaceDirect::RIGHT);//计算四个点锁确定平面的法向量
            //face4
            meshRealIndex = meshIdxVec.IndexsArray.at(3) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV0 = &verticesVect[meshRealIndex];//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(4) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV1 = &verticesVect[meshRealIndex];//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(5) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV2 = &verticesVect[meshRealIndex];//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(0) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV3 = &verticesVect[meshRealIndex];//add by light director
            ComputeNormal(*pV0,*pV1,*pV2,*pV3,FaceDirect::LEFT);//计算四个点锁确定平面的法向量
            //face5
            meshRealIndex = meshIdxVec.IndexsArray.at(3) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV0 = &verticesVect[meshRealIndex];//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(2) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV1 = &verticesVect[meshRealIndex];//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(7) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV2 = &verticesVect[meshRealIndex];//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(4) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV3 = &verticesVect[meshRealIndex];//add by light director
            ComputeNormal(*pV0,*pV1,*pV2,*pV3,FaceDirect::UP);//计算四个点锁确定平面的法向量
            //face6
            meshRealIndex = meshIdxVec.IndexsArray.at(0) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV0 = &verticesVect[meshRealIndex];//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(1) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV1 = &verticesVect[meshRealIndex];//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(5) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV2 = &verticesVect[meshRealIndex];//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(6) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV3 = &verticesVect[meshRealIndex];//add by light director
            ComputeNormal(*pV0,*pV1,*pV2,*pV3,FaceDirect::DOWN);//计算四个点锁确定平面的法向量
        }
        else if (meshIdxVec.IndexsArray.size() == 4)
        { // 四边形
            GLuint meshRealIndex = meshIdxVec.IndexsArray.at(0) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV0 = &verticesVect[meshRealIndex];//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(1) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV1 = &verticesVect[meshRealIndex];//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(2) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV2 = &verticesVect[meshRealIndex];//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(3) - 1 + m_nVertexCount;
            indicesQuad.append(meshRealIndex);
            pV3 = &verticesVect[meshRealIndex];//add by light director
            //ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
        }
    }
    this->m_nVertexCount += vectexArr.size();
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
void CubeGeometry::ComputeNormal(VertexData &v0, VertexData &v1, VertexData &v2, VertexData &v3,FaceDirect direect)
{
    QVector3D firstVec = v1.position- v0.position;
    QVector3D secondVec = v2.position - v0.position;
    //计算两个向量之间的法向量
    QVector3D normal = QVector3D::crossProduct(firstVec, secondVec);
    //法向量单元化
    normal.normalize();

    switch (direect)
    {
        case FaceDirect::UP:
        {
            normal.setY(fabsf(normal.y()));//y值一定为正
            break;
        }
        case FaceDirect::RIGHT:
        {
            normal.setX(fabsf(normal.x()));//x值一定为正
            break;
        }
        case FaceDirect::FRONT:
        {
            normal.setZ(fabsf(normal.z()));//z值一定为正
            break;
        }
        case FaceDirect::LEFT:
        {
            if(normal.x()>0)
                normal.setX(-normal.x());
            break;
        }
        case FaceDirect::DOWN:
        {
            if(normal.y()>0)
                normal.setY(-normal.y());
            break;
        }
        case FaceDirect::BACK:
        {
            if(normal.z()>0)
                normal.setZ(-normal.z());
            break;
        }
    default:
        break;
    }


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
