#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QDebug>
#include <QCryptographicHash>
#include <QThread>

#include "md5Check.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

signals:
    void checkMd5SumSignal(QString filePath);

private slots:
    void on_toolButtonOpenFile_clicked();

    void on_pushButtonClose_clicked();

    void recvMd5CheckSunSlot(const QByteArray &);

    void recvProgressBarSlot(int, int);

private:
    Ui::Widget *ui;

    Md5Check md5Check;
    QThread mThread;
};

#endif // WIDGET_H
