#ifndef SINGLEINSTANCE_H
#define SINGLEINSTANCE_H

#include <QObject>
#include <QLockFile>
#include <QDir>
#include <QDebug>
#include <QCoreApplication>

#ifdef Q_OS_WIN
#include <windows.h>
#else
#include <signal.h>
#include <unistd.h>
#endif

class SingleInstance : public QObject {
    Q_OBJECT
public:
    explicit SingleInstance(const QString& appKey, QObject* parent = nullptr);
    ~SingleInstance();

    bool isRunning();  // 返回true表示已有实例运行
    void killExisting(); // 强制终止已有实例

private:
    bool isProcessAlive(qint64 pid);
    qint64 readPidFromFile();
    void writeCurrentPid();
    void cleanup();

    QString m_lockFilePath;
    QString m_pidFilePath;

#ifdef Q_OS_WIN
    HANDLE m_hMutex = nullptr;
#endif
};

#endif // SINGLEINSTANCE_H
