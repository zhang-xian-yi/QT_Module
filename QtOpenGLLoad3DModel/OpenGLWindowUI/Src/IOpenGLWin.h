#ifndef IOPENGLWIN_H
#define IOPENGLWIN_H
#include "OpenGLWindowUI/Src//OWCommon/OpenGLWindowUI_global.h"
namespace OpenGLWinNS {

class OPENGLWINDOWUI_EXPORT IOpenGLWindows
{
public:
    virtual ~IOpenGLWindows() = default;
public:
    //将指定的控件初始化opengl显示窗口
    virtual void InitOpenGLWindow(QWidget* parent) = 0;
};

}



#endif // IOPENGLWIN_H
