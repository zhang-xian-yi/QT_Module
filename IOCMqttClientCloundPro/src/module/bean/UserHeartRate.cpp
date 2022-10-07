#include "UserHeartRate.h"

UserHeartRate::UserHeartRate()
{
    this->m_user_id = "";
    this->m_rate = 0;
}


UserHeartRate::UserHeartRate(QString u_id,QDateTime i_time,int rate)
{
    this->m_user_id = u_id;
    this->m_time = i_time;
    this->m_rate = rate;
}

QString UserHeartRate::getUid()
{
    return this->m_user_id;
}

void UserHeartRate::setUid(QString i_id)
{
    this->m_user_id = i_id;
}

QDateTime UserHeartRate::getTime()
{
    return this->m_time;
}

void UserHeartRate::setTime(QDateTime i_time)
{
    this->m_time = i_time;
}

int UserHeartRate::getRate()
{
    return  this->m_rate;
}

void UserHeartRate::setRate(int i_rate)
{
    this->m_rate = i_rate;
}

QString UserHeartRate::toString()
{

    QString content = "uid:"+QString(this->m_user_id)+"\t";
    content += "time: "+this->m_time.toString("yyyy-MM-dd hh:mm:ss")+ "\t";
    content += "rate: "+QString::number(this->m_rate)+"\n";

    return content;
}

bool UserHeartRate::operator<(UserHeartRate &temp)
{
    uint this_time = this->getTime().toTime_t();
    uint temp_time = temp.getTime().toTime_t();

    if(this_time < temp_time)
    {
        return true;
    }
    return false;
}

bool UserHeartRate::operator>(UserHeartRate &temp)
{
    uint this_time = this->getTime().toTime_t();
    uint temp_time = temp.getTime().toTime_t();

    if(this_time > temp_time)
    {
        return true;
    }
    return false;
}

bool UserHeartRate::operator==(UserHeartRate &temp)
{
    uint this_time = this->getTime().toTime_t();
    uint temp_time = temp.getTime().toTime_t();

    if(this_time == temp_time)
    {
        return true;
    }
    return false;
}

bool UserHeartRate::isEmpty()
{
    return this->m_user_id == "";
}



