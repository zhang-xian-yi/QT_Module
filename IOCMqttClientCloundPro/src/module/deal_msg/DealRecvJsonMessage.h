#ifndef DEALRECVJSONMESSAGE_H
#define DEALRECVJSONMESSAGE_H

#include "mysqloperation.h"
#include "JSONParseUtil.h"
#include "global.h"
#include "user.h"
#include "UserHeartRate.h"
#include "ledinfo.h"

#include <QObject>
#include <QByteArray>

class DealRecvJsonMessage:public QObject
{
    Q_OBJECT
public:
    JSONParseUtil* getJsonParser();
    static void replaceNotMeanStr(QString &text);
    DealRecvJsonMessage(MYSQLOperation& sql_oper);
    void dealTemperatureInfo(const QByteArray &message);
    void dealRateInfo(const QByteArray &message);
    void dealLedInfo(const QByteArray &message);
signals:
    void signal_main_ui_msg(QString& message);
    void signal_info_ui_msg(QString message);
    void signal_info_ui_setUID(QString uid);
    void signal_deal_LedInfo(LedInfo& info);
private:
    MYSQLOperation& m_mysql_oper;
    JSONParseUtil* m_json_parse;
};

#endif // DEALRECVJSONMESSAGE_H
