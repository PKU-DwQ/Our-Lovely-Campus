#include "header_file/navigationwidget.h"
#include <QHBoxLayout>

NavigationWidget::NavigationWidget(const QString& imagePath, QWidget* parent)
    : QWidget(parent)
{
    // 设置窗口布局
    m_layout = new QGridLayout(this);
    m_layout->setContentsMargins(10, 10, 10, 10);
    m_layout->setSpacing(10);

    // 创建图片查看区域
    m_imageViewer = new ImageViewer(imagePath);
    // 图片放在第1行第1列（从0开始计数），跨越3行1列
    m_layout->addWidget(m_imageViewer, 1, 1, 3, 1);

    // 创建导航按钮
    createNavigationButtons();

    setWindowTitle("燕园地图");
    setStyleSheet("background-color: #35363f;");
    resize(1000, 500);
    m_imageViewer->setFocus();
}

void NavigationWidget::createNavigationButtons()
{
    // 四个方向按钮
    QPushButton* btnUp = new QPushButton(QString::fromUtf8("▲"), this);
    QPushButton* btnDown = new QPushButton(QString::fromUtf8("▼"), this);
    QPushButton* btnLeft = new QPushButton(QString::fromUtf8("◀"), this);
    QPushButton* btnRight = new QPushButton(QString::fromUtf8("▶"), this);

    // 设置按钮样式
    QString buttonStyle1 = QString(
        "QPushButton {"
        "   font-size: 26px;"
        "   min-width: 240px; min-height: 30px;"
        "   background-color: rgba(60, 90, 140, 220);"
        "   color: white;"
        "   border: none;"
        "   border-radius: 30px;"
        "} "
        "QPushButton:hover {"
        "   background-color: rgba(80, 120, 190, 235);"
        "} "
        "QPushButton:pressed {"
        "   background-color: rgba(40, 70, 120, 210);"
        "} "
        );
    QString buttonStyle2 = QString(
        "QPushButton {"
        "   font-size: 36px; "
        "   min-width: 30px; min-height: 260px; "
        "   background-color: rgba(60, 90, 140, 220);"
        "   color: white; "
        "   border: none;"
        "   border-radius: 30px; "
        "} "
        "QPushButton:hover {"
        "   background-color: rgba(80, 120, 190, 235);"
        "} "
        "QPushButton:pressed {"
        "   background-color: rgba(40, 70, 120, 210);"
        "} "
        );
    btnUp->setStyleSheet(buttonStyle1);
    btnDown->setStyleSheet(buttonStyle1);
    btnLeft->setStyleSheet(buttonStyle2);
    btnRight->setStyleSheet(buttonStyle2);

    /* 按钮放置位置调整 - 分居图片四周 */
    // 上按钮放在图片正上方（第0行第1列）
    m_layout->addWidget(btnUp, 0, 1, Qt::AlignHCenter | Qt::AlignBottom);

    // 下按钮放在图片正下方（第4行第1列）
    m_layout->addWidget(btnDown, 4, 1, Qt::AlignHCenter | Qt::AlignTop);

    // 左按钮放在图片左侧（第1行第0列，跨越2行）
    m_layout->addWidget(btnLeft, 1, 0, 2, 1, Qt::AlignRight | Qt::AlignVCenter);

    // 右按钮放在图片右侧（第1行第2列，跨越2行）
    m_layout->addWidget(btnRight, 1, 2, 2, 1, Qt::AlignLeft | Qt::AlignVCenter);

    // 为持续移动功能创建定时器
    QTimer* timerUp = new QTimer(this);
    QTimer* timerDown = new QTimer(this);
    QTimer* timerLeft = new QTimer(this);
    QTimer* timerRight = new QTimer(this);

    // 连接按钮按下/释放信号
    connect(btnUp, &QPushButton::pressed, timerUp, [timerUp]() {
        timerUp->start(50);
    });
    connect(btnUp, &QPushButton::released, timerUp, [timerUp, this]() {
        timerUp->stop();
        m_imageViewer->setFocus();
    });

    connect(btnDown, &QPushButton::pressed, timerDown, [timerDown]() {
        timerDown->start(50);
    });
    connect(btnDown, &QPushButton::released, timerDown, [timerDown, this]() {
        timerDown->stop();
        m_imageViewer->setFocus();
    });

    connect(btnLeft, &QPushButton::pressed, timerLeft, [timerLeft]() {
        timerLeft->start(50);
    });
    connect(btnLeft, &QPushButton::released, timerLeft, [timerLeft, this]() {
        timerLeft->stop();
        m_imageViewer->setFocus();
    });

    connect(btnRight, &QPushButton::pressed, timerRight, [timerRight]() {
        timerRight->start(50);
    });
    connect(btnRight, &QPushButton::released, timerRight, [timerRight, this]() {
        timerRight->stop();
        m_imageViewer->setFocus();
    });

    // 连接定时器到移动函数
    int d = 20;
    connect(timerUp, &QTimer::timeout, this, [this, d]() {
        m_imageViewer->moveView(0, -d);
    });
    connect(timerDown, &QTimer::timeout, this, [this, d]() {
        m_imageViewer->moveView(0, d);
    });
    connect(timerLeft, &QTimer::timeout, this, [this, d]() {
        m_imageViewer->moveView(-d, 0);
    });
    connect(timerRight, &QTimer::timeout, this, [this, d]() {
        m_imageViewer->moveView(d, 0);
    });

    // 添加重置按钮和全屏按钮
    QPushButton* btnReset = new QPushButton("重置位置", this);
    QPushButton* btnFullscreen = new QPushButton("全屏/退出", this);
    QPushButton* btnZoomIn = new QPushButton("放大", this);
    QPushButton* btnZoomOut = new QPushButton("缩小", this);

    // 设置辅助按钮样式
    QString auxButtonStyle = QString(
        "QPushButton {"
        "   padding: 8px 15px;"
        "   background-color: #4e5168;"
        "   color: white;"
        "   border-radius: 4px;"
        "   min-width: 80px;"
        "} "
        "QPushButton:hover { background-color: #5b5f7c; }"
        "QPushButton:pressed { background-color: #3c3f55; }"
        );

    btnReset->setStyleSheet(auxButtonStyle);
    btnFullscreen->setStyleSheet(auxButtonStyle);
    btnZoomIn->setStyleSheet(auxButtonStyle);
    btnZoomOut->setStyleSheet(auxButtonStyle);

    // 添加辅助按钮
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(btnReset);
    buttonLayout->addWidget(btnZoomOut);
    buttonLayout->addWidget(btnZoomIn);
    buttonLayout->addWidget(btnFullscreen);

    m_layout->addLayout(buttonLayout, 6, 1, 1, 1, Qt::AlignHCenter | Qt::AlignTop);

    // 设置布局拉伸比例，确保图片区域是主要显示区域
    m_layout->setRowStretch(0, 0);  // 上按钮行不拉伸
    m_layout->setRowStretch(1, 1);  // 图片区域顶部行可拉伸
    m_layout->setRowStretch(2, 3);  // 图片区域主要行更大幅拉伸
    m_layout->setRowStretch(3, 1);  // 图片区域底部行可拉伸
    m_layout->setRowStretch(4, 0);  // 下按钮行不拉伸

    m_layout->setColumnStretch(0, 0);  // 左边界不拉伸（左按钮所在列）
    m_layout->setColumnStretch(1, 1);  // 图片区域可拉伸（图片显示在此列）
    m_layout->setColumnStretch(2, 0);  // 右边界不拉伸（右按钮所在列）

    // 连接辅助按钮
    connect(btnReset, &QPushButton::clicked, [this]() {
        m_imageViewer->moveView(-m_imageViewer->getOffset().x(),
                                -m_imageViewer->getOffset().y());
        m_imageViewer->setFocus();
    });

    connect(btnFullscreen, &QPushButton::clicked, [this]() {
        if (isFullScreen()) {
            showNormal();
        } else {
            showFullScreen();
        }
        m_imageViewer->setFocus();
    });
}
