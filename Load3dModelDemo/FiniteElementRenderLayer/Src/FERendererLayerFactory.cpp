#include "FERendererLayerFactory.h"
#include "Src/OWMControl/OpenGLWinLayerControl.h"
namespace OWlayerNS
{
    FERendererLayerFactory::FERendererLayerFactory()
        :m_pOWLCtl(QSharedPointer<OpenGLWinLayerControl>(new OpenGLWinLayerControl()))
    {

    }

    FERendererLayerFactory::~FERendererLayerFactory()
    {
        m_pOWLCtl.clear();
    }

    //获取窗口
    QSharedPointer<IOpenGLWin> FERendererLayerFactory::GetWindowPtr()
    {
        if(m_pOWLCtl == nullptr)
        {
            m_pOWLCtl = QSharedPointer<OpenGLWinLayerControl>(new OpenGLWinLayerControl());
        }
        return m_pOWLCtl;
    }
    //获取加载3d模型的操作指针
    QSharedPointer<ILoad3D> FERendererLayerFactory::GetLoad3DPtr()
    {
        if(m_pOWLCtl == nullptr)
        {
            m_pOWLCtl = QSharedPointer<OpenGLWinLayerControl>(new OpenGLWinLayerControl());
        }
        return m_pOWLCtl;
    }
}
