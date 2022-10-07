#include "servicelistviewmodel.h"
#include <QDebug>


class ServiceListviewModelPrivate
{
public:
    enum ModelRoles {
        Name = Qt::UserRole + 1,
        Type,
        Desc,
        Price
    };

    enum EntityIndex{
        Name_index = 0,
        Type_index,
        Desc_index,
        Price_index
    };

    explicit ServiceListviewModelPrivate();

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const ;
    bool setData(QVector<int>& out_roles_user ,const QModelIndex &index, const QVariant &value,int role = Qt::EditRole);
    // Editable:
    QHash<int, QByteArray> roleNames() const;
    Qt::ItemFlags flags(const QModelIndex& index) const;
    bool getDataFromMysql();
public:
    QList<Entity> m_contexts;
};

ServiceListviewModelPrivate::ServiceListviewModelPrivate()
{

}

QVariant ServiceListviewModelPrivate::data(const QModelIndex &index, int role ) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
    QVariant ret;
    switch (role)
    {
        case Name:
            ret = m_contexts.at(index.row()).at(0);
            break;
        case Type:
            ret = m_contexts.at(index.row()).at(1);
            break;
        case Desc:
            ret = m_contexts.at(index.row()).at(2);
            break;
        case Price:
            ret = m_contexts.at(index.row()).at(3);
            break;
        default:
            break;
    }
    return ret;
}

QHash<int, QByteArray> ServiceListviewModelPrivate::roleNames() const
{
    static bool flag = false;

    static QHash<int, QByteArray> roles;
    if(! flag)
    {
        roles.insert(Name, "name");
        roles.insert(Type, "type");
        roles.insert(Desc, "describe");
        roles.insert(Price,"price");
    }
    return roles;
}

bool ServiceListviewModelPrivate::setData(QVector<int>& out_roles_user ,const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value)
    {
        // FIXME: Implement me!
        m_contexts[index.row()][role] = value;
        switch (role)
        {
            case Name_index:
            {
                out_roles_user<<Name;
                break;
            }
            case Type_index:
            {
                out_roles_user<<Type;
                break;
            }
            case Desc_index:
            {
                out_roles_user<<Desc;
                break;
            }
            case Price_index:
            {
                out_roles_user<<Price;
                break;
            }
        default:break;

        }
        return true;
    }
    return false;
}
Qt::ItemFlags ServiceListviewModelPrivate::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
    }
    return Qt::ItemIsEditable; // FIXME: Implement me!
}

bool ServiceListviewModelPrivate::getDataFromMysql()
{
    Entity item(QVariantList() << QVariant("鱼香肉丝") << QVariant("热菜")<<QVariant("利用xxxxxx")<< QVariant("15") );
    Entity item1(QVariantList() << "心痛水" << "酒水"<<"喝下必定心痛"<<"9999");
    Entity item2(QVariantList() << "甜皮鸭" << "冷菜"<<"一直骑着皮皮虾的甜皮鸭"<<"99");
    Entity item3(QVariantList() << "最后的火焰神迹" << "辣椒"<<"让人体会到什么是火焰神迹"<<"199");
    m_contexts.push_back(item);
    m_contexts.push_back(item1);
    m_contexts.push_back(item2);
    m_contexts.push_back(item3);
    return true;
}






//ServiceListviewModel info

ServiceListviewModel::ServiceListviewModel(QObject *parent)
    : QAbstractListModel(parent),
      m_service(new ServiceListviewModelPrivate),
      m_timer(new QTimer)
{
    m_service->getDataFromMysql();
    //定时更新数据
    connect(m_timer,SIGNAL(timeout()),this,SLOT(updateData()));
    m_timer->setInterval(2000);
    m_timer->start();
}

ServiceListviewModel::~ServiceListviewModel()
{
    if(m_service != nullptr)
    {
        delete m_service;
    }
    if(nullptr != m_timer)
    {
        m_timer->stop();
        delete m_timer;
    }
}

/*
QVariant ServiceListviewModel::headerData(int section, Qt::Orientation orientation, int role) const {
    // FIXME: Implement me!
}

bool ServiceListviewModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role) {
    if (value != headerData(section, orientation, role))
    {
        // FIXME: Implement me!
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}
*/

int ServiceListviewModel::rowCount(const QModelIndex &parent) const {
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
    {
        return 0;
    }
    return m_service->m_contexts.size();
}

QVariant ServiceListviewModel::data(const QModelIndex &index, int role) const {
    return m_service->data(index,role);
}

bool ServiceListviewModel::setData(const QModelIndex &index, const QVariant &value, int role  )
{
    static QVector<int> out_roles_;
    bool ret = m_service->setData(out_roles_,index,value,role);
    if(ret)
    {
        emit writeData("xxxxxxx");
        emit dataChanged(index, index ,out_roles_);
    }
    return ret;
}

Qt::ItemFlags ServiceListviewModel::flags(const QModelIndex &index) const
{
    return m_service->flags(index);
}

bool ServiceListviewModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    for (int i = 0; i < count; ++i)
    {
        Entity item(QVariantList() << "茅台酒" << "酒水"<<"yiping"<<"188");
        m_service->m_contexts.insert(i + row, item);
    }
    endInsertRows();
    return true;
}

bool ServiceListviewModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
    return false;
}

QHash<int, QByteArray> ServiceListviewModel::roleNames() const
{
   return m_service->roleNames();
}


void ServiceListviewModel::updateData()
{
    //qDebug()<<"xxxxxxx";
    //index 1,0   mean  下标index 为1 的item  的 第0 个role
    setData(createIndex(1, m_service->Price_index), QVariant(QString::number(qrand() * 10 + 100)), m_service->Price_index);
}

void ServiceListviewModel::doLog(const QString& msg)
{
    qDebug()<<"c++ class recviver msg:"<<msg;
}

