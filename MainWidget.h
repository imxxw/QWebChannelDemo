#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "document.h"
#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QWebEngineView>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

public:
    void appendMessage(const QString &msg);

public slots:
    void sendMsg();

private:
    Document m_document;
    QTextEdit *m_txtContent;
    QLineEdit *m_lineMsg;
    QPushButton *m_btnSend;
    QWebEngineView *m_webView;
};

#endif // MAINDIALOG_H
