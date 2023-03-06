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
    if(!m_pDatParseS->SetFile(filepath))
    {
        return;
    }
    // 更新渲染数据
    m_pCudeDrawEleS->UpdateCubeGeometry(m_pDatParseS->GetNameForZones());
}




