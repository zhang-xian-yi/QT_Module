#include "allfilepathindir.h"
#include <QFileInfo>
#include <QFileInfoList>
#include <QDir>

#include "global.h"

AllFilePathInDir::AllFilePathInDir()
{

}

AllFilePathInDir::~AllFilePathInDir()
{

}

QString AllFilePathInDir::getRootPath() const
{
    return this->m_root_path;
}

void AllFilePathInDir::setRootPath(const QString& path)
{
    this->m_root_path = path;
}
QStringList AllFilePathInDir::getFilePathNameOfSplDir(QString dirPath)
{
    QStringList filePathNames;
    QDir splDir(dirPath);
    QFileInfoList fileInfoListInSplDir = splDir.entryInfoList(QDir::Files);
    QFileInfo tempFileInfo;
    foreach (tempFileInfo, fileInfoListInSplDir) {
        // absoluteFilePath()   -- 截取到的是文件夹的路径
        // absolutePath()       -- 截取的是文件夹所在路径
        filePathNames << tempFileInfo.absoluteFilePath();
    }
    TRACE_DEBUG("Gets the file (path + name) in the specified directory: \n %s\n",filePathNames.join(",").toStdString().c_str());
    return filePathNames;
}

QStringList AllFilePathInDir::getDirPathOfSplDir(QString dirPath)
{
    QStringList dirPaths;
    QDir splDir(dirPath);
    QFileInfoList fileInfoListInSplDir = splDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    QFileInfo tempFileInfo;
    foreach (tempFileInfo, fileInfoListInSplDir) {
        dirPaths << tempFileInfo.absoluteFilePath();
    }
    TRACE_DEBUG("Gets the path to the directory under the specified directory:\n %s\n",dirPaths.join(",").toStdString().c_str());
    return dirPaths;
}

QStringList AllFilePathInDir::getFileAndDirPathNameOfSplDir(QString dirPath)
{
    QStringList fileAndDirPathNames;
    fileAndDirPathNames << getFilePathNameOfSplDir(dirPath);
    fileAndDirPathNames << getDirPathOfSplDir(dirPath);
    TRACE_DEBUG("Gets the full path to the file and directory in the specified directory:\n %s\n",fileAndDirPathNames.join(",").toStdString().c_str());
    return fileAndDirPathNames;
}

int AllFilePathInDir::fileConutInSplDir(QString dirPath)
{
    int count = QDir(dirPath).entryList(QDir::Files).count();
    TRACE_DEBUG("Get file nums in the specified directory:\n %d\n",count);
    return count;
}

int AllFilePathInDir::dirCountInSplDir(QString dirPath)
{
    int count = QDir(dirPath).entryList(QDir::Dirs | QDir::NoDotAndDotDot).count();
    TRACE_DEBUG("Get file nums in the specified directory:\n %d\n",count);
    return count;
}

QStringList AllFilePathInDir::getFilePathNameOfSplAndChildDir(QString dirPath)
{
    QStringList filePathNames;
    // 首先，得到这个目录下面的文件全部
    filePathNames << getFilePathNameOfSplDir(dirPath);

    QStringList childDirs;
    childDirs << getDirPathOfSplDir(dirPath);

    QString tempChildDir;
    foreach (tempChildDir, childDirs) {
        // 取其子文件夹内容
        filePathNames << getFilePathNameOfSplAndChildDir(tempChildDir);
    }
    TRACE_DEBUG("Gets the file path  and child directory in the specified directory:\n %s\n",filePathNames.join(",").toStdString().c_str());
    return filePathNames;
}

QStringList AllFilePathInDir::getDirPathOfSplAndChildDir(QString dirPath)
{
    QStringList dirPathNames;
    dirPathNames << getDirPathOfSplDir(dirPath);

    QString tempChildDir;
    foreach (tempChildDir, dirPathNames) {
        dirPathNames << getDirPathOfSplAndChildDir(tempChildDir);
    }
    TRACE_DEBUG("get dir path and its child dir path in the specified path:\n %s\n",dirPathNames.join(",").toStdString().c_str());
    return dirPathNames;
}

QStringList AllFilePathInDir::getFileAndDirPathNameOfSplAndChildDir(QString dirPath)
{
    static QStringList fileAndDirPathNames;
    fileAndDirPathNames.clear();
    fileAndDirPathNames << getFilePathNameOfSplDir(dirPath);

    QStringList childDirs;
    childDirs << getDirPathOfSplDir(dirPath);

    QString tempChildDir;
    foreach (tempChildDir, childDirs) {
        fileAndDirPathNames << tempChildDir;
        // 取其子文件夹内容
        fileAndDirPathNames << getFileAndDirPathNameOfSplAndChildDir(tempChildDir);
    }
    TRACE_DEBUG("get the dir\file  and its child dir/file:\n %s\n",fileAndDirPathNames.join(",").toStdString().c_str());
    return fileAndDirPathNames;
}
