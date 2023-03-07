#ifndef DATMANAGER_H
#define DATMANAGER_H

#include "Src/FELogicService/OpenGLEntity/FEModel.h"

class CubeGeometry
{
public:
    CubeGeometry();
    ~CubeGeometry();
    // 界面paintGl自动调用
    void drawCubeGeometry(QOpenGLShaderProgram *program);
public:
    void InitCompleteCubeGeometry(QSharedPointer<FEModel> pModel);
    void ReleaseRenderData();
    void SetRenderData(QSharedPointer<FEModel> pModel);
private:
    void ComputeNormal(FEVertex& v0,FEVertex& v1,FEVertex& v2,FEVertex& v3);
    void AssignVertexNormal(FEVertex& vert,QVector3D normal);
private:
    QVector<uint32_t> indexQuad;

    QOpenGLBuffer arrayBuf;   //VBO
    QOpenGLBuffer indexBuf;   //IBO
};

#endif // DATMANAGER_H
