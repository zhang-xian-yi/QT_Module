#include "OpenGLWindow.h"
#include <QDebug>
#include "Src/FELogicService/OpenGLEntity/Material.h"//材质

OpenGLWindow::OpenGLWindow(QWidget * parent) :
    QOpenGLWidget(parent),m_pDrawEleS(nullptr)
{
    OnGLEnvInit = nullptr;
    OnEvent = nullptr;
    GetMVPMat4 = nullptr;
    Get3DPos = nullptr;

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
    makeCurrent();
    m_pDrawEleS.clear();
    doneCurrent();
}

void OpenGLWindow::SetRendererData(QSharedPointer<FEModel> pModel)
{
    m_pDrawEleS->UpdateCubeGeometry(pModel);
}

void OpenGLWindow::SetOpenGLEnvInitCallBack(OpenGLEnvInitCallback InitFuncCB)
{
    this->OnGLEnvInit = InitFuncCB;
}

void OpenGLWindow::SetOnEventCallBack(OnEventCallBack EventFuncCB)
{
    this->OnEvent = EventFuncCB;
}

void OpenGLWindow::SetGetCallBack(GetMat4Callback Mat4FCB)
{
    this->GetMVPMat4 = Mat4FCB;
}

void OpenGLWindow::SetGetCallBack(GetVec3DCallback vec3DFCB)
{
    this->Get3DPos = vec3DFCB;
}

void OpenGLWindow::initializeGL()
{
    glClearColor(0, 0, 0, 1);
    initShaders();
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);
    // Enable back face culling
    glEnable(GL_CULL_FACE);

    m_pDrawEleS = QSharedPointer<CubeGeometry>(new CubeGeometry());
}

void OpenGLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program->setUniformValue("mvp_matrix", this->GetMVPMat4());
    // add by light
    program->setUniformValue("viewPos", this->Get3DPos());
    // 设定灯光位置与颜色
    program->setUniformValue("light1.position", QVector3D({10,10,0}));
    program->setUniformValue("light1.color", QVector3D({255.0,255.0,255.0}));

    Material material(0.1f,0.9f,0.5f,16);
    // 设定材质
    program->setUniformValue("material.ambient", material.ambient);
    program->setUniformValue("material.diffuse", material.diffuse);
    program->setUniformValue("material.specular",  material.specular);
    program->setUniformValue("material.shininess", material.shininess);

    //调度其他函数时 其他函数要使用OpenGL的方法注意要加makeCurrent 表示此区域内视作opengl上下文中执行
    makeCurrent();
    m_pDrawEleS->drawCubeGeometry(program);
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

//编译着色器并连接绑定
void OpenGLWindow::initShaders()
{
    program = QSharedPointer<QOpenGLShaderProgram>(new QOpenGLShaderProgram());
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Res/shaders/basic.vert");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Res/shaders/basic.frag");
    if(!program->link())
    {
        qDebug()<<"shader linkes error";
    }

    if(!program->bind())
    {
        qDebug()<<"shader bind error";
    }
}


