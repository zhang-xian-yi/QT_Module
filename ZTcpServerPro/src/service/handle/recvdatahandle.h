#ifndef RECVDATAHANDLE_H
#define RECVDATAHANDLE_H
#include <QObject>
#include <QTcpSocket>


class RecvDataHandle:public QObject
{
    Q_OBJECT
public:
    explicit RecvDataHandle(QTcpSocket *s,QObject *parent = nullptr);
    ~RecvDataHandle();
signals:
    void signal_getDirAndFileOfSplpath(QString path);

public slots:
    void start();
    void slot_assignCurrFilesList(const QStringList strs);

protected:
    /**
    * @brief:  timer response func
    * @param：  timer event
    * @return: void
    * @date: 2020-10-20
    */
    void timerEvent(QTimerEvent *);

signals:
    void finished(QThread *);

private slots:
    void disconnected();
    void read();
private:
    /**
    * @brief:  handle recv message type
    * @param：
    * @return:
    * @date: 2020-10-20
    */
    void handleRecvCmd(const QByteArray &data);

    void handleRecvFile(const QString &filename,const int& filesize,const QByteArray & data)const;
private:
    enum ECmdType
    {
        UPLOAD_FILE = 0,
        DOWNLOAD_FILE,
        SYN_FILE_LIST,
        MESSAGE ,
        CMD_LENGTH
    };
private:
    int timerID;
    qint64 bytesAvailable;
    QTcpSocket *socket;
    QStringList m_curr_file_list;
};

#endif // RECVDATAHANDLE_H
