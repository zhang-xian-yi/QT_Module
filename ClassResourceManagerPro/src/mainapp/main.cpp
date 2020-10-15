/**
* @brief: 入口 main 函数
* @author zhangxianyi qq-1724920805@qq.com
* @date:  2020-10-15
* project ClassResourceManagerPro
*/

#include <QCoreApplication>
#include "applicationmain.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ApplicationMain main;
    main.start();

    return a.exec();
}
