#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "Src/FECommon/MdlDefine.h"
#include "Src/FELogicService/OpenGLEntity/FEScence.h"
//OpenGL渲染业务
class OpenGLRenderer: public QObject
{
    Q_OBJECT
public:
    OpenGLRenderer();
public:
    //必须在OpenGL 的环境下进行初始化
    void InitEnv();
    //设置回调函数
    void SetGetCallBack(GetMat4Callback Mat4FCB);
    void SetGetCallBack(GetVec3DCallback vec3DFCB);
public slots:
    //设置渲染数据
    void SetRendererDataSlot(QSharedPointer<FEModel> pModel);
public:
    void Draw();//进行数据绘制
private:
    void initShaders();
private:
    GetMat4Callback       GetMVPMat4;//获取mvp矩阵
    GetVec3DCallback      Get3DPos;//获取视角
private:
    QSharedPointer<FEScence>         m_pScene;
    QSharedPointer<QOpenGLShaderProgram> m_pShaderProgram;//着色器
};

#endif // OPENGLRENDERER_H
