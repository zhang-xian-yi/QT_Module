#include "CameraView.h"

CameraView::CameraView()
{

}

void CameraView::DefaultConfig()
{
    this->distance = 5.0;
    this->fovy     = 5.0;
    this->zoom     = 1.0;
    //观察者位置在z轴负方向的位置上
    this->eye      = {0,0, this->zoom * this->distance};
    //被观察物体的中心坐标
    this->center   = {0.0,0.0,0.0};
    //观察者头部朝向y轴方向
    this->up       = {0.0,1.0,0.0};
    //依据上述定义，界面初始化后，从界面中看到的坐标系就是以界面中心为原点、水平向右为x轴正半轴、垂直向上为y轴正半轴、屏幕向内为z轴正半轴
}
