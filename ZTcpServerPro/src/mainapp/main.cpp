#include <QCoreApplication>
#include <QThread>
#include "networkcommunicate.h"
#include "commandhandle.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    NetworkCommunicate n;


    QThread commandHandleThread;
    CommandHandle command(&n);
    command.moveToThread(&commandHandleThread);
    QObject::connect(&commandHandleThread, SIGNAL(started()), &command, SLOT(start()));
    commandHandleThread.start();

    app.exec();
    commandHandleThread.quit();
    commandHandleThread.wait();
    return 0;
}
