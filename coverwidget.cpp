#include "coverwidget.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QFont>

// 构造函数实现
CoverWidget::CoverWidget(QWidget *parent) : QWidget(parent) {
    // 1. 加载封面图片
    if (!coverImage.load(":/image_database/cover.png")) {  // 使用Qt资源系统（推荐）
        coverImage = QPixmap(800, 600);
        coverImage.fill(Qt::gray);
        QPainter painter(&coverImage);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 36, QFont::Bold));
        painter.drawText(coverImage.rect(), Qt::AlignCenter, "北大校园");
    }

    // 2. 初始化按钮
    startButton = new QPushButton("点击开始", this);
    startButton->setFixedSize(200, 60);
    startButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgba(60, 90, 140, 220);"
        "   color: white;"
        "   border-radius: 10px;"
        "   font-size: 18px;"
        "}"
        "QPushButton:hover { background-color: rgba(80, 120, 190, 235); }"
        "QPushButton:pressed { background-color: rgba(40, 70, 120, 210); }"
        );

    // 3. 设置布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 50);  // 底部边距增加到50像素（原为20）
    layout->addStretch(4);                    // 顶部弹性空间权重增加（原为1）
    layout->addWidget(startButton, 0, Qt::AlignCenter);
    layout->addStretch(1);                    // 底部弹性空间保持

    // 4. 连接信号槽
    connect(startButton, &QPushButton::clicked, this, &CoverWidget::startNavigation);
}

// 绘图事件实现
void CoverWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(rect(), coverImage);  // 自适应窗口大小绘制图片
}
