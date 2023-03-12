#include "FERendererLayerService.h"
#include "Src/FECommon/GlobalData.h" //LogLv 与pGLFunc 引入
FERendererLayerService::FERendererLayerService(QWidget * parent)
{
    m_pFEParseS = QSharedPointer<FEFileParser>(new FEFileParser());
    m_pEventHandlerS = QSharedPointer<EventHandler>(new EventHandler());
    m_pRendererS = QSharedPointer<OpenGLRenderer>(new OpenGLRenderer());
    //窗口的初始化会调用init 初始化opengl上下文，无OpenGL上下文 CubeGeometry 的缓冲区创建会失败
    m_openGLWindow = new OpenGLWindow(parent);//由QT父级控件控制释放

    //设置回调函数 必须在openglwidget初始化之前，（initialgl方法执行之前将关系定义，否则调用时会发生空指针）
    auto OnInit = std::bind(&FERendererLayerService::EnvirInitCallBack, this);
    auto OnDraw = std::bind(&FERendererLayerService::OnDrawCallBack, this);
    auto OnEvent = std::bind(&EventHandler::OnEvent, m_pEventHandlerS.get(), std::placeholders::_1);
    auto GetVec3Data = std::bind(&EventHandler::Get3DPos, m_pEventHandlerS.get());
    auto GetMVPMat4 =  std::bind(&EventHandler::GetMVPMatrix4, m_pEventHandlerS.get());
    m_openGLWindow->SetOpenGLEnvInitCallBack(OnInit);
    m_openGLWindow->SetOnEventCallBack(OnEvent);
    m_openGLWindow->SetOnDrawCallBack(OnDraw);
    m_pRendererS->SetGetCallBack(GetVec3Data);
    m_pRendererS->SetGetCallBack(GetMVPMat4);
    //注册
    qRegisterMetaType<QSharedPointer<FEModel>>("QSharedPointer<FEModel>");

    //设置信号槽
    connect(m_openGLWindow,&OpenGLWindow::ResizeGLSig, m_pEventHandlerS.get(),&EventHandler::SlotResigzeGLMat4);
    //解析完成后多线程直接进行处理
    connect(this, SIGNAL(ParseSuccSig(QSharedPointer<FEModel>)), m_pRendererS.get(), SLOT(SetRendererDataSlot(QSharedPointer<FEModel>)));
}

FERendererLayerService::~FERendererLayerService()
{
    m_openGLWindow = nullptr; //减少引用技术由QT父控件控制
}

//加载有限元文件（可以考虑使用多线程技术解析并渲染）
void FERendererLayerService::LoadFiniteElementData(const QString& filepath)
{
    QEventLoop loop;
    connect(this, &FERendererLayerService::ParseFinishSig, &loop, &QEventLoop::quit);
    std::thread DataDealThread([&]
    {
        //解析文件
        QSharedPointer<FEModel> pModel = m_pFEParseS->ParseFile(filepath);
        if(pModel.isNull())
        {
            return;
        }
        emit ParseSuccSig(pModel);
        emit ParseFinishSig();
     });
    //临时线程销毁
    DataDealThread.detach();
    loop.exec();//事件循环不卡ui界面
}

//此方法作为回调函数在 OpenGLWidget中的 initialGL方法中执行
void FERendererLayerService::EnvirInitCallBack()
{
    m_pRendererS->InitEnv();//渲染工具
    m_pEventHandlerS->InitEnv(m_openGLWindow->width(),m_openGLWindow->height());//初始化事件处理系统以及视角
}

//此方法作为回调函数在 OpenGLWidget中的 printGL方法中执行
void FERendererLayerService::OnDrawCallBack()
{
    m_pRendererS->Draw();
}



