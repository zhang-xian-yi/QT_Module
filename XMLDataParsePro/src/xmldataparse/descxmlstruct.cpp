#include "descxmlstruct.h"
#include <QQueue>
BaseTagNode::BaseTagNode()
{
    m_context = "";
    m_tagName = "";
    m_lines = 0;
}

BaseTagNode::~BaseTagNode()
{
    m_attributes.clear();
}

QString BaseTagNode::getTagName() const
{
    return this->m_tagName;
}

QMap<QString, QString> BaseTagNode::getAttr() const
{
    return this->m_attributes;
}

QString BaseTagNode::getContext() const
{
    return this->m_context;
}

unsigned long long BaseTagNode::getLines() const
{
    return this->m_lines;
}

void BaseTagNode::setTagName(const QString &tagName)
{
    this->m_tagName = tagName;
}

void BaseTagNode::appendAttr(const QString &key, const QString &value)
{
    this->m_attributes.insert(key,value);
}

void BaseTagNode::setContext(const QString &context)
{
    this->m_context = context;
}

void BaseTagNode::setLines(const unsigned long long &lines)
{
    this->m_lines = lines;
}
/********************************************************************************************************************/

TagTreeNode::TagTreeNode()
{
    m_parentNode = nullptr;
    m_baseNode = new BaseTagNode;
}

TagTreeNode::~TagTreeNode()
{
    if(nullptr != m_baseNode)
    {
        delete m_baseNode;
        m_baseNode = nullptr;
    }
}

void TagTreeNode::destory()
{
    //子节点入队
    QQueue<TagTreeNode*> queue;
    QList<TagTreeNode*> childList;
    queue.enqueue(this);
    //不为空
    while(! queue.isEmpty())
    {
        TagTreeNode* node = queue.dequeue();
        //入队出队 的所有子节点
        childList = node->getChild();
        foreach(TagTreeNode* tmp,childList)
        {
            queue.enqueue(tmp);
        }
        delete node;
    }
}

TagTreeNode *TagTreeNode::getParentNode() const
{
    return this->m_parentNode;
}

QList<TagTreeNode *> TagTreeNode::getChild() const
{
    return this->m_childList;
}

BaseTagNode *TagTreeNode::getBaseNode() const
{
    return this->m_baseNode;
}

void TagTreeNode::setBaseTagNode(const BaseTagNode *node)
{
    this->m_baseNode = const_cast<BaseTagNode *>(node);
}

void TagTreeNode::appendChild(const TagTreeNode *child)
{
    this->m_childList.append(const_cast<TagTreeNode *>(child) );
}

void TagTreeNode::setParentNode(const TagTreeNode *parentNode)
{
    this->m_parentNode = const_cast<TagTreeNode *>(parentNode);
}


/********************************************************************************************************************/
TagTree::TagTree()
{
    m_root = nullptr;
    m_fileUrl = "";
}

TagTree::~TagTree()
{
    //销毁树
    if(nullptr != m_root)
    {
         m_root->destory();
    }
    m_fileUrl = "";
}

TagTreeNode *TagTree::getRoot() const
{
    return this->m_root;
}

QString TagTree::getFileUrl() const
{
    return this->m_fileUrl;
}

void TagTree::setRoot(const TagTreeNode *node)
{
    this->m_root = const_cast<TagTreeNode *>(node);
}

void TagTree::setFileUrl(const QString &fileurl)
{
    this->m_fileUrl = fileurl;
}
