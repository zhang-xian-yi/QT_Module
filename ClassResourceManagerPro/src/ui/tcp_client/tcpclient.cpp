#include "tcpclient.h"
#include "ui_tcpclient.h"
#include "global.h"
#include <QMessageBox>



ManageTcpCLient::ManageTcpCLient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageTcpCLient)
{
    setupUiConn();
    setupSecureSocket();

    DEBUG_TCP("gouzhao ");
}

ManageTcpCLient::~ManageTcpCLient()
{
    if(nullptr != socket)
    {
        delete socket;
    }
    delete ui;
}

void ManageTcpCLient::connectTo()
{
    socket->connectToHost(ui->hostNameEdit->text(), ui->portBox->value());
    updateEnabledState();
}

void ManageTcpCLient::on_btn_connect()
{
    const bool connected = socket->state() == QAbstractSocket::ConnectedState;
    //如果连接--> 断开   if 断->连接
    connected?disConnect():connectTo();
    updateEnabledState();
    //连接断开/Connect   连接建立/disconnect
    ui->connectButton->setText(connected?"Connect to host":"DisConnected");
}

void ManageTcpCLient::disConnect()
{
    socket->disconnectFromHost();
    updateEnabledState();
}

void ManageTcpCLient::setupUiConn()
{
    ui->setupUi(this);

    connect(ui->hostNameEdit, SIGNAL(textChanged(QString)),
            this, SLOT(updateEnabledState()));
    connect(ui->connectButton, SIGNAL(clicked()),
            this, SLOT(on_btn_connect()));
    connect(ui->sendButton, SIGNAL(clicked()),
            this, SLOT(sendData()));
}

void ManageTcpCLient::setupSecureSocket()
{
    if (nullptr != socket)
    {
        return;
    }

    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(socketError(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(readyRead()),
            this, SLOT(socketReadyRead()));
}

void ManageTcpCLient::updateEnabledState()
{
    const bool unconnected = socket->state() == QAbstractSocket::UnconnectedState;
    ui->hostNameEdit->setReadOnly(!unconnected);
    ui->hostNameEdit->setFocusPolicy(unconnected ? Qt::StrongFocus : Qt::NoFocus);
    ui->hostNameLabel->setEnabled(unconnected);
    ui->portBox->setEnabled(unconnected);
    ui->portLabel->setEnabled(unconnected);
    //ui->connectButton->setEnabled(unconnected && !ui->hostNameEdit->text().isEmpty());

    const bool connected = socket->state() == QAbstractSocket::ConnectedState;
    ui->sessionOutput->setEnabled(connected);
    ui->sessionInput->setEnabled(connected);
    ui->sessionInputLabel->setEnabled(connected);
    ui->sendButton->setEnabled(connected);
}

void ManageTcpCLient::sendData()
{
    const QString input = ui->sessionInput->text();
    appendString(input + '\n');
    socket->write(input.toUtf8() + "\r\n");
    ui->sessionInput->clear();
}

void ManageTcpCLient::appendString(const QString &line)
{
    QTextCursor cursor(ui->sessionOutput->textCursor());
    cursor.movePosition(QTextCursor::End);
    cursor.insertText(line);
}

void ManageTcpCLient::socketStateChanged(QAbstractSocket::SocketState state)
{
    updateEnabledState();

    if (state == QAbstractSocket::UnconnectedState)
    {
        ui->sessionInput->clear();
        ui->hostNameEdit->setPalette(QPalette());
        ui->hostNameEdit->setFocus();
        ui->cipherLabel->setText(tr("<none>"));
    }
    else if(state == QAbstractSocket::ConnectedState)
    {
         DEBUG_TCP("socket connected sunccessful");
    }
    else if(state == QAbstractSocket::ConnectingState)
    {
        DEBUG_TCP("socket connecting");
    }
    else if(state == QAbstractSocket::ConnectionRefusedError)
    {
        DEBUG_TCP("socket refuse connected");
    }
}


void ManageTcpCLient::socketError(QAbstractSocket::SocketError)
{
    if (handlingSocketError)
    {
          return;
    }
    handlingSocketError = true;
    QMessageBox::critical(this, tr("Connection error"), socket->errorString());
    handlingSocketError = false;
}

void ManageTcpCLient::socketReadyRead()
{
    appendString(QString::fromUtf8(socket->readAll()));
}

