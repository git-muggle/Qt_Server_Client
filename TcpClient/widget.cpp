#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    socket = new QTcpSocket;//创建TCP对象
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_cancelButton_clicked()
{
    this->close();
}

void Widget::on_connectButton_clicked()
{
    //获取ip地址和端口号
    QString IP = ui->ipLineEdit->text();
    QString port = ui->portLineEdit->text();

    //连接服务器
    socket->connectToHost(QHostAddress(IP) , port.toShort());

    //连接服务器成功
    connect(socket , &QTcpSocket::connected , [this]()
    {
       QMessageBox::information(this,"连接提示","连接服务器成功");

       this->hide();//当前界面关闭，注意有些东西如局部变量要随之清除掉
       //将socket传到了s里面
       Chat *c = new Chat(socket);//不能在栈上创建对象，要在堆上创建对象，防止该进程结束后窗口随之关闭
       c->show();
    });

    //连接断开，socket会发出信号
    connect(socket , &QTcpSocket::disconnected , [this]()
    {
        QMessageBox::warning(this ,"连接提示","连接异常 网络断开");
    });
}
