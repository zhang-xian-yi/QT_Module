#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QtNetwork>
#include <QTcpSocket>
#include <QAbstractSocket>

#include "allfilepathindir.h"
#include "filehandle.h"
namespace Ui {
class ManageTcpCLient;
}

class ManageTcpCLient : public QWidget
{
    Q_OBJECT
public:
    explicit ManageTcpCLient(QWidget *parent = nullptr);
    ~ManageTcpCLient();
    enum ECmdType
    {
        UPLOAD_FILE = 0,
        DOWNLOAD_FILE,
        SYN_FILE_LIST,
        MESSAGE ,
        CMD_LENGTH
    };
signals:
    /**
    * @brief:  发送 寻找该字符串匹配的目录
    * @date: 2020-10-19
    */
    void signal_find_str(const QString& path,const QString& txt);
    /**
    * @brief:  发送 寻找该字符串匹配的目录
    * @date: 2020-10-19
    */
    void signal_create(const QString& path);
    /**
    * @brief:  发送 寻找该字符串匹配的目录
    * @date: 2020-10-19
    */
    void signal_del(const QString& path);

public slots:
    /**
    * @brief:  将传入的数据 写入 session output 平台
    * @date: 2020-10-19
    */
    void LOG_sessionOut(const QStringList& str);
public:

    /**
    * @brief:  根据输入的路径列表 set 客户端的列表项目
    * @param： QStringList 保存有列表项的所有结构
    * @return: true succeed  false failed load
    * @date: 2020-10-19
    */
    bool setClientListview(const QStringList& list);

    /**
    * @brief:  根据输入 的list 初始化服务器的文件列表
    * @param： list 文件列表
    * @return: bool
    * @date: 2020-10-21
    */
    bool setServerListView(const QStringList& list);

private slots:
    /**
    * @brief:  建立 socket连接
    * @param： void
    * @return: void
    * @date: 2020-10-16
    */
    void connectTo();

    /**
    * @brief: connect 按钮的 响应
    * @param：
    * @return:
    * @date: 2020-10-16
    */
    void on_btn_connect();
    /**
    * @brief: 断开socket 连接
    * @param：
    * @return:
    * @date: 2020-10-16
    */
    void disConnect();
    /**
    * @brief:  根据连接状态 update 按钮/编辑框/ 的Enable
    * @param：void
    * @return: void
    * @date: 2020-10-16
    */
    void updateEnabledState();

    /**
    * @brief: 向连接的服务端发送数据
    * @param：void
    * @return: void
    * @date: 2020-10-16
    */
    void sendData();

    /**
    * @brief: 套接字连接状态改变的响应函数
    * @param：
    * @return:
    * @date: 2020-10-16
    */
    void socketStateChanged(QAbstractSocket::SocketState state);

    /**
    * @brief: socket 发送错误
    * @param：
    * @return:
    * @date: 2020-10-16
    */
    void socketError(QAbstractSocket::SocketError error);

    /**
    * @brief: 套接字读取准备就绪 并在output 中输出
    * @param：
    * @return:
    * @date: 2020-10-16
    */
    void socketReadyRead();

    /**
    * @brief: 响应client dir list 的双击item 信号并通知 资源管理服务
    * @param：
    * @return:
    * @date: 2020-10-19
    */
    void doubleClickedClientListItem(const QModelIndex &index);


    /**
    * @brief: btn_search 的响应函数
    * @param：   void
    * @return:   void
    * @date: 2020-10-19
    */
    void on_btn_search();
    /**
    * @brief:  上传文件到指定的服务器
    * @param：  QString  splpath 文件全路径
    * @return: bool
    * @date: 2020-10-19
    */
    bool on_btn_upload();

    /**
    * @brief: 响应client 单击事件
    * @param：const QModelIndex &index
    * @return: void
    * @date: 2020-10-19
    */
    void on_clientlistview_item_clicked(const QModelIndex &index);

    /**
    * @brief: 响应server list view 的点击事件
    * @param： const QModelIndex &index   列表的index
    * @return: void
    * @date: 2020-10-20
    */
    void on_serverListview_item_clicked(const QModelIndex &index);

    /**
    * @brief: 响应btn_create file 的点击事件
    * @param：
    * @return: void
    * @date: 2020-10-20
    */
    void slot_btn_create_file_clicked();
    /**
    * @brief: 响应btn_create dir 的点击事件
    * @param：
    * @return: void
    * @date: 2020-10-20
    */
    void slot_btn_create_dir_clicked();

    /**
    * @brief: 响应btn_del file 的点击事件
    * @param：
    * @return: void
    * @date: 2020-10-20
    */
    void slot_btn_del_file_clicked();
    /**
    * @brief: 响应btn_create dir 的点击事件
    * @param：
    * @return: void
    * @date: 2020-10-20
    */
    void slot_btn_del_dir_clicked();



    /**
    * @brief: 从服务器下载文件
    * @param：
    * @return:
    * @date: 2020-10-20
    */
    void on_btn_download();

    /**
    * @brief: 同步服务器的文件列表
    * @param：
    * @return:
    * @date: 2020-10-20
    */
    void on_btn_syn_clicked();
private:
    /**
    * @brief: 初始化客户端文件列表
    * @param： void
    * @return: void
    * @date: 2020-10-19
    */
    void initClientFileList();
    /**
    * @brief:  设置 ui 界面的信号与槽
    * @param： void
    * @return: void
    * @date: 2020-10-16
    */
    void setupUiConn();
    /**
    * @brief: 初始化 ssl 连接套接字 以及其信号槽
    * @param： void
    * @return: void
    * @date: 2020-10-16
    */
    void setupSecureSocket();
    /**
    * @brief:  向output 输出框显示 发出的数据
    * @param： line   客户端发送的数据
    * @return: void
    * @date: 2020-10-16
    */
    void appendString(const QString &line);

    /**
    * @brief: 初始化其他连接
    * @param：
    * @return:
    * @date: 2020-10-19
    */
    void initConnect();


private:
    Ui::ManageTcpCLient *ui;
    QTcpSocket* socket = nullptr;
    AllFilePathInDir* m_file_oper;
    FileHandle* m_handle_file;
    bool handlingSocketError = false;
    QString m_upload_file_dir;
    QString m_download_file_dir;
    QString m_client_click_dir;
};

#endif // TCPCLIENT_H
