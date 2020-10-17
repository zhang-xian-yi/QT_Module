#include "User.h"

User::User()
{

}

User::User(const User& user)
{
    this->userId = user.userId;
    this->userName = user.userName;
    this->password = user.password;
    this->macAddr = user.macAddr;
}

User::User(QString id)
{
    this->userId = id;
}
User::User(QString name, QString password)
{
    User(name,password,nullptr,nullptr);
}

User::User(QString name, QString password, QString mac)
{
    this->userName=name;
    this->password=password;
    this->macAddr=mac;
}

User::User(QString userId,QString name, QString password,QString mac)
{
    this->userId = userId;
    this->userName=name;
    this->password=password;
    this->macAddr=mac;
}

//get and set funtion

QString User::getId()
{
    return this->userId;
}

QString User::getName()
{
    return this->userName;
}

QString User::getPassword()
{
    return this->password;
}

QString User::getMACAddr()
{
    return this->macAddr;
}


void User::setMACAddr(QString mac)
{
    this->macAddr = mac;
}

void User::setId(QString userId)
{
    this->userId = userId;
}

void User::setName(QString name)
{
    this->userName = name;
}

void User::setPassword(QString password)
{
    this->password = password;
}


//tostring

QString User::toString()
{
    QString str="userId: ";
    str +=this->getId();

    str += " name: ";
    str +=this->getName();

    str += " password: ";
    str += this->getPassword();

    str += " MacAddr: ";
    str += this->getMACAddr();

    return str;
}

//重载运算符
User& User::operator =(const User& user)
{
    if(this!=&user)
    {
        this->userId = user.userId;
        this->userName = user.userName;
        this->password = user.password;
        this->macAddr = user.macAddr;
    }
    return *this;
}
