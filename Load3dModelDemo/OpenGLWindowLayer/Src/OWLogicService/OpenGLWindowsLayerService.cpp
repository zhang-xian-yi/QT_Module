#include "OpenGLWindowsLayerService.h"
#include "Entity/Model/ModelLoader.h"
#include "Src/OWCommon/GlobalData.h" //LogLv 与pGLFunc 引入
OpenGLWindowsLayerService::OpenGLWindowsLayerService(QWidget * parent):
    m_pScene(nullptr)
{
    m_openGLWindow = new OpenGLWindow;//由QT父级控件控制释放
    m_openGLWindow->setRenderer(new OpenGLRenderer);//由QT父级控件控制释放

    //设置为父控件的大小
    m_pWidgetWin = QWidget::createWindowContainer(m_openGLWindow);//由QT父级控件控制释放
    m_pWidgetWin->setParent(parent);
    m_pWidgetWin->setGeometry(parent->rect().x(),parent->rect().y(),
                      parent->rect().width(),parent->rect().height());

    m_pWidgetWin->setAcceptDrops(true);
    m_pWidgetWin->setFocusPolicy(Qt::StrongFocus);
}

OpenGLWindowsLayerService::~OpenGLWindowsLayerService()
{
    if (m_pScene) {
        delete m_pScene;
        m_pScene = nullptr;
    }
}


void OpenGLWindowsLayerService::CreateScene() {
    if (m_pScene) {
        delete m_pScene;
        m_pScene = nullptr;
    }

    m_pScene = new Scene();
    m_pScene->addGridline(new Gridline);
    m_pScene->addDirectionalLight(new DirectionalLight(QVector3D(1, 1, 1), QVector3D(-2, -4, -3)));

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

void OpenGLWindowsLayerService::polygonAssignMaterial() {
    if (AbstractEntity::getSelected() && AbstractEntity::getSelected()->isMesh())
        static_cast<Mesh*>(AbstractEntity::getSelected())->setMaterial(new Material);
    else
        QMessageBox::critical(0, "Error", "Select a mesh to do this operation.");
}

void OpenGLWindowsLayerService::polygonReverseNormals() {
    if (AbstractEntity::getSelected() && AbstractEntity::getSelected()->isModel())
        static_cast<Model*>(AbstractEntity::getSelected())->reverseNormals();
    else if (AbstractEntity::getSelected() && AbstractEntity::getSelected()->isMesh())
        static_cast<Mesh*>(AbstractEntity::getSelected())->reverseNormals();
    else
        QMessageBox::critical(0, "Error", "Select a model/mesh to do this operation.");
}

void OpenGLWindowsLayerService::polygonReverseTangents() {
    if (AbstractEntity::getSelected() && AbstractEntity::getSelected()->isModel())
        static_cast<Model*>(AbstractEntity::getSelected())->reverseTangents();
    else if (AbstractEntity::getSelected() && AbstractEntity::getSelected()->isMesh())
        static_cast<Mesh*>(AbstractEntity::getSelected())->reverseTangents();
    else
        QMessageBox::critical(0, "Error", "Select a model/mesh to do this operation.");
}

void OpenGLWindowsLayerService::polygonReverseBitangents() {
    if (AbstractEntity::getSelected() && AbstractEntity::getSelected()->isModel())
        static_cast<Model*>(AbstractEntity::getSelected())->reverseBitangents();
    else if (AbstractEntity::getSelected() && AbstractEntity::getSelected()->isMesh())
        static_cast<Mesh*>(AbstractEntity::getSelected())->reverseBitangents();
    else
        QMessageBox::critical(0, "Error", "Select a model/mesh to do this operation.");
}
