#include "recvdatahandle.h"
#include <QThread>
#include "global.h"

RecvDataHandle::RecvDataHandle(QTcpSocket *s, QObject *parent)
    : QObject(parent),
      socket(s)
{
}

void RecvDataHandle::start()
{
    bytesAvailable = 0;
    timerID = startTimer(10);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
    DEBUG_TCP("[recv data handle]:%d new connection coming",QThread::currentThread());
}

void RecvDataHandle::timerEvent(QTimerEvent *)
{
    qint64 bytes = bytesAvailable;
    bytesAvailable = socket->bytesAvailable();
    DEBUG_TCP("[recv data handle]:%d ,available bytes:%d",QThread::currentThread(),bytesAvailable);
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
    LOG_TCP("<threads: %p,ip:%s>recv data:%s",QThread::currentThread(),socket->peerName().toStdString().c_str(),data.toStdString().c_str());
}

void RecvDataHandle::disconnected()
{
    LOG_TCP("<ip:%s > dis connected",socket->peerName().toStdString().c_str());
    emit finished(QThread::currentThread());
}

void RecvDataHandle::read()
{
    if (!timerID)
    {
        timerID = startTimer(10);
    }
}
