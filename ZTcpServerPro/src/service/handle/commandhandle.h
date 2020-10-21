#ifndef COMMANDHANDLE_H
#define COMMANDHANDLE_H
#include <QObject>
#include "networkcommunicate.h"


class CommandHandle : public QObject
{
    Q_OBJECT

public:
    explicit CommandHandle(NetworkCommunicate *n, QObject *parent = 0);
    ~CommandHandle();
signals:

public slots:
    void start(void);

private:
    QFile *fin, *fout;
    QTextStream sin, sout;
    NetworkCommunicate *network;
};

#endif // COMMANDHANDLE_H
