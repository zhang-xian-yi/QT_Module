#ifndef USER_H
#define USER_H

#include <QString>
class User
{
public:
    User();
    User(const User& user);
    User(QString id);
    User(QString name,QString password);
    User(QString name,QString password,QString MACAddr);
    User(QString id,QString name,QString password,QString MACAddr);
    //get  or set funtion
    void setId(QString id);
    void setName(QString name);
    void setPassword(QString password);
    void setMACAddr(QString MacAddr);

    QString getId();
    QString getName();
    QString getPassword();
    QString getMACAddr();

    //tostring
    QString toString();
    //重载运算符
    User& operator =(const User& user);
    bool isEmpty();
private:
    QString userId;
    QString userName;
    QString password;
    QString macAddr;
};

#endif // USER_H
