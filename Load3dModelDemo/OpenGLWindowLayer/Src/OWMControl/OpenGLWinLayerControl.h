#ifndef OPENGLWINLAYERCONTROL
#define OPENGLWINLAYERCONTROL

#include "Src/IOpenGLWin.h"
#include "Src/ILoad3D.h"
#include "Src/ExtStruct.h"
class OpenGLWindowsLayerService;
class Mesh3DParseService;
class OpenGLWinLayerControl:public OWlayerNS::IOpenGLWin,public OWlayerNS::ILoad3D
{
public:
    OpenGLWinLayerControl();
    ~OpenGLWinLayerControl();
public:
    //IOpenGLWin 实现函数
    virtual void initOpenGLWin(QWidget* parent) override;
public:
    //ILoad3D 实现函数
    virtual void Load3DModel(QString path) override;
    //加载3D数据
    virtual void Load3DStructData(QVector<OWlayerNS::InVertex>& vectexArr,QVector<OWlayerNS::InFaceIndex>& indexArray) override;
private:
    void initEnvirnoMent();
private:
    QSharedPointer<OpenGLWindowsLayerService> m_pOWLService;
    QSharedPointer<Mesh3DParseService>        m_pMeshParseService;
};

#endif // OPENGLWINLAYERCONTROL
