#include "EventHandler.h"
#include "Src/FELogicService/DataEntity/CameraView.h"
EventHandler::EventHandler()
{
    this->m_MouseFlag = Qt::NoButton;
    this->m_MousePressFlag = false;
    this->m_xRot = 0;
    this->m_yRot = 0;
    this->m_zRot = 0;
    this->m_xTrans = 0;
    this->m_yTrans = 0;

    //视角初始化
    m_pCamera = QSharedPointer<CameraView>(new CameraView());
    m_pCamera->DefaultConfig();
}

//主要入口处理函数
bool EventHandler::OnEvent(QEvent *e)
{
    if(e->type() == QEvent::Wheel)
    {
        this->wheelEvent(static_cast<QWheelEvent*>(e));
    }
    if(e->type() == QEvent::MouseButtonPress)
    {
        this->mousePressEvent(static_cast<QMouseEvent*>(e));
    }
    if(e->type() == QEvent::MouseButtonRelease)
    {
        this->mouseReleaseEvent(static_cast<QMouseEvent*>(e));
    }
    if(e->type() == QEvent::MouseMove)
    {
        this->mouseMoveEvent(static_cast<QMouseEvent*>(e));
    }

    return true;
}

QMatrix4x4 EventHandler::GetMVPMatrix4()
{
    //此处注意，一定是先将物体进行旋转，再进行平移缩放等其他变换
    //三维空间中的所有变换都是通过矩阵的左乘来实现的（这部分不知道的可单独查资料学习一下哈），因为旋转矩阵是第一个对物体空间坐标进行左乘处理的！
    QMatrix4x4 rotation;
    rotation.rotate(qreal(this->m_zRot)/16.0f, 0.0f, 0.0f, 1.0f);
    rotation.rotate(qreal(this->m_yRot)/16.0f, 0.0f, 1.0f, 0.0f);
    rotation.rotate(qreal(this->m_xRot)/16.0f, 1.0f, 0.0f, 0.0f);
    //计算得到当前旋转矩阵
    rotation = rotation * this->m_rotation;

    QMatrix4x4 viewMat4;
    //得到当前观察者矩阵
    viewMat4.lookAt(m_pCamera->eye, m_pCamera->center, m_pCamera->up);
    viewMat4 = viewMat4 * rotation;
    //得到当前平移矩阵
    QMatrix4x4 tranMat4;
    tranMat4.translate(this->m_xTrans, -1.0 * this->m_yTrans, 0);
    tranMat4 = tranMat4 * this->m_translation;

    //注意缩放，旋转,平移变换，有固定顺序
    return m_projection * viewMat4 * tranMat4;
}

QVector3D EventHandler::Get3DPos()
{
    return m_pCamera->eye;
}

void EventHandler::InitEnv(int width, int height)
{
    this->width = width;
    this->height = height;
}

//处理投影矩阵
void EventHandler::SlotResigzeGLMat4(int w, int h)
{
    this->width = w;
    this->height = h;

    //关联数据
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 0.001, zFar = 1000.0;
    m_projection.setToIdentity();
    // 得到透视矩阵
    m_projection.perspective(m_pCamera->fovy, aspect, zNear, zFar);
}

