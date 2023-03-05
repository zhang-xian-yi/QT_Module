#ifndef IOPENGLWIN_H
#define IOPENGLWIN_H

#include "FiniteElementRenderlayer_global.h" //向外部暴露的接口必须使用带模块名的路径

//向外部暴露的的接口加上命名空间进行隔离, dll内部函数这不用添加命名空间
namespace FERendererNS
{
    class FINITEELEMENTRENDERLAYER_EXPORT IOpenGLWin
    {
    public:
        virtual void initOpenGLWin(QWidget* parent) = 0;
    };
}

#endif // IOPENGLWIN_H
