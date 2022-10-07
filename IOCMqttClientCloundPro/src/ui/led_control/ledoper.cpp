#include "ledoper.h"
#include "ui_ledoper.h"

#include <QDebug>
#include <QDateTime>
#include "global.h"

LedOper::LedOper(QWidget *parent) :
    QWidget(parent),
    m_mysql_oper(MYSQLOperation::getInstance()),
    ui(new Ui::LedOper)
{
    ui->setupUi(this);
    m_update_time = new QTimer();
    init();
}

LedOper::~LedOper()
{
    if(m_update_time != nullptr)
    {
        delete m_update_time;
    }
    delete ui;
}

LedInfo& LedOper::getLedInfoFromUI()
{
    static LedInfo led_info;
    led_info.setId("1");
    led_info.setTime(QDateTime::currentDateTime());
    led_info.setValue(ui->lab_curr_value->text().toUtf8().toInt());
    //qDebug()<<"get led info: "<<led_info.toString();
    return led_info;
}

void LedOper::open_led()
{
    ui->lab_led->setStyleSheet(m_styleOn);

    LedInfo led_info = getLedInfoFromUI();
    led_info.setStatus(LED_STATUS_ON);
    //qDebug()<<"before save info: "<<led_info.toString();
    slotSaveLedStatus(led_info);
}

void LedOper::close_led()
{
    ui->lab_led->setStyleSheet(m_styleOff);
    //save into sql
    LedInfo led_info = getLedInfoFromUI();
    led_info.setStatus(LED_STATUS_OFF);
    //qDebug()<<"before save info: "<<led_info.toString();
    slotSaveLedStatus(led_info);
}

void LedOper::init()
{
    initForm();
    initConnect();

    //默认自动模式
    this->strategy = LED_STRATEGY::AUTO;
    ui->btn_strategy->setText("to Manual mode");
    ui->btn_led_oper->setEnabled(false);

}

void LedOper::initForm()
{
    //灯泡样式
    m_styleOn = "QLabel{border-image:url(:/file/images/light_on.png);border:0px;}";
    m_styleOff = "QLabel{border-image:url(:/file/images/light_off.png);border:0px;}";
    //setLightStyle(m_styleOff);

    ui->btn_led_oper->setFocusPolicy(Qt::NoFocus);

    //根据配置文件初始化LED的状态
    ui->lab_led->setStyleSheet(m_styleOff);
    ui->btn_led_oper->setChecked(false);

    //设置当前时间显示的格式以及字体颜色
    QFont ft;
    ft.setPointSize(16);
    ui->lab_cv->setFont(ft);
    ui->lab_curr_time->setFont(ft);

    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::black);
    ui->lab_cv->setPalette(pa);
    pa.setColor(QPalette::WindowText,Qt::blue);
    ui->lab_curr_time->setPalette(pa);

    //设置当前显示的数据信息
    ft.setPointSize(14);
    ui->lab_curr_value->setFont(ft);
    ui->lab_curr_value->setPalette(pa);
    //按钮字体的显示
    ui->btn_strategy->setFont(ft);
    ui->btn_led_oper->setFont(ft);
    //启动定时器
    m_update_time->start(1000);
}

//信号和槽初始化
void LedOper::initConnect()
{
    connect(ui->btn_led_oper,SIGNAL(clicked()),this,SLOT(on_btn_led_control_clicked()));
    connect(ui->btn_strategy,SIGNAL(clicked()),this,SLOT(on_btn_led_stratyge_clicked()));
    connect(m_update_time,SIGNAL(timeout()),this,SLOT(slotUpdataTime()));
}

void LedOper::on_btn_led_control_clicked()
{
    static LedInfo led_info = getLedInfoFromUI();
    //qDebug()<<"on btn led control clicked strategy: "<<this->strategy;
    QString led_status = ui->btn_led_oper->text();
    if(led_status == "open")
    {
        open_led();
        ui->btn_led_oper->setText("close");
        led_info.setStatus(LED_STATUS_ON);
        emit signalLed(LED_STATUS_ON);
    }
    else if(led_status == "close")
    {
        close_led();
        ui->btn_led_oper->setText("open");
        led_info.setStatus(LED_STATUS_OFF);
        emit signalLed(LED_STATUS_OFF);
    }
}

void LedOper::on_btn_led_stratyge_clicked()
{
    //设置按钮可操作
    if(this->strategy == LED_STRATEGY::AUTO)
    {
        //change the mode
        this->strategy = LED_STRATEGY::MANUNAL;
        //启动为手动模式 打开按键限制 显示
        ui->btn_strategy->setText("to Automatic mode");
        ui->btn_led_oper->setEnabled(true);
    }
    else if(this->strategy == LED_STRATEGY::MANUNAL)
    {
        //change the mode
        this->strategy = LED_STRATEGY::AUTO;
        ui->btn_strategy->setText("to Manual mode");
        ui->btn_led_oper->setEnabled(false);
    }
}


//更新显示当前时间值
void LedOper::slotUpdataTime()
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    ui->lab_curr_time->setText(current_date);
}

//保存灯的状态，写入数据库
void LedOper::slotSaveLedStatus(LedInfo& info)
{
    bool ret = m_mysql_oper.insertLedInfo(info);
    /*
     * debug
    if(ret)
    {
        qDebug()<<"insert succ";
    }
    else {
        qDebug()<<"insert failed";
    }
    */
}

//从 dealRecvMessage 发送过来的LedInfo
void LedOper::slotDealLedInfo(LedInfo& info)
{
    ui->lab_curr_value->setText(QString::number(info.getValue()));
    //qDebug()<<"slot deal led info strategy: "<<this->strategy;
    if(LED_STRATEGY::AUTO == this->strategy )
    {
        //自动模式
        if(info.getValue() > 250)
        {
            close_led();
            emit signalLed(LED_STATUS_OFF);
        }
        else if(info.getValue() <= 250)
        {
            open_led();
            emit signalLed(LED_STATUS_ON);
        }
    }
    else if(LED_STRATEGY::MANUNAL == this->strategy)
    {
        //手动模式
        //....需要改变某些状态

    }

}
