#include "networkcommunicate.h"

#include "recvdatahandle.h"
#include <QtDebug>
#include <QHostAddress>
#include <QThread>
#include "global.h"
NetworkCommunicate::NetworkCommunicate(QObject *parent) :
    QObject(parent)
{
    server = new QTcpServer(this);
    if (!server->listen(QHostAddress::Any, 9999))
    {
        qFatal("Cannot listen on port 6000!");
    }
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    LOG_TCP("[INFO] Server started");
}

NetworkCommunicate::~NetworkCommunicate(void)
{
    LOG_TCP("[INFO] Stopping the server...");
    foreach (QThread *thread, threadPool) {
        thread->quit();
        thread->wait();
        DEBUG_TCP("[thread %d] Deleted",thread);
        delete thread;
    }
}

void NetworkCommunicate::newConnection(void)
{
    //start a thread
    QThread *handleThread = new QThread(this);
    //save thread id
    threadPool.append(handleThread);
    //get socjet in the queue
    QTcpSocket *socket = server->nextPendingConnection();
    // if the thread finish then delete socket in the event queue
    connect(handleThread, SIGNAL(finished()), socket, SLOT(deleteLater()));

    RecvDataHandle *handle = new RecvDataHandle(socket);
    connect(handleThread, SIGNAL(started()), handle, SLOT(start()));
    connect(handleThread, SIGNAL(finished()), handle, SLOT(deleteLater()));
    connect(handle, SIGNAL(finished(QThread*)), this, SLOT(join(QThread*)));
    handle->moveToThread(handleThread);
    //start the thread
    handleThread->start();
}

void NetworkCommunicate::join(QThread *thread)
{
    thread->quit();
    thread->wait();
    threadPool.removeAll(thread);
    DEBUG_TCP("[thread %d] Deleted",thread);
    delete thread;
}
