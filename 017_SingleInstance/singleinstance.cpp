#include "singleinstance.h"
#include <QStandardPaths>
SingleInstance::SingleInstance(const QString& appKey, QObject* parent)
    : QObject(parent)
{
    // 构造唯一文件路径
    QString tempDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
    m_lockFilePath = tempDir + "/" + appKey + ".lock";
    m_pidFilePath = tempDir + "/" + appKey + ".pid";

#ifdef Q_OS_WIN
    // Windows额外使用互斥量
    m_hMutex = CreateMutexW(NULL, TRUE, (L"Global\\" + appKey.toStdWString()).c_str());
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        ReleaseMutex(m_hMutex);
        CloseHandle(m_hMutex);
        m_hMutex = nullptr;
    }
#endif
}

SingleInstance::~SingleInstance() {
    cleanup();
}

bool SingleInstance::isRunning() {
#ifdef Q_OS_WIN
    if (!m_hMutex) return true; // 互斥量创建失败说明已有实例
#endif

    // 第一重检测：QLockFile
    QLockFile lockFile(m_lockFilePath);
    if (!lockFile.tryLock(500)) {
        // 第二重检测：检查进程是否真实存在
        if (isProcessAlive(readPidFromFile())) {
            return true;
        }
        lockFile.removeStaleLockFile(); // 清理失效锁
    }

    writeCurrentPid();
    return false;
}

void SingleInstance::killExisting() {
    qint64 pid = readPidFromFile();
    if (!isProcessAlive(pid)) return;

#ifdef Q_OS_WIN
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (hProcess) {
        TerminateProcess(hProcess, 0);
        CloseHandle(hProcess);
    }
#else
    kill(pid, SIGTERM);
    usleep(50000); // 等待50ms
    if (isProcessAlive(pid)) {
        kill(pid, SIGKILL);
    }
#endif

    cleanup();
}

// 私有方法实现
bool SingleInstance::isProcessAlive(qint64 pid) {
    if (pid <= 0) return false;

#ifdef Q_OS_WIN
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (hProcess) {
        DWORD exitCode;
        GetExitCodeProcess(hProcess, &exitCode);
        CloseHandle(hProcess);
        return (exitCode == STILL_ACTIVE);
    }
#else
    return (kill(pid, 0) == 0);
#endif
    return false;
}

qint64 SingleInstance::readPidFromFile() {
    QFile pidFile(m_pidFilePath);
    if (pidFile.open(QIODevice::ReadOnly)) {
        return pidFile.readAll().toLongLong();
    }
    return -1;
}

void SingleInstance::writeCurrentPid() {
    QFile pidFile(m_pidFilePath);
    if (pidFile.open(QIODevice::WriteOnly)) {
        pidFile.write(QString::number(QCoreApplication::applicationPid()).toUtf8());
    }
}

void SingleInstance::cleanup() {
    QFile::remove(m_lockFilePath);
    QFile::remove(m_pidFilePath);

#ifdef Q_OS_WIN
    if (m_hMutex) {
        ReleaseMutex(m_hMutex);
        CloseHandle(m_hMutex);
        m_hMutex = nullptr;
    }
#endif
}
