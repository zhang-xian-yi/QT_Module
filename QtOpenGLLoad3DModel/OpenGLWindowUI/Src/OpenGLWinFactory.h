#ifndef OPENGLWINFACTORY_H
#define OPENGLWINFACTORY_H
#include "OWCommon/OpenGLWindowUI_global.h"

namespace OpenGLWinNS
{
    class IOpenGLWindows;//

    class OPENGLWINDOWUI_EXPORT OpenGLWinFactory
    {
    SingletonSelfConstruct(OpenGLWinFactory)

    public:
        IOpenGLWindows* GetWindowPtr();

    private:
        IOpenGLWindows* m_pWin;
    };

}

#endif // OPENGLWINFACTORY_H
