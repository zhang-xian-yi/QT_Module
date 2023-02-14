#include "MainWindow.h"

#include <QApplication>
#include "OpenGLWindowLayer/Src/IOpenGLWin.h"
#include "OpenGLWindowLayer/Src/ILoad3D.h"
#include "OpenGLWindowLayer/Src/OpenGLWinLayerrFactory.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setFont(QFont("Microsoft YaHei UI", 9));


    OWlayerNS::IOpenGLWin* pWin =  OWlayerNS::OpenGLWinLayerrFactory::GetInstance().GetWindowPtr();
    MainWindow w;
    pWin->initOpenGLWin(&w);

    //窗口初始化字符才可以加载
    OWlayerNS::ILoad3D* pLM = OWlayerNS::OpenGLWinLayerrFactory::GetInstance().GetLoad3DPtr();
    pLM->Load3DModel("E:\\3DModels\\TransX.obj");

    w.show();
    return a.exec();
}
