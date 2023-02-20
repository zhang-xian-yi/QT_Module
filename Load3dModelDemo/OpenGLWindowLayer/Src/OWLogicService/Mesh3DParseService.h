#ifndef MESH3DPARSESERVICE
#define MESH3DPARSESERVICE
#include "Src/ExtStruct.h"
#include "Entity/Scene/Scene.h"
//解析3D网格结构
class Mesh3DParseService
{
public:
    Mesh3DParseService(QSharedPointer<Scene> pScene);
    ~Mesh3DParseService();
public:
    void Load3DMeshData(QVector<OWlayerNS::InVertex>& vectexArr,QVector<OWlayerNS::InFaceIndex>& indexArray);
private:
    QSharedPointer<Mesh> loadMesh(QVector<OWlayerNS::InVertex> &aiMeshPtr,OWlayerNS::InFaceIndex& face);
private:
    QSharedPointer<Scene>  m_pScene;               //显示的场景创建的场景,由OpenGLScene控制释放
};
#endif // MESH3DPARSESERVICE
