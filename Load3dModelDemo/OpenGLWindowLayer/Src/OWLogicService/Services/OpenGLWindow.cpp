#include "OpenGLWindow.h"
#include "Model/ModelLoader.h"
#include "Src/OWCommon/GlobalData.h" //LogLv 与pGLFunc 引入
OpenGLWindow::OpenGLWindow() {
    m_lastCursorPos = QCursor::pos();
    m_enableMousePicking = true;
    m_renderer = 0;
    m_openGLScene = 0;
    m_customRenderingLoop = 0;
    configSignals();
}


OpenGLWindow::~OpenGLWindow()
{
    if(m_renderer)
    {
        delete m_renderer;
        m_renderer = nullptr;
    }
}

OpenGLWindow::OpenGLWindow(OpenGLScene * openGLScene, OpenGLRenderer * renderer) {
    m_lastCursorPos = QCursor::pos();
    m_enableMousePicking = true;
    m_renderer = renderer;
    m_openGLScene = openGLScene;
    m_customRenderingLoop = 0;
    configSignals();
}

void OpenGLWindow::setScene(OpenGLScene* openGLScene)
{
    if (m_openGLScene)
    {
        disconnect(m_openGLScene, 0, this, 0);
    }
    m_openGLScene = openGLScene;
    configSignals();
}

void OpenGLWindow::setRenderer(OpenGLRenderer * renderer)
{
    m_renderer = renderer;
    if (isInit() && m_renderer)
    {
        m_renderer->reloadShaders();
        if (m_renderer->hasErrorLog())
        {
            QString log = m_renderer->errorLog();
            QMessageBox::critical(0, "Failed to load shaders", log);
            if (logLV >= LOG_LEVEL_ERROR)
                dout << log;
        }
    }
}

void OpenGLWindow::setEnableMousePicking(bool enabled) {
    m_enableMousePicking = enabled;
}

void OpenGLWindow::setCustomRenderingLoop(void (*customRenderingLoop)(Scene*)) {
    m_customRenderingLoop = customRenderingLoop;
}

void OpenGLWindow::initializeGL() {
    GlobalData::GetInstance().InitOpenGLFunc();//初始化OpenGL函数
    pGlFuncs->glEnable(GL_DEPTH_TEST);

    if (m_renderer)
    {
        m_renderer->reloadShaders();
        if (m_renderer->hasErrorLog())
        {
            QString log = m_renderer->errorLog();
            QMessageBox::critical(0, "Failed to load shaders", log);
            if (logLV >= LOG_LEVEL_ERROR)
                dout << log;
        }
    }
    else
    {
        QMessageBox::critical(0, "Failed to initialize OpenGL", "No renderer specified.");
        if (logLV >= LOG_LEVEL_ERROR)
            dout << "No renderer specified";
    }
}

void OpenGLWindow::paintGL() {
    pGlFuncs->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    pGlFuncs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    processUserInput();

    if (m_renderer && m_openGLScene && m_openGLScene->host()->camera()) {
        if (m_customRenderingLoop)
            m_customRenderingLoop(m_openGLScene->host());

        m_openGLScene->host()->camera()->setAspectRatio(float(width()) / height());
        m_openGLScene->commitCameraInfo();
        m_openGLScene->commitLightInfo();

        if (!m_keyPressed[Qt::LeftButton] && m_enableMousePicking)
        {
            //获取鼠标点击所对应的位置
            uint32_t pickingID = m_renderer->pickingPass(m_openGLScene, mapFromGlobal(QCursor::pos()) * devicePixelRatioF());
            //获取点击位置上的mesh
            OpenGLMesh* pickedOpenGLMesh = m_openGLScene->pick(pickingID);
            //如果点击mesh存在
            if (pickedOpenGLMesh)
            {
                //设置模型高亮
                pickedOpenGLMesh->host()->setHighlighted(true);
            }
            else if (Mesh::getHighlighted())//但模型高亮（已被选中）
            {
                //取消高亮
                Mesh::getHighlighted()->setHighlighted(false);
            }
        }
        //渲染场景
        m_renderer->render(m_openGLScene);
    }
}

bool OpenGLWindow::event(QEvent * event) {
    if (QOpenGLWidget::event(event)) return true;
    if (!m_openGLScene) return false;
    //重新绘制事件


    //鼠标事件
    if (event->type() == QEvent::DragEnter)
    {
        QDragEnterEvent* dragEnterEvent = static_cast<QDragEnterEvent*>(event);
        if (dragEnterEvent->mimeData()->hasUrls())
            dragEnterEvent->acceptProposedAction();
        event->accept();
        return true;
    }
    else if (event->type() == QEvent::DragMove)
    {
        QDragMoveEvent* dragMoveEvent = static_cast<QDragMoveEvent*>(event);
        if (dragMoveEvent->mimeData()->hasUrls())
            dragMoveEvent->acceptProposedAction();
        event->accept();
        return true;
    }
    else if (event->type() == QEvent::Drop)
    {
        QDropEvent* dropEvent = static_cast<QDropEvent*>(event);
        foreach(const QUrl &url, dropEvent->mimeData()->urls())
        {
            ModelLoader loader;
            Model* model = loader.loadModelFromFile(url.toLocalFile());

            if (loader.hasErrorLog())
            {
                QString log = loader.errorLog();
                QMessageBox::critical(0, "Error", log);
                if (logLV >= LOG_LEVEL_ERROR)
                    dout << log;
            }

            if (model) m_openGLScene->host()->addModel(model);
        }
        event->accept();
        return true;
    }
    return false;
}

