#ifndef MYSQLOPERATION_H
#define MYSQLOPERATION_H

#include <QtSql>
#include <iostream>
#include "User.h"
#include <QVector>
#include <QSqlDatabase>

class MYSQLOperation
{
public:
    MYSQLOperation();
    ~MYSQLOperation();
    User& selectUserByUserId(QString _id);
public:
    User *user;
private:
    QSqlDatabase db_user;
};

#endif // MYSQLOPERATION_H
