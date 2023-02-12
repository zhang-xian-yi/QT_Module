#ifndef OPENGLWINCONTROL_H
#define OPENGLWINCONTROL_H

#include "Src/IOpenGLWin.h"

namespace OpenGLWinNS {
    class OpenGLWindowUI;

    //
    class OpenGLWinControl:public IOpenGLWindows
    {
    public:
        OpenGLWinControl();
        ~OpenGLWinControl();
    public:
       virtual void InitOpenGLWindow(QWidget* parent) override;
    private:
        OpenGLWindowUI* m_pOpenGLWinS;
    };
}


#endif // OPENGLWINCONTROL_H
