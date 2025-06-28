#include "head_file/chatdialog.h"
#include "head_file/imageviewer.h"
#include <QPainter>
#include <QFont>
#include <QResizeEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QTimer>


ChatDialog* makeChatDialog(QString name, ImageViewer* p){
    return new ChatDialog(":/icon/" + name,
                   2,
                   "这是pku一只可爱的小乌龟,在未名湖里游啊游。",
                   "您好！我是pku一只可爱的小乌龟,在未名湖里游啊游",
                   "你是一只生活在未名湖里的乌龟，你的名字叫小北。你热爱北大，喜欢帮助游客和同学。请用可爱、活泼的语气回答问题。",
                   "未名湖小龟",
                   p);
}
ChatDialog::ChatDialog(const QString& imagePath,int num, const QString& infoText,
                       const QString&welcome, const QString& identity, const QString&name, QWidget *parent) :
    QDialog(parent), m_imagePath(imagePath), m_infoText(infoText),m_imagenum(num),welcomewords(welcome),Defaultidentity(identity),name(name) {
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

    // 初始化当前图片索引
    m_currentImageIndex = 0;

    // 创建图片容器（使用自定义控件）
    m_imageContainer = new ImageWidget(this);
    m_imageContainer->setFixedSize(180, 180);

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
    addMessage(name, welcomewords);
    loadCurrentImage();

    // 设置AI角色为乌龟（后台操作，不显示）
    QTimer::singleShot(100, this, [this]() {
        // 构建系统消息（不显示在界面上）
        QJsonObject systemMessage;
        systemMessage["role"] = "system";
        systemMessage["content"] = Defaultidentity;

        // 添加到消息历史但不显示
        m_chatHistory.append(systemMessage);
    });
}

void ChatDialog::loadCurrentImage() {
    // 构建图片目录路径
    QDir imageDir(m_imagePath + "/photo");

    // 获取所有支持的图片文件
    QStringList imageFiles = imageDir.entryList(
        QStringList() << "*.jpg" << "*.jpeg" << "*.png",
        QDir::Files, QDir::Name
        );

    // 确保索引在有效范围内
    if (m_currentImageIndex < 0) m_currentImageIndex = imageFiles.size() - 1;
    if (m_currentImageIndex >= imageFiles.size()) m_currentImageIndex = 0;

    if (!imageFiles.isEmpty() && m_currentImageIndex < imageFiles.size()) {
        // 构建完整图片路径
        QString imagePath = imageDir.filePath(imageFiles[m_currentImageIndex]);
        QPixmap pixmap(imagePath);

        // 设置到图片控件
        if (!pixmap.isNull()) {
            m_imageContainer->setPixmap(pixmap);
        } else {
            // 清空图片显示
            m_imageContainer->setPixmap(QPixmap());
        }
    }

    // 更新页码显示
    updateImage();
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

    // 添加用户消息到聊天记录（显示）
    addMessage("您", text);

    // 创建用户消息对象（添加到API请求）
    QJsonObject userMessage;
    userMessage["role"] = "user";
    userMessage["content"] = text;
    m_chatHistory.append(userMessage);

    // 显示"思考中..."提示
    addMessage(name, "思考中...");

    // 准备API请求
    QNetworkRequest request(QUrl("https://api.deepseek.com/v1/chat/completions"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 读取API密钥
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

    // 构建请求数据（包含系统消息和完整对话历史）
    QJsonObject requestData;
    requestData["model"] = "deepseek-chat";
    requestData["messages"] = m_chatHistory; // 使用完整对话历史
    requestData["temperature"] = 0.7;
    requestData["max_tokens"] = 2000;

    QJsonDocument doc(requestData);

    // 发送请求
    QNetworkReply *reply = networkManager->post(request, doc.toJson());
    userInput->clear();

    // 连接响应处理
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        handleApiResponse(reply);
        reply->deleteLater();
    });
}

void ChatDialog::handleApiResponse(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        addMessage(name, "请求失败: " + reply->errorString());
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObject = jsonResponse.object();

    if (!jsonObject.contains("choices")) {
        addMessage(name, "无效的API响应");
        return;
    }

    QJsonArray choices = jsonObject["choices"].toArray();
    if (choices.isEmpty()) {
        addMessage(name, "未收到响应内容");
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
    addMessage(name, content);
}

