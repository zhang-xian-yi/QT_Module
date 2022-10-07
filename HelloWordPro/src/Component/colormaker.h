#ifndef COLORMAKER_H
#define COLORMAKER_H

#include <QObject>
#include <QColor>

class ColorMaker : public QObject
{
    Q_OBJECT
    Q_ENUMS(GenerateAlgorithm)
    Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor time_color READ getTimeColor )
public:
    explicit ColorMaker(QObject *parent = nullptr);
    ~ColorMaker();

    enum GenerateAlgorithm{
        RandomRGB,
        RandomRed,
        RandomGreen,
        RandomBlue,
        LinearIncrease
    };


public:
    QColor getColor()const;
    void setColor(const QColor& color_);
    QColor getTimeColor() const;
    Q_INVOKABLE GenerateAlgorithm getAlgorithm() const;
    Q_INVOKABLE void setAlgorithm(GenerateAlgorithm algorithm_);
signals:
    void colorChanged(const QColor& color);
    void currentTime(const QString& strTime);
public slots:
    void start();
    void stop();
protected:
    void timeEvent(QTimerEvent* e);
private:
    GenerateAlgorithm m_algorithm;
    QColor m_curr_color;
    int m_n_color_time;
};

#endif // COLORMAKER_H
