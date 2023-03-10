#ifndef FEMESH_H
#define FEMESH_H

#include "Src/FELogicService/DrawElement/AbstractDE.h"
#include "FEVertex.h"
class FEMesh
{
public:
    FEMesh();
public:
    //创建模型顶点缓冲区（所有mesh）--必须在OpenGL上下文之中
    void CreateBuffer(QVector<FEVertex>& AllVertexArr);
    //绘制
    void Draw(QSharedPointer<QOpenGLShaderProgram> program);
public:
    //此处的索引数组实际上时网格体的所有顶点索引，但因为绘制方式不同,这些顶点个能会产生更多的顶点作为索引进行绘制
    QVector<GLuint> indexVect;//
private:
    QSharedPointer<AbstractDE> m_pDrawEleS;//抽象接口绘制元素
};

#endif // FEMESH_H
