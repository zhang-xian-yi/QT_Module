#ifndef XMLDATAPARSEHANDLE_H
#define XMLDATAPARSEHANDLE_H
#include <QString>
#include <QXmlStreamReader>
#include <QtCore/qglobal.h>

#if defined(XMLDATAPARSE_LIBRARY)
#  define XMLDATAPARSE_EXPORT Q_DECL_EXPORT
#else
#  define XMLDATAPARSE_EXPORT Q_DECL_IMPORT
#endif
class BaseTagNode;
class TagTreeNode;
class TagTree;


class XMLDATAPARSE_EXPORT XMLDataParseHandle
{
public:
    explicit XMLDataParseHandle();
    ~XMLDataParseHandle();
    TagTree* startParseXMLFile(const QString& path);
private:
    TagTree* parseXMLData();
private:
    //处理xml 文件的开始元素
    void handleStartElement(TagTree* retTree,TagTreeNode** current_parent);
    //
    QString getAttributeValue(const QString& attributeName);
    QString getCurrentTagName()const;
    void setTagAttribute(TagTreeNode* tmp,const QString& tagKey);

private:
    //依次解析是否解析过程中
    bool   m_bRunParseFlag;
    //xml 流读取器
    QXmlStreamReader*  m_xmlReader;
    //构建的标签树
    QList<TagTree*>    m_tagTreeList;
};

#endif // XMLDATAPARSEHANDLE_H
