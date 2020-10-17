#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QTextStream>
#include <QUrl>
#include <QDir>
#include <QMessageBox>
#include <QIcon>
#include "global.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->m_thread.start();
    this->m_encrup.moveToThread(&m_thread);

    ui->setupUi(this);
    ui->radioBtn_encryp->setChecked(true);
    ui->progressBar->setValue(0);

    setWindowTitle(tr("加密-解密工具"));
    setWindowIcon(QIcon(":/images/window.ico"));

    initConnect();
}

MainWindow::~MainWindow()
{
    m_thread.exit();
    m_thread.wait(3 * 1000); //10秒超时
    delete ui;
}

void MainWindow::initConnect()
{
    connect(ui->btn_file_src,SIGNAL(clicked()),this,SLOT(on_btn_choose_file_src_onclick()));
    connect(ui->btn_file_dest,SIGNAL(clicked()),this,SLOT(on_btn_choose_file_dest_onclick()));
    connect(ui->btn_ok,SIGNAL(clicked()),this,SLOT(on_btn_ok_onclick()));
    connect(&m_encrup,SIGNAL(sendProgressBarSignal(int,int)),this,SLOT(recvProgressBarSlot(int,int)));
}


//btn response func
void MainWindow::on_btn_choose_file_src_onclick()
{
    //clear progress
    ui->progressBar->setValue(0);

    QString file_src_path = QFileDialog::getOpenFileName(this,tr("选择需要的文件"),"/",tr("*.txt"));
    QFileInfo file_info(file_src_path);
    TRACE("file_src_path: %s\n",file_src_path.toLatin1().data());
    if(file_info.exists())
    {
        ui->lineEdit_file_src->setText(file_src_path);
    }
    else
    {
        ui->lineEdit_file_src->setText(tr("该文件不存在"));
    }

}

void MainWindow::on_btn_choose_file_dest_onclick()
{
    QUrl file_dest_path = QFileDialog::getExistingDirectory(this,tr("选择需要保存的路径"));
    TRACE("file_src_path: %s\n",file_dest_path.url().toLatin1().data());
    //set the url
    if(file_dest_path.isValid())
    {
        ui->lineEdit_file_dest->setText(file_dest_path.url());
    }
    else
    {
        QMessageBox::information(this,tr("目标路径信息:"),"目标路径不合法");
    }

}

void MainWindow::on_btn_ok_onclick()
{
    QFile file(ui->lineEdit_file_src->text());
    //如果文件不存在 无法加密
    if(!file.exists())
    {
        QMessageBox::information(this,tr("源文件信息:"),"文件不存在!!");
        return;
    }
    QDir dest_dir(ui->lineEdit_file_dest->text());
    if(! dest_dir.exists())
    {
        QMessageBox::information(this,tr("目标路径信息:"),"目标路径不合法");
        return;
    }

    if(ui->radioBtn_encryp->isChecked())
    {
        //如果是加密文件
        this->m_encrup.encryptFile(ui->lineEdit_file_src->text(),ui->lineEdit_file_dest->text());
    }
    else if(ui->radioBtn_deencryp->isChecked())
    {
        //如果是解密文件
        this->m_encrup.decryptFile(ui->lineEdit_file_src->text(),ui->lineEdit_file_dest->text());
    }
}

void MainWindow::recvProgressBarSlot(int current,int total)
{
    ui->progressBar->setMaximum(total);
    ui->progressBar->setValue(current);
}
