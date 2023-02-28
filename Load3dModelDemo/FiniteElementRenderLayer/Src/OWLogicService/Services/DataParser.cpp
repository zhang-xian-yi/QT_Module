#include "datparser.h"

#include "../Common/Src/ExtStruct.h"

namespace DatFileParse {

DatParser::DatParser()
{
    m_pStuDatFile = new Dat();
}

DatParser::~DatParser()
{
    delete m_pStuDatFile;
}

bool DatParser::ChooseDatDialog(QString strLocal)
{
    QFileDialog fileDialog;
    const QStringList filters({"dat files (*.dat)", "Any files (*)"});
    fileDialog.setNameFilters(filters);
    fileDialog.setFileMode(QFileDialog::FileMode::ExistingFiles);
    if (!strLocal.isEmpty())
    {
        fileDialog.setDirectory(strLocal);
    }
    fileDialog.setAcceptMode(QFileDialog::AcceptMode::AcceptOpen);
    if (fileDialog.exec())
    {
        QStringList files = fileDialog.selectedFiles();
        return this->SetFile(files);
    }
    return true;
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

QVector<QVector3D> DatParser::GetCoordinates()
{
    QVector<QVector3D> _data3D;
    foreach (auto pZone, m_pStuDatFile->allZone)
    {
        if (this->m_strTitle.compare(*pZone->pTitleAddr) == 0)
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
                QVector3D varPoint3D;
                varPoint3D.setX(varData->variableData.at(varXIndex));
                varPoint3D.setY(varData->variableData.at(varYIndex));
                varPoint3D.setZ(varData->variableData.at(varZIndex));
                _data3D.append(varPoint3D);
                varXIndex += varCount;
                varYIndex += varCount;
                varZIndex += varCount;
            }
        }
    }
    return _data3D;
}

QVector<CommonNS::InVertex> DatParser::GetCoordinatesVertex(QString zoneName)
{
    QVector<CommonNS::InVertex> vertexVector;
    foreach (auto pZone, m_pStuDatFile->allZone)
    {
        if (pZone->zoneHeaders.contains("T") && zoneName == pZone->zoneHeaders["T"])
        {
            if (this->m_strTitle.compare(*pZone->pTitleAddr) == 0)
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
                    CommonNS::Vec3F varPoint3D;
                    CommonNS::InVertex vertexCoord;
                    varPoint3D.one = varData->variableData.at(varXIndex);
                    varPoint3D.two = varData->variableData.at(varYIndex);
                    varPoint3D.three = varData->variableData.at(varZIndex);
                    vertexCoord.PostionXYZ = varPoint3D;
                    vertexVector.append(vertexCoord);
                    varXIndex += varCount;
                    varYIndex += varCount;
                    varZIndex += varCount;
                }
            }
        }
    }
    return vertexVector;
}

void DatParser::SetCurrentTitle(QString title)
{
    this->m_strTitle = title;
}

QVector<QVector<int> > DatParser::GetMeshers(QString zoneName)
{
    QVector<QVector<int>> _Meshers;
    foreach (auto pZone, m_pStuDatFile->allZone)
    {
        if (this->m_strTitle.compare(*pZone->pTitleAddr) == 0)
        {
            if (pZone->zoneHeaders.contains("T") && zoneName == pZone->zoneHeaders["T"])
            {
                int nMeshCount = pZone->zoneHeaders["E"].toInt();
                int nMeshPointC = pZone->zoneData.size() / nMeshCount;
                int idx = 0;
                QVector<int> _Points;
                while (idx < pZone->zoneData.size())
                {
                    _Points.append(pZone->zoneData.at(idx));
                    if (0 == (idx % nMeshPointC))
                    {
                        _Meshers.append(_Points);
                        _Points.clear();
                    }
                    idx++;
                }
            }
        }
    }
    return _Meshers;
}

