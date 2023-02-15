#include "OpenGLWindowsLayerService.h"
#include "Entity/Model/ModelLoader.h"
#include "Src/OWCommon/GlobalData.h" //LogLv 与pGLFunc 引入
OpenGLWindowsLayerService::OpenGLWindowsLayerService(QWidget * parent):
    m_pScene(nullptr)
{
    m_openGLWindow = new OpenGLWindow;//由QT父级控件控制释放
    m_openGLWindow->setRenderer(new OpenGLRenderer);//由QT父级控件控制释放

    //设置为父控件的大小
    m_openGLWindow->setParent(parent);
    m_openGLWindow->setGeometry(parent->rect().x(),parent->rect().y(),
                      parent->rect().width(),parent->rect().height());

    m_openGLWindow->setAcceptDrops(true);
    m_openGLWindow->setFocusPolicy(Qt::StrongFocus);


}

OpenGLWindowsLayerService::~OpenGLWindowsLayerService()
{
    m_openGLWindow = nullptr; //由QT父控件控制
}


void OpenGLWindowsLayerService::CreateScene() {
    if (m_pScene) {
        delete m_pScene;
        m_pScene = nullptr;
    }

    m_pScene = new Scene();
    m_pScene->addDirectionalLight(new DirectionalLight(QVector3D(1, 1, 1), QVector3D(-2, -4, -3)));//增加方向光
    //m_pScene->addGridline(new Gridline); 增加网格线

    m_openGLWindow->setScene(new OpenGLScene(m_pScene));
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

