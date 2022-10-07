#include "mysqloperation.h"

#include "user.h"
#include <QVector>
#include <QDateTime>

#define MYSQL_HOSTNAME      "localhost"
#define MYSQL_PORT          "3306"
#define MYSQL_DATABASENAME  "internet_of_thing"
#define MYSQL_USER          "root"
#define MYSQL_PASS          "123456"


MYSQLOperation::~MYSQLOperation()
{
    db_user.close();
}


static User& execSQLForOne(QString sql)
{
    QSqlQuery querySet;
    querySet.exec(sql);

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

MYSQLOperation::MYSQLOperation()
{
    db_user = QSqlDatabase::addDatabase("QMYSQL");

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

static void replaceSomeChar(QString& temp)
{
    temp.replace(".000","");
    temp.replace("T"," ");
}
QVector<UserHeartRate>& MYSQLOperation::getRateById(QString uid)
{
    QString sql = "select * from heart_rate where id="+uid;

    QSqlQuery querySet;
    querySet.exec(sql);

    static QVector<UserHeartRate> o_user;
    o_user.clear();

    while(querySet.next())
    {
        UserHeartRate temp;
        //解析数据
        QString id = querySet.value("id").toString();
        QString sql_time = querySet.value("time").toString();

        replaceSomeChar(sql_time);
        //qDebug()<<"sql time:"<<sql_time;
        QDateTime time = QDateTime::fromString(sql_time, "yyyy-MM-dd hh:mm:ss");
        //qDebug()<<"every time: "<<time.toString();

        int rate = querySet.value("rate").toString().toInt();
        //封装User
        temp.setUid(id);
        temp.setTime(time);
        temp.setRate(rate);


        o_user.append(temp);
    }
    return o_user;
}


User& MYSQLOperation::selectUserByUserId(QString _id)
{
    //创建执行语句的对象
    QString sql = "select * from users where userId="+_id;

    return execSQLForOne(sql);
}

User& MYSQLOperation::selectUserByName(QString _name)
{
    //如果是字符串的比较  必须在 sql 执行中加入 ‘’
    QString sql = "select * from users where userName= \'"+_name+" \' ";

    return execSQLForOne(sql);
}


bool MYSQLOperation::insertRateInfo(UserHeartRate &rate)
{
    //m_mysql_oper
    QSqlQuery query(this->db_user);
    query.prepare("insert into heart_rate(id,time,rate) VALUES (?,?,?)");
    query.addBindValue(rate.getUid());   //在绑定要插入的值
    query.addBindValue(rate.getTime());
    query.addBindValue(rate.getRate());
    return query.exec();
}

bool MYSQLOperation::updateRateInfo(UserHeartRate &i_old, UserHeartRate &i_new)
{
    QSqlQuery query(this->db_user);
    query.prepare("update heart_rate set time=?,rate=? where id=? and rate = ?");
    query.addBindValue(i_new.getTime());
    query.addBindValue(i_new.getRate());
    query.addBindValue(i_old.getUid());
    query.addBindValue(i_old.getRate());
    return query.exec();
}


bool MYSQLOperation::insertLedInfo(LedInfo &info)
{
    //m_mysql_oper
    //qDebug()<<"insert info: "<<info.toString();
    QSqlQuery query(this->db_user);
    query.prepare("insert into led_info(id,time,status) VALUES (?,?,?)");
    query.addBindValue(info.getId());   //在绑定要插入的值
    query.addBindValue(info.getTime());
    query.addBindValue(info.getStatus());
    bool ret = query.exec();
    /*
    if(!ret)
    {
        qDebug()<<"insert failed info: "<<query.lastError().text();
    }
    */
    return ret;
}

bool MYSQLOperation::updateLedInfo(LedInfo& old_info,LedInfo& new_info)
{
    QSqlQuery query(this->db_user);
    query.prepare("update led_info set time=?,status=? where id=? and time = ? and status = ?");
    query.addBindValue(new_info.getTime());
    query.addBindValue(new_info.getStatus());
    query.addBindValue(old_info.getId());
    query.addBindValue(old_info.getTime());
    query.addBindValue(old_info.getStatus());
    return query.exec();
}



