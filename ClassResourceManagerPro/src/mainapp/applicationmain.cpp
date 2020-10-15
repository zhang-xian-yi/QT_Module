/**
* @brief: 应用程序的启动窗口
* @author zhangxianyi qq-1724920805@qq.com
* @date:  2020-10-15
* project ClassResourceManagerPro
*/
#include "applicationmain.h"

ApplicationMain::ApplicationMain():
    m_res_manage(new ResourceManage)
{
    initConnect();
}

ApplicationMain::~ApplicationMain()
{
    if(nullptr != m_res_manage)
    {
        delete m_res_manage;
    }
}

void ApplicationMain::initConnect()
{
    //连接 业务类 和 界面类信息交互

}
void ApplicationMain::start()
{
    QString root_path = "G:/QT-project/";
    //m_res_manage->initFileList(root_path);

    //搜索文件
    //m_res_manage->findFile(root_path,"stringutil.h");

    //搜索文件夹
    //m_res_manage->findDirectory(root_path,"src");

    //创建文件夹
    //m_res_manage->createDirecty(root_path,"testResourceManager");
    //创建文件
    //m_res_manage->createFile(root_path+"/"+"testResourceManager","amp.txt");

    //删除文件
    //m_res_manage->deleteFileOrDirecty(root_path+"/"+"testResourceManager");

    //
}
