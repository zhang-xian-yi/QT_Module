#ifndef DATAMANAGER_H
#define DATAMANAGER_H


#include "DataParser.h"

class DataManager
{
public:
    DataManager(QSharedPointer<DatParser> pDatParse);
    DataManager();
    ~DataManager();

    bool SetFile(QString strFile);
    bool SetFile(QStringList strFiles);
    // 设置坐标标识
    void SetCoordVarSymbol(CoordVarSymbol varSymbol);
    // 返回坐标信息
    InVertex GetCoordinatesVertex(QString zoneName);
    // 返回网格体信息
    QVector<InFaceIndex> GetMeshersIndex(QString zoneName);

    // 返回所有数据标题
    QStringList GetTitles();
    // 返回某标题下的所有空间区域名称
    QStringList GetNameForZones();
    // 返回所有要素变量名称 X,Y,Z,u...
    QStringList GetNameForVariables(QString zoneName);
    // 返回空间区域的信息 如T = XXX, N = 888...等
    QMap<QString, QString> GetInfoForZone(QString zoneName);
    // 返回设置的标题下的某要素变量数据
    QVector<float> GetValuesForOneVariable(QString var);

    static DataManager *GetInstance();
protected:
    void ClearCaches();
private:
    QSharedPointer<DatParser> m_pDatParser;
    QMap<QString, QStringList>* m_pVariablesNameListForZone;
    QMap<QString, QMap<QString, QString>>* m_pZoneInfoMapForZone;
    QMap<QString, InVertex>* m_pVertexCoordPhysicalForZone;
    QMap<QString, QVector<InFaceIndex>>* m_pMeshCubeGeometryForZone;
};

#endif // DATAMANAGER_H
