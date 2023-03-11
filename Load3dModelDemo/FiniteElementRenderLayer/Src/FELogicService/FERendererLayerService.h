#ifndef FERENDERERLAYERSERVICE_H
#define FERENDERERLAYERSERVICE_H

#ifdef DEBUG_VLD
/*
vld 需要deghelp.dll 、 Microsoft.DTfW.DHL.manifest、 vld_x64.dll 一起放入执行目录，
且必须安装vld程序（读取配置文件）vld.ini
*/
//#include "vld/vld.h"

#endif

#include "LogicServices/OpenGLWindow.h"
#include "LogicServices/FEFileParser.h"
#include "OpenGLService/EventHandler.h"
#include "OpenGLService/OpenGLRenderer.h"
#include "OpenGLEntity/FEScence.h"
class FERendererLayerService:public QObject
{
    Q_OBJECT
public:
    FERendererLayerService(QWidget *parent = 0);
    ~FERendererLayerService();
public:
    void LoadFiniteElementData(const QString& filepath);
private:
    //此方法作为回调函数在 OpenGLWidget中的 initialGL方法中执行
    void EnvirInitCallBack();
    //此方法作为回调函数在 OpenGLWidget中的 printGL方法中执行
    void OnDrawCallBack();
private:
    OpenGLWindow*  m_openGLWindow;  //openGL的窗口 由QT自身控制释放
    QSharedPointer<FEFileParser> m_pFEParseS; //有限元文件解析工具
    QSharedPointer<EventHandler> m_pEventHandlerS; //事件处理
    QSharedPointer<FEScence> m_pScene; //场景
    QSharedPointer<OpenGLRenderer> m_pRendererS; //渲染
};

#endif // FERENDERERLAYERSERVICE_H
