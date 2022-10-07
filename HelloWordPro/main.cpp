#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "colormaker.h"
#include <QQuickView>
#include <QtQml>



int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ColorMaker>("cn.HelloWord.fun",1,0,"ColorMaker");

    QQuickView viewer;
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.setSource(QUrl("qrc:///qml/c++QML/CMmain.qml"));
    viewer.show();
    /*  1
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
    */
    return app.exec();
}
