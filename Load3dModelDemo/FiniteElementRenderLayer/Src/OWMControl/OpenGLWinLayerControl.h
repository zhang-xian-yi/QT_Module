#ifndef OPENGLWINLAYERCONTROL
#define OPENGLWINLAYERCONTROL

#include "Src/IOpenGLWin.h"
#include "Src/ILoad3D.h"
#include "Common/Src/ExtStruct.h"
class OpenGLWindowsLayerService;
class OpenGLWinLayerControl:public OWlayerNS::IOpenGLWin,public OWlayerNS::ILoad3D
{
public:
    OpenGLWinLayerControl();
    ~OpenGLWinLayerControl();
public:
    //IOpenGLWin 实现函数
    virtual void initOpenGLWin(QWidget* parent) override;
public:
    //加载3D数据
    virtual void LoadFiniteElementData(const QString& finiteElePath) override;
private:
    void initEnvirnoMent();
private:
    QSharedPointer<OpenGLWindowsLayerService>        m_pOWLService;
};

#endif // OPENGLWINLAYERCONTROL
