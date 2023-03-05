#ifndef OPENGLWINLAYERCONTROL
#define OPENGLWINLAYERCONTROL

#include "Src/IOpenGLWin.h"
#include "Src/ILoad3D.h"
#include "Src/OWCommon/ExtStruct.h"

class FERendererLayerService;
class FERendererLayerControl:public FERendererNS::IOpenGLWin,public FERendererNS::ILoad3D
{
public:
    FERendererLayerControl();
    ~FERendererLayerControl();
public:
    //IOpenGLWin 实现函数
    virtual void initOpenGLWin(QWidget* parent) override;
public:
    //加载3D数据
    virtual void LoadFiniteElementData(const QString& finiteElePath) override;
private:
    void initEnvirnoMent();
private:
    QSharedPointer<FERendererLayerService>        m_pOWLService;
};

#endif // OPENGLWINLAYERCONTROL
