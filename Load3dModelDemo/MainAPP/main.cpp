#include "MainWindow.h"

#include <QApplication>
#include "OpenGLWindowLayer/Src/IOpenGLWin.h"
#include "OpenGLWindowLayer/Src/ILoad3D.h"
#include "OpenGLWindowLayer/Src/OpenGLWinLayerrFactory.h"

void StructData(QVector<OWlayerNS::InVertex>& VArr,QVector<OWlayerNS::InFaceIndex>& IArr)
{
    OWlayerNS::InVertex v1;
    v1.PostionXYZ = {-0.00512283,-0.00902463,0.0143911};
    v1.NormalUVW = {-9.98539,-0.0210532,0.196846};
    v1.TexCoord = {503.895,-584.548,439.263};

    OWlayerNS::InVertex v2;
    v2.PostionXYZ = {-0.00512283,-0.00902463,0.0143911};
    v2.NormalUVW = {-9.98539,-0.0210532,0.196846};
    v2.TexCoord = {503.895,-584.548,439.263};

    OWlayerNS::InVertex v3;
    v3.PostionXYZ = {-0.00512283,-0.00902463,0.0143911};
    v3.NormalUVW = {-9.98539,-0.0210532,0.196846};
    v3.TexCoord = {503.895,-584.548,439.263};

    OWlayerNS::InVertex v4;
    v4.PostionXYZ = {-0.00512283,-0.00902463,0.0143911};
    v4.NormalUVW = {-9.98539,-0.0210532,0.196846};
    v4.TexCoord = {503.895,-584.548,439.263};

    OWlayerNS::InVertex v5;
    v5.PostionXYZ = {-0.00512283,-0.00902463,0.0143911};
    v5.NormalUVW = {-9.98539,-0.0210532,0.196846};
    v5.TexCoord = {503.895,-584.548,439.263};

    VArr.append({v1,v2,v3,v4,v5});
    //5466 4099 430 430 5282 5282 5282 5282

    OWlayerNS::InFaceIndex i1;
    i1.IndexsArray.append({0,1,2,2,3,3,4,4});

    OWlayerNS::InFaceIndex i2;
    i2.IndexsArray.append({0,1,2,2,3,3,3,3});

    OWlayerNS::InFaceIndex i3;
    i3.IndexsArray.append({0,1,3,3,2,3,3,4});
    IArr.append({i1,i2,i3});
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setFont(QFont("Microsoft YaHei UI", 9));


    QSharedPointer<OWlayerNS::IOpenGLWin> pWin =  OWlayerNS::OpenGLWinLayerrFactory::GetInstance().GetWindowPtr();
    MainWindow w;
    pWin->initOpenGLWin(&w);

    //窗口初始化字符才可以加载
    QSharedPointer<OWlayerNS::ILoad3D> pLM = OWlayerNS::OpenGLWinLayerrFactory::GetInstance().GetLoad3DPtr();
    pLM->Load3DModel("E:\\3DModels\\TransX.obj");


    /*
    QVector<OWlayerNS::InVertex> vectexArr;
    QVector<OWlayerNS::InFaceIndex> indexArray;

    StructData(vectexArr,indexArray);
    pLM->Load3DStructData(vectexArr,indexArray);
    */
    w.show();
    return a.exec();
}


