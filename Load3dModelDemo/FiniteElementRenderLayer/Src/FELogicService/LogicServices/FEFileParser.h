#ifndef DATPARSER_H
#define DATPARSER_H

#include "Src/FELogicService/DataEntity/FEFileData.h"
#include "Src/FELogicService/OpenGLEntity/FEModel.h"
class FEFileParser:public QObject
{
    Q_OBJECT
public:
    FEFileParser();
    ~FEFileParser();
public:
    QSharedPointer<FEModel> ParseFile(const QString& strFile);
private:
    //将文件数据转化内opengl所需要的内部数据
    QSharedPointer<FEModel> Convert(QSharedPointer<FEFileData> pFEFileData);
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
    QSharedPointer<FEModel> m_pFEModel;
};


#endif // DATPARSER_H
