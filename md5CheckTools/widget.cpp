#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    mThread.start();
    md5Check.moveToThread(&mThread);

    //调用方式 都是属于parent线程
    connect(this, SIGNAL(checkMd5SumSignal(QString)),
            &md5Check, SLOT(getMd5CheckSumSlot(QString)));

    connect(&md5Check, SIGNAL(sendMd5CheckSunSignal(QByteArray)),
            this, SLOT(recvMd5CheckSunSlot(QByteArray)));

    connect(&md5Check, SIGNAL(sendProgressBarSignal(int, int)),
            this, SLOT(recvProgressBarSlot(int, int)));
}

Widget::~Widget()
{
    mThread.exit();
    mThread.wait(10 * 1000); //10秒超时
    delete ui;
}

void Widget::on_toolButtonOpenFile_clicked()
{
    QFileInfo md5FileInfo;
    QByteArray md5;
    QString md5FileName = QFileDialog::getOpenFileName(this,
                                            QString::fromLocal8Bit("选择需要MD5的文件"));
    qDebug() << md5FileName;

    md5FileInfo = QFileInfo(md5FileName);

    if(md5FileInfo.exists())
    {
        ui->lineEdit->setText(md5FileInfo.fileName());
        emit checkMd5SumSignal(md5FileName);
    }

    ui->textBrowser->setText(md5);
}

void Widget::on_pushButtonClose_clicked()
{
    this->close();
}

void Widget::recvMd5CheckSunSlot(const QByteArray & md5)
{
    ui->textBrowser->setText(md5);
}

void Widget::recvProgressBarSlot(int current, int total)
{
    //qDebug() << "recvProgressBarSlot" << current << total;
    ui->progressBar->setMaximum(total);
    ui->progressBar->setValue(current);
}
