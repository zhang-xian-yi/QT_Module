#ifndef OPENGLWINLAYERCONTROL
#define OPENGLWINLAYERCONTROL

#include "Src/IOpenGLWin.h"
#include "Src/ILoad3D.h"
class OpenGLWindowsLayerService;

class OpenGLWinLayerControl:public OWlayerNS::IOpenGLWin,public OWlayerNS::ILoad3D
{
public:
    OpenGLWinLayerControl();
public:
    //IOpenGLWin 实现函数
    void initOpenGLWin(QWidget* parent) override;
public:
    //ILoad3D 实现函数
    void Load3DModel(QString path) override;
private:
    void initEnvirnoMent();
private:
    OpenGLWindowsLayerService* m_pOWLService;
};

#endif // OPENGLWINLAYERCONTROL
