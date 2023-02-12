#ifndef LOADMODELFACTORY_H
#define LOADMODELFACTORY_H

#include "Load3DModel/Src/LMCommon/Load3DModel_global.h" //此为其他模块包含此头文件时可以索引的目录
#include "Load3DModel/Src/ILoadModel.h"
namespace Load3dModelNS
{
    class LOAD3DMODEL_EXPORT LoadModelFactory
    {
    //单例定义
    SingletonSelfConstruct(LoadModelFactory)

    public:
        ILoad3DModel* GetLoad3DModelPtr();//工厂定义

    private:
        ILoad3DModel* m_pLMSCtl;//3d模型加载业务控制器
    };
}



#endif // LOADMODELFACTORY_H
