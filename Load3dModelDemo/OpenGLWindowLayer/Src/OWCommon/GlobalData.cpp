#include "GlobalData.h"

GlobalData::GlobalData()
    :log_level(NO_LOG),
     m_pGLFuncs(nullptr)
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
    }
}

QOpenGLFunctions_3_3_Core *GlobalData::GetGLFunc()
{
    return m_pGLFuncs;
}
