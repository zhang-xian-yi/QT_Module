#ifndef OPENGLRENDER_H
#define OPENGLRENDER_H

#include "CubeGeometry.h"
#include "Src/FELogicService/OpenGLEntity/FEModel.h"
#include "Src/FELogicService/OpenGLEntity/CameraView.h"

class OpenGLWindow : public QOpenGLWidget
{
    Q_OBJECT
public:
    OpenGLWindow(QWidget *parent = nullptr);
    ~OpenGLWindow();
    void Rotate(QMatrix4x4 matrix);
    void SetRendererData(QSharedPointer<FEModel> pModel);
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void initShaders();
    int setRotation(int angle);
    void normalizeAngle(int &angle);

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
