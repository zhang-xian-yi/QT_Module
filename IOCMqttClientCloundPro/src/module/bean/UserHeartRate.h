#ifndef USERHEARTRATE_H
#define USERHEARTRATE_H

#include <QString>
#include <QDateTime>


class UserHeartRate
{
public:
    UserHeartRate();
    UserHeartRate(QString u_id,QDateTime i_time,int rate);

	QString toString();
    QString getUid();
    void setUid(QString i_id);
    QDateTime getTime();
    void setTime(QDateTime i_time);
    int getRate();
    void setRate(int i_rate);
    bool isEmpty();
    bool operator> (UserHeartRate& temp);
    bool operator< (UserHeartRate& temp);
    bool operator== (UserHeartRate& temp);
private:
    QString m_user_id;
    QDateTime m_time;
    int m_rate;
};

#endif // USERHEARTRATE_H
