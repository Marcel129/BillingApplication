#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QLocale>
#include <QTranslator>
#include <QObject>

#include <my_classs.h>
#include <invoice.h>
#include <database.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);


    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "testy_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }
    my_classs my_class_instantiondupa (nullptr);

    QSharedPointer<database> db(new database);
    invoice myInvoice(db);


     if(!db->getIsLoaded()){
         qDebug()<<"Failed to load data";
     }

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("my_class_instantiondupa", &my_class_instantiondupa);
    engine.rootContext()->setContextProperty("myInvoice", &myInvoice);
    engine.rootContext()->setContextProperty("myDatabase", db.data());

//    my_class_instantiondupa.setText("ADAM");
    my_class_instantiondupa.addToList("bogdan");
    my_class_instantiondupa.addToList("domino");
    my_class_instantiondupa.addToList("stefan");
    my_class_instantiondupa.addToList("w naturze");

    QDate a;

    qDebug( ) << a.currentDate().toString("dd.MM.yyyy");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
