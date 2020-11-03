/**
* @brief: 应用程序的启动窗口
* @author zhangxianyi qq-1724920805@qq.com
* @date:  2020-10-15
* project ClassResourceManagerPro
*/
#include "applicationmain.h"
#include "stringutil.h"
ApplicationMain::ApplicationMain():
    m_client(new ManageTcpCLient),
    m_res_manage(new ResourceManage)
{
    initConnect();
}

ApplicationMain::~ApplicationMain()
{
    if(nullptr != m_res_manage)
    {
        delete  m_res_manage;
    }
    if(nullptr != m_client)
    {
        delete m_client;
        m_client = nullptr;
    }
}

void ApplicationMain::initConnect()
{
    //连接 业务类 和 界面类信息交互
    connect(m_res_manage,SIGNAL(signal_log(const QStringList& )),m_client,SLOT(LOG_sessionOut(const QStringList&)) );
    connect(m_client,SIGNAL(signal_find_str(const QString& ,const QString& )),m_res_manage,SLOT(slot_search(const QString&,const QString&)));

    connect(m_client,SIGNAL(signal_create(const QString&)),m_res_manage,SLOT(slot_create(const QString&)));
    connect(m_client,SIGNAL(signal_del(const QString&)),m_res_manage,SLOT(slot_del(const QString&)));
}
void ApplicationMain::start()
{
    m_client->show();
}
