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

    glDrawElements(GL_QUADS, indicesQuad.size(), GL_UNSIGNED_SHORT, 0);
}

void CubeGeometry::SetRenderData(QVector<CommonNS::InVertex> &vectexArr, QVector<CommonNS::InFaceIndex> &indexArray)
{
    foreach (CommonNS::InVertex quadPoint, vectexArr)
    {
        verticesVect.append({QVector3D(quadPoint.PostionXYZ.one, quadPoint.PostionXYZ.two, quadPoint.PostionXYZ.three), QVector3D(0.3, 0.6, 0.2)});
    }
    foreach (CommonNS::InFaceIndex meshIdxVec, indexArray)
    {
        if (meshIdxVec.IndexsArray.size() == 8) // 0123 4567
        { // 六面体
            //face1
            int meshRealIndex = meshIdxVec.IndexsArray.at(0) - 1;
            indicesQuad.append(meshRealIndex);
            verticesVect[meshRealIndex].normal = {0,0,1};//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(1) - 1;
            indicesQuad.append(meshRealIndex);
            verticesVect[meshRealIndex].normal = {0,0,1};//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(2) - 1;
            indicesQuad.append(meshRealIndex);
            verticesVect[meshRealIndex].normal = {0,0,1};//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(3) - 1;
            indicesQuad.append(meshRealIndex);
            verticesVect[meshRealIndex].normal = {0,0,1};//add by light director
            //face2
            meshRealIndex = meshIdxVec.IndexsArray.at(4) - 1;
            indicesQuad.append(meshRealIndex);
            verticesVect[meshRealIndex].normal = {0,0,-1};//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(5) - 1;
            indicesQuad.append(meshRealIndex);
            verticesVect[meshRealIndex].normal = {0,0,-1};//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(6) - 1;
            indicesQuad.append(meshRealIndex);
            verticesVect[meshRealIndex].normal = {0,0,-1};//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(7) - 1;
            indicesQuad.append(meshRealIndex);
            verticesVect[meshRealIndex].normal = {0,0,-1};//add by light director
            //face 3
            meshRealIndex = meshIdxVec.IndexsArray.at(2) - 1;
            indicesQuad.append(meshRealIndex);
            verticesVect[meshRealIndex].normal = {1,0,0};//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(7) - 1;
            indicesQuad.append(meshRealIndex);
            verticesVect[meshRealIndex].normal = {1,0,0};//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(6) - 1;
            indicesQuad.append(meshRealIndex);
            verticesVect[meshRealIndex].normal = {1,0,0};//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(1) - 1;
            indicesQuad.append(meshRealIndex);
            verticesVect[meshRealIndex].normal = {1,0,0};//add by light director
            //face4
            meshRealIndex = meshIdxVec.IndexsArray.at(3) - 1;
            indicesQuad.append(meshRealIndex);
            verticesVect[meshRealIndex].normal = {0,1,0};//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(4) - 1;
            indicesQuad.append(meshRealIndex);
            verticesVect[meshRealIndex].normal = {0,1,0};//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(5) - 1;
            indicesQuad.append(meshRealIndex);
            verticesVect[meshRealIndex].normal = {0,1,0};//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(0) - 1;
            indicesQuad.append(meshRealIndex);
            verticesVect[meshRealIndex].normal = {0,1,0};//add by light director
        }
        else if (meshIdxVec.IndexsArray.size() == 4)
        { // 四边形
            int meshRealIndex = meshIdxVec.IndexsArray.at(0) - 1;
            indicesQuad.append(meshRealIndex);
            verticesVect[meshRealIndex].normal = {1,0,0};//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(1) - 1;
            indicesQuad.append(meshRealIndex);
            verticesVect[meshRealIndex].normal = {1,0,0};//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(2) - 1;
            indicesQuad.append(meshRealIndex);
            verticesVect[meshRealIndex].normal = {1,0,0};//add by light director
            meshRealIndex = meshIdxVec.IndexsArray.at(3) - 1;
            indicesQuad.append(meshRealIndex);
            verticesVect[meshRealIndex].normal = {1,0,0};//add by light director
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
    this->indexBuf.allocate(indicesQuad.constData(), indicesQuad.size() * sizeof(GLushort));
    this->indexBuf.setUsagePattern(QOpenGLBuffer::StaticDraw);

    this->m_nVertexCount = 0;
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

