/*****************************************************************************
 * commonlistmodel.h
 *
 * Created: 8 2017 by amir
 *
 * Copyright 2017 "INTERSET". All rights reserved.
**************************************************************************/
#ifndef SERVICELISTVIEWMODEL_H
#define SERVICELISTVIEWMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QTimer>
#include "entity.h"

class ServiceListviewModelPrivate;

class ServiceListviewModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit ServiceListviewModel(QObject *parent = nullptr);
    ~ServiceListviewModel() override;
    /*
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;
    */
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole) override;
    QHash<int, QByteArray> roleNames() const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Q_INVOKABLE void doLog(const QString& msg);
signals:
    void writeData(QString data);
private slots:
    void updateData();
private:
    ServiceListviewModelPrivate* m_service;
    QTimer * m_timer;
};

#endif // SERVICELISTVIEWMODEL_H
