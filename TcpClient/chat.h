#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class Chat;
}

class Chat : public QWidget
{
    Q_OBJECT

public:
    explicit Chat(QTcpSocket *s, QWidget *parent = 0);//parent有默认参数，要放后面
    ~Chat();

private slots:
    void on_clearButton_clicked();

    void on_sendButton_clicked();

private:
    Ui::Chat *ui;
    QTcpSocket *socket;
};

#endif // CHAT_H
