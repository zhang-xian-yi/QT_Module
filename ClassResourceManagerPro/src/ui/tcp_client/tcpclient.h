#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QtNetwork>
#include <QTcpSocket>
#include <QAbstractSocket>

#include "allfilepathindir.h"

namespace Ui {
class ManageTcpCLient;
}

class ManageTcpCLient : public QWidget
{
    Q_OBJECT
public:
    explicit ManageTcpCLient(QWidget *parent = nullptr);
    ~ManageTcpCLient();

signals:
    /**
    * @brief:  发送 寻找该字符串匹配的目录
    * @date: 2020-10-19
    */
    void signal_find_str(const QString& path,const QString& txt);
public slots:
    /**
    * @brief:  将传入的数据 写入 session output 平台
    * @date: 2020-10-19
    */
    void LOG_sessionOut(const QStringList& str);
public:

    /**
    * @brief:  根据输入的根路径 set 客户端的列表项目
    * @param： QStringList 保存有列表项的所有结构
    * @return: true succeed  false failed load
    * @date: 2020-10-19
    */
    bool setClientListview(const QStringList& list);



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
    * @brief: 套接字准备就绪 并在output 中输出
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

    /**
    * @brief:  上传文件到指定的服务器
    * @param：  QString  splpath 文件全路径
    * @return: bool
    * @date: 2020-10-19
    */
    bool on_btn_upload();

    /**
    * @brief: 响应client 单击事件
    * @param：
    * @return:
    * @date: 2020-10-19
    */
    void on_clientlistview_item_clicked(const QModelIndex &index);
private:
    Ui::ManageTcpCLient *ui;
    QTcpSocket* socket = nullptr;
    AllFilePathInDir* m_file_oper;
    bool handlingSocketError = false;
    QString m_upload_file_dir;
};

#endif // TCPCLIENT_H
