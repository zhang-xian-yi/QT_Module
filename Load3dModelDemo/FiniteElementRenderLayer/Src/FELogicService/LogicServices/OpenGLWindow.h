#ifndef OPENGLRENDER_H
#define OPENGLRENDER_H

#include "Src/FECommon/MdlDefine.h"
#include "Src/FELogicService/OpenGLEntity/FEScence.h"

class OpenGLWindow : public QOpenGLWidget
{
    Q_OBJECT
public:
    OpenGLWindow(QWidget *parent = nullptr);
    ~OpenGLWindow();
public:
    void SetOpenGLEnvInitCallBack(OpenGLEnvInitCallback InitFuncCB);
    void SetOnEventCallBack(OnEventCallBack EventFuncCB);
    void SetOnDrawCallBack(DrawCallback DrawFCB);
signals:
    void ResizeGLSig(int w,int h);
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    //事件处理函数
    virtual bool eventFilter(QObject* obj,QEvent *e) override;
private:
    bool isHanldeEvent(QEvent *e);
private:
    OpenGLEnvInitCallback OnGLEnvInit;//定义在initializeGL方法中执行的环境初始化
    OnEventCallBack       OnEvent;//定义在eventFilter方法中执行的事件处理
    DrawCallback          OnDraw;//绘制时调用的回调函数
};

#endif // OPENGLRENDER_H
