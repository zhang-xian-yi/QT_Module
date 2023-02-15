#ifndef OPENGLWINLAYERCONTROL
#define OPENGLWINLAYERCONTROL

#include "Src/IOpenGLWin.h"
#include "Src/ILoad3D.h"
class OpenGLWindowsLayerService;

class OpenGLWinLayerControl:public OWlayerNS::IOpenGLWin,public OWlayerNS::ILoad3D
{
public:
    OpenGLWinLayerControl();
    ~OpenGLWinLayerControl();
public:
    //IOpenGLWin 实现函数
    virtual void initOpenGLWin(QWidget* parent) override;
    virtual void resizeOpenGLWin(int w,int h) override;
public:
    //ILoad3D 实现函数
    virtual void Load3DModel(QString path) override;
private:
    void initEnvirnoMent();
private:
    OpenGLWindowsLayerService* m_pOWLService;
};

#endif // OPENGLWINLAYERCONTROL
