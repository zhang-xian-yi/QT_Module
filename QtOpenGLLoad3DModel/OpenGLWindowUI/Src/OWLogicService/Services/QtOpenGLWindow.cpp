#include "QtOpenGLWindow.h"
#include "OpenGLWindowUI/Src/OWCommon/MacroDefine.h"
#include "OpenGLWindowUI/Src/OWCommon/OWGlobalData.h"
#include <QDebug>
namespace OpenGLWinNS {

    QtOpenGLWindow::QtOpenGLWindow(QWidget *parent)
        :QOpenGLWidget(parent)
    {
        //设置显示区域与控件大小相同
        this->setGeometry(parent->rect().x(),parent->rect().y(),
                          parent->rect().width(),parent->rect().height());

        m_pTimer = new QTimer();
        //定时渲染
        connect(m_pTimer,SIGNAL(timeout()),SLOT(onRenderTimerShot()));

        m_pTimer->start(20);

        m_lastCursorPos = QCursor::pos();
        m_enableMousePicking = true;
        m_renderer = 0;
        m_openGLScene = 0;
        m_fpsCounter = new FPSCounter(this);
        m_customRenderingLoop = 0;
    }

    QtOpenGLWindow::~QtOpenGLWindow()
    {
        if(m_pTimer)
        {
            m_pTimer->stop();
            delete m_pTimer;
            m_pTimer = NULL;
        }
    }

    void QtOpenGLWindow::setScene(OpenGLScene *openGLScene)
    {
        if (m_openGLScene)
            disconnect(m_openGLScene, 0, this, 0);
        m_openGLScene = openGLScene;
        if (m_openGLScene)
            connect(m_openGLScene, SIGNAL(destroyed(QObject*)), this, SLOT(sceneDestroyed(QObject*)));
    }

    void QtOpenGLWindow::setRenderer(OpenGLRenderer *renderer)
    {
        m_renderer = renderer;
        if (isInitialized() && m_renderer) {
            m_renderer->reloadShaders();
            if (m_renderer->hasErrorLog()) {
                QString log = m_renderer->errorLog();
                QMessageBox::critical(0, "Failed to load shaders", log);
                if (OpenGLWinNS::OWGlobalData::GetInstance().log_level  >= LOG_LEVEL_ERROR)
                    dout << log;
            }
        }
    }

    void QtOpenGLWindow::setEnableMousePicking(bool enabled)
    {
        m_enableMousePicking = enabled;
    }

    void QtOpenGLWindow::setCustomRenderingLoop(void (*customRenderingLoop)(Scene *))
    {
        m_customRenderingLoop = customRenderingLoop;
    }

    //错误回调函数
    static void GLFWErrorCallback(int error, const char* description)
    {
        qDebug("error:{0},desc:{1}",error,description);
    }

    void QtOpenGLWindow::initializeGL()
    {
        initializeOpenGLFunctions();//必须加入否则报错 ASSERT: "QOpenGLFunctions::isInitialized(d_ptr)"

        /* Initialize the library */
        if (!glfwInit())
        {
            return ;
        }
        //设置错误日志回调函数
        glfwSetErrorCallback(GLFWErrorCallback);

        // Decide GL+GLSL versions
        // GL 3.0 + GLSL 130
        //const char* glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

        //获取加载
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        //必须获取opengl的上下文
        if (status == 0)
        {
            return ;
        }
    }

    void QtOpenGLWindow::resizeGL(int w, int h)
    {
        //this->glViewport(0,0,w,h);
    }

    void QtOpenGLWindow::paintGL()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void QtOpenGLWindow::onRenderTimerShot()
    {

    }



}

