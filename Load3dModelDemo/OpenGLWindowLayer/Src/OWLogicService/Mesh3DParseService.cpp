#include "Mesh3DParseService.h"
#include "Model/Model.h"
#include "Mesh/Mesh.h"
Mesh3DParseService::Mesh3DParseService(QSharedPointer<Scene> pScene)
    :m_pScene(pScene)
{

}
Mesh3DParseService::~Mesh3DParseService()
{
    m_pScene.clear();
}

void Mesh3DParseService::Load3DMeshData(QVector<OWlayerNS::InVertex> &vectexArr, QVector<OWlayerNS::InFaceIndex> &indexArray)
{
    //模型结构
    QSharedPointer<Model> model = QSharedPointer<Model>(new Model);
    model->setObjectName("3DMeshData");
    //加载网格信息
    for (int i = 0; i < indexArray.size(); i++)
    {
        OWlayerNS::InFaceIndex face= indexArray.at(i);
        //获取定点信息
        model->addChildMesh(loadMesh(vectexArr,face));
    }

    //模型中心显示
    QVector3D center = model->centerOfMass();

    for (int i = 0; i < model->childMeshes().size(); i++)
        model->childMeshes()[i]->translate(-center);
    for (int i = 0; i < model->childModels().size(); i++)
        model->childModels()[i]->translate(-center);

    model->translate(center);

    //添加场景中的模型
    if (m_pScene && model)
    {
        m_pScene->addModel(model);
    }
}


QSharedPointer<Mesh> Mesh3DParseService::loadMesh(QVector<OWlayerNS::InVertex> &InVertexArray,OWlayerNS::InFaceIndex& face)
{
    QSharedPointer<Mesh> mesh = QSharedPointer<Mesh>(new Mesh);
    mesh->setObjectName("Untitled");

    QMap<int,int> replaceVIMap;

    for (int i = 0; i < face.IndexsArray.size(); i++)
    {
        int vertexIndex = face.IndexsArray.at(i);
        //过滤重复的点索引
        if(!replaceVIMap.contains(vertexIndex))
        {
            //构造定点
            Vertex vertex;
            auto inV = InVertexArray.at(vertexIndex);
            //加载XYZ
            vertex.position.setX(inV.PostionXYZ.one);
            vertex.position.setY(inV.PostionXYZ.two);
            vertex.position.setZ(inV.PostionXYZ.three);
            //加载UVW
            vertex.normal.setX(inV.NormalUVW.one);
            vertex.normal.setY(inV.NormalUVW.two);
            vertex.normal.setZ(inV.NormalUVW.three);
            //加载切线空间数据

            //加载纹理坐标
            vertex.texCoords.setX(inV.TexCoord.one);
            vertex.texCoords.setY(inV.TexCoord.two);
            //保存网格顶点
            mesh->m_vertices.push_back(vertex);
            //保存网格索引
            //mesh->setMeshType(Mesh::MeshType::Triangle);//默认三角形
            //非重复定点 第一次添加为0
            replaceVIMap.insert(vertexIndex,mesh->m_vertices.size() - 1);//确保网格定点不重复
        }
        //保存索引
        mesh->m_indices.push_back(replaceVIMap[vertexIndex]);
    }
    //默认材质
    QSharedPointer<Material> material = QSharedPointer<Material>(new Material);
    mesh->setMaterial(material);
    //默认渲染方式
    mesh->setMeshType(Mesh::MeshType::Point);
    //移动中心节点
    QVector3D center = mesh->centerOfMass();
    for (int i = 0; i < mesh->m_vertices.size(); i++)
        mesh->m_vertices[i].position -= center;
    mesh->m_position = center;

    return mesh;
}
