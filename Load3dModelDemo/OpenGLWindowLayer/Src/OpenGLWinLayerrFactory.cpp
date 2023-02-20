#include "OpenGLWinLayerrFactory.h"
#include "Src/OWMControl/OpenGLWinLayerControl.h"
namespace OWlayerNS
{
    OpenGLWinLayerrFactory::OpenGLWinLayerrFactory()
        :m_pOWLCtl(QSharedPointer<OpenGLWinLayerControl>(new OpenGLWinLayerControl()))
    {

    }

    OpenGLWinLayerrFactory::~OpenGLWinLayerrFactory()
    {
        m_pOWLCtl.clear();
        if (logLV == DEBUG_DESTORY_INFO)
            dout << "OpenGLWinLayerrFactory is destroyed";
    }

    //获取窗口
    QSharedPointer<IOpenGLWin> OpenGLWinLayerrFactory::GetWindowPtr()
    {
        if(m_pOWLCtl == nullptr)
        {
            m_pOWLCtl = QSharedPointer<OpenGLWinLayerControl>(new OpenGLWinLayerControl());
        }
        return m_pOWLCtl;
    }
    //获取加载3d模型的操作指针
    QSharedPointer<ILoad3D> OpenGLWinLayerrFactory::GetLoad3DPtr()
    {
        if(m_pOWLCtl == nullptr)
        {
            m_pOWLCtl = QSharedPointer<OpenGLWinLayerControl>(new OpenGLWinLayerControl());
        }
        return m_pOWLCtl;
    }
}
