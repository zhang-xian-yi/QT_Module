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
    //提交GPU数据
    void Commit();
    //释放模型的缓冲区（所有mesh）
    void RelaseBuffer();
public:
    //模型有所有的顶点数据
    QVector<FEVertex> verticesVect;
    QVector<FEMesh> meshVect;
private:
    QOpenGLBuffer arrayBuf;   //VBO
};

#endif // FEMODEL_H
