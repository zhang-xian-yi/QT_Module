#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QtNetwork>
#include <QTcpSocket>
#include <QAbstractSocket>



namespace Ui {
class ManageTcpCLient;
}

class ManageTcpCLient : public QWidget
{
    Q_OBJECT
public:
    explicit ManageTcpCLient(QWidget *parent = nullptr);
    ~ManageTcpCLient();

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

private:
    /**
    * @brief:  初始化ui 界面的信号与槽
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

private:
    Ui::ManageTcpCLient *ui;
    QTcpSocket* socket = nullptr;
    bool handlingSocketError = false;

};

#endif // TCPCLIENT_H
