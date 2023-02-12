#ifndef LOAD3DMODEL_H
#define LOAD3DMODEL_H

#include "Load3DModel/Src/LMCommon/Load3DModel_global.h" //此为其他模块包含此头文件时可以索引的目录
class Scene; //场景

namespace Load3dModelNS
{
    class LOAD3DMODEL_EXPORT ILoad3DModel
    {
    public:
        ILoad3DModel() =default;
        ~ILoad3DModel() =default;
    public:
        virtual Scene* Load3DModelFromFile(const QString& modelPath) = 0;
    };
}



#endif // LOAD3DMODEL_H
