#include "colormaker.h"
#include <QDateTime>

ColorMaker::ColorMaker(QObject *parent) :
    QObject(parent),
    m_algorithm(RandomRGB),
    m_curr_color(Qt::black),
    m_n_color_time(0)
{
    qsrand(QDateTime::currentDateTime().toTime_t());
}

ColorMaker::~ColorMaker()
{

}

QColor ColorMaker::getColor()const
{
    return m_curr_color;
}

void ColorMaker::setColor(const QColor &color_)
{
    m_curr_color = color_;
    emit colorChanged(m_curr_color);
}

ColorMaker::GenerateAlgorithm ColorMaker::getAlgorithm() const
{
    return m_algorithm;
}

void ColorMaker::setAlgorithm(GenerateAlgorithm algorithm_)
{
    m_algorithm = algorithm_;
}

QColor ColorMaker::getTimeColor() const
{
    QTime time = QTime::currentTime();
    int r = time.hour();
    int g = time.minute()*2;
    int b = time.second()*4;
    return QColor::fromRgb(r,g,b);

}

void ColorMaker::start()
{
    if(0 == m_n_color_time )
    {
        m_n_color_time = startTimer(1000);
    }
}

void ColorMaker::stop()
{
    if(0 < m_n_color_time)
    {
        killTimer(m_n_color_time);
        m_n_color_time = 0;
    }
}


#include <QTimerEvent>
void ColorMaker::timeEvent(QTimerEvent *e)
{
    if(m_n_color_time == e->timerId())
    {
        switch (m_algorithm)
        {
            case RandomRGB:
            {
                m_curr_color.setRgb(qrand()%255,qrand()%255,qrand()%255);
                break;
            }
            case RandomRed:
            {
                m_curr_color.setRed(qrand()%255);
                break;
            }
            case RandomGreen:
            {
                m_curr_color.setGreen(qrand()%255);
                break;
            }
            case RandomBlue:
            {
                m_curr_color.setBlue(qrand()%255);
                break;
            }
            case LinearIncrease:
            {
                int r = m_curr_color.red() +10;
                int g = m_curr_color.green() + 10;
                int b = m_curr_color.blue() + 10;
                m_curr_color.setRgb(r,g,b);
                break;
            }
        }

        emit colorChanged(m_curr_color);
        emit currentTime(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    }
    else
    {
        QObject::timerEvent(e);
    }
}
