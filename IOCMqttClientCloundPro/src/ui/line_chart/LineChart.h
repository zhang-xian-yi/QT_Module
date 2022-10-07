#ifndef LINECHART_H
#define LINECHART_H

#include <QWidget>
#include <QChart>
#include <QLineSeries>
#include <QChartView>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QTimer>
#include <QMutex>
#include "mysqloperation.h"

#define X_WIDTH 200 //x轴宽度
#define Y_FLOAT 100 //Y轴数据浮动大小
#define UPDATE_TIME 100 //每6000ms更新一次数据
#define RAND_NUM 50 //随机数取值范围

using namespace QtCharts;

QT_CHARTS_USE_NAMESPACE


namespace Ui {
class LineChart;
}

class LineChart : public QWidget
{
    Q_OBJECT

public:
    explicit LineChart(MYSQLOperation& sqloper,QWidget *parent = nullptr);
    ~LineChart();
public:
    void updateLineChart();//更新折线图
    void initVar();//初始化变量
    void initUi();//初始化UI
private slots:
    void upXYPos(QString uid);//更新折线图及坐标
    void on_btn_search_clicked();
private:
    Ui::LineChart *ui;
    QMutex  _line_mutext;
    QTimer*  _chart_timer;
    QChart*  _chart_view;
    QValueAxis*  _rate_axisY;
    QDateTimeAxis* _date_axisX;
    MYSQLOperation& m_mysql_oper;

    QLineSeries* _serise;
};

#endif // LINECHART_H
