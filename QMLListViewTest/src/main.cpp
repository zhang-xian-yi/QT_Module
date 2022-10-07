#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "servicelistviewmodel.h"

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    ServiceListviewModel model;
    QQmlContext *ctx = engine.rootContext();
    ctx->setContextProperty("ServicerModel", &model);
    engine.load(QUrl(QStringLiteral("qrc:/src/ui/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
