/**
* @brief: 资源管理类的 cpp 文件
* @author zhangxianyi qq-1724920805@qq.com
* @date:  2020-10-15
* project ClassResourceManagerPro
*/

#include "resourcemanage.h"
#include "global.h"
#include "stringutil.h"
#include <QDir>
#include <QFile>

ResourceManage::ResourceManage()
{

}

ResourceManage::~ResourceManage()
{

}

void ResourceManage::initFileList(const QString & path)
{
     //获取指定目录/及其子目录 文件的全路径
     m_resource = m_file_oper->getFilePathNameOfSplAndChildDir(path);
     LOG_INFO("init file list:%s\n\n",m_resource.join(",").toStdString().c_str());
}

QStringList ResourceManage::listFileByPath(const QString &path)
{
    return m_file_oper->getFileAndDirPathNameOfSplDir(path);
}

QStringList ResourceManage::findFile(const QString& splpath,const QString &filename)const
{
    QStringList m_Filelist;//找到的文件存入此队列
    QStringList matchFIleList;

    matchFIleList << m_file_oper->getFilePathNameOfSplAndChildDir(splpath);
    m_Filelist = StringUtil::getInstance().getMatchStr(m_resource,filename);
    LOG_INFO("find the file %s \n",m_Filelist.join(",").toStdString().c_str());
    return m_Filelist;
}

QStringList ResourceManage::findDirectory(const QString &splpath, const QString &direct_str)const
{
    QStringList t_driects = m_file_oper->getDirPathOfSplAndChildDir(splpath);
    QStringList t_ret_direct = StringUtil::getInstance().getMatchStr(t_driects,direct_str);
    LOG_INFO("final match directies :%s\n\n",t_ret_direct.join(",").toStdString().c_str());
    return t_ret_direct;
}
bool ResourceManage::createFile(const QString &path, const QString &name)const
{
    QString filename = path +"/"+name;
    TRACE_DEBUG("create file %s\n",filename.toStdString().c_str());
    static QFile file(filename);
    if( ! file.exists())
    {
        file.open( QIODevice::ReadWrite | QIODevice::Text );
        file.close();
        return true;
    }
    return false;
}

bool ResourceManage::createDirecty(const QString &path, const QString &name) const
{
    QString direct = path + "/" + name;
    TRACE_DEBUG("create direct %s\n",direct.toStdString().c_str());
    QDir dir(direct);
    if( ! dir.exists())
    {
        return dir.mkdir(direct);
    }
    return false;
}

bool ResourceManage::deleteFileOrDirecty(const QString &path)const
{
    TRACE_DEBUG("delete direct or file %s\n",path.toStdString().c_str());
    QFileInfo fileinfo(path);
    if(fileinfo.exists())
    {
        if(fileinfo.isDir())
        {
            QDir dir(path);
            dir.removeRecursively();
            return true;
        }
        else if(fileinfo.isFile())
        {
            QFile::remove(path);
            return true;
        }
    }
    return false;
}

bool ResourceManage::renameFileOrDirectory(const QString &oldpath,const QString &newname)const
{
    QFileInfo fileinfo(oldpath);
    if(fileinfo.exists())
    {
        if(fileinfo.isDir())
        {
            QDir dir(oldpath);
            QString root = StringUtil::getInstance().getParentPath(oldpath);
            dir.rename(oldpath,root+"/"+newname);
        }
        else if(fileinfo.isFile())
        {
            QString root = StringUtil::getInstance().getParentPath(oldpath);
            return QFile::rename(oldpath,root+"/"+newname);
        }
    }
}
