#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <functional>
#include <QFileSystemWatcher>
#include <QObject>
#include <QDir>
#include <QTimer>

class QString;

class FileWatcher : public QObject
{
    Q_OBJECT
public:
    explicit FileWatcher(QObject *parent = Q_NULLPTR);
    void setDirectory(const QString &path);

signals:
    void update();

public slots:
    void directoryChanged(const QString &path);
    void fileChanged(const QString &path);

private:
    void onTimeout();
    void addPaths();

private:
    QFileSystemWatcher watcher;
    QDir dir;
    QTimer timer;
};

#endif // FILEWATCHER_H
