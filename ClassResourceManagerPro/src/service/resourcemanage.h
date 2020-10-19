#ifndef RESOURCEMANAGE_H
#define RESOURCEMANAGE_H

#include "allfilepathindir.h"
#include <QObject>

class ResourceManage:public QObject
{
    Q_OBJECT
signals:
    void signal_log(const QStringList& list);
public slots:
    /**
    * @brief: 用于响应搜索函数的 槽
    * @param： splpath 指定路径
    *          name  文件名/文件夹名
    * @return:
    * @date: 2020-10-19
    */
    bool slot_search(const QString& path,const QString& txt);
public:
    explicit ResourceManage();
    ~ResourceManage();

    /**
    * @brief: 获取 传入路径之下的所有目录以及文件
    * @param： path
    * @return: void
    * @date: 2020-10-15
    */
    QStringList initFileList(const QString& path);

    /**
    @brief：在一个目录下查找指定文件
    @param：splpath,要搜索的路径
           filename,要搜索的文件名
    @return  返回搜索到的文件列表（路径+文件名）
    */
    QStringList findFile(const QString& splpath,const QString& file)const;

    /**
    @brief：在一个目录下查找指定目录（包含关系）
    @param：splpath,要搜索的路径
           filename,要搜索的目录名
    @return  返回搜索到的文件列表（路径）
    */
    QStringList findDirectory(const QString& splpath,const QString& direct_str)const;

    /**
    * @brief: 在指定路径下 创建-文件
    * @param： QString path   指定路径
    *          QString name   文件名
    * @return: bool
    * @date: 2020-10-15
    */
    bool createFile(const QString& path,const QString& name)const;

    /**
    * @brief: 在指定路径下 创建-文件夹
    * @param： QString path   指定路径
    *          QString name   文件夹名
    * @return: bool
    * @date: 2020-10-15
    */
    bool createDirecty(const QString& path,const QString& name)const;

    /**
    * @brief: 删除 文件/文件夹
    * @param：QString path
    * @return: bool
    * @date: 2020-10-15
    */
    bool deleteFileOrDirecty(const QString& path)const;

    /**
    * @brief: 重命名文件夹 /文件
    * @param：QString path   重命名（文件/文件夹）的路径
    *         Qstring name  新的名字
    * @return:
    * @date: 2020-10-15
    */
    bool renameFileOrDirectory(const QString& name,const QString &newname)const;
private:
    AllFilePathInDir* m_file_oper;
    QString m_curr_dir;

};

#endif // RESOURCEMANAGE_H
