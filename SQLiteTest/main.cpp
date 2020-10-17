#include <QCoreApplication>

#include "sqliteoper.h"
#include "global.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    SQLiteOper *oper = new SQLiteOper();
    QString table_name = "employers";
    QVector<QString> key;
    key.append("eid");
    key.append("ename");
    key.append("epassword");
    QVector<QString> key_type;
    key_type.append("long");
    key_type.append("varchar(32)");
    key_type.append("varchar(32)");
    SQLiteTable table(table_name,key,key_type);

    //oper->createTable(table);
    TRACE("main  xxxxxxxxxxxx");

    /*
    QVector<QString> value;
    value.append("0706200003");
    value.append("yangjiujie");
    value.append("666666");
    oper->insertRecord(table_name,value);
    */

    oper->deketeRecord(table_name,"eid","0706200002");

    delete oper;
    return a.exec();
}
