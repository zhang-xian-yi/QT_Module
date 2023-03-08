#ifndef DATMANAGER_H
#define DATMANAGER_H

#include "Src/FELogicService/OpenGLEntity/FEModel.h"


class CubeGeometry
{
public:
    CubeGeometry();
    ~CubeGeometry();

    // 界面paintGl自动调用
    void drawCubeGeometry(QSharedPointer<QOpenGLShaderProgram> program);
    // 更新立体数据
    void UpdateCubeGeometry(QSharedPointer<FEModel> m_pModel);
protected:
    void SetRenderData(QVector<QSharedPointer<FEVertex>>& vertexArr,QVector<QSharedPointer<FEMesh>>& meshArr);
    void InitCompleteCubeGeometry();
    void ReleaseRenderData();
private:
    void ComputeNormal(FEVertex& v0,FEVertex& v1,FEVertex& v2,FEVertex& v3);
    void AssignVertexNormal(FEVertex& vert,QVector3D normal);
private:
    QVector<FEVertex> verticesVect;
    QVector<GLuint> indicesQuad;

    QOpenGLBuffer arrayBuf;   //VBO
    QOpenGLBuffer indexBuf;   //IBO
};


#endif // DATMANAGER_H
