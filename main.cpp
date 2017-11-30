#include <QGuiApplication>
#include <QQuickView>
#include <QUrl>
#include <QQmlEngine>

#include "filewatcher.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickView view;

    const QDir dir("/home/qwerty/github/FileWatcher");
    const QUrl fileName = QUrl::fromLocalFile(dir.filePath("main.qml"));

    view.setWidth(400);
    view.setHeight(400);
    view.show();

    FileWatcher watcher;
    QObject::connect(&watcher, &FileWatcher::update,  [&view, fileName](){
            view.engine()->clearComponentCache();
            view.setSource(fileName);
         });

    watcher.setDirectory(dir.absolutePath());

    return app.exec();
}
