#ifndef FERENDERERFACTORY_H
#define FERENDERERFACTORY_H

#include "FiniteElementRenderlayer_global.h" //向外部暴露的接口必须使用带模块名的路径
#include "IOpenGLWin.h"
#include "ILoad3D.h"

class FERendererLayerControl;

//向外部暴露的的接口加上命名空间进行隔离, dll内部函数这不用添加命名空间

namespace FERendererNS
{
    class FINITEELEMENTRENDERLAYER_EXPORT FERendererLayerFactory
    {
    private:
        FERendererLayerFactory() ;
        ~FERendererLayerFactory() ;
        FERendererLayerFactory(FERendererLayerFactory& instance) = delete;
        FERendererLayerFactory& operator=(const FERendererLayerFactory& instance) = delete;
    public:
        static FERendererLayerFactory& GetInstance()
        {
            static FERendererLayerFactory instance;
            return instance;
        }

    public:
        //获取opengGL窗口初始化的结果
        QSharedPointer<IOpenGLWin> GetWindowPtr();
        //获取加载3d模型的操作接口
        QSharedPointer<ILoad3D> GetLoad3DPtr();
    private:
        //控制器指针
        QSharedPointer<FERendererLayerControl> m_pOWLCtl;
    };
}


#endif // FERENDERERFACTORY_H
