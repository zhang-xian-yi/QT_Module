#include "FERendererLayerService.h"
#include "Src/FECommon/GlobalData.h" //LogLv 与pGLFunc 引入
FERendererLayerService::FERendererLayerService(QWidget * parent)
{
    m_openGLWindow = new OpenGLWindow(parent);//由QT父级控件控制释放

    m_pDatParseS = QSharedPointer<DatParser>(new DatParser());
    m_pCudeDrawEleS = QSharedPointer<CubeGeometry>(new CubeGeometry());
    //设置为父控件的大小
    m_openGLWindow->setParent(parent);
    m_openGLWindow->setGeometry(parent->rect().x(),parent->rect().y(),
                      parent->rect().width(),parent->rect().height());

    m_openGLWindow->setAcceptDrops(true);
    m_openGLWindow->setFocusPolicy(Qt::StrongFocus);
}

FERendererLayerService::~FERendererLayerService()
{
    m_openGLWindow = nullptr; //减少引用技术由QT父控件控制
}

void FERendererLayerService::LoadFiniteElementData(const QString& filepath)
{
    if(!m_pDatParseS->ParseFile(filepath))
    {
        return;
    }
    /*
    // 清除已渲染的数据
    m_pCudeDrawEleS->ReleaseRenderData();
    // 遍历渲染的空间区域
    for(int j = 0;j < zoneNameList.size(); ++j)
    {
        qDebug() << "zoneName:" << zoneNameList.at(j);
        // 网格面、体数据信息获取
        auto MeshersIndex = oDataMng->GetMeshersIndex(zoneNameList.at(j));
        // 坐标点信息获取
        auto CoordinatesVertex = oDataMng->GetCoordinatesVertex(zoneNameList.at(j));
        // 设置渲染数据
        this->SetRenderData(CoordinatesVertex, MeshersIndex);
    }
    // 完成初始化渲染数据 - 将CPU数据设置到GPU缓存中
    this->InitCompleteCubeGeometry();    // 清除已渲染的数据
    */
}




