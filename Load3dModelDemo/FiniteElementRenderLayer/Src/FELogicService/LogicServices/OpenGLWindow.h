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
    void Rotate(QMatrix4x4 matrix);
    void SetRendererData(QSharedPointer<FEModel> pModel);
public:
    void SetOpenGLEnvInitCallBack(OpenGLEnvInitCallback InitFuncCB);
    void SetOnEventCallBack(OnEventCallBack EventFuncCB);
    void SetGetCallBack(GetMat4Callback Mat4FCB);
    void SetGetCallBack(GetVec3DCallback vec3DFCB);
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    //事件处理函数
    virtual bool eventFilter(QObject* obj,QEvent *e) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    void initShaders();
    int setRotation(int angle);
    void normalizeAngle(int &angle);
private:
    bool isHanldeEvent(QEvent *e);
private:
    OpenGLEnvInitCallback OnGLEnvInit;//定义在initializeGL方法中执行的环境初始化
    OnEventCallBack       OnEvent;//定义在eventFilter方法中执行的事件处理
    DrawCallback          OnDraw;//绘制时调用的回调函数
    GetMat4Callback       GetMVPMat4;//获取mvp矩阵
    GetVec3DCallback      Get3DPos;//获取值
private:
    QSharedPointer<CubeGeometry> m_pDrawEleS;
    QSharedPointer<QOpenGLShaderProgram> program;//着色器
    QSharedPointer<CameraView> m_pCamera;      //记录观察者视角相关数据
    QMatrix4x4 projection;      //透视矩阵
    QMatrix4x4 m_translation;   //平移矩阵
    QMatrix4x4 m_rotation;   //旋转矩阵
    int m_MouseFlag;         //记录按下的鼠标按键
    bool m_MousePressFlag;   //记录鼠标按键是否已按下
    QPoint mousePressPosition;     //记录鼠标按下时的坐标位置

    int m_xRot;   //记录绕x轴旋转的角度
    int m_yRot;   //记录绕y轴旋转的角度
    int m_zRot;   //记录绕z轴旋转的角度
    qreal m_xTrans;  //记录沿x轴移动的位置
    qreal m_yTrans;  //记录沿y轴移动的位置
};

#endif // OPENGLRENDER_H
