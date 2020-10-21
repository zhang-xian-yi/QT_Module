#include "recvdatahandle.h"
#include <QThread>
#include "global.h"
#include <QHostAddress>
#include <QFile>
#include "allfilepathindir.h"
#include "stringutil.h"

RecvDataHandle::RecvDataHandle(QTcpSocket *s,QObject *parent)
    : QObject(parent),
      socket(s)
{
}

RecvDataHandle::~RecvDataHandle()
{

}

void RecvDataHandle::start()
{
    //init the file list
    emit signal_getDirAndFileOfSplpath("data/");
    bytesAvailable = 0;
    timerID = startTimer(10);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
    DEBUG_TCP("[client:ip:%s,thread  %p]: new connection coming",
              socket->peerAddress().toString().toStdString().c_str(),
              QThread::currentThread());
}

void RecvDataHandle::timerEvent(QTimerEvent *)
{   
    qint64 bytes = bytesAvailable;
    bytesAvailable = socket->bytesAvailable();
    //DEBUG_TCP("[client:ip:%s,thread  %p],available bytes:%d", \
              socket->peerAddress().toString().toStdString().c_str(),\
              QThread::currentThread(),\
              bytesAvailable);
    if (bytesAvailable != bytes)
    {
        return;
    }

    killTimer(timerID);
    timerID = 0;
    if (bytesAvailable == 0)
    {
        return;
    }

    bytesAvailable = 0;

    QByteArray data = socket->readAll();
    handleRecvCmd(data);
    //LOG_TCP("<threads: %p,ip:%s>recv data:%s",QThread::currentThread() \
            ,socket->peerAddress().toString().toStdString().c_str()\
            ,data.toStdString().c_str());

}

void RecvDataHandle::disconnected()
{
    LOG_TCP("<ip:%s > dis connected",socket->peerAddress().toString().toStdString().c_str());
    emit finished(QThread::currentThread());
}

void RecvDataHandle::read()
{
    if (!timerID)
    {
        timerID = startTimer(100);
    }
}
void RecvDataHandle::slot_assignCurrFilesList(const QStringList strs)
{
    m_curr_file_list = strs;
}
void RecvDataHandle::handleRecvCmd(const QByteArray &data)
{
    QList<QByteArray> array = data.split('`');
    int cmd_type = array[0].toInt();
    LOG_TCP("cmd is %s",data.toStdString().c_str());
    switch (cmd_type)
    {
        case UPLOAD_FILE:
        {
            int filesize = array[1].toInt();
            QString filepath = array[2];
            QByteArray content = array[3];
            handleRecvFile(filepath,filesize,content);
            break;
        }
        case DOWNLOAD_FILE:
        {
            QString filename = StringUtil::getInstance().getLastNameofFilePath(array[1]);
            QString path = "data/"+filename;
            QFile file(path);
            LOG_TCP("server RECV download file: %s",path.toStdString().c_str());
            if(file.exists())
            {
                if(file.open(QIODevice::ReadOnly))
                {
                    QByteArray send_data;
                    send_data.append(QString::number(DOWNLOAD_FILE)+'`');
                    send_data.append(filename+'`');
                    send_data.append( file.readAll() );
                    socket->write(send_data);
                    LOG_TCP("server send data: %s",send_data.toStdString().c_str());
                    file.close();
                }
            }
            break;
        }
        case SYN_FILE_LIST:
        {
            emit signal_getDirAndFileOfSplpath("data/");
            m_curr_file_list = StringUtil::getInstance().getLastNameOfFileList(m_curr_file_list);
            QString data = QString::number(SYN_FILE_LIST)+"`"+m_curr_file_list.join(",").toStdString().c_str();
            socket->write(data.toStdString().c_str());
            DEBUG_FILE("data :%s",data.toStdString().c_str());
            break;
        }
        case MESSAGE:
        {
            break;
        }
        default:break;
    }
}

void RecvDataHandle::handleRecvFile(const QString &filename,const int& filesize,const QByteArray & data)const
{
    QString path = "data/"+filename;
    QFile file(path);
    if(! file.exists())
    {
        if(file.open(QIODevice::ReadWrite))
        {
            file.write(data);
            file.waitForBytesWritten(1000);
        }
        file.close();
    }
}
