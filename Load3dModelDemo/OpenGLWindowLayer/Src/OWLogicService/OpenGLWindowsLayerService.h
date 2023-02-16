#pragma once

#ifdef DEBUG_VLD
/*
vld 需要deghelp.dll 、 Microsoft.DTfW.DHL.manifest、 vld_x64.dll 一起放入执行目录，
且必须安装vld程序（读取配置文件）vld.ini
*/
//#include "vld/vld.h"

#endif


#include "Services/OpenGLWindow.h"
#include "Entity/Scene/Scene.h"

class OpenGLWindowsLayerService:public QObject {
    Q_OBJECT
public:
    OpenGLWindowsLayerService(QWidget *parent = 0);
    ~OpenGLWindowsLayerService();
public:
    void CreateScene();//创建场景
    void ImportModelFile(QString& filepath);//加载模型
private:
    OpenGLWindow*  m_openGLWindow;  //openGL的窗口 由QT自身控制释放
    QSharedPointer<Scene>  m_pScene;               //显示的场景创建的场景,由OpenGLScene控制释放
};
