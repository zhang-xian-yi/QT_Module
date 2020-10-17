#ifndef CONNECTMYSQL_H
#define CONNECTMYSQL_H

#include <QObject>
#include <QDebug>
#include <qsql.h>

class ConnectMysql : public QObject
{
    Q_OBJECT
public:
    explicit ConnectMysql(QObject *parent = nullptr);

signals:

public slots:
};

#endif // CONNECTMYSQL_H
