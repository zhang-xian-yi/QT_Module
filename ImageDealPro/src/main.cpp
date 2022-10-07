#include <QGuiApplication>
#include <QtQml>
#include <QQuickView>
#include <QQuickItem>
#include <QtDebug>
#include "imageprocesseror.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ImageProcesseror>("cn.callQML.viewer",1,0,"ImageProcessor");
    QQuickView viewer;
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.setSource(QUrl("qrc:/appfile/qml/main.qml"));
    viewer.show();

    return app.exec();
}
