#include "FERendererLayerService.h"
#include "Src/FECommon/GlobalData.h" //LogLv 与pGLFunc 引入
FERendererLayerService::FERendererLayerService(QWidget * parent):
    m_pDatParseS(new DatParser()),m_pCudeDrawEleS(new CubeGeometry())
{
    m_openGLWindow = new OpenGLWindow();//由QT父级控件控制释放

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
    if(!m_pDatParseS->SetFile(filepath))
    {
        return;
    }
    auto zones = m_pDatParseS->GetNameForZones();

    // 遍历渲染的空间区域
    for(int j = 0;j < zones.size(); ++j)
    {
        qDebug() << "zoneName:" << zones.at(j);
        // 网格面、体数据信息获取
        auto MeshersIndex = m_pDatParseS->GetMeshersIndex(zones.at(j));
        // 坐标点信息获取
        auto CoordinatesVertex = m_pDatParseS->GetCoordinatesVertex(zones.at(j));
        // 设置渲染数据
        m_pCudeDrawEleS->SetRenderData(CoordinatesVertex, MeshersIndex);
    }
}




