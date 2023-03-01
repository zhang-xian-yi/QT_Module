#include "FERendererLayerControl.h"
#include "Src/OWLogicService/FERendererLayerService.h"

FERendererLayerControl::FERendererLayerControl()
    :m_pOWLService(nullptr)
{

}

FERendererLayerControl::~FERendererLayerControl()
{
    m_pOWLService.clear();
}

void FERendererLayerControl::initOpenGLWin(QWidget* parent)
{
    if(m_pOWLService == nullptr)
    {
        initEnvirnoMent();
        m_pOWLService = QSharedPointer<FERendererLayerService>(new FERendererLayerService(parent));
    }

}

void FERendererLayerControl::initEnvirnoMent()
{
    QSurfaceFormat openGLFormat;
    openGLFormat.setVersion(4, 5);
    openGLFormat.setProfile(QSurfaceFormat::CoreProfile);
    openGLFormat.setDepthBufferSize(24);
    openGLFormat.setStencilBufferSize(8);
    QSurfaceFormat::setDefaultFormat(openGLFormat);
}

//加载3d数据
void FERendererLayerControl::LoadFiniteElementData(const QString& finiteElePath)
{
    if(m_pOWLService)
    {
        m_pOWLService->LoadFiniteElementData(finiteElePath);
    }
}

