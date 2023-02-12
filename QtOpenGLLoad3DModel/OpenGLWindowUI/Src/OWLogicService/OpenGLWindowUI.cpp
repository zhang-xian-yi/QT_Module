#include "OpenGLWindowUI.h"
#include "Services/QtOpenGLWindow.h"

namespace OpenGLWinNS {

    OpenGLWindowUI::OpenGLWindowUI(QWidget *parent)
        :m_pGlWin(new QtOpenGLWindow(parent))
    {

    }

    OpenGLWindowUI::~OpenGLWindowUI()
    {
        m_pGlWin = nullptr;
    }
}

