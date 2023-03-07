#include "ConvertOpenGLData.h"


QSharedPointer<FEModel> ConvertOpenGLData::Convert(QSharedPointer<FEFileData> pFEFileData)
{
    m_pFEModel = QSharedPointer<FEModel>(new FEModel());

    QVector<QSharedPointer<FEFileVertex>>& FileVertexArr = pFEFileData->GetVertexVector();
    //遍历顶点数组
    foreach (auto pVertex, FileVertexArr)
    {
        QSharedPointer<FEVertex> v = QSharedPointer<FEVertex>(new FEVertex);
        v->position = {(*pVertex)[0],(*pVertex)[1],(*pVertex)[2]};//012 是有限元文件中固定的xyz，3D坐标
        //添加顶点
        m_pFEModel->verticesVect.append(v);
    }

    QVector<QSharedPointer<FEFileMesh>> & FileMeshArr = pFEFileData->GetMeshVector();
    //遍历网格数组
    foreach (auto pMesh, FileMeshArr)
    {
        QSharedPointer<FEMesh> m = QSharedPointer<FEMesh>(new FEMesh);
        m->indexVect = pMesh->indexData;
        //添加网格
        m_pFEModel->meshVect.append(m);
    }
    return m_pFEModel;
}
