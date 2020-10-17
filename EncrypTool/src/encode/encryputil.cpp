#include "encryputil.h"
#include "global.h"
#include <QFile>
#include <QChar>
#include <QTextStream>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

static QString getOutFilePath(const QString filepath,const QString out_path)
{
    //写入指定文件
    int last_index = filepath.lastIndexOf("/");
    QString file_name = filepath.right(filepath.length()-last_index-1);
    QString out_file_path = out_path+"/"+file_name;
    TRACE("out_file_path: %s\n",out_file_path.toLatin1().data());
    return out_file_path;
}


void EncrypUtil::encryptFile(const QString& filepath,const QString out_path)
{
    QFile in_file(filepath);
    QTextStream in(&in_file);
    QString str;
    if(in_file.open(QIODevice::ReadOnly))
    {
        str = in.readAll();
        TRACE("read in file %s\n",str.toStdString().c_str());

        int len = str.length();
        for(int i=0;i<len;++i)
        {
            str[i] = QChar::fromLatin1(str[i].toLatin1() - 1);
        }
        TRACE("write in file %s\n",str.toStdString().c_str());
    }
    in_file.close();



    QFile out_file(getOutFilePath(filepath,out_path));
    if(out_file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&out_file);
        out << str;
        out.flush();
        emit sendProgressBarSignal(str.length(),str.length());
    }
    out_file.close();
}



void EncrypUtil::decryptFile(const QString& filepath,const QString out_path)
{
    QFile file(filepath);
    QTextStream fin(&file);
    QString str;
    if(file.open(QIODevice::ReadOnly))
    {
        str = fin.readAll();
        int len = str.length();
        for(int i=0;i<len;++i)
        {
            str[i] = QChar::fromLatin1(str[i].toLatin1() + 1);
        }
        TRACE("deencryp write in file %s\n",str.toStdString().c_str());
    }
    file.close();

    QFile out_file(getOutFilePath(filepath,out_path));
    if(out_file.open(QIODevice::WriteOnly))
    {
        QTextStream fout(&out_file);
        fout << str;
        out_file.flush();
        emit sendProgressBarSignal(str.length(),str.length());
    }
    out_file.close();
}






