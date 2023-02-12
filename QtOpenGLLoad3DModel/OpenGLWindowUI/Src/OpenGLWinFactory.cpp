#include "openglwinfactory.h"
//opengl窗口
#include "IOpenGLWin.h"
#include "OWMControl/OpenGLWinControl.h"
namespace OpenGLWinNS
{
    OpenGLWinFactory::OpenGLWinFactory()
        :m_pWin(nullptr)
    {

    }

    OpenGLWinFactory::~OpenGLWinFactory()
    {
        if(m_pWin)
        {
            delete m_pWin;
            m_pWin = nullptr;
        }
    }

    //获取窗口
    IOpenGLWindows* OpenGLWinFactory::GetWindowPtr()
    {
        if(m_pWin == nullptr)
        {
            m_pWin = new OpenGLWinControl();           
        }
        return m_pWin;
    }

}
