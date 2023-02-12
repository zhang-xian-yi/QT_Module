#ifndef LMSERVICECONTROL
#define LMSERVICECONTROL
#include "Load3DModel/Src/ILoadModel.h"

class Scene; //场景

namespace Load3dModelNS
{
    class Load3DModelService;

    class LMServiceControl:public ILoad3DModel
    {
    public:
        LMServiceControl();
    public:
        virtual Scene* Load3DModelFromFile(const QString& modelPath);

    private:
        Load3DModelService* m_pLMService;
    };
}


#endif // LMSERVICECONTROL
