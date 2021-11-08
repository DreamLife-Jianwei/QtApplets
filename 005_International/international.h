#ifndef INTERNATIONAL_H
#define INTERNATIONAL_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class International; }
QT_END_NAMESPACE

class International : public QWidget
{
    Q_OBJECT

public:
    International(QWidget *parent = nullptr);
    ~International();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::International *ui;
};
#endif // INTERNATIONAL_H
