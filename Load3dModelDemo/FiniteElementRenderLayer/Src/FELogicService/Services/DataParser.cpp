#include "DataParser.h"

Q_GLOBAL_STATIC_WITH_ARGS(QString, Dat_Title,       ("TITLE"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, Dat_Itle,        ("ITLE"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, Dat_Variables,   ("VARIABLES"))
Q_GLOBAL_STATIC_WITH_ARGS(QString, Dat_Zone,        ("ZONE"))

DatParser::DatParser()
{
    m_pStuDatFile = new Dat();
}

DatParser::~DatParser()
{
    delete m_pStuDatFile;
}

bool DatParser::ParseFile(const QString& strFile)
{
    m_pTitle = "";
    m_pVariable = NULL;
    m_pZone = NULL;
    QTime qtime;
    qtime.start();
    QFile _file(strFile);
    if (!_file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream outStream(&_file);
    while (!outStream.atEnd())
    {
        QString lineTextData = outStream.readLine();
        LineDataProcess(lineTextData);
    }
    qDebug()<<qtime.elapsed()/1000.0<<"s";
    return true;
}

void DatParser::LineDataProcess(QString strline)
{
    if (strline.startsWith("TITLE") || strline.startsWith("ITLE"))
    {
        //DataArea::AREA_TITLE;
        this->SaveTitle(strline);
    }
    else if (strline.startsWith("VARIABLES"))
    {
        //DataArea::AREA_VARIBLE;
        this->SaveVariable(strline);
    }
    else if (strline.startsWith("ZONE"))
    {
        this->SaveZone(strline);
    }
    else
    {
        if (this->NoneDataLine(strline))
        {
            //DataArea::AREA_ZONE;
            m_pZone->pVariableAddr = m_pVariable;
            m_pZone->pTitleAddr = &m_pTitle;
            return;
        }
        this->SaveAreaData(strline,DataArea::AREA_ZONE);
    }
}

bool DatParser::NoneDataLine(QString strline)
{
    if (strline.isEmpty())
    {
        m_bIsGoneGRLF = true;
        return true;
    }
    return false;
}

void DatParser::SaveTitle(QString strline)
{
    QStringList strParts = strline.split('=');
    if (1 < strParts.count())
    {
        QString strGetTitle = this->EraseExtraChar(strParts.value(1));
        foreach (auto strExistTitle, m_pStuDatFile->allTitle)
        {
            if (*strExistTitle == strGetTitle)
            {
                m_pTitle = strExistTitle;
                return;
            }
        }
        m_pTitle = strGetTitle;
        m_pStuDatFile->allTitle.append(m_pTitle);
    }
}

void DatParser::SaveVariable(QString strline)
{
    auto strParts = strline.split('=');
    if (1 < strParts.count())
    {
        m_pVariable = new DatVariables();
        m_pStuDatFile->allVariable.append(m_pVariable);
        QString strVariables = strParts.value(1);
        strVariables = strVariables.replace("\t\t\t\t\t\t\t\t", ",");
        auto strVaribleParts = strVariables.split(',');
        for (int idx = 0; idx < strVaribleParts.size(); idx++)
        {
            auto strVar = this->EraseExtraChar(strVaribleParts.value(idx));
            m_pVariable->variableNames.append(strVar);
        }
    }
}

void DatParser::SaveZone(QString strline)
{
    strline = strline.remove(0, QString(Dat_Zone->data()).size());
    auto strZoneParts = strline.split(',');
    // 存储已解析的标题、变量要素数据
    if (NULL != m_pZone)
    {
        m_pZone->pVariableAddr = m_pVariable;
        m_pZone->pTitleAddr = m_pTitle;
    }
    m_pZone = new DatZones();
    m_pStuDatFile->allZone.append(m_pZone);
    foreach (auto oneZone, strZoneParts)
    {
        auto aZoneParts = oneZone.split('=');
        QString strZoneKey = this->EraseExtraChar(aZoneParts.value(0));
        QString strZoneValue = this->EraseExtraChar(aZoneParts.value(1));
        m_pZone->zoneHeaders[strZoneKey] = strZoneValue;
    }
}

void DatParser::SaveAreaData(QString strline,DataArea currArea)
{
    // 通过空格分割数据
    auto dataParts = strline.split(' ');
    // 边解析边校验 1、数据分区域校验 2、数据个数对应校验
    foreach (auto data, dataParts)
    {
        if (!data.isEmpty())
        {
            if (DataArea::AREA_VARIBLE == currArea)
            {
                auto fData = data.toFloat();
                m_pVariable->variableData.append(fData);
            }
            else if (DataArea::AREA_ZONE == currArea)
            {
                auto iData = data.toInt();
                m_pZone->zoneData.append(iData);
            }
        }
    }
}

QString DatParser::EraseExtraChar(QString strData)
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


InVertex DatParser::GetCoordinatesVertex(QString zoneName)
{
    InVertex vertexVector;
    foreach (auto pZone, m_pStuDatFile->allZone)
    {
        if (pZone->zoneHeaders.contains("T") && zoneName == pZone->zoneHeaders["T"])
        {
            auto varData = pZone->pVariableAddr;
            auto varCount = varData->variableNames.size();
            auto varXIndex = varData->variableNames.indexOf(m_stuVarSymbol.symbolX);
            auto varYIndex = varData->variableNames.indexOf(m_stuVarSymbol.symbolY);
            auto varZIndex = varData->variableNames.indexOf(m_stuVarSymbol.symbolZ);

            auto nTotalVarCount = varData->variableData.size();
            while (varXIndex < nTotalVarCount
                   && varYIndex < nTotalVarCount
                   && varZIndex < nTotalVarCount)
            {
                Vec3F varPoint3D;
                varPoint3D.one = varData->variableData.at(varXIndex);
                varPoint3D.two = varData->variableData.at(varYIndex);
                varPoint3D.three = varData->variableData.at(varZIndex);

                varXIndex += varCount;
                varYIndex += varCount;
                varZIndex += varCount;
            }
        }
    }
    return vertexVector;
}

QVector<InFaceIndex> DatParser::GetMeshersIndex(QString zoneName)
{
    QVector<InFaceIndex> indexArray;
    foreach (auto pZone, m_pStuDatFile->allZone)
    {
        if (pZone->zoneHeaders.contains("T") && zoneName == pZone->zoneHeaders["T"])
        {
            int nMeshCount = pZone->zoneHeaders["E"].toInt();
            int nMeshPointC = pZone->zoneData.size() / nMeshCount;
            int idx = 0;
            QVector<uint32_t> _Points;
            while (idx < pZone->zoneData.size())
            {
                _Points.append(pZone->zoneData.at(idx));
                if (idx != 0 && 0 == ((idx + 1) % nMeshPointC))
                {
                    InFaceIndex meshVector;
                    foreach (auto data, _Points)
                    {
                        meshVector.IndexsArray.append(data);
                    }
                    indexArray.append(meshVector);
                    _Points.clear();
                }
                idx++;
            }
        }
    }
    return indexArray;
}
