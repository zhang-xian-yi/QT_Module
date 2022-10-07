#include "DealRecvJsonMessage.h"
#include <QVector>

#define DATA_LENGTH     10

DealRecvJsonMessage::DealRecvJsonMessage(MYSQLOperation& sql_oper):
    m_mysql_oper(sql_oper)
{
   m_json_parse = new JSONParseUtil();
}

static UserHeartRate& getMaxTime(QVector<UserHeartRate> data)
{
    static UserHeartRate max;
    max = data.at(0);
    foreach(UserHeartRate rate,data)
    {
        if(rate > max)
        {
            max = rate;
        }
    }
    return max;
}

static UserHeartRate& getMinTime(QVector<UserHeartRate> data)
{
    static UserHeartRate min;
    min = data.at(0);
    foreach(UserHeartRate rate,data)
    {
        if(rate < min)
        {
            min = rate;
        }
    }
    return min;
}

void DealRecvJsonMessage::replaceNotMeanStr(QString &text)
{
    text.replace(QString("\n"),QString(""));
    text.replace(QString("\""),QString(""));
}

JSONParseUtil* DealRecvJsonMessage::getJsonParser()
{
    return m_json_parse;
}



void DealRecvJsonMessage::dealTemperatureInfo(const QByteArray &message)
{
    QString uid = ToQString(m_json_parse->getValueByKey(message.toStdString(),"userId"));
    replaceNotMeanStr(uid);
    if(uid.isEmpty()  || uid == "" || uid == nullptr)
    {
        return;
    }
    emit signal_info_ui_setUID(uid);
    User user = m_mysql_oper.selectUserByUserId(uid);
    if(! user.isEmpty())
    {
        QString content = "sql data match info:\n";
        content += user.toString();
        emit signal_info_ui_msg(content);
    }
    else
    {
        QString content = "the user is not exist";
        emit signal_main_ui_msg(content);
    }
}

void DealRecvJsonMessage::dealRateInfo(const QByteArray &message)
{
    std::string jsonstr = message.toStdString();
    QString id = ToQString(m_json_parse->getValueByKey(jsonstr,"userId"));
    replaceNotMeanStr(id);
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString rate_str =  ToQString(m_json_parse->getValueByKey(jsonstr,"rate"));
    replaceNotMeanStr(rate_str);
    int rate_int = rate_str.toInt();

    UserHeartRate rate(id,time,rate_int);
    //qDebug()<<"recv rate :"<<rate.toString();
    QVector<UserHeartRate> ret = m_mysql_oper.getRateById(id);
    if(ret.length() < DATA_LENGTH)
    {
        //insert
        m_mysql_oper.insertRateInfo(rate);
    }
    else if(ret.length() == DATA_LENGTH)
    {
        //update the oldest record
        UserHeartRate min = getMinTime(ret);
        m_mysql_oper.updateRateInfo(min,rate);
    }
}


void DealRecvJsonMessage::dealLedInfo(const QByteArray &message)
{
    std::string jsonstr = message.toStdString();
    QString id = ToQString(m_json_parse->getValueByKey(jsonstr,"led_id"));
    replaceNotMeanStr(id);

    QString value_str =  ToQString(m_json_parse->getValueByKey(jsonstr,"value"));
    replaceNotMeanStr(value_str);
    int value_int = value_str.toUtf8().toInt();

    static LedInfo info;
    info.setId(id);
    info.setValue(value_int);
    emit signal_deal_LedInfo(info);
}
