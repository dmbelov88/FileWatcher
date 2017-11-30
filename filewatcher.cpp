#include <QDebug>
#include <QString>

#include "filewatcher.h"

FileWatcher::FileWatcher(QObject *parent)
: QObject(parent)
{
    QObject::connect(&watcher, &QFileSystemWatcher::directoryChanged, this, &FileWatcher::directoryChanged);
    QObject::connect(&watcher, &QFileSystemWatcher::fileChanged, this, &FileWatcher::fileChanged);

    timer.setSingleShot(true);

    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setNameFilters(QStringList() << "*.qml");

    QObject::connect(&timer, &QTimer::timeout, this, &FileWatcher::onTimeout);
}

void FileWatcher::addPaths()
{
    QStringList entries = dir.entryList();
    for (int i = 0; i < entries.size(); ++i)
        entries[i].prepend(dir.absolutePath() + "/");

    watcher.addPaths(entries);
}

void FileWatcher::setDirectory(const QString &path)
{
    if (!watcher.addPath(path))
        qWarning() << "Could not add path: " << path;
    else
    {
        dir.setPath(path);
        addPaths();
    }
}

void FileWatcher::directoryChanged(const QString &path)
{
    Q_UNUSED(path);
    addPaths();
}

void FileWatcher::fileChanged(const QString &path)
{
    Q_UNUSED(path);
    timer.start();
}

void FileWatcher::onTimeout()
{
    emit update();
}
