#include "mysqloperation.h"

#define MYSQL_HOSTNAME      "localhost"
#define MYSQL_PORT          "3306"
#define MYSQL_DATABASENAME  "internet_of_thing"
#define MYSQL_USER          "root"
#define MYSQL_PASS          "123456"

MYSQLOperation::MYSQLOperation()
{
    db_user = QSqlDatabase::addDatabase("QMYSQL");
    user = nullptr;

    //设置 该链接的属性
    db_user.setHostName(MYSQL_HOSTNAME);
    db_user.setPort(3306);
    db_user.setDatabaseName(MYSQL_DATABASENAME);
    db_user.setUserName(MYSQL_USER);
    db_user.setPassword(MYSQL_PASS);

    //测试是否连接成功
    if(! db_user.open() )
    {
        std::cout<<"connect failed"<<std::endl;
    }
}

MYSQLOperation::~MYSQLOperation()
{
    if(user!=nullptr)
    {
        delete user;
    }
}

User& MYSQLOperation::selectUserByUserId(QString _id)
{
    //创建执行语句的对象
    QString sql = "select * from users where userId="+_id;
    QSqlQuery querySet;
    querySet.exec(sql);
    //只有一条数据
    //封装User
    static User o_user;
    while(querySet.next())
    {
        //解析数据
        QString user_id = querySet.value("userId").toString();
        QString user_name = querySet.value("userName").toString();
        QString user_password = querySet.value("password").toString();
        QString user_mac = querySet.value("macAddr").toString();
        //封装User
        o_user.setId(user_id);
        o_user.setName(user_name);
        o_user.setPassword(user_password);
        o_user.setMACAddr(user_mac);
    }
    return o_user;
}
