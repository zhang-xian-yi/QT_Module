#include "md5Check.h"

Md5Check::Md5Check(QObject *parent) : QObject(parent)
{

}

void Md5Check::getMd5CheckSumSlot(QString checkFile)
{
    QFileInfo md5FileInfo;
    QString md5FileName = checkFile;
    qDebug() << md5FileName;
    QByteArray md5;

    qDebug() << "getMd5CheckSumSlot";
    md5FileInfo = QFileInfo(md5FileName);

    int loopIndex_ = 0;
    int fileSize =  int(md5FileInfo.size() / (1024 * 1024));
    qDebug() << "fileSize" << fileSize;
    if(md5FileInfo.exists())
    {
        QFile file(md5FileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            qDebug() << file.errorString();
        }
        else
        {
            qDebug() << "open sucess !";

            QCryptographicHash hash(QCryptographicHash::Md5);

            while(!file.atEnd())
            {
                QByteArray content = file.read(1024*1024); //1M
                hash.addData(content);
                emit sendProgressBarSignal(++loopIndex_, fileSize);
            }

            //emit sendProgressBarSignal(fileSize, fileSize);  //作弊

            md5  = hash.result().toHex();
            emit sendMd5CheckSunSignal(md5);
            qDebug() << md5;
        }
    }
}
