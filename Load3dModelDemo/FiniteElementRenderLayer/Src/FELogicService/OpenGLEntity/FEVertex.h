#ifndef FEVERTEX_H
#define FEVERTEX_H

//openGL 的顶点数据
class FEVertex
{
public:
    FEVertex();
public:
    QVector3D position;    //顶点位置
    QVector3D color;       //顶点颜色
    QVector3D normal;      //顶点法线
};

#endif // FEVERTEX_H