void OpenGLWindow::keyPressEvent(QKeyEvent * event) {
    m_keyPressed[event->key()] = true;
    event->accept();
}

void OpenGLWindow::keyReleaseEvent(QKeyEvent * event) {
    m_keyPressed[event->key()] = false;
    event->accept();
}

void OpenGLWindow::mousePressEvent(QMouseEvent * event) {
    if (!m_openGLScene || event->button() != Qt::LeftButton) return;

    m_lastCursorPos = mapFromGlobal(QCursor::pos());
    m_lastMousePressTime = QTime::currentTime();
    m_keyPressed[event->button()] = true;
    event->accept();

    if (Mesh::getHighlighted() && Mesh::getHighlighted()->isGizmo())
        m_openGLScene->host()->transformGizmo()->setTransformAxis(Mesh::getHighlighted());
}

void OpenGLWindow::mouseReleaseEvent(QMouseEvent * event) {
    if (!m_openGLScene || event->button() != Qt::LeftButton) return;

    m_keyPressed[event->button()] = false;
    m_openGLScene->host()->transformGizmo()->setTransformAxis(TransformGizmo::None);
    event->accept();

    if (m_lastMousePressTime.msecsTo(QTime::currentTime()) < 200) { // click
        if (Mesh::getHighlighted()) {
            if (!Mesh::getHighlighted()->isGizmo()) {
                Mesh::getHighlighted()->setSelected(true);
                m_openGLScene->host()->transformGizmo()->bindTo(Mesh::getSelected());
            }
        } else if (Mesh::getSelected()) {
            Mesh::getSelected()->setSelected(false);
            m_openGLScene->host()->transformGizmo()->unbind();
        }
    }
}

void OpenGLWindow::wheelEvent(QWheelEvent * event) {
    if (!m_openGLScene) return;

    if (!event->pixelDelta().isNull())
        m_openGLScene->host()->camera()->moveForward(event->pixelDelta().y());
    else if (!event->angleDelta().isNull())
        m_openGLScene->host()->camera()->moveForward(event->angleDelta().y());

    event->accept();
}

void OpenGLWindow::focusOutEvent(QFocusEvent *) {
    for (int i = 0; i < m_keyPressed.keys().size(); i++)
        m_keyPressed[m_keyPressed.keys()[i]] = false;
}

void OpenGLWindow::processUserInput() {
    if (!m_openGLScene || !m_openGLScene->host()->camera()) return;

    float shift = 1.0f;
    if (m_keyPressed[Qt::Key_Shift]) shift *= 5.0f;
    //视角移动
    if (m_keyPressed[Qt::Key_W]) m_openGLScene->host()->camera()->moveForward(shift);
    if (m_keyPressed[Qt::Key_S]) m_openGLScene->host()->camera()->moveForward(-shift);
    if (m_keyPressed[Qt::Key_A]) m_openGLScene->host()->camera()->moveRight(-shift);
    if (m_keyPressed[Qt::Key_D]) m_openGLScene->host()->camera()->moveRight(shift);
    if (m_keyPressed[Qt::Key_Q]) m_openGLScene->host()->camera()->moveUp(-shift);
    if (m_keyPressed[Qt::Key_E]) m_openGLScene->host()->camera()->moveUp(shift);
    //变换轴变换
    if (m_keyPressed[Qt::Key_1]) m_openGLScene->host()->transformGizmo()->setTransformMode(TransformGizmo::Translate);
    if (m_keyPressed[Qt::Key_2]) m_openGLScene->host()->transformGizmo()->setTransformMode(TransformGizmo::Rotate);
    if (m_keyPressed[Qt::Key_3]) m_openGLScene->host()->transformGizmo()->setTransformMode(TransformGizmo::Scale);
    //用户输入的鼠标相应
    if (m_keyPressed[Qt::LeftButton]) {
        QPoint cntCursorPos = mapFromGlobal(QCursor::pos());
        TransformGizmo* gizmo = m_openGLScene->host()->transformGizmo();
        if (gizmo->visible() && gizmo->transformAxis() != TransformGizmo::None) {
            gizmo->drag(m_lastCursorPos, cntCursorPos,
                        width(), height(),
                        m_openGLScene->host()->camera()->projectionMatrix(),
                        m_openGLScene->host()->camera()->viewMatrix());
        } else {
            m_openGLScene->host()->camera()->turnLeft((m_lastCursorPos.x() - cntCursorPos.x()) / 10.0f);
            m_openGLScene->host()->camera()->lookUp((m_lastCursorPos.y() - cntCursorPos.y()) / 10.0f);
        }
        m_lastCursorPos = cntCursorPos;
    }
}

void OpenGLWindow::configSignals() {
    //关键代码，联通用户操作域ui刷新的方式
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
    if(m_openGLScene)
    {
        connect(m_openGLScene, SIGNAL(destroyed(QObject*)), this, SLOT(sceneDestroyed(QObject*)));
        //设置坐标轴永远在上
        m_openGLScene->host()->transformGizmo()->setAlwaysOnTop(false);
    }
}

void OpenGLWindow::sceneDestroyed(QObject *) {
    m_openGLScene = nullptr;
}

