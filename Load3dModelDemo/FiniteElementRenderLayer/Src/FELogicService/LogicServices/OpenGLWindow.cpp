#include "OpenGLWindow.h"
#include <QDebug>

OpenGLWindow::OpenGLWindow(QWidget * parent) :
    QOpenGLWidget(parent)
{
    OnGLEnvInit = nullptr;
    OnEvent = nullptr;
    OnDraw = nullptr;
    //设置父控件的大小
    this->setParent(parent);
    this->setGeometry(parent->rect().x(),parent->rect().y(),
                      parent->rect().width(),parent->rect().height());
    //设置为父控件的大小
    this->setAcceptDrops(true);
    this->setFocusPolicy(Qt::StrongFocus);
    //安装事件过滤器
    this->installEventFilter(this);
}

OpenGLWindow::~OpenGLWindow()
{

}

void OpenGLWindow::SetOpenGLEnvInitCallBack(OpenGLEnvInitCallback InitFuncCB)
{
    this->OnGLEnvInit = InitFuncCB;
}

void OpenGLWindow::SetOnEventCallBack(OnEventCallBack EventFuncCB)
{
    this->OnEvent = EventFuncCB;
}

void OpenGLWindow::SetOnDrawCallBack(DrawCallback DrawFCB)
{
    this->OnDraw = DrawFCB;
}

void OpenGLWindow::initializeGL()
{
    glClearColor(0, 0, 0, 1);
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);
    // Enable back face culling
    glEnable(GL_CULL_FACE);

    OnGLEnvInit();//初始化环境 回调函数
}

void OpenGLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //调度其他函数时 其他函数要使用OpenGL的方法注意要加makeCurrent 表示此区域内视作opengl上下文中执行
    makeCurrent();
    this->OnDraw(); //如果为空 可以直接崩溃方便检查
    doneCurrent();
}

//保证界面内物体的显示不受界面纵横比变化而变形
void OpenGLWindow::resizeGL(int w, int h)
{
    emit ResizeGLSig(w,h);
}


bool OpenGLWindow::eventFilter(QObject* obj,QEvent *e)
{
    if(OnEvent != nullptr && obj == this && isHanldeEvent(e))
    {
        //使用回调函数处理
        OnEvent(e);
        update();
    }
    //非处理信号交给父类处理
    return QOpenGLWidget::eventFilter(obj,e);
}

bool OpenGLWindow::isHanldeEvent(QEvent *e)
{
    //特殊处理的事件
    static QList<QEvent::Type> typeList = {QEvent::Type::MouseButtonPress,
                                           QEvent::Type::MouseButtonRelease,
                                           QEvent::Type::MouseMove,
                                           QEvent::Type::Wheel};

    return typeList.contains(e->type());
}

