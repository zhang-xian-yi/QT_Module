#include "MainWindow.h"

#include <QApplication>
#include "OpenGLWindowLayer/Src/IOpenGLWin.h"
#include "OpenGLWindowLayer/Src/ILoad3D.h"
#include "OpenGLWindowLayer/Src/OpenGLWinLayerrFactory.h"

#include "FiniteElementRenderLayer/Src/IOpenGLWin.h"
#include "FiniteElementRenderLayer/Src/ILoad3D.h"
#include "FiniteElementRenderLayer/Src/FERendererLayerFactory.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setFont(QFont("Microsoft YaHei UI", 9));
    MainWindow w;
    w.setGeometry(100,100,800,600);
    //窗口初始化字符才可以加载
    /*
    QSharedPointer<OWlayerNS::IOpenGLWin> pWin =  OWlayerNS::OpenGLWinLayerrFactory::GetInstance().GetWindowPtr();
    pWin->initOpenGLWin(&w);
    w.show();//先显示窗口 再加载
    QSharedPointer<OWlayerNS::ILoad3D> pLM = OWlayerNS::OpenGLWinLayerrFactory::GetInstance().GetLoad3DPtr();
    pLM->Load3DModel("D:\\3DModels\\obj\\Weapon_1.obj");
    */


    QSharedPointer<FERendererNS::IOpenGLWin> pWin =  FERendererNS::FERendererLayerFactory::GetInstance().GetWindowPtr();
    pWin->initOpenGLWin(&w);
    w.show();//先显示窗口 再加载
    QSharedPointer<FERendererNS::ILoad3D> pLM = FERendererNS::FERendererLayerFactory::GetInstance().GetLoad3DPtr();
    pLM->LoadFiniteElementData("D:\\3DModels\\result_rank_3300_0.dat");


    return a.exec();
}
