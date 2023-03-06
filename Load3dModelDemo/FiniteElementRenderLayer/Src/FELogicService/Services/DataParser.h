#ifndef DATPARSER_H
#define DATPARSER_H

#include "Src/FECommon/ExtStruct.h"

enum DataArea
{
    AREA_TITLE,
    AREA_VARIBLE,
    AREA_ZONE
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

class DatParser
{
public:
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
public:
    DatParser();
    ~DatParser();

    bool ParseFile(const QString& strFile);
    // 返回坐标信息
    InVertex GetCoordinatesVertex(QString zoneName);
    // 返回网格体信息
    QVector<InFaceIndex> GetMeshersIndex(QString zoneName);

private:
    void LineDataProcess(QString strline);
    bool NoneDataLine(QString strline);//判断数据是否全部为空

    void SaveTitle(QString strline);
    void SaveVariable(QString strline);
    void SaveZone(QString strline);
    void SaveAreaData(QString strline,DataArea currArea);
    //过滤无用字符
    QString EraseExtraChar(QString strData);
private:
    // 是否经过回车换行符
    bool m_bIsGoneGRLF;
    // 标题
    QString m_pTitle;
    // 变量要素
    DatVariables *m_pVariable;
    // 空间区域
    DatZones *m_pZone;
    // 解析的数据
    Dat* m_pStuDatFile;

    // 当前坐标 变量标识
    CoordVarSymbol m_stuVarSymbol;
};


#endif // DATPARSER_H
