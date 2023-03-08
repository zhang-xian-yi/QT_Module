#ifndef FESCENCE_H
#define FESCENCE_H

#include "FEModel.h"

//视角
class CameraView
{
public:
    CameraView();
    void DefaultConfig();
public:
    float     distance;    //观察者距被观察物体中心点的初始距离
    float     fovy;        //观察者视角的大小
    float     zoom;        //观察者距被观察物体中心点的距离倍数，用于缩放控制
    QVector3D  eye;        //观察者在被观察物体的三维坐标系中的位置
    QVector3D  center;     //被观察物体的中心点坐标，为[0,0,0]
    QVector3D  up;         //观察者的头部朝向
};

//光源
class LightSource
{
public:
    LightSource();
};


//场景
class FEScence
{
public:
    FEScence();
    //创建默认场景--注意QT OpenGL 的初始化必须在initialGL中执行，所以此函数作为回调函数进行处理
    void CreateDefaultScence();
private:
    //光源
    QSharedPointer<LightSource> m_pLightSrc;
    //视角
    QSharedPointer<CameraView> m_pCamera;
    //模型集合
    QVector<QSharedPointer<FEModel>> m_modelVect;
};

#endif // FESCENCE_H
