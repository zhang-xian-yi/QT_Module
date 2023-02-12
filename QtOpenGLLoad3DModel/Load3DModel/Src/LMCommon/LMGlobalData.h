#pragma once
#include "Load3DModel_global.h"

namespace Load3dModelNS
{
    class LMGlobalData
    {
        //单例定义
        SingletonSelfConstruct(LMGlobalData)
    public:
        int log_level;
    };

}

