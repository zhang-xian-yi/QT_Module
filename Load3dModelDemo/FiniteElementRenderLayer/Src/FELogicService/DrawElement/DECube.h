#ifndef DECUDE_H
#define DECUDE_H
#include "AbstractDE.h"


//正六边体的绘制
class DECube:public AbstractDE
{
public:
    DECube();
    ~DECube();
    // paintGl自动调用
    virtual void Draw(QSharedPointer<QOpenGLShaderProgram> program)override;
    //设置需要渲染的数据(需要计算法向量-所以必须设置渲染数据之后，才能进行渲染)
    virtual QVector<GLuint>& ComputeRendererData(QVector<FEVertex>& allVertexArr,QVector<GLuint>& indexArr)override;
private:
    void ComputeNormal(FEVertex& v0,FEVertex& v1,FEVertex& v2,FEVertex& v3);
    void AssignVertexNormal(FEVertex& vert,QVector3D normal);
private:
    QVector<GLuint> m_indexVect;//真实的索引数组
};


#endif // DECUDE_H
