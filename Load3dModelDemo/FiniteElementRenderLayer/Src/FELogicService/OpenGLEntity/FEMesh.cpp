#include "FEMesh.h"
#include "Src/FELogicService/DrawElement/DECube.h"
FEMesh::FEMesh()
{

}

QVector<GLuint>& FEMesh::Compute(QVector<FEVertex> &AllVertexArr)
{
    //8个顶点--画正正六面体
    if(this->indexVect.size() == 8)
    {
        m_pDrawEleS = QSharedPointer<AbstractDE>(new DECube());
    }

    //根据不同的渲染元素--绘制不同的索引设置，并改变对应顶点的数据
    return m_pDrawEleS->ComputeRendererData(AllVertexArr,this->indexVect);
}

void FEMesh::Draw(QSharedPointer<QOpenGLShaderProgram> program)
{
    //绘制对应mesh 的网格
    m_pDrawEleS->Draw(program);
}
