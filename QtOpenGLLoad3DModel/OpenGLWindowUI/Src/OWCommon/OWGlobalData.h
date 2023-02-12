#pragma once
#include "OpenGLWindowUI_global.h"

namespace OpenGLWinNS
{
    class OWGlobalData
    {
        //单例定义
        SingletonSelfConstruct(OWGlobalData)
    public:
        int log_level;
    };

}

