#ifndef LEDOPER_H
#define LEDOPER_H

#include <QWidget>
#include "mysqloperation.h"
#include <QTimer>


namespace Ui {
class LedOper;
}


#define   LED_ON         1
#define   LED_OFF        0

#define   QDEBUG        0

enum LED_STATUS
{
    LED_STATUS_ON = 0,
    LED_STATUS_OFF
};

enum LED_STRATEGY
{
    AUTO = 10,
    MANUNAL
};

class LedOper : public QWidget
{
    Q_OBJECT

public:
    explicit LedOper(QWidget *parent = nullptr);
    ~LedOper();

    void open_led();
    void close_led();

private:
    void initForm();
    void init();
    void initConnect();

    LedInfo& getLedInfoFromUI();

public slots:
    void slotDealLedInfo(LedInfo& info);

private slots:
    void on_btn_led_control_clicked();
    void on_btn_led_stratyge_clicked();

    void slotUpdataTime();
    void slotSaveLedStatus(LedInfo& info);

signals:
    void signalLed(LED_STATUS status);

private:
    Ui::LedOper *ui;
    QString m_styleOn;                  //灯打开
    QString m_styleOff;                 //灯关闭
    MYSQLOperation&  m_mysql_oper;
    LED_STRATEGY strategy;
    QTimer* m_update_time;
};

#endif // LEDOPER_H
