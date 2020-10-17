#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "encryputil.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:

private:
    void initConnect();
    void initControl();
private slots:
    //选择源文件的路径
    void on_btn_choose_file_src_onclick();
    //选择目标文件的路径
    void on_btn_choose_file_dest_onclick();
    //确认操作
    void on_btn_ok_onclick();
    //接受进度信号
    void recvProgressBarSlot(int current,int total);
private:
    Ui::MainWindow *ui;
    //Encryp thread
    QThread m_thread;
    EncrypUtil m_encrup;
};

#endif // MAINWINDOW_H
