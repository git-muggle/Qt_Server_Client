#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    server = new QTcpServer;

    server->listen(QHostAddress::AnyIPv4,PORt);//监听的端口或者网卡
    //客户端发起连接，server发出信号
    connect(server,&QTcpServer::newConnection,this,&Widget::newClientHandler);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::newClientHandler()
{
    //建立TCP连接
    QTcpSocket *socket = server->nextPendingConnection();
    //socket->peerAddress();//获取客户端地址
    //socket->peerPort();//获取客户端的端口号

    ui->ipLineEdit->setText(socket->peerAddress().toString());//显示Ip地址
    ui->portLIneEdit->setText(QString::number(socket->peerPort()));//无符号短整型转换为string

    //服务器收到客户端发送的信息，socket发出readyread信号
    //connect(socket,&QTcpSocket::readyRead,this,&Widget::clientInfoSlot);

    //启动线程
    myThread *t = new myThread(socket);//创建线程对象
    t->start();                        //开始线程

    connect(t,&myThread::sendToWidget,this,&Widget::threadSlot);
}

//void Widget::clientInfoSlot()
//{
    //获取信号的发出者
//    QTcpSocket *s = (QTcpSocket *)sender();
//    ui->mainLineEdit->setText(QString(s->readAll()));
//}

void Widget::threadSlot(QByteArray b)
{
    ui->mainLineEdit->setText(QString(b));
}





