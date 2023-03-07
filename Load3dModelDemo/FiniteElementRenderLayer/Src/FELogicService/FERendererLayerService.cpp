#include "FERendererLayerService.h"
#include "Src/FECommon/GlobalData.h" //LogLv 与pGLFunc 引入
FERendererLayerService::FERendererLayerService(QWidget * parent)
{
    m_pFEParseS = QSharedPointer<FEFileParser>(new FEFileParser());
    m_pConvertS = QSharedPointer<ConvertOpenGLData>(new ConvertOpenGLData());
    m_pCudeDrawEleS = QSharedPointer<CubeGeometry>(new CubeGeometry());
    m_openGLWindow = new OpenGLWindow(m_pCudeDrawEleS,parent);//由QT父级控件控制释放
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
    //解析文件
    QSharedPointer<FEFileData> parseData = m_pFEParseS->ParseFile(filepath);
    if(parseData.isNull())
    {
        return;
    }
    //转化数据
    QSharedPointer<FEModel> pModel = m_pConvertS->Convert(parseData);
    // 清除已渲染的数据
    m_pCudeDrawEleS->ReleaseRenderData();
    // 设置渲染数据
    m_pCudeDrawEleS->SetRenderData(pModel);
    // 完成初始化渲染数据 - 将CPU数据设置到GPU缓存中
    m_pCudeDrawEleS->InitCompleteCubeGeometry(pModel);    // 清除已渲染的数据
}




