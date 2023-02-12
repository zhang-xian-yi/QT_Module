#include "LoadModelFactory.h"

#include "LMMControl/LMServiceControl.h"

namespace Load3dModelNS
{
    LoadModelFactory::LoadModelFactory()
        :m_pLMSCtl(nullptr)
    {

    }
    LoadModelFactory::~LoadModelFactory()
    {
        if(m_pLMSCtl)
        {
            delete m_pLMSCtl;
            m_pLMSCtl = nullptr;
        }
    }

    ILoad3DModel* LoadModelFactory::GetLoad3DModelPtr()
    {
        if(m_pLMSCtl == nullptr)
        {
            m_pLMSCtl = new LMServiceControl();
        }
        return m_pLMSCtl;
    }

}

