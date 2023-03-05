#ifndef OPENGLRENDER_H
#define OPENGLRENDER_H

#include "CubeGeometry.h"
#include "Src/FECommon/ExtStruct.h"
//该结构体用来定义观察者视角的相关信息
typedef  struct
{
    float     distance;    //观察者距被观察物体中心点的初始距离
    float     fovy;        //观察者视角的大小
    float     zoom;        //观察者距被观察物体中心点的距离倍数，用于缩放控制
    QVector3D  eye;        //观察者在被观察物体的三维坐标系中的位置
    QVector3D  center;     //被观察物体的中心点坐标，为[0,0,0]
    QVector3D  up;         //观察者的头部朝向
}CameraView;

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGLWindow(QWidget *parent = nullptr);
    ~OpenGLWindow();
    void Rotate(QMatrix4x4 matrix);

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
    void initTextures();
    int setRotation(int angle);
    void normalizeAngle(int &angle);

private:
    CubeGeometry *cubeGeometry;
    QOpenGLShaderProgram *program;
    QMatrix4x4 projection;      //透视矩阵
    QMatrix4x4 m_translation;   //平移矩阵
    QMatrix4x4 m_rotation;   //旋转矩阵
    int m_MouseFlag;         //记录按下的鼠标按键
    bool m_MousePressFlag;   //记录鼠标按键是否已按下
    QPoint mousePressPosition;     //记录鼠标按下时的坐标位置
    CameraView Camera;      //记录观察者视角相关数据
    int m_xRot;   //记录绕x轴旋转的角度
    int m_yRot;   //记录绕y轴旋转的角度
    int m_zRot;   //记录绕z轴旋转的角度
    qreal m_xTrans;  //记录沿x轴移动的位置
    qreal m_yTrans;  //记录沿y轴移动的位置
};

#endif // OPENGLRENDER_H
