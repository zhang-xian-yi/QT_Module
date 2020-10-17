#ifndef MD5CHECK_H
#define MD5CHECK_H

#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QDebug>
#include <QCryptographicHash>


class Md5Check : public QObject
{
    Q_OBJECT
public:
    explicit Md5Check(QObject *parent = nullptr);

public:


signals:
    void sendMd5CheckSunSignal(const QByteArray &);
    void sendProgressBarSignal(int, int);

private slots:
    void getMd5CheckSumSlot(QString checkFile);

public slots:

};

#endif // MD5CHECK_H
