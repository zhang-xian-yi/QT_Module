#include "CubeGeometry.h"

CubeGeometry::CubeGeometry():indexBuf(QOpenGLBuffer::IndexBuffer)
{
    this->arrayBuf.create();
    this->indexBuf.create();
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
    glDrawElements(GL_QUADS, indicesQuad.size(), GL_UNSIGNED_INT, 0);
}

void CubeGeometry::SetRenderData(QSharedPointer<FEModel> pModel)
{
    auto vertexArr = pModel->verticesVect;
    auto indexArray = pModel->meshVect;
    foreach (const QSharedPointer<FEMesh> meshIdxVec, indexArray)
    {
        QSharedPointer<FEVertex> pV0,pV1,pV2,pV3;
        GLuint meshRealIndex;
        //face1
        meshRealIndex = meshIdxVec->indexVect.at(0) - 1;
        indicesQuad.append(meshRealIndex);
        pV0 = vertexArr[meshRealIndex];//add by light director
        meshRealIndex = meshIdxVec->indexVect.at(1) - 1 ;
        indicesQuad.append(meshRealIndex);
        pV1 = vertexArr[meshRealIndex];//add by light director
        meshRealIndex = meshIdxVec->indexVect.at(2) - 1 ;
        indicesQuad.append(meshRealIndex);
        pV2 = vertexArr[meshRealIndex];//add by light director
        meshRealIndex = meshIdxVec->indexVect.at(3) - 1 ;
        indicesQuad.append(meshRealIndex);
        pV3 = vertexArr[meshRealIndex];//add by light director
        ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
        //face2
        meshRealIndex = meshIdxVec->indexVect.at(4) - 1 ;
        indicesQuad.append(meshRealIndex);
        pV0 = vertexArr[meshRealIndex];//add by light director
        meshRealIndex = meshIdxVec->indexVect.at(5) - 1 ;
        indicesQuad.append(meshRealIndex);
        pV1 = vertexArr[meshRealIndex];//add by light director
        meshRealIndex = meshIdxVec->indexVect.at(6) - 1 ;
        indicesQuad.append(meshRealIndex);
        pV2 = vertexArr[meshRealIndex];//add by light director
        meshRealIndex = meshIdxVec->indexVect.at(7) - 1 ;
        indicesQuad.append(meshRealIndex);
        pV3 = vertexArr[meshRealIndex];//add by light director
        ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
        //face3
        meshRealIndex = meshIdxVec->indexVect.at(2) - 1 ;
        indicesQuad.append(meshRealIndex);
        pV0 = vertexArr[meshRealIndex];//add by light director
        meshRealIndex = meshIdxVec->indexVect.at(7) - 1 ;
        indicesQuad.append(meshRealIndex);
        pV1 = vertexArr[meshRealIndex];//add by light director
        meshRealIndex = meshIdxVec->indexVect.at(6) - 1 ;
        indicesQuad.append(meshRealIndex);
        pV2 = vertexArr[meshRealIndex];//add by light director
        meshRealIndex = meshIdxVec->indexVect.at(1) - 1 ;
        indicesQuad.append(meshRealIndex);
        pV3 = vertexArr[meshRealIndex];//add by light director
        ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
        //face4
        meshRealIndex = meshIdxVec->indexVect.at(3) - 1 ;
        indicesQuad.append(meshRealIndex);
        pV0 = vertexArr[meshRealIndex];//add by light director
        meshRealIndex = meshIdxVec->indexVect.at(4) - 1 ;
        indicesQuad.append(meshRealIndex);
        pV1 = vertexArr[meshRealIndex];//add by light director
        meshRealIndex = meshIdxVec->indexVect.at(5) - 1 ;
        indicesQuad.append(meshRealIndex);
        pV2 = vertexArr[meshRealIndex];//add by light director
        meshRealIndex = meshIdxVec->indexVect.at(0) - 1 ;
        indicesQuad.append(meshRealIndex);
        pV3 = vertexArr[meshRealIndex];//add by light director
        ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
        //face5
        meshRealIndex = meshIdxVec->indexVect.at(3) - 1 ;
        indicesQuad.append(meshRealIndex);
        pV0 = vertexArr[meshRealIndex];//add by light director
        meshRealIndex = meshIdxVec->indexVect.at(2) - 1 ;
        indicesQuad.append(meshRealIndex);
        pV1 = vertexArr[meshRealIndex];//add by light director
        meshRealIndex = meshIdxVec->indexVect.at(7) - 1 ;
        indicesQuad.append(meshRealIndex);
        pV2 = vertexArr[meshRealIndex];//add by light director
        meshRealIndex = meshIdxVec->indexVect.at(4) - 1 ;
        indicesQuad.append(meshRealIndex);
        pV3 = vertexArr[meshRealIndex];//add by light director
        ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
        //face6
        meshRealIndex = meshIdxVec->indexVect.at(0) - 1 ;
        indicesQuad.append(meshRealIndex);
        pV0 = vertexArr[meshRealIndex];//add by light director
        meshRealIndex = meshIdxVec->indexVect.at(1) - 1 ;
        indicesQuad.append(meshRealIndex);
        pV1 = vertexArr[meshRealIndex];//add by light director
        meshRealIndex = meshIdxVec->indexVect.at(5) - 1 ;
        indicesQuad.append(meshRealIndex);
        pV2 = vertexArr[meshRealIndex];//add by light director
        meshRealIndex = meshIdxVec->indexVect.at(6) - 1 ;
        indicesQuad.append(meshRealIndex);
        pV3 = vertexArr[meshRealIndex];//add by light director
        ComputeNormal(*pV0,*pV1,*pV2,*pV3);//计算四个点锁确定平面的法向量
    }
}

void CubeGeometry::InitCompleteCubeGeometry(QSharedPointer<FEModel> pModel)
{
    this->arrayBuf.bind();
    this->arrayBuf.allocate(pModel->verticesVect.constData(), pModel->verticesVect.size() * sizeof(FEVertex));
    this->arrayBuf.setUsagePattern(QOpenGLBuffer::StaticDraw);

    this->indexBuf.bind();
    this->indexBuf.allocate(indicesQuad.constData(), indicesQuad.size() * sizeof(GLuint));
    this->indexBuf.setUsagePattern(QOpenGLBuffer::StaticDraw);
}

void CubeGeometry::ReleaseRenderData()
{
    this->indicesQuad.clear();

    this->arrayBuf.release();
    this->indexBuf.release();

}
//计算四个点决定的平面的法向量
void CubeGeometry::ComputeNormal(FEVertex &v0, FEVertex &v1, FEVertex &v2, FEVertex &v3)
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


void CubeGeometry::AssignVertexNormal(FEVertex &vert,QVector3D normal)
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
