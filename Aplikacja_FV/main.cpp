#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "fv.h"
#include "plants_data.h"
#include "client_data.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

     Plants p;
     Recipers_r c;
     c.load();
          p.load();
 p.saveInFile();
           c.saveInFile();

    FV f;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("f", &f);

    if(!f.init()){
        qDebug()<<"Inicjalizacja fv nie powiodła sie";
    }

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);



    return app.exec();
}
