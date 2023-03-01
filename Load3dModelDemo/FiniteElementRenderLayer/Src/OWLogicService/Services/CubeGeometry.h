#ifndef DATMANAGER_H
#define DATMANAGER_H
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QMutex>
#include "Src/OWCommon/ExtStruct.h"

struct VertexData
{
    QVector3D position;    //顶点位置
    QVector3D color;       //顶点颜色
    QVector3D normal = {0,0,0};      //定点法线 -- 决定光反射方向 add by zxy
};

enum FaceDirect
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    FRONT,
    BACK,
};

class CubeGeometry : public QOpenGLFunctions
{
public:
    CubeGeometry();
    ~CubeGeometry();

    void drawCubeGeometry(QOpenGLShaderProgram *program);
    void SetRenderData(QVector<InVertex>& vectexArr,QVector<InFaceIndex>& indexArray);
    void InitCompleteCubeGeometry();
    void ReleaseRenderData();

    static CubeGeometry* GetInstance();
private:
    void ComputeNormal(VertexData& v0,VertexData& v1,VertexData& v2,VertexData& v3,FaceDirect direect);
    void AssignVertexNormal(VertexData& vert,QVector3D normal);
private:
    static CubeGeometry* m_pStatInstance;
    QVector<VertexData> verticesVect;
    QVector<GLuint> indicesQuad;
    static QMutex m_oMutex;

    QOpenGLBuffer arrayBuf;   //VBO
    QOpenGLBuffer indexBuf;   //IBO
    GLuint m_nVertexCount;
};

#endif // DATMANAGER_H
