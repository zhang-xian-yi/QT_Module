#ifndef FEMODEL_H
#define FEMODEL_H

#include "FEMesh.h"

class FEModel
{
public:
    FEModel();

public:
    //模型有所有的顶点数据
    QVector<QSharedPointer<FEVertex>> verticesVect;
    QVector<QSharedPointer<FEMesh>> meshVect;
};

#endif // FEMODEL_H
