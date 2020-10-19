#include "tcpclient.h"
#include "ui_tcpclient.h"
#include "global.h"
#include <QMessageBox>
#include "stringutil.h"
#include <QDateTime>

ManageTcpCLient::ManageTcpCLient(QWidget *parent) :
    QWidget(parent),
    m_file_oper(new AllFilePathInDir),
    ui(new Ui::ManageTcpCLient)
{
    setupUiConn();
    setupSecureSocket();
    initConnect();

    initClientFileList();

}

ManageTcpCLient::~ManageTcpCLient()
{
    if(nullptr != m_file_oper)
    {
        delete m_file_oper;
    }

    if(nullptr != socket)
    {
        delete socket;
    }
    delete ui;
}

void ManageTcpCLient::LOG_sessionOut(const QStringList &strs)
{
    ui->sessionOutput->clear();
    foreach(QString item,strs)
    {
        ui->sessionOutput->append(item);
    }
}

bool ManageTcpCLient::setClientListview(const QStringList &list)
{
    QItemSelectionModel *m = ui->client_listView->selectionModel();
    delete m;
    // set model 并不会释放内存 需要释放之前的内存
    QStringListModel *model = new QStringListModel(list);
    ui->client_listView->setModel(model);
    return true;
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
    //设置listview 不可编辑
    ui->client_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->server_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->curr_dir_lab->setVisible(false);
    ui->curr_dir_lab->setText(ui->root_path_lineEdit->text());

    connect(ui->hostNameEdit, SIGNAL(textChanged(QString)),
            this, SLOT(updateEnabledState()));
    connect(ui->connectButton, SIGNAL(clicked()),
            this, SLOT(on_btn_connect()));
    connect(ui->sendButton, SIGNAL(clicked()),
            this, SLOT(sendData()));


    //初始化 client list 的connect
    connect(ui->client_listView,SIGNAL(doubleClicked(const QModelIndex &)),
            this,SLOT(doubleClickedClientListItem(const QModelIndex &)));
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
    ui->server_listView->setEnabled(connected);
    ui->sendButton->setEnabled(connected);
    ui->btn_upload->setEnabled(connected);
    ui->btn_preview->setEnabled(connected);
    ui->btn_download->setEnabled(connected);
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

void ManageTcpCLient::initConnect()
{
    connect(ui->btn_search,SIGNAL(clicked()),this,SLOT(on_btn_search()));
    connect(ui->btn_upload,SIGNAL(clicked()),this,SLOT(on_btn_upload()));
}

bool ManageTcpCLient::on_btn_upload()
{
    QFile file(m_upload_file_dir);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray array = file.readAll();
        //写入文件
        socket->write(array);
        return true;
    }
    return false;
}

void ManageTcpCLient::on_clientlistview_item_clicked(const QModelIndex &index)
{
    QString txt = ui->client_listView->model()->data(index).toString();
    m_upload_file_dir = ui->curr_dir_lab->text()+"\\"+txt;
}

void ManageTcpCLient::socketStateChanged(QAbstractSocket::SocketState state)
{
    updateEnabledState();

    if (state == QAbstractSocket::UnconnectedState)
    {
        ui->sessionInput->clear();
        ui->hostNameEdit->setPalette(QPalette());
        ui->hostNameEdit->setFocus();
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
    appendString("date:%s"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm")+QString::fromUtf8(socket->readAll()));
}

void ManageTcpCLient::doubleClickedClientListItem(const QModelIndex &index)
{
    static QString curr_dir;
    curr_dir = ui->curr_dir_lab->text();
    QString txt = ui->client_listView->model()->data(index).toString();
    DEBUG_UI("double clicked item txt:%s",txt.toStdString().c_str());
    //获取选中的路径
    curr_dir = curr_dir +"\\"+txt;
    QFileInfo fileinfo(curr_dir);
    if(fileinfo.isDir())
    {
        //【更新】  该目录下的所有文件/文件夹 会被显示到client listview中
        QStringList list = m_file_oper->getFileAndDirPathNameOfSplDir(curr_dir);
        setClientListview( StringUtil::getInstance().getLastNameOfFileList(list));
        ui->curr_dir_lab->setText(curr_dir);
    }
    else if(fileinfo.isFile())
    {
        ui->sessionOutput->clear();
        ui->sessionOutput->append("date:"+QDateTime::currentDateTime().toString("yyyy-MM-ss hh:mm")+" \t 文件信息: \n");
        QFile file(curr_dir);
        file.open(QFile::ReadOnly);
        QString content = file.readAll();
        ui->sessionOutput->append(content);
        file.close();
    }
}

void ManageTcpCLient::on_btn_search()
{
    QString txt = ui->root_path_lineEdit->text();
    DEBUG_UI("search txt:%s",txt.toStdString().c_str());
    //如果是路径 则更新client 文件列表的显示
    QFileInfo fileinfo(txt);
    if(fileinfo.isDir())
    {
        //如果是文件夹进行 搜索
        if(fileinfo.exists())
        {
            ui->curr_dir_lab->setText(txt);
            initClientFileList();
        }
    }
    else if(fileinfo.isFile())
    {
        //如果是文件 搜索结果会在out 显示
        QString root_path = ui->curr_dir_lab->text();
        root_path = StringUtil::getInstance().getFirstName(root_path);
        emit signal_find_str(root_path,txt);
    }
    else
    {
        //如果是待搜索的字符串（模糊搜索）
        QString root_path = ui->curr_dir_lab->text();
        root_path = StringUtil::getInstance().getFirstName(root_path);
        emit signal_find_str(root_path,txt);
    }

}

void ManageTcpCLient::initClientFileList()
{
    QStringList ret = m_file_oper->getFileAndDirPathNameOfSplDir(ui->curr_dir_lab->text());
    setClientListview(StringUtil::getInstance().getLastNameOfFileList(ret));
}

