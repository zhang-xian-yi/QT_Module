#ifndef SHOWINFOUI_H
#define SHOWINFOUI_H

#include <QDialog>


namespace Ui {
class ShowInfoUI;
}

class ShowInfoUI : public QDialog
{
    Q_OBJECT
public:
    enum PersonState
    {
        NORMAL = 0,
        NOT_NORMAL,
    };

public:
    explicit ShowInfoUI(QWidget *parent = nullptr);
    ~ShowInfoUI();
    void setMacAddr(QString& mac);
    void setEquipInfo(QString& info);
    void setCurrTem(QString& curr_tem );
    void setPersonState(QString&  text,PersonState flag);
public slots:
    void setUserId(QString uid);
    void addUserIdInfo(QString  text);
private:
    Ui::ShowInfoUI *ui;
};

#endif // SHOWINFOUI_H
