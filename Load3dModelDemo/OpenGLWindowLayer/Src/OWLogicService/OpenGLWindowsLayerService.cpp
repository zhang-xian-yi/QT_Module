#include "OpenGLWindowsLayerService.h"
#include "Entity/Model/ModelLoader.h"
#include "Src/OWCommon/GlobalData.h" //LogLv 与pGLFunc 引入
OpenGLWindowsLayerService::OpenGLWindowsLayerService(QWidget * parent):
    m_pScene(nullptr)
{
    m_openGLWindow = QSharedPointer<OpenGLWindow>(new OpenGLWindow);//由QT父级控件控制释放
    m_openGLWindow->setRenderer(QSharedPointer<OpenGLRenderer>(new OpenGLRenderer));//由QT父级控件控制释放

    //设置为父控件的大小
    m_openGLWindow->setParent(parent);
    m_openGLWindow->setGeometry(parent->rect().x(),parent->rect().y(),
                      parent->rect().width(),parent->rect().height());

    m_openGLWindow->setAcceptDrops(true);
    m_openGLWindow->setFocusPolicy(Qt::StrongFocus);


}

OpenGLWindowsLayerService::~OpenGLWindowsLayerService()
{
    m_pScene = nullptr;//减少引用计数
    m_openGLWindow = nullptr; //减少引用技术由QT父控件控制
    if (logLV == DEBUG_DESTORY_INFO)
        dout << "OpenGLWindowsLayerService is destroyed";
}


void OpenGLWindowsLayerService::CreateScene() {

    m_pScene = QSharedPointer<Scene>(new Scene);
    m_pScene->addDirectionalLight(new DirectionalLight(QVector3D(1, 1, 1), QVector3D(-2, -4, -3)));//增加方向光
    //m_pScene->addGridline(new Gridline); 增加网格线

    auto GLScene = QSharedPointer<OpenGLScene>(new OpenGLScene(m_pScene));
    m_openGLWindow->setScene(GLScene);
}

void OpenGLWindowsLayerService::ImportModelFile(QString& filepath)
{
    ModelLoader loader;
    Model* model = loader.loadModelFromFile(filepath);

    if (loader.hasErrorLog()) {
        QString log = loader.errorLog();
        QMessageBox::critical(0, "Error", log);
        if (logLV >= LOG_LEVEL_ERROR)
            dout << log;
    }

    if (m_pScene && model) m_pScene->addModel(model);
}

