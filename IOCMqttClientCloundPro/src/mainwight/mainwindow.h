#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "qmqttclient.h"
#include "showinfoui.h"
#include "JSONParseUtil.h"
#include "jsonparseutil_global.h"
#include "mysqloperation.h"
#include "LineChart.h"
#include "DealRecvJsonMessage.h"
#include "ledoper.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void setClientPort(quint16 p);

private slots:
    void on_buttonConnect_clicked();
    void on_buttonQuit_clicked();
    void on_buttonPublish_clicked();
    void on_buttonClear_clicked();
    void on_buttonSubscribe_clicked();
    void on_buttonShowInfo_clicked();
    void on_buttonGetRates_clicked();
    void on_button_led_clicked();

    void updateLogStateChange();
    void brokerDisconnected();
    void doConnected();
    void doLog(const QString & text);
    void doMessageRecvied(const QByteArray &message, const QMqttTopicName &topic);
private:
    void setInfoUiMessage(const QByteArray &message);
private:
    void initEnvConnect();
private:
    Ui::MainWindow *main_ui;
    ShowInfoUI* info_ui;
    QMqttClient *m_client;
    MYSQLOperation& m_mysql_oper;
    LineChart*   m_line_chart;
    DealRecvJsonMessage*   m_recv_deal;
    LedOper * m_led_oper;
};

#endif // MAINWINDOW_H
