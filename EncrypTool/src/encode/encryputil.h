#ifndef ENCRYPUTIL_H
#define ENCRYPUTIL_H

#include <QString>
#include <QObject>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#define ENCRYP_MAX_SIZE     128
#include <string.h>

class EncrypUtil:public QObject
{
    Q_OBJECT
signals:
    void sendProgressBarSignal(int,int);
public:
    void encryptFile(const QString& filepath,const QString out_path);
    void decryptFile(const QString& filepath,const QString out_path);
};
#endif // ENCRYPUTIL_H
