#ifndef FEMESH_H
#define FEMESH_H

#include "FEVertex.h"

class FEMesh
{
public:
    FEMesh();

public:
    QVector<uint32_t> indexVect;
};

#endif // FEMESH_H
