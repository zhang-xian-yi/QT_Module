#ifndef RECVDATAHANDLE_H
#define RECVDATAHANDLE_H
#include <QObject>
#include <QTcpSocket>


class RecvDataHandle:public QObject
{
    Q_OBJECT
public:
    explicit RecvDataHandle(QTcpSocket *s, QObject *parent = nullptr);

public slots:
    void start();

protected:
    void timerEvent(QTimerEvent *);

signals:
    void finished(QThread *);

private slots:
    void disconnected();
    void read();

private:
    int timerID;
    qint64 bytesAvailable;
    QTcpSocket *socket;
};

#endif // RECVDATAHANDLE_H
