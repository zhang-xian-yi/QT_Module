#ifndef FILEHANDLE_H
#define FILEHANDLE_H

#include <QObject>
#include <QDataStream>
#include <QByteArray>


class FileHandle : public QObject
{
    Q_OBJECT
public:
    explicit FileHandle(QObject *parent = nullptr);

public:
    /**
    * @brief:  返回输入字符串路径所构成的数据流
    * @param： filepath 传入文件路径
    * @return: 返回该数据流
    * @date: 2020-10-20
    */
    const QByteArray& handleFile(const QString& filepath);
private:
    /**
    * @brief:  打开文件
    * @param： 文件字符串
    * @return: bool
    * @date: 2020-10-20
    */
    bool openFile(const QString& filepath);
    /**
    * @brief: 设置 某个文件的文件头
    * @param： QFileInfo 文件描述类
    * @return: void
    * @date: 2020-10-20
    */
    QString assignFileHeader();
public:
    enum ECmdType
    {
        UPLOAD_FILE = 0,
        DOWNLOAD_FILE,
        SYN_FILE_LIST,
        MESSAGE ,
        CMD_LENGTH
    };
private:
    ECmdType m_cmd;
    int m_payloadsize;
    QByteArray m_sendout;
    QString filename;
    int file_size;
};

#endif // FILEHANDLE_H
