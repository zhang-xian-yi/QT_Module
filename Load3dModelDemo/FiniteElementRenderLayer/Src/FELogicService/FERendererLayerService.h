#pragma once

#ifdef DEBUG_VLD
/*
vld 需要deghelp.dll 、 Microsoft.DTfW.DHL.manifest、 vld_x64.dll 一起放入执行目录，
且必须安装vld程序（读取配置文件）vld.ini
*/
//#include "vld/vld.h"

#endif

#include "Services/OpenGLWindow.h"
#include "Services/DataParser.h"
#include "Services/CubeGeometry.h"
class FERendererLayerService:public QObject
{
    Q_OBJECT
public:
    FERendererLayerService(QWidget *parent = 0);
    ~FERendererLayerService();
public:
    void LoadFiniteElementData(const QString& filepath);
private:
    OpenGLWindow*  m_openGLWindow;  //openGL的窗口 由QT自身控制释放
    QScopedPointer<DatParser> m_pDatParseS; //有限元文件解析工具
    QScopedPointer<CubeGeometry> m_pCudeDrawEleS; //有限元文件解析工具
};
