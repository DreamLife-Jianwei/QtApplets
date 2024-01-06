#include "widget.h"
#include "qdebug.h"
#include "ui_widget.h"
#include <windows.h>
static PDH_HQUERY cpuQuery;
static PDH_HCOUNTER cpuTotal;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("SystemInfo");
    initCpuUsage();
    m_getSystemInfo = new QTimer;
    connect(m_getSystemInfo,&QTimer::timeout,this,&Widget::slot_getSystemInfor);
    m_getSystemInfo->start(1000);
}

Widget::~Widget()
{
    m_getSystemInfo->stop();
    m_getSystemInfo->deleteLater();
    delete ui;
}

void Widget::initCpuUsage()
{
    PdhOpenQuery(NULL, NULL, &cpuQuery);
    // 这里使用了反斜杠转义
    QString str = "\\Processor(_Total)\\% Processor Time";
    PdhAddEnglishCounter(cpuQuery, (LPCWSTR)str.utf16(), NULL, &cpuTotal);
    PdhCollectQueryData(cpuQuery);
}

void Widget::getCurrentCpuUsage()
{
    PDH_FMT_COUNTERVALUE counterVal;

    PdhCollectQueryData(cpuQuery);
    PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);

    ui->label_cpu->setText(QString::number( counterVal.doubleValue) + "%");
}

void Widget::getMemory()
{
// 初始化MEMORYSTATUSEX结构
    MEMORYSTATUSEX memStatus;
    memStatus.dwLength = sizeof(memStatus);

    // 获取内存状态
    if (GlobalMemoryStatusEx(&memStatus)) {

        ui->label_memory_total->setText(QString::number((memStatus.ullTotalPhys / (1024 * 1024))));
        ui->label_memory_ava->setText(QString::number((memStatus.ullAvailPhys / (1024 * 1024))));
        ui->label_memory->setText(QString::number(memStatus.dwMemoryLoad)+"%");

    }
}

void Widget::slot_getSystemInfor()
{
    getCurrentCpuUsage();
    getMemory();
}

