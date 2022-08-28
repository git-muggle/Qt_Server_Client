#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class myThread : public QThread
{
    Q_OBJECT
public:
    explicit myThread(QTcpSocket *s);
    void run();//线程函数入口

signals:
    void sendToWidget(QByteArray b);

public slots:
    void clientINfoSlot();

private:
    QTcpSocket *socket;
};

#endif // MYTHREAD_H
