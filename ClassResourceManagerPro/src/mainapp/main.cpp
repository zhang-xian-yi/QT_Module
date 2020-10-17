/**
* @brief: 入口 main 函数
* @author zhangxianyi qq-1724920805@qq.com
* @date:  2020-10-15
* project ClassResourceManagerPro
*/

#include <QApplication>
#include "applicationmain.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ApplicationMain appmain;
    appmain.start();

    return a.exec();
}



