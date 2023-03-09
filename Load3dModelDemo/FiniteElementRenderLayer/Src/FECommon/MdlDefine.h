#ifndef MDLDEFINE_H
#define MDLDEFINE_H


class QEvent;
//定义函数指针
typedef std::function<bool(QEvent* event)> OnEventCallBack;//事件处理 返回值bool  参数QEvent
typedef std::function<void()> OpenGLEnvInitCallback;//opengl环境初始化 无返回值，无参数
typedef std::function<void()> DrawCallback;//绘制paintgl 函数中调用的回调 无返回值，无参数
typedef std::function<QMatrix4x4()> GetMat4Callback;//获取4X4矩阵，mat4返回值，无参数
typedef std::function<QVector3D()> GetVec3DCallback;//获取3D数据，QVector3D返回值，无参数
#endif // MDLDEFINE_H
