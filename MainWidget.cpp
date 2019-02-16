#include "MainWidget.h"
#include <QWebEnginePage>
#include <QWebChannel>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("利用QWebChannel实现qt端和网页端通信示例");

    m_txtContent = new QTextEdit;
    m_lineMsg = new QLineEdit;
    m_btnSend = new QPushButton;
    m_btnSend->setText("发送");
    m_btnSend->setMinimumWidth(40);
    m_btnSend->setMaximumWidth(40);

    QHBoxLayout *layoutMsg = new QHBoxLayout();
    layoutMsg->addWidget(m_lineMsg);
    layoutMsg->addWidget(m_btnSend);
    QVBoxLayout *layoutLeft = new QVBoxLayout();
    layoutLeft->addWidget(m_txtContent);
    layoutLeft->addLayout(layoutMsg);
    layoutLeft->setMargin(0);
    QWidget *widgetLeft = new QWidget();
    widgetLeft->setLayout(layoutLeft);

    m_webView = new QWebEngineView();
    QWebEnginePage *page = new QWebEnginePage(this); //创建一个网页视图对象
    m_webView->setPage(page);

    QWebChannel *channel = new QWebChannel(this); //为网页视图页面创建通道channel
    channel->registerObject(QStringLiteral("document"), &m_document);//注册通道对象供JS调用,"document"为注册名，JS调用的对象名必须和它相同
    page->setWebChannel(channel); //设置通道

    //下面任选一种都可以
    page->setUrl(QUrl("qrc:/index.html"));
//    page->load(QUrl("qrc:/index.html"));
//    m_webView->load(QUrl("qrc:/index.html"));

    QSplitter *splitter = new QSplitter;
    splitter->setOrientation(Qt::Horizontal);
    splitter->addWidget(widgetLeft);
    splitter->addWidget(m_webView);

    QHBoxLayout *layoutMain = new QHBoxLayout(this);
    layoutMain->setMargin(0);
    layoutMain->addWidget(splitter);

    m_txtContent->setPlainText("QWebChannel准备好了...\n");

    connect(m_btnSend, &QPushButton::clicked,this,&MainWidget::sendMsg);
    connect(&m_document, &Document::textReceived, this,
            [this](const QString& msg){appendMessage(QString("收到信息：%1").arg(msg));});
}

MainWidget::~MainWidget()
{

}

void MainWidget::appendMessage(const QString &msg)
{
    m_txtContent->append(msg);
}

void MainWidget::sendMsg()
{
    QString sMsg = m_lineMsg->text();
    sMsg = sMsg.trimmed();
    if(!sMsg.isEmpty())
    {
        m_document.sendText(m_lineMsg->text());
        appendMessage("发送嘻嘻:" + sMsg);
    }
}
