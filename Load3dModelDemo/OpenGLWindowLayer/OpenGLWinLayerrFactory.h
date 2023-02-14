#ifndef OPENGLWINLAYER_H
#define OPENGLWINLAYER_H

#include "OpenGLWindowLayer/Src/OWCommon/OpenGLWindowLayer_global.h" //向外部暴露的接口必须使用带模块名的路径
#include "IOpenGLWin.h"

class OPENGLWINDOWLAYER_EXPORT OpenGLWinLayerrFactory
{
public:
    OpenGLWinLayerrFactory();

public:
    IOpenGLWin* GetWInPtr();
};

#endif // OPENGLWINLAYER_H
