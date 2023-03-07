#include "FEFileParser.h"

FEFileParser::FEFileParser()
{
    m_pFEFileData = QSharedPointer<FEFileData>(new FEFileData());
}

FEFileParser::~FEFileParser()
{
    m_pFEFileData.clear();
}

bool FEFileParser::ParseFile(const QString& strFile)
{
    m_pFEFileData.clear();
    //显示读取时间
    QTime qtime;
    qtime.start();
    QFile _file(strFile);
    if (!_file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream outStream(&_file);
    //逐行读取
    int lineNum = 1;
    while (!outStream.atEnd())
    {
        LineDataProcess(outStream.readLine(),lineNum);
        ++lineNum;
    }
    qDebug()<<qtime.elapsed()/1000.0<<"s";
    return true;
}

void FEFileParser::LineDataProcess(QString strline,int lineNum)
{
    static int maxVertexLines;
    static int maxMeshLines;
    if (lineNum == 1)
    {
        this->SaveTitle(strline);//ITLE 开始  一个文件仅执行一次
    }
    else if (lineNum == 2)
    {
        this->SaveVariable(strline);//VARIABLES 变量名称列表 一个文件仅执行一次
    }
    else if (lineNum == 3)
    {
        maxVertexLines = 0;//避免多文件同时读取的行数错位
        this->SaveZoneConfig(strline);//ZONE 空间域 一个文件仅执行一次
        int vertexNum = m_pFEFileData->GetCfgInfo(FEFileData::EFEFileConfig::E_VertexNum).toInt();
        maxVertexLines = vertexNum + 3;//顶点个数与配置信息行数
    }
    else if (lineNum<= maxVertexLines) //变量区域区间【4，maxVertexLines】，文件行数索引从1开始
    {
        //存储变量
        this->SaveVertexData(strline);
    }
    else if(lineNum == maxVertexLines + 1)//变量与网格体之间的空行 一个文件仅执行一次
    {
        //顶点区域结束行 + 1（空行分割）+ 最大网格数 = 最大网格的行数
        maxMeshLines = m_pFEFileData->GetCfgInfo(FEFileData::EFEFileConfig::E_VertexNum).toInt() + 1 +
                       m_pFEFileData->GetCfgInfo(FEFileData::EFEFileConfig::E_MeshNum).toInt();
    }
    else if(lineNum <= maxMeshLines)//网格体
    {
        //存储网格体
        this->SaveMeshData(strline);
    }
}

void FEFileParser::SaveTitle(QString strline)
{
    QStringList strParts = strline.split('=');
    if (1 < strParts.count())
    {
        QString strTitle = this->EraseExtraChar(strParts.value(1));
        //添加标题信息
        m_pFEFileData->AddCfgInfo(FEFileData::EFEFileConfig::E_TITLE,strTitle);
    }
}

void FEFileParser::SaveVariable(QString strline)
{
    auto strParts = strline.split('=');
    //存在数据
    if (1 <= strParts.count())
    {
        QString strVariables = strParts.value(1).replace("\t\t\t\t\t\t\t\t", ",");
        auto strVaribleParts = strVariables.split(',');
        for (int idx = 0; idx < strVaribleParts.size(); idx++)
        {
            auto strVar = this->EraseExtraChar(strVaribleParts.value(idx));
            //构造变量键值对
            FEFileVertex::keyList.append(strVar);
        }
    }
}

void FEFileParser::SaveZoneConfig(QString strline)
{
    strline = strline.remove(0, 4);//移除zone 字符串
    //按照,分组键值对
    auto strZoneParts = strline.split(',');
    foreach (auto oneZone, strZoneParts)
    {
        //获取键值对
        auto aZoneParts = oneZone.split('=');
        QString strZoneKey = this->EraseExtraChar(aZoneParts.value(0));
        QString strZoneValue = this->EraseExtraChar(aZoneParts.value(1));
        //判断配置信息的类型
        if(strZoneKey == "T")
        {
            m_pFEFileData->AddCfgInfo(FEFileData::EFEFileConfig::E_Type,strZoneValue);
        }
        else if(strZoneKey == "N")
        {
            m_pFEFileData->AddCfgInfo(FEFileData::EFEFileConfig::E_VertexNum,strZoneValue);
        }
        else if(strZoneKey == "E")
        {
            m_pFEFileData->AddCfgInfo(FEFileData::EFEFileConfig::E_MeshNum,strZoneValue);
        }
        else if(strZoneKey == "DATAPACKING")
        {
            m_pFEFileData->AddCfgInfo(FEFileData::EFEFileConfig::E_DataPacking,strZoneValue);
        }
        else if(strZoneKey == "ZONETYPE")
        {
            m_pFEFileData->AddCfgInfo(FEFileData::EFEFileConfig::E_ZoneType,strZoneValue);
        }
    }
}

void FEFileParser::SaveVertexData(QString strline)
{
    // 通过空格分割数据
    auto dataParts = strline.split(' ');
    // 构造一个指定对象
    QSharedPointer<FEFileVertex> vertex(new FEFileVertex());
    //填充数据
    for (int i = 0; i < dataParts.size(); ++i)
    {
        float fData = dataParts[i].toFloat();
        //获取固定的坐标索引字符串
        QString index = FEFileVertex::keyList.at(i);
        vertex->m_dataMap[index] = fData;
    }
    m_pFEFileData->AddVertex(vertex);
}

void FEFileParser::SaveMeshData(QString strline)
{
    // 通过空格分割数据
    auto dataParts = strline.split(' ');
    // 构造一个指定对象
    QSharedPointer<FEFileMesh> mesh(new FEFileMesh());
    //填充数据
    for (int i = 0; i < dataParts.size(); ++i)
    {
        //添加索引
        mesh->indexData.append(dataParts[i].toInt());
    }
    m_pFEFileData->AddMesh(mesh);
}

QString FEFileParser::EraseExtraChar(QString strData)
{
    // 移除两端的 \r \t \v \f
    auto str = strData.trimmed();
    // 移除两端的 "
    if (str.startsWith('"'))
        str = str.remove(0, 1);
    if (str.endsWith('"'))
        str.truncate(str.length() - 1);
    return str;
}
