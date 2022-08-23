#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QLocale>
#include <QTranslator>
#include <QObject>

#include <my_classs.h>
#include <invoice.h>
#include <database.h>
#include <invreclistmodel.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    qmlRegisterType<InvRecListModel>("InvRecords", 1, 0, "InvRecListModel");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "testy_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    qDebug()<<"143"<<numberInWords_polish(143.14);
    qDebug()<<"9"<<numberInWords_polish(9);
    qDebug()<<"43"<<numberInWords_polish(43);
    qDebug()<<"100"<<numberInWords_polish(100);
    qDebug()<<"57"<<numberInWords_polish(57);
    qDebug()<<"300"<<numberInWords_polish(300);
    qDebug()<<"345"<<numberInWords_polish(345);
    qDebug()<<"14"<<numberInWords_polish(14);

    QSharedPointer<database> db(new database);
    invoice myInvoice(db);

     if(!db->getIsLoaded()){
         qDebug()<<"Failed to load data";
     }

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("myInvoice", &myInvoice);
    engine.rootContext()->setContextProperty("myDatabase", db.data());

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
