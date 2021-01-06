#ifndef DESCXMLSTRUCT_H
#define DESCXMLSTRUCT_H
#include <QMap>
#include <QString>
#include <QList>
#include <QtCore/qglobal.h>

#if defined(XMLDATAPARSE_LIBRARY)
#  define XMLDATAPARSE_EXPORT Q_DECL_EXPORT
#else
#  define XMLDATAPARSE_EXPORT Q_DECL_IMPORT
#endif


class XMLDATAPARSE_EXPORT BaseTagNode
{
public:
    explicit BaseTagNode();
    ~BaseTagNode();
    //get
    QString getTagName()const;
    QMap<QString,QString> getAttr()const;
    QString getContext()const;
    unsigned long long getLines()const;
    //set
    void setTagName(const QString& tagName);
    void appendAttr(const QString& key,const QString& value);
    void setContext(const QString& context);
    void setLines(const unsigned long long& lines);
private:
    //标签名
    QString                m_tagName;
    //属性键值对
    QMap<QString,QString>  m_attributes;
    //标签内容
    QString                m_context;
    //标签行数
    unsigned long long     m_lines;
};



class XMLDATAPARSE_EXPORT TagTreeNode
{
public:
    explicit TagTreeNode();
    ~TagTreeNode();
    //显示调用摧毁树结构
    void destory();
    //get
    TagTreeNode* getParentNode()const;
    QList<TagTreeNode*> getChild()const;
    BaseTagNode* getBaseNode()const;
    //set
    void setBaseTagNode(const BaseTagNode* node);
    void appendChild(const TagTreeNode* child);
    void setParentNode(const TagTreeNode* parentNode);
private:
    TagTreeNode*          m_parentNode;
    QList<TagTreeNode*>   m_childList;
    BaseTagNode*          m_baseNode;
};


class XMLDATAPARSE_EXPORT TagTree
{
public:
    explicit TagTree();
    ~TagTree();
    TagTreeNode* getRoot()const;
    QString getFileUrl()const;
    void setRoot(const TagTreeNode* node);
    void setFileUrl(const QString& fileurl);
private:
    QString m_fileUrl;
    TagTreeNode* m_root;
};


#endif // DESCXMLSTRUCT_H
