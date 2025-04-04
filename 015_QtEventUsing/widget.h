#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QEvent>
#include <QProcess>
#include <queue>
#include <memory>
#include <atomic>

// 自定义事件类型
class LoadTestEvent : public QEvent
{
public:
    static const QEvent::Type LoadTestEventType = 
        static_cast<QEvent::Type>(QEvent::User + 1);
    
    LoadTestEvent() : QEvent(LoadTestEventType) {}
};

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    bool event(QEvent *event) override;

private slots:
    void slot_timerOut();
    void on_pushButton_simulate_clicked();

private:
    void appendLog(const QString& message);
    void sendNextBatch();
    void simulateEventLoad(int eventCount);
    void updatePerformanceMetrics();
    qint64 getCurrentProcessMemoryUsage();

    Ui::Widget *ui;
    QTimer *m_timer;
    QTimer *m_simulateTimer;
    QTime m_elapsedTimer;
    QTime m_processTimer;
    std::queue<std::unique_ptr<LoadTestEvent>> m_eventQueue;
    std::atomic<int> m_remainingEvents{0};
    std::atomic<int> m_processedEvents{0};
    qint64 m_totalProcessTime = 0;
    int m_eventCount = 0;
    double m_averageLoad = 0.0;
    qint64 m_lastEventTime = 0;
    qint64 m_lastMemoryUsage = 0;
    double m_memoryGrowthRate = 0.0;
    qint64 m_maxEventDelay = 0;
    qint64 m_totalEventDelay = 0;
    int m_eventDelayCount = 0;
    QProcess m_process;
    const int BATCH_SIZE = 50;
};

#endif // WIDGET_H
