#include "GlobalData.h"

GlobalData::GlobalData()
    :log_level(DEBUG_DESTORY_INFO),
     m_pGLFuncs(nullptr),
     isInitF(false)
{

}

GlobalData::~GlobalData()
{

}

void GlobalData::InitOpenGLFunc()
{
    //初始化GL的func
    if(m_pGLFuncs == nullptr)
    {
        m_pGLFuncs = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
        m_pGLFuncs->initializeOpenGLFunctions();
        isInitF = true;
    }
}

bool GlobalData::IsInitOpenGLFuncs() const
{
    return isInitF;
}

QOpenGLFunctions_3_3_Core *GlobalData::GetGLFunc()const
{
    return m_pGLFuncs;
}
