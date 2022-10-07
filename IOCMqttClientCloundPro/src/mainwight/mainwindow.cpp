#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore/QDateTime>
#include <QtWidgets/QMessageBox>

#include "global.h"
#include "user.h"
#include "UserHeartRate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_mysql_oper( MYSQLOperation::getInstance() ),
    main_ui(new Ui::MainWindow)
{
    info_ui = new ShowInfoUI();
    m_client = new QMqttClient(this);
    m_recv_deal = new DealRecvJsonMessage(this->m_mysql_oper);
    m_line_chart = new LineChart(this->m_mysql_oper);
    m_led_oper = new LedOper();

    main_ui->setupUi(this);
    setMaximumSize(600,450);
    setMinimumSize(400,300);

    m_client->setHostname(main_ui->lineEditHost->text());
    m_client->setPort((quint16)main_ui->spinBoxPort->value());
    m_client->setUsername(main_ui->lineEdit_username->text());
    m_client->setPassword(main_ui->lineEdit_pass->text());

    initEnvConnect();
}

MainWindow::~MainWindow()
{
    if(m_led_oper != nullptr)
    {
        delete m_led_oper;
        m_led_oper = nullptr;
    }
    if(m_line_chart != nullptr)
    {
        delete m_line_chart;
        m_line_chart = nullptr;
    }
    if(m_recv_deal != nullptr)
    {
        delete m_recv_deal;
        m_recv_deal = nullptr;
    }

    if(m_client != nullptr)
    {
        m_client->disconnect();
        delete m_client;
        m_client = nullptr;
    }


    delete info_ui;
    delete main_ui;
}


void MainWindow::initEnvConnect()
{

    connect(m_client, &QMqttClient::stateChanged, this, &MainWindow::updateLogStateChange);
    connect(m_client, &QMqttClient::disconnected, this, &MainWindow::brokerDisconnected);
    connect(m_client,&QMqttClient::connected,this,&MainWindow::doConnected);

    connect(m_client,&QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic){
        this->doMessageRecvied(message,topic);
    });

    connect(m_client, &QMqttClient::pingResponseReceived, this, [this]() {
        const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(" PingResponse")
                    + QLatin1Char('\n');
        main_ui->editLog->insertPlainText(content);
    });

    connect(main_ui->lineEditHost, &QLineEdit::textChanged, m_client, &QMqttClient::setHostname);

    connect(main_ui->spinBoxPort, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::setClientPort);

    connect(main_ui->btn_clear,SIGNAL(clicked()),this,SLOT(on_buttonClear_clicked()));
    connect(main_ui->btn_connect,SIGNAL(clicked()),this,SLOT(on_buttonConnect_clicked()));
    connect(main_ui->btn_quit,SIGNAL(clicked()),this,SLOT(on_buttonQuit_clicked()));
    connect(main_ui->btn_subscribe,SIGNAL(clicked()),this,SLOT(on_buttonSubscribe_clicked()));
    connect(main_ui->btn_publish,SIGNAL(clicked()),this,SLOT(on_buttonPublish_clicked()));
    connect(main_ui->btn_showInfo,SIGNAL(clicked()) ,this,SLOT(on_buttonShowInfo_clicked()));
    connect(main_ui->btn_rate,SIGNAL(clicked()),this,SLOT(on_buttonGetRates_clicked()));
    connect(main_ui->btn_led,SIGNAL(clicked()),this,SLOT(on_button_led_clicked()));

    connect(this->m_recv_deal,SIGNAL(signal_main_ui_msg(QString& )),this,SLOT(doLog(QString& )));
    connect(this->m_recv_deal,SIGNAL(signal_info_ui_msg(QString )),this->info_ui,SLOT(addUserIdInfo(QString )));
    connect(this->m_recv_deal,SIGNAL(signal_info_ui_setUID(QString )),this->info_ui,SLOT(setUserId(QString )));
    connect(this->m_led_oper,&LedOper::signalLed,this,[this](LED_STATUS statu) {
        QString str_status = QString::number(statu);
        main_ui->lineEditMessage->setText(str_status);
        on_buttonPublish_clicked();
    });
    connect(this->m_recv_deal,SIGNAL(signal_deal_LedInfo(LedInfo&)),this->m_led_oper,SLOT(slotDealLedInfo(LedInfo& )));
    updateLogStateChange();
}


