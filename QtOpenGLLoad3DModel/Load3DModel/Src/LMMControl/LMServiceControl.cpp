#include "LMServiceControl.h"
#include "Load3DModel/Src/LMLogicService/Load3DModelService.h"
#include "Load3DModel/Src/LMLogicService/Entity/Scene/Scene.h"
namespace Load3dModelNS
{
    LMServiceControl::LMServiceControl()
        :m_pLMService(new Load3DModelService())
    {

    }

    ///加载3d模型的文件
    Scene* LMServiceControl::Load3DModelFromFile(const QString &modelPath)
    {
        return m_pLMService->Load3DModelFromFile(modelPath);
    }
}


