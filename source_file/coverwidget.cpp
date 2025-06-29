#include "header_file/coverwidget.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QFont>
#include <QFile>

// 构造函数实现
CoverWidget::CoverWidget(QWidget *parent) : QWidget(parent) {
    // 1. 加载封面图片
    if (!coverImage.load(":/image_database/cover.jpeg")) {  // 使用Qt资源系统（推荐）
        coverImage = QPixmap(1200, 1000);
        coverImage.fill(Qt::gray);
        QPainter painter(&coverImage);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 36, QFont::Bold));
        painter.drawText(coverImage.rect(), Qt::AlignCenter, "北大校园");
    }

    // 2. 初始化按钮
    startButton = new QPushButton("Enter PKU", this);
    startButton->setFixedSize(200, 60);
    startButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgba(200, 16, 46, 100);"
        "   color: white;"
        "   border-radius: 10px;"
        "   font-size: 18px;"
        "}"
        "QPushButton:hover { background-color: rgba(200, 16, 46, 235); }"
        "QPushButton:pressed { background-color: rgba(160, 10, 35, 210); }"
        );

    // 3. 设置布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 20);  // 底部边距增加到50像素（原为20）
    layout->addStretch(4);                    // 顶部弹性空间权重增加（原为1）
    layout->addWidget(startButton, 0, Qt::AlignCenter);
    layout->addStretch(1);                    // 底部弹性空间保持

    // 4. 连接信号槽
    connect(startButton, &QPushButton::clicked, this, &CoverWidget::startNavigation);

<<<<<<< HEAD
=======
    // 5. 初始化音频播放器
    m_player = new QMediaPlayer(this);
    m_audioOutput = new QAudioOutput(this);
    m_player->setAudioOutput(m_audioOutput);

    // 设置音量
    m_audioOutput->setVolume(1.0); // 设置最大音量
    m_audioOutput->setMuted(false);
    // 添加错误处理
    connect(m_player, &QMediaPlayer::errorOccurred, this, [](QMediaPlayer::Error error, const QString &errorString) {
        qDebug() << "Media error:" << error << " - " << errorString;
    });

    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, [](QMediaPlayer::MediaStatus status) {
        qDebug() << "Media status:" << status;
    });
    // 加载音乐文件
    QString musicPath = ":/music/hh.mp3";  // 确保音乐文件在资源中

    // 尝试加载音乐文件
    if (QFile::exists(musicPath)) {
        m_player->setSource(QUrl(musicPath));
        // 设置循环播放
        m_player->setLoops(QMediaPlayer::Infinite);
        // 开始播放
        m_player->play();
        qDebug() << "start music";
    } else {
        qDebug() << "music not found:" << musicPath;
    }
>>>>>>> d2e8884a263c5d8d42aa9272aa84950daadbd77b
}

// 绘图事件实现
void CoverWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(rect(), coverImage);  // 自适应窗口大小绘制图片
}
