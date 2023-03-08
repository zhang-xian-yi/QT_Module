#ifndef DATMANAGER_H
#define DATMANAGER_H

#include "Src/FELogicService/OpenGLEntity/FEModel.h"

struct VertexData
{
    QVector3D position;    //顶点位置
    QVector3D color;       //顶点颜色
    QVector3D normal = {0,0,0};      //定点法线 -- 决定光反射方向 add by zxy
};


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
    void ComputeNormal(VertexData& v0,VertexData& v1,VertexData& v2,VertexData& v3);
    void AssignVertexNormal(VertexData& vert,QVector3D normal);
private:
    QVector<VertexData> verticesVect;
    QVector<GLuint> indicesQuad;

    QOpenGLBuffer arrayBuf;   //VBO
    QOpenGLBuffer indexBuf;   //IBO
    GLuint m_nVertexCount;

    QString m_strRenderElementName;
};


#endif // DATMANAGER_H
