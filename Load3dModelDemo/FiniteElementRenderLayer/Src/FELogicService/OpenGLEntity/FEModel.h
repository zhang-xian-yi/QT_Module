#ifndef FEMODEL_H
#define FEMODEL_H

#include "FEMesh.h"

class FEModel
{
public:
    FEModel();

public:
    //创建模型顶点缓冲区（所有mesh）--必须在OpenGL上下文之中
    void CreateBuffer();
    //绘制
    void DrawModel(QSharedPointer<QOpenGLShaderProgram> program);
public:
    //模型有所有的顶点数据
    QVector<FEVertex> verticesVect;
    //保存索引的网格数据
    QVector<FEMesh> meshVect;
private:
    QSharedPointer<QOpenGLBuffer> m_pVertexBuf;   //VBO
};

#endif // FEMODEL_H
