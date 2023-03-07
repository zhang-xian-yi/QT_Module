#ifndef FEFILEDATA_H
#define FEFILEDATA_H

//公开使用
struct FEFileVertex
{
    //键值对m_dataMap 键值模板 在所有顶点对象生成之前必须赋值
    static QList<QString> keyList;
public:
    //默认构造指定键值的顶点数据
    inline FEFileVertex()
    {
        foreach (QString key, keyList)
        {
            m_dataMap[key] = 0.0f;
        }
    }
public:
    //单独对象的变量数据
    QMap<QString,float> m_dataMap;
};

struct FEFileMesh
{
    QVector<int> indexData;
};

//有限元文件的数据
class FEFileData
{
public:
    //仅在FEFileData 中操作使用，外部仅作为标记传参，描述有限元文件中的配置数据
    enum class EFEFileConfig:unsigned char
    {
        E_TITLE,//标题
        E_Type,//文件类型
        E_VertexNum,//顶点个数
        E_MeshNum,//网格数
        E_DataPacking,//数据类型
        E_ZoneType,//空间类型
    };
public:
    FEFileData();
    ~FEFileData();
public:
    void AddCfgInfo(EFEFileConfig key,QString& value);//插入配置信息
    QString GetCfgInfo(EFEFileConfig key)const;//获取配置信息
    void AddVertex(QSharedPointer<FEFileVertex> vertex);//添加顶点信息
    void AddMesh(QSharedPointer<FEFileMesh> mesh);//添加网格信息
    QVector<QSharedPointer<FEFileVertex>>& GetVertexVector();//获取顶点集合
    QVector<QSharedPointer<FEFileMesh>>& GetMeshVector();//获取网格集合
private:
    void InitCfgMap();
private:
    QMap<EFEFileConfig,QString> m_cfgMap;//有限元配置
    QVector<QSharedPointer<FEFileVertex>> m_vertexVec;//有限元顶点数据
    QVector<QSharedPointer<FEFileMesh>> m_meshVec;//有限元网格体数据
};


#endif // FEFILEDATA_H
