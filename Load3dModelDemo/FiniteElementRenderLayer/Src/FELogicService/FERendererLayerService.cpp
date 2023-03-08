#include "FERendererLayerService.h"
#include "Src/FECommon/GlobalData.h" //LogLv 与pGLFunc 引入
FERendererLayerService::FERendererLayerService(QWidget * parent)
{
    m_pFEParseS = QSharedPointer<FEFileParser>(new FEFileParser());
    m_pConvertS = QSharedPointer<ConvertOpenGLData>(new ConvertOpenGLData());
    //窗口的初始化会调用init 初始化opengl上下文，无OpenGL上下文 CubeGeometry 的缓冲区创建会失败
    m_openGLWindow = new OpenGLWindow(parent);//由QT父级控件控制释放
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
    //开始渲染
    m_openGLWindow->SetRendererData(pModel);
}




