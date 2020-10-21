#include "filehandle.h"
#include <QFile>
#include "stringutil.h"
#include "global.h"
FileHandle::FileHandle(QObject *parent) : QObject(parent)
{

}

const QByteArray& FileHandle::handleFile(const QString &filepath)
{
    if(!openFile(filepath))
    {
        DEBUG_NETWORK("error open file");
        return m_sendout;
    }
    DEBUG_NETWORK("[handle file :%s]",m_sendout.toStdString().c_str());
    return m_sendout;
}

bool FileHandle::openFile(const QString &filepath)
{
    QFile file(filepath);
    if(file.open(QIODevice::ReadOnly))
    {
        filename = StringUtil::getInstance().getLastNameofFilePath(filepath);
        file_size = file.size();
        m_cmd = UPLOAD_FILE;
        //清空一次数据
        m_sendout.clear();
        m_sendout.append(assignFileHeader());
        m_sendout.append(file.readAll());
        file.close();
        DEBUG_NETWORK("filename:%s\n",filename.toStdString().c_str());
        return true;
    }
    return false;
}

QString FileHandle::assignFileHeader()
{
    QString ret = QString::number(m_cmd)+"`"+QString::number(file_size)+"`"+filename+"`";
    return ret;
}
