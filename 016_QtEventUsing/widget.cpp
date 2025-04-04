#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QThread>
#include <QTime>
#include <QDateTime>
#include <QTextCodec>
#include <QScrollBar>
#include <QProcess>
#include <QOperatingSystemVersion>
#include <QCoreApplication>
#include <QQueue>
#include <memory>
#include <atomic>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    
    // 设置文本编码
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    
    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&Widget::slot_timerOut);
    m_timer->start(1000); // 每秒触发一次
    m_elapsedTimer.start();
    m_processTimer.start();

    // 初始化模拟事件定时器
    m_simulateTimer = new QTimer(this);
    m_simulateTimer->setInterval(20); // 每20ms发送一批事件
    connect(m_simulateTimer, &QTimer::timeout, this, &Widget::sendNextBatch);

    // 初始化性能监控
    m_lastEventTime = m_elapsedTimer.elapsed();
    m_lastMemoryUsage = getCurrentProcessMemoryUsage();
}

Widget::~Widget()
{
    delete ui;
}

qint64 Widget::getCurrentProcessMemoryUsage()
{
    QProcess process;
    QStringList arguments;
    arguments << "/FO" << "CSV" << "/NH" << "/FI" << QString("PID eq ") + QString::number(QCoreApplication::applicationPid());
    process.start("tasklist", arguments);
    process.waitForFinished();
    
    QString output = process.readAllStandardOutput();
    QStringList lines = output.split("\n");
    if (!lines.isEmpty()) {
        QStringList fields = lines[0].split(",");
        if (fields.size() > 4) {
            // 内存使用量在第5个字段，格式为 "xxx,xxx K"
            QString memoryStr = fields[4].trimmed();
            memoryStr = memoryStr.remove("\"");
            memoryStr = memoryStr.remove(" K");
            memoryStr = memoryStr.remove(",");
            return memoryStr.toLongLong() * 1024; // 转换为字节
        }
    }
    return 0;
}

void Widget::appendLog(const QString& message)
{
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    QString logMessage = QString("[%1] %2").arg(timestamp).arg(message);
    ui->plainTextEdit->appendPlainText(logMessage);
    // 自动滚动到底部
    ui->plainTextEdit->verticalScrollBar()->setValue(
        ui->plainTextEdit->verticalScrollBar()->maximum()
    );
}

void Widget::updatePerformanceMetrics()
{
    // 计算内存使用情况
    qint64 currentMemoryUsage = getCurrentProcessMemoryUsage();
    if (m_lastMemoryUsage > 0) {
        m_memoryGrowthRate = static_cast<double>(currentMemoryUsage - m_lastMemoryUsage) / 
                            static_cast<double>(m_lastMemoryUsage) * 100.0;
    }
    m_lastMemoryUsage = currentMemoryUsage;

    // 计算事件处理延迟
    qint64 currentTime = m_elapsedTimer.elapsed();
    qint64 eventDelay = currentTime - m_lastEventTime;
    if (eventDelay > m_maxEventDelay) {
        m_maxEventDelay = eventDelay;
    }
    m_totalEventDelay += eventDelay;
    m_eventDelayCount++;
    m_lastEventTime = currentTime;

    // 输出性能指标
    QString metrics = QString::fromUtf8("性能指标 - 内存使用: %1 MB 内存增长率: %2% 最大事件延迟: %3 ms 平均事件延迟: %4 ms")
        .arg(QString::number(currentMemoryUsage / (1024 * 1024), 'f', 2))
        .arg(QString::number(m_memoryGrowthRate, 'f', 2))
        .arg(QString::number(m_maxEventDelay))
        .arg(QString::number(m_eventDelayCount > 0 ? m_totalEventDelay / m_eventDelayCount : 0));
    
    appendLog(metrics);
}

bool Widget::event(QEvent *event)
{
    if (event->type() == LoadTestEvent::LoadTestEventType) {
        // 模拟一些处理时间，但不阻塞
        QThread::usleep(50); // 使用微秒级延迟，减少阻塞
        m_processedEvents++;
        return true;
    }
    return QWidget::event(event);
}

void Widget::sendNextBatch()
{
    if (m_remainingEvents <= 0) {
        m_simulateTimer->stop();
        appendLog(QString::fromUtf8("事件模拟完成，共处理事件: %1").arg(m_processedEvents));
        return;
    }

    int currentRemaining = m_remainingEvents.load();
    int batchSize = std::min(BATCH_SIZE, currentRemaining);
    
    // 创建事件并加入队列
    for (int i = 0; i < batchSize; ++i) {
        auto event = std::make_unique<LoadTestEvent>();
        m_eventQueue.push(std::move(event));
    }
    
    // 发送队列中的事件
    while (!m_eventQueue.empty()) {
        auto event = std::move(m_eventQueue.front());
        m_eventQueue.pop();
        QApplication::postEvent(this, event.release());
    }
    
    m_remainingEvents -= batchSize;
}

void Widget::simulateEventLoad(int eventCount)
{
    appendLog(QString::fromUtf8("开始模拟事件负载，事件数量: %1").arg(eventCount));
    m_remainingEvents = eventCount;
    m_processedEvents = 0;
    m_simulateTimer->start();
    
    // 重置性能指标
    m_maxEventDelay = 0;
    m_totalEventDelay = 0;
    m_eventDelayCount = 0;
}

void Widget::slot_timerOut()
{
    // 重置处理时间计时器
    m_processTimer.restart();
    
    // 处理所有待处理的事件
    QApplication::processEvents();
    
    // 获取实际的事件处理时间
    qint64 processTime = m_processTimer.elapsed();
    m_totalProcessTime += processTime;
    
    // 计算负载（事件处理时间占总时间的比例）
    double load = static_cast<double>(processTime) / 1000.0; // 转换为秒
    
    // 更新平均负载
    m_eventCount++;
    m_averageLoad = static_cast<double>(m_totalProcessTime) / (m_eventCount * 1000.0);
    
    // 输出负载信息
    QString logMessage = QString::fromUtf8("事件系统负载: %1% 平均负载: %2% 事件计数: %3 处理时间: %4 ms 待处理事件数: %5 已处理事件数: %6")
        .arg(load * 100, 0, 'f', 2)
        .arg(m_averageLoad * 100, 0, 'f', 2)
        .arg(m_eventCount)
        .arg(processTime)
        .arg(m_remainingEvents.load())
        .arg(m_processedEvents.load());
    
    appendLog(logMessage);
    
    // 更新性能指标
    updatePerformanceMetrics();
}

void Widget::on_pushButton_simulate_clicked()
{
    simulateEventLoad(ui->spinBox->value() * 1000);
}

