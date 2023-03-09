#ifndef OPENGLRENDER_H
#define OPENGLRENDER_H

#include "CubeGeometry.h"
#include "Src/FECommon/MdlDefine.h"
#include "Src/FELogicService/OpenGLEntity/FEScence.h"

class OpenGLWindow : public QOpenGLWidget
{
    Q_OBJECT
public:
    OpenGLWindow(QWidget *parent = nullptr);
    ~OpenGLWindow();
    void SetRendererData(QSharedPointer<FEModel> pModel);
public:
    void SetOpenGLEnvInitCallBack(OpenGLEnvInitCallback InitFuncCB);
    void SetOnEventCallBack(OnEventCallBack EventFuncCB);
    void SetGetCallBack(GetMat4Callback Mat4FCB);
    void SetGetCallBack(GetVec3DCallback vec3DFCB);
signals:
    void ResizeGLSig(int w,int h);
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    //事件处理函数
    virtual bool eventFilter(QObject* obj,QEvent *e) override;
private:
    void initShaders();
    bool isHanldeEvent(QEvent *e);
private:
    OpenGLEnvInitCallback OnGLEnvInit;//定义在initializeGL方法中执行的环境初始化
    OnEventCallBack       OnEvent;//定义在eventFilter方法中执行的事件处理
    DrawCallback          OnDraw;//绘制时调用的回调函数
    GetMat4Callback       GetMVPMat4;//获取mvp矩阵
    GetVec3DCallback      Get3DPos;//获取视角
private:
    QSharedPointer<CubeGeometry> m_pDrawEleS;
    QSharedPointer<QOpenGLShaderProgram> program;//着色器
    QSharedPointer<CameraView> m_pCamera;      //记录观察者视角相关数据
};

#endif // OPENGLRENDER_H
