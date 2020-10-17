#include <QCoreApplication>
#include "confighelperutil.h"

#include "global.h"

#include "encryputil.h"
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString filepath = QCoreApplication::applicationDirPath();
    filepath += "/sysConfig.ini";
    //EncrypUtil::encryptFile(filepath);


    TRACE("end set value");
    QString hostname =  ConfigHelperUtil::getInstance().getValue("MySQLConfig","hostname");
    QString port =  ConfigHelperUtil::getInstance().getValue("MySQLConfig","port");
    QString username =  ConfigHelperUtil::getInstance().getValue("MySQLConfig","username");
    QString password =  ConfigHelperUtil::getInstance().getValue("MySQLConfig","password");
    QString database = ConfigHelperUtil::getInstance().getValue("MySQLConfig","database");
    qDebug()<<"hostname: "<<hostname
           <<"\nport: "<<port
          <<"\nusername: "<<username
         <<"\ndatabase name: "<<database
         <<"\npassword: "<<password;

    EncrypUtil::encryptFile(filepath);
    return a.exec();
}
