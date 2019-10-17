#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QQuickPaintedItem>
#include <QPainter>
#include <QtQuick>
#include <QObject>

#include <iostream>

#include "simulation.h"
#include "organism.h"

#include "neuralnetwork.h"

int main(int argc, char *argv[])
{
	NeuralNetwork nn;
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QQuickItem* container = engine.rootObjects().first()->findChild<QQuickItem*>("container");

    Simulation sim(container->findChild<QQuickItem*>("column"), Simulation::Mode::train);

    return app.exec();
}

