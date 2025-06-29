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

}

// 绘图事件实现
void CoverWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(rect(), coverImage);  // 自适应窗口大小绘制图片
}
