#ifndef DATPARSER_H
#define DATPARSER_H

#include "Src/FELogicService/DataEntity/FEFileData.h"
class FEFileParser
{
public:
    FEFileParser();
    ~FEFileParser();

    QSharedPointer<FEFileData> ParseFile(const QString& strFile);

private:
    void LineDataProcess(QString strline,int lineNum);
    void SaveTitle(QString strline);//有限元文件第一行
    void SaveVariable(QString strline);//有限元文件第二行
    void SaveZoneConfig(QString strline);//有限元文件第三行
    void SaveVertexData(QString strline);//有限元文件顶点数据
    void SaveMeshData(QString strline);//有限元文件网格数据
    //过滤无用字符
    QString EraseExtraChar(QString strData);
private:
    QSharedPointer<FEFileData> m_pFEFileData;//有限元数据
};


#endif // DATPARSER_H
