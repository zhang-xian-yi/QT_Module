#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

class CameraView;

class EventHandler:public QObject
{
    Q_OBJECT
public:
    EventHandler();
public:
    bool OnEvent(QEvent* e);
    //获取经过事件处理后的MVP矩阵
    QMatrix4x4 GetMVPMatrix4();
    QVector3D Get3DPos();
    void InitEnv(int width,int height);
signals:
    void SigWheelAngle(int angle);
public:
    void SlotResigzeGLMat4(int w,int h);
private:
    void wheelEvent(QWheelEvent *event) ;
    void mousePressEvent(QMouseEvent *event) ;
    void mouseMoveEvent(QMouseEvent *event) ;
    void mouseReleaseEvent(QMouseEvent *event) ;
private:
    int  setRotation(int angle);
    void normalizeAngle(int &angle);
private:
    QMatrix4x4 m_projection;    //透视矩阵
    QMatrix4x4 m_translation;   //平移矩阵
    QMatrix4x4 m_rotation;      //旋转矩阵

    int m_MouseFlag;         //记录按下的鼠标按键
    bool m_MousePressFlag;   //记录鼠标按键是否已按下
    QPoint mousePressPosition;     //记录鼠标按下时的坐标位置

    int m_xRot;   //记录绕x轴旋转的角度
    int m_yRot;   //记录绕y轴旋转的角度
    int m_zRot;   //记录绕z轴旋转的角度

    qreal m_xTrans;  //记录沿x轴移动的位置
    qreal m_yTrans;  //记录沿y轴移动的位置

    //视角
    QSharedPointer<CameraView> m_pCamera;

    uint32_t width;     //窗口宽度
    uint32_t height;    //窗口高度
};

#endif // EVENTHANDLER_H
