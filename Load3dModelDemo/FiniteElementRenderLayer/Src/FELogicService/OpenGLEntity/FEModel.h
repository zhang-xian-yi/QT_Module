#ifndef FEMODEL_H
#define FEMODEL_H

#include "FEMesh.h"


class FEModel
{
public:
    FEModel();

public:
    //提交指定数据
    void Commit();
    //绘制
    void DrawModel(QSharedPointer<QOpenGLShaderProgram> program);
public:
    //模型有所有的顶点数据
    QVector<FEVertex> verticesVect;
    //保存索引的网格数据
    QVector<FEMesh> meshVect;
private:
    QSharedPointer<QOpenGLVertexArrayObject> m_vao;
    QSharedPointer<QOpenGLBuffer> m_pVertexBuf;   //VBO
    QSharedPointer<QOpenGLBuffer> m_pIndexBuf;   //VBO
    QVector<GLuint> m_indexVect;//索引缓冲区
};

#endif // FEMODEL_H
