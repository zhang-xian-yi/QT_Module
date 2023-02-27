#include "OpenGLWinLayerControl.h"
#include "Src/OWLogicService/OpenGLWindowsLayerService.h"

OpenGLWinLayerControl::OpenGLWinLayerControl()
    :m_pOWLService(nullptr)
{

}

OpenGLWinLayerControl::~OpenGLWinLayerControl()
{
    m_pOWLService.clear();
}

void OpenGLWinLayerControl::initOpenGLWin(QWidget* parent)
{
    if(m_pOWLService == nullptr)
    {
        initEnvirnoMent();
        m_pOWLService = QSharedPointer<OpenGLWindowsLayerService>(new OpenGLWindowsLayerService(parent));
    }

}

void OpenGLWinLayerControl::initEnvirnoMent()
{
    QSurfaceFormat openGLFormat;
    openGLFormat.setVersion(4, 5);
    openGLFormat.setProfile(QSurfaceFormat::CoreProfile);
    openGLFormat.setDepthBufferSize(24);
    openGLFormat.setStencilBufferSize(8);
    QSurfaceFormat::setDefaultFormat(openGLFormat);
}

//加载3d数据
void OpenGLWinLayerControl::LoadFiniteElementData(const QString& finiteElePath)
{
    if(m_pOWLService)
    {
        m_pOWLService->LoadFiniteElementData(finiteElePath);
    }
}

