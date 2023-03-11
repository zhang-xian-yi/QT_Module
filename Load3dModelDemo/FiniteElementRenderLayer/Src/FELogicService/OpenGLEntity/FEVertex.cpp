#include "FEVertex.h"

FEVertex::FEVertex()
{
    position = {0,0,0};
    color = QVector3D(0/255.0, 181/255.0, 0/255.0);//默认绿色
    normal = {0,0,0};
}
