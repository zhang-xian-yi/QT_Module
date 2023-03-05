#ifndef DATPARSER_H
#define DATPARSER_H

#include "Src/OWCommon/ExtStruct.h"


Q_GLOBAL_STATIC_WITH_ARGS(QString, Dat_Title,       ("TITLE"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, Dat_Itle,        ("ITLE"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, Dat_Variables,   ("VARIABLES"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, Dat_Zone,        ("ZONE"))

enum DataArea
{
    AREA_TITLE,
    AREA_VARIBLE,
    AREA_ZONE
};

class DatParser
{
    struct DatVariables
    {
        DatVariables() {}
        QList<QString> variableNames;
        QVector<float> variableData;
    };
    struct DatZones
    {
        DatZones() { pVariableAddr = nullptr; pTitleAddr = nullptr; }
        QMap<QString, QString> zoneHeaders;
        QVector<int> zoneData;
        // 每行数据个数 = 数据总个数 / 网格节点个数

        DatVariables *pVariableAddr;
        QString *pTitleAddr;
    };
    struct Dat
    {
        Dat() {}
        ~Dat(){}
        QList<QString *> allTitle;
        QList<DatVariables *> allVariable;
        QList<DatZones *> allZone;
    };
    struct CoordVarSymbol
    {
        CoordVarSymbol() {}
        CoordVarSymbol(QString x, QString y, QString z)
        {
            this->symbolX = x;
            this->symbolY = y;
            this->symbolZ = z;
        }
        QString symbolX = "X";
        QString symbolY = "Y";
        QString symbolZ = "Z";
    };
public:
    DatParser();
    ~DatParser();

    bool SetFile(QString strFile);
    bool SetFile(QStringList strFiles);
    // 设置当前标题
    void SetCurrentTitle(QString title);
    // 设置坐标标识
    void SetCoordVarSymbol(CoordVarSymbol varSymbol);
    // 返回模型位置信息
    QVector<QVector3D> GetCoordinates();
    // 返回坐标信息
    QVector<InVertex> GetCoordinatesVertex(QString zoneName);
    // 返回网格体信息
    QVector<QVector<int>> GetMeshers(QString zoneName);
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
    // 返回某要素变量数据
    QVector<float> GetValuesForOneVariable(QString var);
protected:
    /* 返回2D x,y 数据列表 */
    QList<QVector2D> GetValuesFor2D(QString varX, QString varY);
    QList<QVector3D> GetValuesFor3D(QString varX, QString varY, QString varZ);
    QList<QVector4D> GetValuesFor4D(QString varX, QString varY, QString varZ, QString varW);
    // 返回某空间区域数据
    QVector<int> GetGridDataForZone(QString zone);
    // 返回某空间区域的所有字段名称
    QStringList GetFieldKeyNameForZone(QString zone);
    // 返回某空间区域的某字段值
    QString GetOneValueForOneZone(QString zone, QString key);
private:
    void LineDataProcess(QString strline);
    bool NoneDataLine(QString strline);

    void SaveTitle(QString strline);
    void SaveVariable(QString strline);
    void SaveZone(QString strline);
    void SaveAreaData(QString strline);

    QString EraseExtraChar(QString strData);
    void SaveLastZoneForTitleVar();
private:
    // 当前数据区域
    DataArea m_emCurDataArea;
    // 是否经过回车换行符
    bool m_bIsGoneGRLF;
    // 标题
    QString *m_pTitle;
    // 变量要素
    DatVariables *m_pVariable;
    // 空间区域
    DatZones *m_pZone;
    // 解析的数据
    Dat* m_pStuDatFile;

    // 当前的标题
    QString m_strTitle;
    // 当前坐标 变量标识
    CoordVarSymbol m_stuVarSymbol;
};

#endif // DATPARSER_H
