#include "DataParser.h"

DatParser::DatParser()
{
    m_pStuDatFile = new Dat();
}

DatParser::~DatParser()
{
    delete m_pStuDatFile;
}

bool DatParser::SetFile(QString strFile)
{
    m_pTitle = NULL;
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
        this->LineDataProcess(lineTextData);
    }
    // 2023年2月25日 修复一个文件有多个zone时，其最后一个zone保存的标题和要素地址为空
    this->SaveLastZoneForTitleVar();
    qDebug()<<qtime.elapsed()/1000.0<<"s";
    return true;
}

bool DatParser::SetFile(QStringList strFiles)
{
    foreach (auto file, strFiles)
    {
        if (!this->SetFile(file))
        {
            return false;
        }
    }
    qDebug() << "Complete Parse!!!";
    return true;
}

void DatParser::SetCoordVarSymbol(CoordVarSymbol varSymbol)
{
    this->m_stuVarSymbol = varSymbol;
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
            // 获取物理量名称
            vertexVector.PhyQuaNameVec = this->GetPhysicalQuatityName(varData->variableNames);
            // 获取物理量的索引
            auto varPhyQuaNameIdx = this->GetPhysicalQuatityIndices(varData->variableNames, vertexVector.PhyQuaNameVec);
            auto nTotalVarCount = varData->variableData.size();
            while (varXIndex < nTotalVarCount
                   && varYIndex < nTotalVarCount
                   && varZIndex < nTotalVarCount)
            {
                Vec3F varPoint3D;
                varPoint3D.one = varData->variableData.at(varXIndex);
                varPoint3D.two = varData->variableData.at(varYIndex);
                varPoint3D.three = varData->variableData.at(varZIndex);
                CoordPhysical stCoordPhysi;
                stCoordPhysi.PostionXYZ = varPoint3D;
                stCoordPhysi.PhyQuaValueVec.append(this->GetPyhsicalVariableForValue(varData->variableData, varPhyQuaNameIdx, varCount));
                vertexVector.stCoordPhysicalVec.append(stCoordPhysi);
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

QStringList DatParser::GetTitles()
{
    QStringList titleList;
    if (NULL != m_pStuDatFile)
    {
        foreach (auto title, m_pStuDatFile->allTitle)
        {
            titleList.append(*title);
        }
    }
    return titleList;
}

QStringList DatParser::GetNameForVariables(QString zoneName)
{
    QStringList varList;
    if (NULL != m_pStuDatFile)
    {
        foreach (auto zone, m_pStuDatFile->allZone)
        {
            if (zone->zoneHeaders.contains("T") && zoneName == zone->zoneHeaders["T"])
            {
                foreach (auto zoneVar, zone->pVariableAddr->variableNames)
                {
                    if (!varList.contains(zoneVar))
                    {
                        varList.append(zoneVar);
                    }
                }
            }
        }
    }
    return varList;
}

QMap<QString, QString> DatParser::GetInfoForZone(QString zoneName)
{
    QMap<QString, QString> zoneInfoMap;
    if (NULL != m_pStuDatFile)
    {
        foreach (auto zone, m_pStuDatFile->allZone)
        {
            if (zone->zoneHeaders.contains("T") && zoneName == zone->zoneHeaders["T"])
            {
                zoneInfoMap = zone->zoneHeaders;
            }
        }
    }
    return zoneInfoMap;
}

QStringList DatParser::GetNameForZones()
{
    QStringList zoneNameList;
    if (NULL != m_pStuDatFile)
    {
        foreach (auto zone, m_pStuDatFile->allZone)
        {
            if (zone->zoneHeaders.contains("T"))
            {
                auto val = zone->zoneHeaders["T"];
                if (!zoneNameList.contains(val))
                {
                    zoneNameList.append(val);
                }
            }
        }
    }
    return zoneNameList;
}

QVector<float> DatParser::GetValuesForOneVariable(QString var)
{
    QVector<float> _data1D;
    if (NULL != m_pStuDatFile)
    {
        foreach (auto zone, m_pStuDatFile->allZone)
        {
            auto varData = zone->pVariableAddr;
            if (!varData->variableNames.contains(var))
            {
                continue;
            }
            auto varCount = varData->variableNames.size();
            auto varIndex = varData->variableNames.indexOf(var);
            while (varIndex < varData->variableData.size())
            {
                _data1D.append(varData->variableData.at(varIndex));
                varIndex += varCount;
            }
        }
    }
    return _data1D;
}

QVector<float> DatParser::GetValuesForOneVariable(QString var, QString zoneName)
{
    QVector<float> _data1D;
    if (NULL != m_pStuDatFile)
    {
        foreach (auto zone, m_pStuDatFile->allZone)
        {
            if (zone->zoneHeaders.contains("T") && zoneName == zone->zoneHeaders["T"])
            {
                auto varData = zone->pVariableAddr;
                auto varCount = varData->variableNames.size();
                auto varIndex = varData->variableNames.indexOf(var);
                while (varIndex < varData->variableData.size())
                {
                    _data1D.append(varData->variableData.at(varIndex));
                    varIndex += varCount;
                }
            }
        }
    }
    return _data1D;
}

QVector<float> DatParser::GetPyhsicalVariableForValue(const QVector<float> &srcData, QVector<int> &varIndices, const int &nVarCount)
{
    QVector<float> varValueVec;
    for (int nIdx = 0; nIdx < varIndices.size(); ++nIdx)
    {
        varValueVec.append(srcData.at(varIndices.at(nIdx)));
        varIndices[nIdx] += nVarCount;
    }
    return varValueVec;
}

QVector<QString> DatParser::GetPhysicalQuatityName(const QList<QString> &src)
{
    QVector<QString> physicalQuatityVec;
    foreach (auto name, src)
    {
        if (name != m_stuVarSymbol.symbolX && name != m_stuVarSymbol.symbolY && name != m_stuVarSymbol.symbolZ)
        {
            physicalQuatityVec.append(name);
        }
    }
    return physicalQuatityVec;
}

QVector<int> DatParser::GetPhysicalQuatityIndices(const QList<QString> &src, const QVector<QString> &phyQuaSrc)
{
    QVector<int> physiQuaIndices;
    foreach (auto phyQuaName, phyQuaSrc)
    {
        if (src.contains(phyQuaName))
        {
            physiQuaIndices.append(src.indexOf(phyQuaName));
        }
    }
    return physiQuaIndices;
}

QVector<int> DatParser::GetGridDataForZone(QString zone)
{
    QVector<int> zoneGridData;
    if (NULL != m_pStuDatFile)
    {
        foreach (auto var, m_pStuDatFile->allZone)
        {
            if (var->zoneHeaders.contains("T") &&
                    var->zoneHeaders["T"] == zone)
            {
                zoneGridData = var->zoneData;
            }
        }
    }
    return zoneGridData;
}

QStringList DatParser::GetFieldKeyNameForZone(QString zone)
{
    QStringList strList;
    if (NULL != m_pStuDatFile)
    {
        foreach (auto var, m_pStuDatFile->allZone)
        {
            if (var->zoneHeaders.contains("T") &&
                    var->zoneHeaders["T"] == zone)
            {
                foreach (auto varKey, var->zoneHeaders.keys())
                {
                    strList.append(varKey);
                }
            }
        }
    }
    return strList;
}

QString DatParser::GetOneValueForOneZone(QString zone, QString key)
{
    QString fieldValue;
    if (NULL != m_pStuDatFile)
    {
        foreach (auto var, m_pStuDatFile->allZone)
        {
            if (var->zoneHeaders.contains("T") &&
                    var->zoneHeaders["T"] == zone)
            {
                fieldValue = var->zoneHeaders[key];
            }
        }
    }
    return fieldValue;
}

void DatParser::LineDataProcess(QString strline)
{
    if (strline.startsWith(Dat_Title->data()) || strline.startsWith(Dat_Itle->data()))
    {
        m_emCurDataArea = DataArea::AREA_TITLE;
        this->SaveTitle(strline);
    }
    else if (strline.startsWith(Dat_Variables->data()))
    {
        m_emCurDataArea = DataArea::AREA_VARIBLE;
        this->SaveVariable(strline);
    }
    else if (strline.startsWith(Dat_Zone->data()))
    {
        if (m_bIsGoneGRLF && (DataArea::AREA_VARIBLE != m_emCurDataArea))
        {
            m_emCurDataArea = DataArea::AREA_ZONE;
        }
        this->SaveZone(strline);
    }
    else
    {
        if (this->NoneDataLine(strline))
        {
            m_emCurDataArea = DataArea::AREA_ZONE;
            m_pZone->pVariableAddr = m_pVariable;
            m_pZone->pTitleAddr = m_pTitle;
            return;
        }
        this->SaveAreaData(strline);
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
        m_pTitle = new QString();
        *m_pTitle = strGetTitle;
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
        QString strZoneKey = "", strZoneValue = "";
        for (int idx = 0; idx < aZoneParts.size(); ++idx)
        {
            if (0 == idx)
            {
                strZoneKey = this->EraseExtraChar(aZoneParts.value(idx));
            }
            else if (1 == idx)
            {
                strZoneValue = this->EraseExtraChar(aZoneParts.value(idx));
            }
        }
        m_pZone->zoneHeaders[strZoneKey] = strZoneValue;
    }
}

void DatParser::SaveAreaData(QString strline)
{
    // 通过空格分割数据
    auto dataParts = strline.split(' ');
    // 边解析边校验 1、数据分区域校验 2、数据个数对应校验
    foreach (auto data, dataParts)
    {
        if (!data.isEmpty())
        {
            if (DataArea::AREA_VARIBLE == m_emCurDataArea)
            {
                auto fData = data.toFloat();
                m_pVariable->variableData.append(fData);
            }
            else if (DataArea::AREA_ZONE == m_emCurDataArea)
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

void DatParser::SaveLastZoneForTitleVar()
{
    if (nullptr != m_pZone)
    {
        if (nullptr == m_pZone->pTitleAddr && nullptr != m_pTitle)
        {
            m_pZone->pTitleAddr = m_pTitle;
        }
        if (nullptr == m_pZone->pVariableAddr && nullptr != m_pVariable)
        {
            m_pZone->pVariableAddr = m_pVariable;
        }
    }
}



