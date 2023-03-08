#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H


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

#endif // CAMERAVIEW_H
