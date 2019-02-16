#ifndef DOCUMENT_H
#define DOCUMENT_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QObject>
#include <QString>

// qt端和HTML页面之间交互要用到的类
class Document : public QObject
{
    Q_OBJECT

public:
    explicit Document(QObject *parent = nullptr){}

    void sendText(const QString &text)
    {
        emit textSent(text);//发送给html页面
    }

public slots:
    //在HTML端的JavaScript中调用，在qt端显示
    void receiveText(const QString &text)
    {
        emit textReceived(text);//发送给主界面
    }

signals:
    //发送消息给HTML页面（此信号在html端的JavaScript中进行连接）
    void textSent(const QString &text);

    //发送消息给主界面
    void textReceived(const QString &text);
};

#endif // DOCUMENT_H
