#ifndef DATMANAGER_H
#define DATMANAGER_H


#include "../Common/Src/ExtStruct.h"

struct VertexData
{
    QVector3D position;    //顶点位置
    QVector3D color;       //顶点颜色
    QVector3D normal;      //定点法线 -- 决定光反射方向 add by zxy
};

class CubeGeometry : public QOpenGLFunctions
{
public:
    CubeGeometry();
    ~CubeGeometry();

    void drawCubeGeometry(QOpenGLShaderProgram *program);
    void SetRenderData(QVector<CommonNS::InVertex>& vectexArr,QVector<CommonNS::InFaceIndex>& indexArray);
    void InitCompleteCubeGeometry();

    static CubeGeometry* GetInstance();
private:
    static CubeGeometry* m_pStatInstance;
    QVector<VertexData> verticesVect;
    QVector<GLushort> indicesQuad;
    static QMutex m_oMutex;

    QOpenGLBuffer arrayBuf;   //VBO
    QOpenGLBuffer indexBuf;   //IBO
    int m_nVertexCount;
};


#endif // DATMANAGER_H
