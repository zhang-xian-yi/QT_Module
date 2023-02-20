#ifndef EXTSTRUCT_H
#define EXTSTRUCT_H
#include "OpenGLWindowLayer_global.h" //向外部暴露的接口必须使用带模块名的路径
namespace OWlayerNS
{
    struct OPENGLWINDOWLAYER_EXPORT Vec3F
    {
        float x;
        float y;
        float z;
    };

    struct OPENGLWINDOWLAYER_EXPORT Vec2F
    {
        float x;
        float y;
    };


    //输入定点数据
    struct OPENGLWINDOWLAYER_EXPORT InVertex
    {
        Vec3F PostionXYZ;//模型场景坐标（相对于场景模型中心不同的坐标点） 3个浮点数
        Vec3F NormalUVW;//模型视图坐标（相对于观察者中心不同的坐标点）  3个浮点数
        Vec3F TangentSpace;
    };

    //输入网格面数据
    struct OPENGLWINDOWLAYER_EXPORT InFaceIndex
    {
        QVector<uint32_t> IndexsArray;
    };
}
#endif // EXTSTRUCT_H
