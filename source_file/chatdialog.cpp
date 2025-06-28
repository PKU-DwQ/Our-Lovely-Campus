#include "head_file/chatdialog.h"
#include <QPainter>
#include <QFont>

ChatDialog::ChatDialog(const QString& imagePath, const QString& infoText, QWidget *parent) : QDialog(parent), m_imagePath(imagePath), m_infoText(infoText) {
    setWindowTitle("北大地图助手");
    resize(500, 600);

    // 设置对话框样式
    setStyleSheet(
        "QDialog {"
        "   background-color: white;"
        "   padding: 10px;"
        "   color: black;"
        "}"

        "QTextEdit {"
        "   background-color: white;"
        "   border: 1px solid #d1d1d1;"
        "   border-radius: 8px;"
        "   padding: 10px;"
        "   font-size: 14px;"
        "   color: black;"
        "}"

        "QLineEdit {"
        "   background-color: #e6f7ff;"
        "   border: 2px solid #91d5ff;"
        "   border-radius: 6px;"
        "   padding: 8px;"
        "   font-size: 14px;"
        "   color: black;"
        "}"
        "QLineEdit:focus {"
        "   border: 2px solid #1890ff;"
        "}"

        "QPushButton {"
        "   background-color: #4e6ef2;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 6px;"
        "   padding: 8px 16px;"
        "   font-weight: bold;"
        "   min-height: 36px;"
        "}"
        "QPushButton:hover { background-color: #3d5afe; }"
        "QPushButton:pressed { background-color: #2d4cf0; }"
        );

    // 创建主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10, 150, 10, 10);

    // 创建聊天历史区域
    chatHistory = new QTextEdit(this);
    chatHistory->setReadOnly(true);
    mainLayout->addWidget(chatHistory, 1);

    // 创建输入区域
    QHBoxLayout *inputLayout = new QHBoxLayout();
    userInput = new QLineEdit(this);
    sendButton = new QPushButton("发送", this);
    sendButton->setFixedWidth(80);

    inputLayout->addWidget(userInput, 1);
    inputLayout->addWidget(sendButton);
    mainLayout->addLayout(inputLayout);

    // 初始化网络管理器
    networkManager = new QNetworkAccessManager(this);

    // 连接信号槽
    connect(sendButton, &QPushButton::clicked, this, &ChatDialog::sendMessage);
    connect(userInput, &QLineEdit::returnPressed, this, &ChatDialog::sendMessage);

    // 添加欢迎消息
    addMessage("北大小乌龟", "您好！我是pku一只可爱的小乌龟,在未名湖里游啊游");
}

void ChatDialog::paintEvent(QPaintEvent *event) {
    QDialog::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 1. 绘制顶部背景
    painter.fillRect(QRect(10, 10, width() - 20, 130), Qt::white);

    // 2. 绘制图片 (20, 20) 位置，120x120大小
    QPixmap pixmap(m_imagePath);
    if (!pixmap.isNull()) {
        pixmap = pixmap.scaled(120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter.drawPixmap(20, 20, pixmap);
    } else {
        // 图片加载失败时绘制占位符
        painter.setPen(Qt::black);
        painter.drawRect(20, 20, 120, 120);
        painter.drawText(QRect(20, 20, 120, 120), Qt::AlignCenter, "图片");
    }

    // 3. 绘制文字区域 (150, 20) 位置
    QRect textRect(150, 20, width() - 170, 120);

    // 绘制文字区域背景
    painter.fillRect(textRect, Qt::white);

    // 绘制边框
    painter.setPen(QPen(QColor(145, 213, 255), 1));
    painter.drawRoundedRect(textRect, 8, 8);

    // 绘制文字
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 10));
    QString text = "这是pku一只可爱的小乌龟,在未名湖里游啊游。";
    painter.drawText(textRect.adjusted(10, 10, -10, -10),
                     Qt::AlignLeft | Qt::AlignTop | Qt::TextWordWrap,
                     m_infoText);
}

void ChatDialog::addMessage(const QString &sender, const QString &message) {
    // 使用黑色文字格式
    QString formatted = QString("<div style='margin-bottom: 10px; color: black;'><b>%1:</b> %2</div>")
                            .arg(sender.toHtmlEscaped(), message.toHtmlEscaped());

    chatHistory->append(formatted);
    chatHistory->verticalScrollBar()->setValue(chatHistory->verticalScrollBar()->maximum());
}

void ChatDialog::sendMessage() {
    QString text = userInput->text().trimmed();
    if (text.isEmpty()) return;

    // 添加用户消息
    addMessage("您", text);
    userInput->clear();

    // 准备API请求
    QNetworkRequest request(QUrl("https://api.deepseek.com/v1/chat/completions"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    // 读取 config.json
    QFile configFile(":/config.json");
    if (configFile.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(configFile.readAll());
        QJsonObject obj = doc.object();
        QString apiKey = obj["api_key"].toString();
        qDebug() << "apiKey:" << apiKey;
        request.setRawHeader("Authorization", apiKey.toUtf8());
    }
    else {
        qDebug() << "failed to open jsonfile";
    }
    // 构建请求数据
    QJsonObject messageObject;
    messageObject["role"] = "user";
    messageObject["content"] = text;

    QJsonObject requestData;
    requestData["model"] = "deepseek-chat";
    requestData["messages"] = QJsonArray() << messageObject;
    requestData["temperature"] = 0.7;
    requestData["max_tokens"] = 2000;

    QJsonDocument doc(requestData);

    // 发送请求
    QNetworkReply *reply = networkManager->post(request, doc.toJson());

    // 显示加载状态
    addMessage("北大小助手", "思考中...");

    // 连接响应处理
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        handleApiResponse(reply);
        reply->deleteLater();
    });
}

void ChatDialog::handleApiResponse(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        addMessage("DeepSeek AI", "请求失败: " + reply->errorString());
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObject = jsonResponse.object();

    if (!jsonObject.contains("choices")) {
        addMessage("DeepSeek AI", "无效的API响应");
        return;
    }

    QJsonArray choices = jsonObject["choices"].toArray();
    if (choices.isEmpty()) {
        addMessage("DeepSeek AI", "未收到响应内容");
        return;
    }

    QJsonObject firstChoice = choices[0].toObject();
    QJsonObject message = firstChoice["message"].toObject();
    QString content = message["content"].toString().trimmed();

    // 移除最后的"思考中..."消息
    chatHistory->moveCursor(QTextCursor::End);
    chatHistory->moveCursor(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);
    chatHistory->textCursor().removeSelectedText();
    chatHistory->textCursor().deletePreviousChar();

    // 添加AI回复
    addMessage("北大小助手", content);
}
