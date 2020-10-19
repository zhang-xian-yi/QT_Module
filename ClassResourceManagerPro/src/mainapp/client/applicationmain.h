#ifndef APPLICATIONMAIN_H
#define APPLICATIONMAIN_H
/**
* @brief: hfile for APplication
* @author zhangxianyi qq-1724920805@qq.com
* @date:  2020-10-15
* project ClassResourceManagerPro
*/
#include "tcpclient.h"
#include "resourcemanage.h"
class ApplicationMain:public QObject
{
    Q_OBJECT
public:
    explicit ApplicationMain();
    ~ApplicationMain();
    /**
    * @brief: 启动程序的接口
    * @param： void
    * @return: void
    * @date: 2020-10-15
    */
    void start();
private:
    /**
    * @brief: 初始化所需要的信号 和槽
    * @param：void
    * @return: void
    * @date: 2020-10-15
    */
    void initConnect();
private:
    ManageTcpCLient* m_client;
    ResourceManage* m_res_manage;
};

#endif // APPLICATIONMAIN_H
