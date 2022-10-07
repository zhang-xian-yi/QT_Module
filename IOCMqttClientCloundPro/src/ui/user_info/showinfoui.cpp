#include "ShowInfoUI.h"
#include "ui_showinfoui.h"

#include <QDebug>

ShowInfoUI::ShowInfoUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowInfoUI)
{
    ui->setupUi(this);

}

ShowInfoUI::~ShowInfoUI()
{
    delete ui;
}

void ShowInfoUI::setUserId(QString uid)
{
    ui->textBrowser_userid->clear();
    ui->textBrowser_userid->setText(uid);
}

void ShowInfoUI::setMacAddr(QString& mac)
{
    ui->textBrowser_macaddr->clear();
    ui->textBrowser_macaddr->setText(mac);
}

void ShowInfoUI::setCurrTem(QString &curr_tem)
{
    ui->textBrowser_curr_tem->clear();
    ui->textBrowser_curr_tem->setText(curr_tem);
}

void ShowInfoUI::setEquipInfo(QString &info)
{
    ui->textBrowser_equip_info->clear();
    ui->textBrowser_equip_info->setText(info);
}

void ShowInfoUI::setPersonState(QString &text,PersonState flag)
{
    ui->textBrowser_person_state->clear();
    QString showText = text;
    if(flag == PersonState::NOT_NORMAL)
    {
        showText = "<font color=\"#FF0000\">" + text + "</font>";
    }
    ui->textBrowser_person_state->append(showText);
    ui->textBrowser_person_state->append("\n");
}

void ShowInfoUI::addUserIdInfo(QString text)
{
    ui->textBrowser_userid->append(text);
}
