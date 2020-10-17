#include <QCoreApplication>
#include "mysqloperation.h"

using namespace  std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MYSQLOperation oper;

    User user = oper.selectUserByUserId("41704442");
    qDebug()<<user.toString();

    return a.exec();
}
