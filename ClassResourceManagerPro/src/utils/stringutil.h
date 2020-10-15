#ifndef STRINGUTIL_H
#define STRINGUTIL_H
#include <QString>
#include <QCoreApplication>

class StringUtil
{
public:
    /** 单例模式 */
    static StringUtil& getInstance();

public:
    /**
    @brief：获取传入两个字符串 字符相同的个数
    @param：str1,要比较的字符串1
            str2,要比较的字符串2
    @return  返回 相同字符个数
    */
    int getMathNum(const QString& str1,const QString& str2)const;
    /**
    @brief：从list 中 获取 与str 相匹配的项
    @param：list,存放待比较的字符串序列
           str,要比较的字符串
    @return  返回匹配 具有相似度的 字符串序列
    */
    QStringList getMatchStr(const QStringList list,const QString& str)const;
    /**
    @brief：从list 中 获取 与str 最大相似度匹配的项
    @param：list,存放待比较的字符串序列
           str,要比较的字符串
    @return  返回匹配 具有最大相似度的 字符串
    */
    QString getMaxMatchStr(const QStringList list,const QString& str)const;

    /**
    @brief：从传入路径中 截取 最后一个 ‘/’ 之后的内容
    @param：path, 一个传入的路径
           str,要比较的字符串
    @return  返回被截取的 文件名/目录名
    */
    QString getLastNameofFilePath(const QString& path)const;

    /**
    * @brief: 获取传入字符串路径的 right ‘/’ 之前的内容
    * @param： QString path
    * @return: QString parentpath
    * @date: 2020-10-15
    */
    QString getParentPath(const QString& path)const;
private:
    /** Forbid external construction */
    StringUtil();
    /** External destructions are prohibited */
    ~StringUtil();
    /** External replication constructs are prohibited */
    StringUtil(const StringUtil &)=delete;
    /** Prohibit external assignment operations */
    StringUtil &operator=(StringUtil &)=delete;
};

#endif // STRINGUTIL_H
