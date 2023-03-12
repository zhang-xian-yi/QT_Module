#ifndef FESCENCE_H
#define FESCENCE_H

#include "FEModel.h"
#include "Src/FELogicService/DataEntity/Material.h"
//光源
class LightSource
{
public:
    LightSource();
public:
    QVector3D LPostion;
    QVector3D LColor;
};


//场景
class FEScence
{
public:
    FEScence();
    //创建默认场景--注意QT OpenGL 的初始化必须在initialGL中执行，所以此函数作为回调函数进行处理
    void CreateDefaultScence();

    void Draw(QSharedPointer<QOpenGLShaderProgram> program);
public:
    //光源
    QSharedPointer<LightSource> m_pLightSrc;
    QSharedPointer<Material> m_pMaterial;
    //模型集合
    QVector<QSharedPointer<FEModel>> m_modelVect;
};

#endif // FESCENCE_H