void MainWindow::on_buttonConnect_clicked()
{
    //验证密码
    QString name = main_ui->lineEdit_username->text();
    DealRecvJsonMessage::replaceNotMeanStr(name);
    User user = m_mysql_oper.selectUserByName(name);
    if( user.getPassword() != main_ui->lineEdit_pass->text())
    {
        main_ui->editLog->appendPlainText("the user login failed user");
        return;
    }

    main_ui->editLog->appendPlainText("the user login succ");
    if (m_client->state() == QMqttClient::Disconnected)
    {
        main_ui->lineEditHost->setEnabled(false);
        main_ui->spinBoxPort->setEnabled(false);
        main_ui->lineEdit_username->setEnabled(false);
        main_ui->lineEdit_pass->setEnabled(false);
        main_ui->btn_connect->setText(tr("Disconnect"));
        m_client->connectToHost();
    }
    else
    {
        main_ui->lineEditHost->setEnabled(true);
        main_ui->spinBoxPort->setEnabled(true);
        main_ui->lineEdit_username->setEnabled(true);
        main_ui->lineEdit_pass->setEnabled(true);
        main_ui->btn_connect->setText(tr("Connect"));
        m_client->disconnectFromHost();
    }
}

void MainWindow::on_button_led_clicked()
{
    if(m_led_oper != nullptr)
    {
        m_led_oper->show();
    }
}

void MainWindow::updateLogStateChange()
{
    const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(": State Change")
                    + QString::number(m_client->state())
                    + QLatin1Char('\n');
    main_ui->editLog->insertPlainText(content);
}

void MainWindow::brokerDisconnected()
{
    main_ui->lineEditHost->setEnabled(true);
    main_ui->spinBoxPort->setEnabled(true);
    main_ui->lineEdit_username->setEnabled(true);
    main_ui->lineEdit_pass->setEnabled(true);
    main_ui->btn_connect->setText(tr("Connect"));

    info_ui->close();
}

void MainWindow::setClientPort(quint16 p)
{
    m_client->setPort(p);
}

void MainWindow::on_buttonPublish_clicked()
{
    QString topic = main_ui->lineEditTopic->text() +"_cmd";
    QByteArray msg = main_ui->lineEditMessage->text().toUtf8();
    if (m_client->publish(topic, msg) == -1)
    {
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not publish message"));
    }
}

void MainWindow::on_buttonSubscribe_clicked()
{
    auto subscription = m_client->subscribe(main_ui->lineEditTopic->text());
    if (!subscription) {
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
        return;
    }
}

void MainWindow::doConnected()
{
    doLog("Connected to addr: "+m_client->hostname()+"  succ\n");
}

void MainWindow::doMessageRecvied(const QByteArray &message, const QMqttTopicName &topic)
{

    const QString content = QDateTime::currentDateTime().toString()
                + QLatin1String(" Received Topic: ")
                + topic.name()
                + QLatin1String(" Message: ")
                + message
                + QLatin1Char('\n');
    main_ui->editLog->insertPlainText(content);


    if(topic.name() == "qtmqtt/topic_temperature")
    {
        setInfoUiMessage(message);
        m_recv_deal->dealTemperatureInfo(message);
    }
    else if(topic.name() == "qtmqtt/topic_rate")
    {
        m_recv_deal->dealRateInfo(message);
        //刷新一次具体解析信息
        m_line_chart->updateLineChart();
    }
    else if(topic.name() == "qtmqtt/topic_led")
    {
        m_recv_deal->dealLedInfo(message);
    }
}




void MainWindow::on_buttonGetRates_clicked()
{
    if(m_line_chart == nullptr)
    {
        m_line_chart = new LineChart(this->m_mysql_oper);
    }
    m_line_chart->show();
}


void MainWindow::on_buttonQuit_clicked()
{
    QApplication::quit();
}


void MainWindow::on_buttonShowInfo_clicked()
{
    if(info_ui == nullptr)
    {
        info_ui = new ShowInfoUI();
    }
    info_ui->show();
}

void MainWindow::on_buttonClear_clicked()
{
    main_ui->editLog->clear();
}


void MainWindow::doLog(const QString& text)
{
    main_ui->editLog->insertPlainText(text);
}


void MainWindow::setInfoUiMessage(const QByteArray &message)
{
    static JSONParseUtil* json_parse  = m_recv_deal->getJsonParser();
    std::string jsonstr = message.toStdString();
    QString mac = ToQString(json_parse->getValueByKey(jsonstr,"macAddr"));

    DealRecvJsonMessage::replaceNotMeanStr(mac);
    info_ui->setMacAddr(mac);

    QString curr_tem = ToQString(json_parse->getValueByKey(jsonstr,"currTem"));
    DealRecvJsonMessage::replaceNotMeanStr(curr_tem);
    info_ui->setCurrTem(curr_tem);

    QString equip_info = ToQString(json_parse->getValueByKey(jsonstr,"equipInfo"));
    DealRecvJsonMessage::replaceNotMeanStr(equip_info);
    info_ui->setEquipInfo(equip_info);
    if( "37.3" < curr_tem)
    {
        QString text = "not normal";
        info_ui->setPersonState(text,ShowInfoUI::PersonState::NOT_NORMAL);
    }
    else
    {
        QString text = "normal";
        info_ui->setPersonState(text,ShowInfoUI::PersonState::NORMAL);
    }
}



