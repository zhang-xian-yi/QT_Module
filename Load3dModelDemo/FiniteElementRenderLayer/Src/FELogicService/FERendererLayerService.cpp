#include "FERendererLayerService.h"
#include "Src/FECommon/GlobalData.h" //LogLv 与pGLFunc 引入
FERendererLayerService::FERendererLayerService(QWidget * parent)
{
    m_pFEParseS = QSharedPointer<FEFileParser>(new FEFileParser());
    m_pConvertS = QSharedPointer<ConvertOpenGLData>(new ConvertOpenGLData());
    m_pEventHandlerS = QSharedPointer<EventHandler>(new EventHandler());
    m_pScene = QSharedPointer<FEScence>(new FEScence());
    //窗口的初始化会调用init 初始化opengl上下文，无OpenGL上下文 CubeGeometry 的缓冲区创建会失败
    m_openGLWindow = new OpenGLWindow(parent);//由QT父级控件控制释放

    //设置回调函数 必须在openglwidget初始化之前，（initialgl方法执行之前将关系定义，否则调用时会发生空指针）
    auto OnInit = std::bind(&FERendererLayerService::EnvirInitCallBack, this);
    auto OnEvent = std::bind(&EventHandler::OnEvent, m_pEventHandlerS.get(), std::placeholders::_1);
    auto GetVec3Data = std::bind(&EventHandler::Get3DPos, m_pEventHandlerS.get());
    auto GetMVPMat4 =  std::bind(&EventHandler::GetMVPMatrix4, m_pEventHandlerS.get());
    m_openGLWindow->SetOpenGLEnvInitCallBack(OnInit);
    m_openGLWindow->SetOnEventCallBack(OnEvent);
    m_openGLWindow->SetGetCallBack(GetVec3Data);
    m_openGLWindow->SetGetCallBack(GetMVPMat4);
    //设置信号槽
    connect(m_openGLWindow,&OpenGLWindow::ResizeGLSig, m_pEventHandlerS.get(),&EventHandler::SlotResigzeGLMat4);
}

FERendererLayerService::~FERendererLayerService()
{
    m_openGLWindow = nullptr; //减少引用技术由QT父控件控制
}

//加载有限元文件（可以考虑使用多线程技术解析并渲染）
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

//此方法作为回调函数在 OpenGLWidget中的 initialGL方法中执行
void FERendererLayerService::EnvirInitCallBack()
{
    m_pScene->CreateDefaultScence();//创建场景
    //初始化事件处理系统以及视角
    m_pEventHandlerS->InitEnv(m_openGLWindow->width(),m_openGLWindow->height());
}



