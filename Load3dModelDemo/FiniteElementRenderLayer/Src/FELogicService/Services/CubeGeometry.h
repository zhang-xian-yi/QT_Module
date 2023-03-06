#ifndef DATMANAGER_H
#define DATMANAGER_H

#include "Src/FECommon/ExtStruct.h"

struct VertexData
{
    QVector3D position;    //顶点位置
    QVector3D color;       //顶点颜色
    QVector3D normal = {0,0,0};      //定点法线 -- 决定光反射方向 add by zxy
};

enum FaceDirect
{
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    FRONT,
    BACK,
};

class CubeGeometry
{
public:
    CubeGeometry();
    ~CubeGeometry();

    static CubeGeometry* GetInstance();
    // 界面paintGl自动调用
    void drawCubeGeometry(QOpenGLShaderProgram *program);
public:
    void SetRenderData(InVertex &vectexArr, QVector<InFaceIndex>& indexArray);
    void InitCompleteCubeGeometry();
    void ReleaseRenderData();
private:
    void ComputeNormal(VertexData& v0,VertexData& v1,VertexData& v2,VertexData& v3,FaceDirect direect);
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
