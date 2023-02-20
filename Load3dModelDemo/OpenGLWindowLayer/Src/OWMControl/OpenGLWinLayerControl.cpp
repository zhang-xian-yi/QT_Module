#include "OpenGLWinLayerControl.h"
#include "Src/OWLogicService/OpenGLWindowsLayerService.h"
#include "Src/OWLogicService/Mesh3DParseService.h"
OpenGLWinLayerControl::OpenGLWinLayerControl()
    :m_pOWLService(nullptr),m_pMeshParseService(nullptr)
{

}

OpenGLWinLayerControl::~OpenGLWinLayerControl()
{
    m_pOWLService.clear();
    m_pMeshParseService.clear();
    if (logLV == DEBUG_DESTORY_INFO)
        dout << "OpenGLWinLayerControl is destroyed";
}

void OpenGLWinLayerControl::initOpenGLWin(QWidget* parent)
{
    if(m_pOWLService == nullptr)
    {
        initEnvirnoMent();
        m_pOWLService = QSharedPointer<OpenGLWindowsLayerService>(new OpenGLWindowsLayerService(parent));
        auto scene = m_pOWLService->CreateScene();//初始化场景
        m_pMeshParseService = QSharedPointer<Mesh3DParseService>(new Mesh3DParseService(scene));
    }

}

void OpenGLWinLayerControl::initEnvirnoMent()
{
    QSurfaceFormat openGLFormat;
    openGLFormat.setVersion(3, 3);
    openGLFormat.setProfile(QSurfaceFormat::CoreProfile);
    openGLFormat.setDepthBufferSize(24);
    openGLFormat.setStencilBufferSize(8);
    QSurfaceFormat::setDefaultFormat(openGLFormat);
}


void OpenGLWinLayerControl::Load3DModel(QString path)
{
    if(m_pOWLService)
    {
        m_pOWLService->ImportModelFile(path);
    }
}

//加载3d数据
void OpenGLWinLayerControl::Load3DStructData(QVector<OWlayerNS::InVertex> & vectexArr, QVector<OWlayerNS::InFaceIndex> & indexArray)
{
    if(m_pMeshParseService)
    {
        m_pMeshParseService->Load3DMeshData(vectexArr,indexArray);
    }
}