//缩放控制就是控制观察者的位置到被观察物体中心位置的距离，即改变m_pCamera->eye的值
void EventHandler::wheelEvent(QWheelEvent *event)
{
    if(this->m_MousePressFlag)
        return;
    if(event->angleDelta().y() > 0)
    {
        m_pCamera->zoom -= 0.1;
    }
    else
    {
        m_pCamera->zoom += 0.1;
    }

    if(m_pCamera->zoom >= 3)
    {
        m_pCamera->zoom = 3;
    }
    else if(m_pCamera->zoom <= 0.1)
    {
        m_pCamera->zoom = 0.1;
    }
    //定义的观察者的位置是在z轴上，所以只改变m_pCamera->eye的z值即可实现物体缩放效果
    m_pCamera->eye.setZ(m_pCamera->zoom * m_pCamera->distance);
}
//用于记录按下鼠标的类型并记录鼠标按下时的位置
void EventHandler::mousePressEvent(QMouseEvent *event)
{
    if(event->button() & Qt::LeftButton)
    {
        this->m_MouseFlag = Qt::LeftButton;
    }
    else if(event->button() & Qt::RightButton)
    {
        this->m_MouseFlag = Qt::RightButton;
    }
    else if(event->button() & Qt::MidButton)
    {
        this->m_MouseFlag = Qt::MidButton;
    }
    this->m_MousePressFlag = true;
    this->mousePressPosition = event->pos();
}
//根据鼠标移动的量和鼠标类型进行对应处理操作
void EventHandler::mouseMoveEvent(QMouseEvent *event)
{
    QPoint diff = event->pos() - mousePressPosition;
    if(this->m_MouseFlag == Qt::LeftButton)
    {
        //按下鼠标左键并移动控制被观察物体绕x轴和y轴进行旋转
        this->m_xRot = setRotation(4 * diff.x());
        this->m_yRot = setRotation(4 * diff.y());
    }
    else if(this->m_MouseFlag == Qt::RightButton)
    {
        //按下鼠标右键并移动控制被观察物体绕x轴和z轴进行旋转
        this->m_xRot = setRotation(4 * diff.x());
        this->m_zRot = setRotation(4 * diff.y());
    }
    else if(this->m_MouseFlag == Qt::MidButton)
    {
        //按下鼠标中键（即滚轮）并移动实现被观察物体的拖拽平移
        if(!this->m_MousePressFlag)
            return;
        //以下计算是将在界面内移动鼠标的距离投影到被观察物体的xoy平面内，得到物体实际应该移动的距离
        qreal w_h_ratio = (qreal)(width) / (qreal)(height);
        qreal cube_view_height = 2 * m_pCamera->zoom * m_pCamera->distance * qTan(qDegreesToRadians(m_pCamera->fovy/2));
        qreal cube_view_width = w_h_ratio * cube_view_height;
        this->m_xTrans = cube_view_width / qreal(width) * qreal(diff.x());
        this->m_yTrans = cube_view_height / qreal(height) * qreal(diff.y());
    }
}

//鼠标释放后，记录当前的旋转或平移矩阵
void EventHandler::mouseReleaseEvent(QMouseEvent *event)
{
    if((event->button() & Qt::LeftButton) || (event->button() & Qt::RightButton))
    {
        this->m_MousePressFlag = false;
        QMatrix4x4 m;
        //此处注意，因为欧拉旋转的特性，物体绕三个轴旋转的顺序不同，最终旋转后得到的物体角度是不相同的，所以，每次旋转要保证轴的顺序一致
        m.rotate(qreal(this->m_zRot)/16.0f, 0.0f, 0.0f, 1.0f);
        m.rotate(qreal(this->m_yRot)/16.0f, 0.0f, 1.0f, 0.0f);
        m.rotate(qreal(this->m_xRot)/16.0f, 1.0f, 0.0f, 0.0f);
        this->m_rotation = m * this->m_rotation;
        this->m_xRot = 0;
        this->m_yRot = 0;
        this->m_zRot = 0;
    }
    else if(event->button() & Qt::MidButton)
    {
        this->m_MousePressFlag = false;
        QMatrix4x4 m;
        m.translate(this->m_xTrans, -1.0 *this->m_yTrans, 0);
        this->m_translation = m * this->m_translation;
        this->m_xTrans = 0;
        this->m_yTrans = 0;
    }
}


int EventHandler::setRotation(int angle)
{
    normalizeAngle(angle);
    return angle;
}

void EventHandler::normalizeAngle(int &angle)
{
    while (angle < 0)
    {
        angle += 360 * 16;
    }
    while (angle > 360 * 16)
    {
        angle -= 360 * 16;
    }
}

