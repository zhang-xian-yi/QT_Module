#include "LineChart.h"
#include "UserHeartRate.h"

#include "ui_linechart.h"

#include <QVector>


LineChart::LineChart(MYSQLOperation& sqloper,QWidget *parent) :
    QWidget(parent),
    m_mysql_oper(sqloper),
    ui(new Ui::LineChart)
{
    ui->setupUi(this);
    setMaximumSize(1000,780);
    setMinimumSize(800,600);
    initVar();
    initUi();

    connect(ui->btn_search,SIGNAL(clicked()),this,SLOT(on_btn_search_clicked()));

}

LineChart::~LineChart()
{
    if(this->_serise != nullptr)
    {
        delete this->_serise;
    }
    if(this->_date_axisX != nullptr)
    {
        delete this->_date_axisX;
    }
    if(this->_rate_axisY != nullptr)
    {
        delete this->_rate_axisY;
    }
    if(this->_chart_view != nullptr)
    {
        delete this->_chart_view;
    }
    if(this->_chart_timer != nullptr)
    {
        delete this->_chart_timer;
    }

    delete ui;
}
static UserHeartRate& getMaxTime(QVector<UserHeartRate> data)
{
    static UserHeartRate max;
    max = data.at(0);
    foreach(UserHeartRate rate,data)
    {
        if(rate > max)
        {
            max = rate;
        }
    }
    return max;
}

static UserHeartRate& getMinTime(QVector<UserHeartRate> data)
{
    static UserHeartRate min;
    min = data.at(0);
    foreach(UserHeartRate rate,data)
    {
        if(rate < min)
        {
            min = rate;
        }
    }
    return min;
}

void LineChart::initUi()
{
    //折线图显示
    ui->widget->setChart(this->_chart_view);
    //主题背景
    this->_chart_view->setTheme(QChart::ChartThemeBrownSand);
    //设置chart标题
    this->_chart_view->setTitle("Heart Rate Line Chart");
    //uppos
    upXYPos(QString("41704445"));
    //y 坐标信息
    this->_rate_axisY->setTitleText("heart rate data");
    this->_rate_axisY->setMax(120);
    this->_rate_axisY->setMin(40);
    this->_chart_view->legend()->setVisible(true);
    this->_chart_view->addAxis(this->_rate_axisY,Qt::AlignLeft);
    //每100ms添加数据并更新折线图
    connect(this->_chart_timer,SIGNAL(timeout()),this,SLOT(upXPos()));

}

void LineChart::initVar()
{
    //添加view
    this->_chart_view = new QChart();
    this->_serise = nullptr;
    this->_date_axisX = new QDateTimeAxis();
    this->_rate_axisY = new QValueAxis();
    this->_chart_timer = new QTimer(this);
}

void LineChart::updateLineChart()
{
    QString name = ui->lineEdit_uid->text();
    //qDebug()<<"name: "<<name;
    upXYPos(name);
}


void LineChart::upXYPos(QString uid)
{
    //曲线名称

    if(_serise != nullptr)
    {
        //free the last new memery
        delete _serise;
        //_serise = nullptr;
    }
    _serise = new QLineSeries();
    User user = m_mysql_oper.selectUserByUserId(uid);

    QString name = uid +"     "+user.getName();
    _serise->setName(name);

    QVector<UserHeartRate> data = m_mysql_oper.getRateById(uid);
    if(data.isEmpty())
    {
        return;
    }
    UserHeartRate max;
    UserHeartRate min;
    if(data.isEmpty())
    {
        return;
    }
    else
    {
        // 从数据库中查出的最大时间值和最小时间值最为x坐标的边界
        max = getMaxTime(data);
        min = getMinTime(data);
        foreach(UserHeartRate rate,data)
        {
            _serise->append(rate.getTime().toSecsSinceEpoch(),rate.getRate());
        }
    }


    //x坐标信息
    this->_date_axisX->setMax(max.getTime());
    this->_date_axisX->setMin(min.getTime());
    this->_date_axisX->setTitleText("time sequence");
    this->_date_axisX->setFormat("yyyy-MM-dd hh:mm:ss");
    this->_chart_view->addAxis(this->_date_axisX,Qt::AlignBottom);
    _serise->attachAxis(this->_date_axisX);
    _serise->attachAxis(this->_rate_axisY);

    //添加折线
    this->_chart_view->addSeries(_serise);
}

void LineChart::on_btn_search_clicked()
{
   updateLineChart();
}
