#include "head_file/chatdialog.h"
#include <QPainter>
#include <QFont>
#include <QResizeEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>

ChatDialog::ChatDialog(const QString& imagePath,int num, const QString& infoText, QWidget *parent) :
    QDialog(parent), m_imagePath(imagePath), m_infoText(infoText),m_imagenum(num) {
    setWindowTitle("北大地图助手");
    resize(600, 700); // 增大窗口尺寸以适应新布局

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
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(15, 15, 15, 15);

    // === 顶部区域布局 ===
    QHBoxLayout *topLayout = new QHBoxLayout();

    // 图片区域
    QVBoxLayout *imageLayout = new QVBoxLayout();
    imageLayout->setAlignment(Qt::AlignCenter);

    // 图片导航按钮布局
    QHBoxLayout *navLayout = new QHBoxLayout();
    navLayout->setAlignment(Qt::AlignCenter);

    // 创建左右箭头按钮
    m_prevButton = new QPushButton("◀", this);
    m_nextButton = new QPushButton("▶", this);
    m_pageLabel = new QLabel("1/"+QString("%1").arg(m_imagenum+1), this);

    // 设置按钮样式
    QString buttonStyle =
        "QPushButton {"
        "   background-color: rgba(255, 255, 255, 150);"
        "   color: black;"
        "   border: none;"
        "   border-radius: 15px;"
        "   min-width: 30px;"
        "   min-height: 30px;"
        "   font-size: 16px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(200, 230, 255, 200);"
        "}";

    m_prevButton->setStyleSheet(buttonStyle);
    m_nextButton->setStyleSheet(buttonStyle);

    // 设置页码标签样式
    m_pageLabel->setStyleSheet(
        "QLabel {"
        "   background-color: rgba(0, 0, 0, 120);"
        "   color: white;"
        "   border-radius: 8px;"
        "   padding: 2px 8px;"
        "   font-size: 12px;"
        "}");
    m_pageLabel->setAlignment(Qt::AlignCenter);
    m_pageLabel->setFixedSize(50, 20);

    // 将导航控件添加到布局 (左箭头 - 图片 - 右箭头)
    navLayout->addWidget(m_prevButton);

    // 创建图片标签 (图片将在paintEvent中绘制)
    m_imageContainer = new QWidget(this);
    m_imageContainer->setFixedSize(180, 180); // 增大图片区域

    navLayout->addWidget(m_imageContainer);
    navLayout->addWidget(m_nextButton);

    // 将导航布局和页码标签添加到图片布局
    imageLayout->addLayout(navLayout);
    imageLayout->addWidget(m_pageLabel, 0, Qt::AlignCenter);

    // 信息文本区域
    m_infoLabel = new QLabel(this);
    m_infoLabel->setText(m_infoText);
    m_infoLabel->setWordWrap(true);
    m_infoLabel->setStyleSheet(
        "QLabel {"
        "   background-color: white;"
        "   border: 1px solid #91d5ff;"
        "   border-radius: 8px;"
        "   padding: 12px;"
        "   font-size: 14px;"
        "   color: black;"
        "}");
    m_infoLabel->setFixedWidth(350); // 固定宽度以保持布局整齐

    // 将图片区域和信息区域添加到顶部布局
    topLayout->addLayout(imageLayout);
    topLayout->addWidget(m_infoLabel);

    // === 聊天区域布局 ===
    chatHistory = new QTextEdit(this);
    chatHistory->setReadOnly(true);

    // 输入区域
    QHBoxLayout *inputLayout = new QHBoxLayout();
    userInput = new QLineEdit(this);
    sendButton = new QPushButton("发送", this);
    sendButton->setFixedWidth(100);

    inputLayout->addWidget(userInput, 1);
    inputLayout->addWidget(sendButton);

    // 将各区域添加到主布局
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(chatHistory, 1);
    mainLayout->addLayout(inputLayout);

    // 初始化网络管理器
    networkManager = new QNetworkAccessManager(this);

    // 连接信号槽
    connect(sendButton, &QPushButton::clicked, this, &ChatDialog::sendMessage);
    connect(userInput, &QLineEdit::returnPressed, this, &ChatDialog::sendMessage);
    connect(m_prevButton, &QPushButton::clicked, this, &ChatDialog::prevImage);
    connect(m_nextButton, &QPushButton::clicked, this, &ChatDialog::nextImage);

    // 添加欢迎消息
    addMessage("北大小乌龟", "您好！我是pku一只可爱的小乌龟,在未名湖里游啊游");
}

void ChatDialog::paintEvent(QPaintEvent *event) {
    QDialog::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制图片区域
    QRect imageRect = m_imageContainer->geometry();
    imageRect.adjust(0, 0, -1, -1); // 调整边界

    // 绘制背景
    painter.fillRect(imageRect, Qt::white);

    // 绘制边框
    painter.setPen(QPen(QColor(145, 213, 255), 1));
    painter.drawRect(imageRect);
    QString imagePath = QString("%1/%2.png").arg(m_imagePath).arg(m_currentImageIndex);
    QPixmap pixmap(imagePath);
    if (!pixmap.isNull()) {
        pixmap = pixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        int x = imageRect.x() + (imageRect.width() - pixmap.width()) / 2;
        int y = imageRect.y() + (imageRect.height() - pixmap.height()) / 2;
        painter.drawPixmap(x, y, pixmap);
    } else {
        // 图片加载失败时绘制占位符
        painter.setPen(Qt::white);
        painter.drawRect(imageRect.x() + 15, imageRect.y() + 15, 150, 150);
        painter.drawText(imageRect.adjusted(15, 15, -15, -15), Qt::AlignCenter, "图片加载失败");
        qDebug() << "Mouse click pos:" ;
    }
}

void ChatDialog::updateImage() {
    // 更新页码标签
    m_pageLabel->setText(QString("%1/%2").arg(m_currentImageIndex + 1).arg(m_imagenum + 1));
    update(); // 触发重绘
}

void ChatDialog::prevImage() {
    m_currentImageIndex--;
    if (m_currentImageIndex < 0) m_currentImageIndex = m_imagenum; // 循环切换
    updateImage();
}

void ChatDialog::nextImage() {
    m_currentImageIndex++;
    if (m_currentImageIndex > m_imagenum) m_currentImageIndex = 0; // 循环切换
    updateImage();
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

