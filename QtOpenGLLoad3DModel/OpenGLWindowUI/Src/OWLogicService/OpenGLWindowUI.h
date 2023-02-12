#ifndef OpenGLWindowUI_H
#define OpenGLWindowUI_H

namespace OpenGLWinNS {

    class QtOpenGLWindow;
}

namespace OpenGLWinNS {

    class OpenGLWindowUI
    {
    public:
        OpenGLWindowUI(QWidget* parent);
        ~OpenGLWindowUI();

    private:
        QtOpenGLWindow* m_pGlWin;
    };
}


#endif // OpenGLWindowUI_H
