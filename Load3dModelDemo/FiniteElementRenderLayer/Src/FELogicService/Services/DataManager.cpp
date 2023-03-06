#include "DataManager.h"


DataManager::DataManager(QSharedPointer<DatParser> pDatParse)
{
    m_pDatParser = pDatParse;
    m_pVariablesNameListForZone = new QMap<QString, QStringList>;
    m_pZoneInfoMapForZone = new QMap<QString, QMap<QString, QString>>;
    m_pVertexCoordPhysicalForZone = new QMap<QString, InVertex>;
    m_pMeshCubeGeometryForZone = new QMap<QString, QVector<InFaceIndex>>;
}

DataManager::DataManager()
{
    m_pDatParser = nullptr;
    m_pVariablesNameListForZone = new QMap<QString, QStringList>;
    m_pZoneInfoMapForZone = new QMap<QString, QMap<QString, QString>>;
    m_pVertexCoordPhysicalForZone = new QMap<QString, InVertex>;
    m_pMeshCubeGeometryForZone = new QMap<QString, QVector<InFaceIndex>>;
}

DataManager::~DataManager()
{
    delete m_pVariablesNameListForZone;
    m_pVariablesNameListForZone = nullptr;
    delete m_pZoneInfoMapForZone;
    m_pZoneInfoMapForZone = nullptr;
    delete m_pVertexCoordPhysicalForZone;
    m_pVertexCoordPhysicalForZone = nullptr;
    delete m_pMeshCubeGeometryForZone;
    m_pMeshCubeGeometryForZone = nullptr;
}

bool DataManager::SetFile(QString strFile)
{

    return this->m_pDatParser->SetFile(strFile);
}

bool DataManager::SetFile(QStringList strFiles)
{

    return this->m_pDatParser->SetFile(strFiles);
}

void DataManager::SetCoordVarSymbol(CoordVarSymbol varSymbol)
{
    this->m_pDatParser->SetCoordVarSymbol(varSymbol);
}

InVertex DataManager::GetCoordinatesVertex(QString zoneName)
{
    if (!m_pVertexCoordPhysicalForZone->contains(zoneName))
    {
        m_pVertexCoordPhysicalForZone->insert(zoneName, this->m_pDatParser->GetCoordinatesVertex(zoneName));
    }
    return this->m_pVertexCoordPhysicalForZone->value(zoneName);
}

QVector<InFaceIndex> DataManager::GetMeshersIndex(QString zoneName)
{
    if (!m_pMeshCubeGeometryForZone->contains(zoneName))
    {
        m_pMeshCubeGeometryForZone->insert(zoneName, this->m_pDatParser->GetMeshersIndex(zoneName));
    }
    return this->m_pMeshCubeGeometryForZone->value(zoneName);
}

QStringList DataManager::GetTitles()
{
    return this->m_pDatParser->GetTitles();
}

QStringList DataManager::GetNameForZones()
{
    return this->m_pDatParser->GetNameForZones();
}

QStringList DataManager::GetNameForVariables(QString zoneName)
{
    if (!m_pVariablesNameListForZone->contains(zoneName))
    {
        m_pVariablesNameListForZone->insert(zoneName, this->m_pDatParser->GetNameForVariables(zoneName));
    }
    return m_pVariablesNameListForZone->value(zoneName);
}

QMap<QString, QString> DataManager::GetInfoForZone(QString zoneName)
{
    if (!m_pZoneInfoMapForZone->contains(zoneName))
    {
        m_pZoneInfoMapForZone->insert(zoneName, this->m_pDatParser->GetInfoForZone(zoneName));
    }
    return m_pZoneInfoMapForZone->value(zoneName);
}

QVector<float> DataManager::GetValuesForOneVariable(QString var)
{
    return this->m_pDatParser->GetValuesForOneVariable(var);
}

DataManager* DataManager::GetInstance()
{
    static DataManager instance;
    return &instance;
}

void DataManager::ClearCaches()
{
    m_pVariablesNameListForZone->clear();
    m_pZoneInfoMapForZone->clear();
    m_pVertexCoordPhysicalForZone->clear();
    m_pMeshCubeGeometryForZone->clear();
}
