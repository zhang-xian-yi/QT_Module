#pragma once

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

private slots:
    //刷新矩阵
    void polygonAssignMaterial();
    void polygonReverseNormals();
    void polygonReverseTangents();
    void polygonReverseBitangents();
private:
    QWidget* m_pWidgetWin;         //与m_openGLWindow是一样的地址只是窗口被强转为QWidget
    OpenGLWindow *m_openGLWindow;  //openGL的窗口
    Scene *m_pScene;                 //显示的场景
};
