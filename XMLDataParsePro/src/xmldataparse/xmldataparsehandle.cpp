#include "xmldataparsehandle.h"
#include <QFile>
#include "xmldataparse/descxmlstruct.h"

static QStringList gAttributeList;


XMLDataParseHandle::XMLDataParseHandle()
{
    m_bRunParseFlag = false;
    m_xmlReader = new QXmlStreamReader;
    if(gAttributeList.isEmpty())
    {
        gAttributeList<<"name"<<"kind"<<"type"<<"href";
    }
}

XMLDataParseHandle::~XMLDataParseHandle()
{
    //释放所有构建的tagTree
    foreach(TagTree* tmp,m_tagTreeList)
    {
        delete tmp;
    }
    m_tagTreeList.clear();
    if(nullptr != m_xmlReader)
    {
        delete m_xmlReader;
        m_xmlReader = nullptr;
    }
}
/**
* @brief: 判断路径是否合法 并且解析生成标签树
* @param：
* @return:
* @date: 2021-01-06
*/
TagTree *XMLDataParseHandle::startParseXMLFile(const QString &path)
{
    QFile file(path);
    if(file.exists())
    {
        //文件合法
        m_xmlReader->setDevice(&file);
        if( file.open(QIODevice::ReadOnly) )
        {
            TagTree* ret = parseXMLData();
            if(nullptr != ret)
            {
                ret->setFileUrl(path);
            }
            return ret;
        }
        return nullptr;
    }
    else
    {
        return nullptr;
    }
}


/**
* @brief: 依赖流 读取器 生成标签树
* @param： void
* @return: 构建完成的标签书
* @date: 2021-01-06
*/
TagTree *XMLDataParseHandle::parseXMLData()
{
    TagTree* ret = new TagTree;
    TagTreeNode* curr_parent = nullptr;
    //不在解析过程中 立刻跳出
    while (! this->m_bRunParseFlag)
    {
        QXmlStreamReader::TokenType nType = m_xmlReader->tokenType();
        switch (nType)
        {
            case QXmlStreamReader::Invalid:
            {
                m_bRunParseFlag = true;
                break;
            }
            case QXmlStreamReader::StartElement:
            {
                handleStartElement(ret,&curr_parent);
                break;
            }
            case QXmlStreamReader::EndElement:
            {
                curr_parent = curr_parent->getParentNode();
                m_xmlReader->readNext();
                break;
            }
            case QXmlStreamReader::EndDocument:
            {
                m_bRunParseFlag = true;
                break;
            }
            default:
            {
                m_xmlReader->readNext();
                break;
            }
        }
    }

    if(m_xmlReader->hasError())
    {
        //释放已经后构建好的标签树
        delete ret;
        return nullptr;
    }
    //添加进入内容管理列表
    m_tagTreeList.append(ret);
    return ret;
}

void XMLDataParseHandle::handleStartElement(TagTree *retTree, TagTreeNode **current_parent)
{
    TagTreeNode * tmpNode = new TagTreeNode;
    //保存节点信息
    tmpNode->getBaseNode()->setLines(m_xmlReader->lineNumber()); //保存行数
    tmpNode->getBaseNode()->setTagName(getCurrentTagName());//保存 标签名
    //设置属性键值对
    foreach(QString str,gAttributeList)
    {
        setTagAttribute(tmpNode,str);
    }
    //保存内容
    m_xmlReader->readNext();
    tmpNode->getBaseNode()->setContext(m_xmlReader->text().toString().trimmed());
    //保存节点之间的关系  包括根节点情况下的 nullptr
    tmpNode->setParentNode(*current_parent);
    if(nullptr == *current_parent)
    {
        retTree->setRoot(tmpNode);
    }
    else
    {
        (*current_parent)->appendChild(tmpNode);
    }
    //改变当前父级节点的数据
    *current_parent = tmpNode;
}


/**
* @brief: 获取属性值 根据传入的属性名
* @param：
* @return:  如果没有返回 空
* @date: 2021-01-06
*/
QString XMLDataParseHandle::getAttributeValue(const QString &attributeName)
{
    return m_xmlReader->attributes().value(attributeName).toString();
}
/**
* @brief:  获取流读取 读取未知标签的标签名
* @param：
* @return:
* @date: 2021-01-06
*/
QString XMLDataParseHandle::getCurrentTagName() const
{
    return m_xmlReader->name().toString();
}

/**
* @brief: 树结点 set 属性值
* @param：
* @return:
* @date: 2021-01-06
*/
void XMLDataParseHandle::setTagAttribute(TagTreeNode *tmp, const QString &tagKey)
{
    QString value = getAttributeValue(tagKey);
    if(! value.isEmpty())
    {
        tmp->getBaseNode()->appendAttr(tagKey,value);
    }
}
