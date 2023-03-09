#ifndef DECUDE_H
#define DECUDE_H
#include "AbstractDE.h"


//正六边体的绘制
class DECube:public AbstractDE
{
public:
    DECube();
    ~DECube();
    //设置需要渲染的数据(需要计算法向量-所以必须设置渲染数据之后，才能进行渲染)
    virtual void SetRendererData(QVector<FEVertex>& vertexArr,QVector<FEMesh>& meshArr)override;
    // paintGl自动调用
    virtual void Draw(QSharedPointer<QOpenGLShaderProgram> program)override;
private:
    void ComputeNormal(FEVertex& v0,FEVertex& v1,FEVertex& v2,FEVertex& v3);
    void AssignVertexNormal(FEVertex& vert,QVector3D normal);
private:
    QVector<GLuint> indicesQuad;//索引数组
    QOpenGLBuffer indexBuf;   //IBO
};


#endif // DECUDE_H
