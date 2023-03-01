#include "OpenGLWinLayerControl.h"
#include "Src/OWLogicService/OpenGLWindowsLayerService.h"
OpenGLWinLayerControl::OpenGLWinLayerControl()
    :m_pOWLService(nullptr)
{

}

OpenGLWinLayerControl::~OpenGLWinLayerControl()
{
    m_pOWLService.clear();
    if (logLV == DEBUG_DESTORY_INFO)
        dout << "OpenGLWinLayerControl is destroyed";
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
    openGLFormat.setVersion(3, 3);
    openGLFormat.setProfile(QSurfaceFormat::CoreProfile);
    openGLFormat.setDepthBufferSize(24);
    openGLFormat.setStencilBufferSize(8);
    QSurfaceFormat::setDefaultFormat(openGLFormat);
}


void OpenGLWinLayerControl::Load3DModel(QString path)
{
    if(m_pOWLService)
    {
        m_pOWLService->ImportModelFile(path);
    }
}

