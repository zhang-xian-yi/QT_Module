#ifndef ALLFILEPATHINDIR_H
#define ALLFILEPATHINDIR_H

#include <QString>
#include <QStringList>
#include <QObject>

class AllFilePathInDir:public QObject
{
    Q_OBJECT
signals:
    void signal_getFileAndDirPathNameOfSplDir(const QStringList list);
public:
    /** Forbid external construction */
    explicit AllFilePathInDir(){};
public slots:
    /** 获取指定目录下的 文件（路径+名称）
     * @brief getFilePathNameOfSplDir
     * @param dirPath               目标文件夹的目录
     * @return QStringList
     */
     QStringList         getFilePathNameOfSplDir(QString dirPath);

    /** 获取在指定目录下的目录的路径
     * @brief getDirPathOfSplDir
     * @param dirPath               目标文件夹的目录
     * @return QStringList
     */
     QStringList         getDirPathOfSplDir(QString dirPath);

    /** 获取指定目录下的文件和目录的全路径
     * @brief getFileAndDirPathNameOfSplDir
     * @param dirPath               目标文件夹的目录
     * @return QStringList
     */
     QStringList         getFileAndDirPathNameOfSplDir(QString dirPath);

    /** 在指定文件夹下的文件数
     * @brief fileConutInSplDir
     * @param dirPath               目标文件夹的目录
     * @return int
     */
     int                 fileConutInSplDir(QString dirPath);

    /** 在指定文件夹下的目录数
     * @brief dirCountInSplDir
     * @param dirPath               目标文件夹的目录
     * @return int
     */
     int                 dirCountInSplDir(QString dirPath);

    /** 获取指定目录及其子目录下文件的全路径
     * @brief getFilePathNameOfSplAndChildDir
     * @param dirPath               目标文件夹的目录
     * @return QStringList
     */
     QStringList         getFilePathNameOfSplAndChildDir(QString dirPath);

    /** 获取指定目录及其子目录下的文件夹的全路径
     * @brief getDirPathOfSplAndChildDir
     * @param dirPath               目标文件夹的目录
     * @return QStringList
     */
     QStringList         getDirPathOfSplAndChildDir(QString dirPath);

    /** 获取指定目录及其子目录下的文件与目录的全路径
     * @brief getFileAndDirPathNameOfSplAndChildDir
     * @param dirPath               目标文件夹的目录
     * @return QStringList
     */
     QStringList         getFileAndDirPathNameOfSplAndChildDir(QString dirPath);
};

#endif // ALLFILEPATHINDIR_H
