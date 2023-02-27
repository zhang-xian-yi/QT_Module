#include "GlobalData.h"

GlobalData::GlobalData()
    :pGLFuncs(nullptr)
{

}

GlobalData::~GlobalData()
{

}

bool GlobalData::InitOpenGLFuncEnv()
{
    //初始化GL的func
    if(pGLFuncs == nullptr)
    {
        pGLFuncs = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();
        pGLFuncs->initializeOpenGLFunctions();
    }
    return true;
}
