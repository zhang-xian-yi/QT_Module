#include "ledinfo.h"

LedInfo::LedInfo()
{

}

QString LedInfo::getId()
{
    return this->id;
}

void LedInfo::setId(QString i_id)
{
    this->id = i_id;
}

QDateTime LedInfo::getTime()
{
    return this->time;
}

void LedInfo::setTime(QDateTime i_time)
{
    this->time = i_time;
}

int LedInfo::getStatus()
{
    return this->status;
}

void LedInfo::setStatus(int i_status)
{
    this->status = i_status;
}

int LedInfo::getValue()
{
    return this->value;
}

void LedInfo::setValue(int i_value)
{
    this->value = i_value;
}

QString LedInfo::toString()
{
    QString content = "id: "+ this->id + "  value: "+QString::number(this->value) ;
    content += "    time:  "+this->time.toString("yyyy-MM-dd hh:mm:ss");
    return content;
}
