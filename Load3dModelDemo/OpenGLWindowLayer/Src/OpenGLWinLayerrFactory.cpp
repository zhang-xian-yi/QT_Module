#include "OpenGLWinLayerrFactory.h"
#include "Src/OWMControl/OpenGLWinLayerControl.h"
namespace OWlayerNS
{
    OpenGLWinLayerrFactory::OpenGLWinLayerrFactory()
        :m_pOWLCtl(new OpenGLWinLayerControl())
    {

    }

    OpenGLWinLayerrFactory::~OpenGLWinLayerrFactory()
    {
        if(m_pOWLCtl)
        {
            delete m_pOWLCtl;
            m_pOWLCtl = nullptr;
        }
        if (logLV == DEBUG_DESTORY_INFO)
            dout << "OpenGLWinLayerrFactory is destroyed";
    }

    //获取窗口
    IOpenGLWin* OpenGLWinLayerrFactory::GetWindowPtr()
    {
        if(m_pOWLCtl == nullptr)
        {
            m_pOWLCtl = new OpenGLWinLayerControl();
        }
        return m_pOWLCtl;
    }
    //获取加载3d模型的操作指针
    ILoad3D *OpenGLWinLayerrFactory::GetLoad3DPtr()
    {
        if(m_pOWLCtl == nullptr)
        {
            m_pOWLCtl = new OpenGLWinLayerControl();
        }
        return m_pOWLCtl;
    }
}
