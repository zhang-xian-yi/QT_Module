#include "OpenGLWinControl.h"
#include "Src/OWLogicService/OpenGLWindowUI.h"

namespace OpenGLWinNS
{

    OpenGLWinControl::OpenGLWinControl()
        :m_pOpenGLWinS(nullptr)
    {

    }

    OpenGLWinControl::~OpenGLWinControl()
    {
        if(m_pOpenGLWinS)
        {
            delete m_pOpenGLWinS;
            m_pOpenGLWinS = nullptr;
        }
    }

    void OpenGLWinControl::InitOpenGLWindow(QWidget *parent)
    {
        if(m_pOpenGLWinS == nullptr)
        {
            m_pOpenGLWinS = new OpenGLWindowUI(parent);
        }
    }

}