QVector<CommonNS::InFaceIndex> DatParser::GetMeshersIndex(QString zoneName)
{
    QVector<CommonNS::InFaceIndex> indexArray;
    foreach (auto pZone, m_pStuDatFile->allZone)
    {
        if (this->m_strTitle.compare(*pZone->pTitleAddr) == 0)
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
                        CommonNS::InFaceIndex meshVector;
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
            if (*zone->pTitleAddr == this->m_strTitle)
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
            if (*zone->pTitleAddr == this->m_strTitle)
            {
                if (zone->zoneHeaders.contains("T") && zoneName == zone->zoneHeaders["T"])
                {
                    zoneInfoMap = zone->zoneHeaders;
                }
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
            if (*zone->pTitleAddr == this->m_strTitle)
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
    }
    return zoneNameList;
}

QVector<float> DatParser::GetValuesForOneVariable(QString var)
{
    QVector<float> _data1D;
    if (NULL != m_pStuDatFile)
    {
        foreach (auto varData, m_pStuDatFile->allVariable)
        {
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

QList<QVector2D> DatParser::GetValuesFor2D(QString varX, QString varY)
{
    QList<QVector2D> _data2D;
    if (NULL != m_pStuDatFile)
    {
        foreach (auto varData, m_pStuDatFile->allVariable)
        {
            auto varCount = varData->variableNames.size();
            auto varXIndex = varData->variableNames.indexOf(varX);
            auto varYIndex = varData->variableNames.indexOf(varY);
            auto nTotalVarCount = varData->variableData.size();
            while (varXIndex < nTotalVarCount
                   && varYIndex < nTotalVarCount)
            {
                QVector2D varPoint2D;
                varPoint2D.setX(varData->variableData.at(varXIndex));
                varPoint2D.setY(varData->variableData.at(varYIndex));
                _data2D.append(varPoint2D);
                varXIndex += varCount;
                varYIndex += varCount;
            }
        }
    }
    return _data2D;
}

QList<QVector3D> DatParser::GetValuesFor3D(QString varX, QString varY, QString varZ)
{
    QList<QVector3D> _data3D;
    if (NULL != m_pStuDatFile)
    {
        foreach (auto varData, m_pStuDatFile->allVariable)
        {
            auto varCount = varData->variableNames.size();
            auto varXIndex = varData->variableNames.indexOf(varX);
            auto varYIndex = varData->variableNames.indexOf(varY);
            auto varZIndex = varData->variableNames.indexOf(varZ);
            auto nTotalVarCount = varData->variableData.size();
            while (varXIndex < nTotalVarCount
                   && varYIndex < nTotalVarCount
                   && varZIndex < nTotalVarCount)
            {
                QVector3D varPoint3D;
                varPoint3D.setX(varData->variableData.at(varXIndex));
                varPoint3D.setY(varData->variableData.at(varYIndex));
                varPoint3D.setZ(varData->variableData.at(varZIndex));
                _data3D.append(varPoint3D);
                varXIndex += varCount;
                varYIndex += varCount;
                varZIndex += varCount;
            }
        }
    }
    return _data3D;
}

QList<QVector4D> DatParser::GetValuesFor4D(QString varX, QString varY, QString varZ, QString varW)
{
    QList<QVector4D> _data4D;
    if (NULL != m_pStuDatFile)
    {
        foreach (auto varData, m_pStuDatFile->allVariable)
        {
            auto varCount = varData->variableNames.size();
            auto varXIndex = varData->variableNames.indexOf(varX);
            auto varYIndex = varData->variableNames.indexOf(varY);
            auto varZIndex = varData->variableNames.indexOf(varZ);
            auto varWIndex = varData->variableNames.indexOf(varW);
            auto nTotalVarCount = varData->variableData.size();
            while (varXIndex < nTotalVarCount
                   && varYIndex < nTotalVarCount
                   && varZIndex < nTotalVarCount
                   && varWIndex < nTotalVarCount)
            {
                QVector4D varPoint4D;
                varPoint4D.setX(varData->variableData.at(varXIndex));
                varPoint4D.setY(varData->variableData.at(varYIndex));
                varPoint4D.setZ(varData->variableData.at(varZIndex));
                varPoint4D.setW(varData->variableData.at(varWIndex));
                _data4D.append(varPoint4D);
                varXIndex += varCount;
                varYIndex += varCount;
                varZIndex += varCount;
                varWIndex += varCount;
            }
        }
    }
    return _data4D;
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

void DatFileParse::DatParser::LineDataProcess(QString strline)
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

bool DatFileParse::DatParser::NoneDataLine(QString strline)
{
    if (strline.isEmpty())
    {
        m_bIsGoneGRLF = true;
        return true;
    }
    return false;
}

void DatFileParse::DatParser::SaveTitle(QString strline)
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

void DatFileParse::DatParser::SaveVariable(QString strline)
{
    auto strParts = strline.split('=');
    if (1 < strParts.count())
    {
        m_pVariable = new DatVariables();
        m_pStuDatFile->allVariable.append(m_pVariable);
        auto strVariables = strParts.value(1);
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

} // DatFileParse
