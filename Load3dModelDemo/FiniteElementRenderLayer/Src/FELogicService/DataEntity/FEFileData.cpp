#include "FEFileData.h"

//定义静态成员
QList<QString> FEFileVertex::keyList;

FEFileData::FEFileData()
{
    InitCfgMap();//将配置信息全部赋空值
}

FEFileData::~FEFileData()
{
    m_cfgMap.clear();
    //智能指针 自动释放
    m_vertexVec.clear();
    m_meshVec.clear();
}

void FEFileData::AddCfgInfo(EFEFileConfig key, QString &value)
{
    m_cfgMap[key] = value;
}

QString FEFileData::GetCfgInfo(EFEFileConfig key) const
{
    return  m_cfgMap[key];
}

void FEFileData::AddVertex(QSharedPointer<FEFileVertex> vertex)
{
    m_vertexVec.append(vertex);
}

void FEFileData::AddMesh(QSharedPointer<FEFileMesh> mesh)
{
    m_meshVec.append(mesh);
}

QVector<QSharedPointer<FEFileVertex>> & FEFileData::GetVertexVector()
{
    return m_vertexVec;
}

QVector<QSharedPointer<FEFileMesh>> & FEFileData::GetMeshVector()
{
    return m_meshVec;
}

void FEFileData::InitCfgMap()
{
    m_cfgMap[FEFileData::EFEFileConfig::E_TITLE] = "";
    m_cfgMap[FEFileData::EFEFileConfig::E_Type] = "";
    m_cfgMap[FEFileData::EFEFileConfig::E_VertexNum] = "";
    m_cfgMap[FEFileData::EFEFileConfig::E_MeshNum] = "";
    m_cfgMap[FEFileData::EFEFileConfig::E_DataPacking] = "";
    m_cfgMap[FEFileData::EFEFileConfig::E_ZoneType] = "";
}


//读取
/***************************************************************************************************************/
/*FEFileVertex                                                                                                             */
/***************************************************************************************************************/
FEFileVertex::FEFileVertex()
{
    foreach (QString key, keyList)
    {
        m_dataMap[key] = 0.0f;
    }
}

const float &FEFileVertex::operator [](int i) const
{
    return m_dataMap[keyList[i]];
}

float & FEFileVertex::operator [](int i)
{
    return m_dataMap[keyList[i]];
}
