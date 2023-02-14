#include "OpenGLWinLayerControl.h"
#include "Src/OWLogicService/OpenGLWindowsLayerService.h"
#include "Src/OWCommon/MacroDefine.h"

int log_level = LOG_LEVEL_WARNING;//此处定义日志等级，且定义一次

OpenGLWinLayerControl::OpenGLWinLayerControl()
    :m_pOWLService(nullptr)
{

}

void OpenGLWinLayerControl::initOpenGLWin(QWidget* parent)
{
    if(m_pOWLService == nullptr)
    {
        initEnvirnoMent();
        m_pOWLService = new OpenGLWindowsLayerService(parent);
        m_pOWLService->CreateScene();//初始化场景
    }

}

void OpenGLWinLayerControl::Load3DModel(QString path)
{
    if(m_pOWLService)
    {
        m_pOWLService->ImportModelFile(path);
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
