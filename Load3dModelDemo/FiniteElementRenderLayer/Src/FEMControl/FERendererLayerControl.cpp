#include "FERendererLayerControl.h"
#include "Src/FELogicService/FERendererLayerService.h"

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
    //初始化显卡
    QSurfaceFormat openGLFormat;
    openGLFormat.setDepthBufferSize(24);
    openGLFormat.setStencilBufferSize(8);
    openGLFormat.setVersion(3, 3);
    //CompatibilityProfile 可以使用早期的OpenGL版本的功能
    //CoreProfile 3.0  OpenGL3.0版本中已弃用的功能不可用。
    //注意 此处若是使用核心模式，请确保OpenGL相关使用的全部都是3.0版本之后的功能，否则渲染一定失败（黑屏）
    openGLFormat.setProfile(QSurfaceFormat::CompatibilityProfile);
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

