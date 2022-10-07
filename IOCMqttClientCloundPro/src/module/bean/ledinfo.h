#ifndef LEDINFO_H
#define LEDINFO_H

#include <QString>
#include <QDateTime>

class LedInfo
{
public:
    LedInfo();

    QString getId();
    void    setId(QString i_id);

    QDateTime getTime();
    void    setTime(QDateTime i_time);

    int     getStatus();
    void    setStatus(int i_on);

    int     getValue();
    void     setValue(int i_value);

    QString toString();
private:
    QString id;
    QDateTime time;
    int value;
    int status;
};

#endif // LEDINFO_H
