#ifndef ABSTRACTDE_H
#define ABSTRACTDE_H

#include "Src/FELogicService/OpenGLEntity/FEVertex.h"

class AbstractDE
{
public:
    //设置渲染数据 注意必须为实际结构体，而不是指针
    virtual void SetRendererData(QVector<FEVertex>& vertexArr,QVector<GLuint>& meshArr) = 0;
    // 界面paintGl自动调用
    virtual void Draw(QSharedPointer<QOpenGLShaderProgram> program) = 0;
};


#endif // ABSTRACTDE_H
