#ifndef MYSQLOPERATION_H
#define MYSQLOPERATION_H

#include <QtSql>
#include <iostream>
#include <QVector>
#include <QSqlDatabase>
#include "user.h"
#include "UserHeartRate.h"
#include "ledinfo.h"

class MYSQLOperation
{
public:
       ~MYSQLOperation();
public:
    static MYSQLOperation& getInstance()
    {
        static MYSQLOperation instance;
        return instance;
    }

    User& selectUserByUserId(QString _id);
	User& selectUserByName(QString _name);
    QVector<UserHeartRate>& getRateById(QString uid);

    bool insertRateInfo(UserHeartRate& rate);
    bool updateRateInfo(UserHeartRate& i_old,UserHeartRate& i_new);

    bool insertLedInfo(LedInfo& info);
    bool updateLedInfo(LedInfo& old_info,LedInfo& new_info);
private:
    explicit MYSQLOperation();
    MYSQLOperation(const MYSQLOperation&)=delete;
    //MYSQLOperation& operator=(const MYSQLOperation&)=delete;

private:
    QSqlDatabase db_user;
};

#endif // MYSQLOPERATION_H
