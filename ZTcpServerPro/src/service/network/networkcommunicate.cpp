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
    m_direct_oper = new AllFilePathInDir();
    if (!server->listen(QHostAddress::Any, 9999))
    {
        qFatal("Cannot listen on port 9999!");
    }
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    LOG_TCP("[INFO] Server started");
}

NetworkCommunicate::~NetworkCommunicate(void)
{
    if(nullptr!=m_direct_oper)
    {
        delete m_direct_oper;
        m_direct_oper = nullptr;
    }
    LOG_TCP("[INFO] Stopping the server...");
    foreach (QThread *thread, threadPool) {
        thread->quit();
        thread->wait();
        DEBUG_TCP("[thread %d] Deleted",thread);
        delete thread;
        thread = nullptr;
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
    //predict muti thread call function error
    connect(m_direct_oper,SIGNAL(signal_getFileAndDirPathNameOfSplDir(const QStringList )),handle,SLOT(slot_assignCurrFilesList(const QStringList )));
    connect(handle,SIGNAL(signal_getDirAndFileOfSplpath(QString)),m_direct_oper,SLOT(getFileAndDirPathNameOfSplDir(QString)));
    //create func destory func
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
