#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "personlistmodel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<PersonListModel>("PersonListModel", 1, 0, "PersonListModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
