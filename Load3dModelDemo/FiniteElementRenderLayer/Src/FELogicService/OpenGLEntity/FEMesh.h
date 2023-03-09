#ifndef FEMESH_H
#define FEMESH_H

#include "FEVertex.h"

class FEMesh
{
public:
    FEMesh();
public:
    //创建模型顶点缓冲区（所有mesh）--必须在OpenGL上下文之中
    void CreateBuffer();
    //提交GPU数据
    void Commit(QVector<FEVertex>& AllVertexArr ,QVector<uint32_t>& indexArr);
    //释放模型的缓冲区（所有mesh）
    void RelaseBuffer();
public:
    QVector<uint32_t> indexVect;
    //索引缓冲区
    QOpenGLBuffer indexBuf;//IBO


};

#endif // FEMESH_H
