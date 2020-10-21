#include "commandhandle.h"
#include <QtCore>



CommandHandle::CommandHandle(NetworkCommunicate *n, QObject *parent) :
    QObject(parent), network(n)
{
    fin = new QFile(this);
    fin->open(stdin, QIODevice::ReadOnly);
    sin.setDevice(fin);
    fout = new QFile(this);
    fout->open(stdout, QIODevice::WriteOnly);
    sout.setDevice(fout);
}

CommandHandle::~CommandHandle()
{
    fin->close();
    fout->close();
    if(nullptr != network)
    {
        delete network;
    }
}

void CommandHandle::start(void)
{
loop:
    sout.flush();
    QString input(sin.readLine());
    if (input.isNull())
        goto loop;
    if (input == "stop")
    {
        qApp->quit();
        return;
    }
    else if (input == "state")
    {
        if (network->server->isListening())
            sout << "[INFO] Server listening\n";
        else
            sout << "[INFO] Server not listening\n";
    }
    goto loop;
}
