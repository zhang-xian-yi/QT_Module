#include "MainWindow.h"

#include <QApplication>
#include "OpenGLWindowUI/Src/IOpenGLWin.h"
#include "OpenGLWindowUI/Src/openglwinfactory.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    OpenGLWinNS::IOpenGLWindows* pWin =  OpenGLWinNS::OpenGLWinFactory::GetInstance().GetWindowPtr();
    pWin->InitOpenGLWindow(&w);



    w.show();
    return a.exec();
}
