#ifndef OPENGLWINLAYER_H
#define OPENGLWINLAYER_H

#include "OpenGLWindowLayer_global.h" //向外部暴露的接口必须使用带模块名的路径
#include "IOpenGLWin.h"
#include "ILoad3D.h"

class OpenGLWinLayerControl;

//向外部暴露的的接口加上命名空间进行隔离, dll内部函数这不用添加命名空间

namespace OWlayerNS
{
    class OPENGLWINDOWLAYER_EXPORT OpenGLWinLayerrFactory
    {
    private:
        OpenGLWinLayerrFactory();
        ~OpenGLWinLayerrFactory();
        OpenGLWinLayerrFactory(OpenGLWinLayerrFactory& instance) = delete;
        OpenGLWinLayerrFactory& operator=(const OpenGLWinLayerrFactory& instance) = delete;
    public:
        static OpenGLWinLayerrFactory& GetInstance()
        {
            static OpenGLWinLayerrFactory instance;
            return instance;
        }

    public:
        //获取opengGL窗口初始化的结果
        IOpenGLWin* GetWindowPtr();
        //获取加载3d模型的操作接口
        ILoad3D* GetLoad3DPtr();
    private:
        //控制器指针
        OpenGLWinLayerControl* m_pOWLCtl;
    };
}


#endif // OPENGLWINLAYER_H
