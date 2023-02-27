#include "OpenGLWindowsLayerService.h"
#include "Src/OWCommon/GlobalData.h" //LogLv 与pGLFunc 引入
OpenGLWindowsLayerService::OpenGLWindowsLayerService(QWidget * parent)
{
    m_openGLWindow = new OpenGLWindow();//由QT父级控件控制释放

    //设置为父控件的大小
    m_openGLWindow->setParent(parent);
    m_openGLWindow->setGeometry(parent->rect().x(),parent->rect().y(),
                      parent->rect().width(),parent->rect().height());

    m_openGLWindow->setAcceptDrops(true);
    m_openGLWindow->setFocusPolicy(Qt::StrongFocus);
}

OpenGLWindowsLayerService::~OpenGLWindowsLayerService()
{
    m_openGLWindow = nullptr; //减少引用技术由QT父控件控制
}

void OpenGLWindowsLayerService::LoadFiniteElementData(const QString& filepath)
{

}




