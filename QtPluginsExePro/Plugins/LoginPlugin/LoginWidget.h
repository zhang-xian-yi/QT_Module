#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWidget; }
QT_END_NAMESPACE

class LoginWidget : public QMainWindow
{
    Q_OBJECT

public:
    LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

private:
    Ui::LoginWidget *ui;
};
#endif // LOGINWIDGET_H
