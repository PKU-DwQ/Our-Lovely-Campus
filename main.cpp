#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QGridLayout>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QPoint>
#include <QTimer>

class ImageViewer : public QWidget {
public:
    explicit ImageViewer(const QString& imagePath, QWidget* parent = nullptr)
        : QWidget(parent), m_offset(0, 0)
    {
        if (!m_background.load(imagePath)) {
            qDebug() << "无法加载图片:" << imagePath;
            createErrorImage();
        }

        setMinimumSize(600, 600);
    }

    void paintEvent(QPaintEvent* event) override
    {
        Q_UNUSED(event);
        QPainter painter(this);

        // 绘制背景
        painter.fillRect(rect(), QColor(50, 50, 60));

        if (!m_background.isNull()) {
            // 计算实际显示区域
            int drawWidth = qMin(width(), m_background.width());
            int drawHeight = qMin(height(), m_background.height());

            painter.drawPixmap(0, 0, drawWidth, drawHeight, m_background,
                               m_offset.x(), m_offset.y(), drawWidth, drawHeight);
        }
        else {
            painter.setPen(Qt::red);
            painter.setFont(QFont("Arial", 16));
            painter.drawText(rect(), Qt::AlignCenter, "图片加载失败");
        }

        // 绘制信息栏
        painter.fillRect(0, 0, width(), 30, QColor(0, 0, 0, 150));
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 10));
        painter.drawText(15, 22, QString("图片视图 - 偏移(%1, %2)").arg(m_offset.x()).arg(m_offset.y()));
    }

    // 公开移动方法供其它组件调用
    void moveView(int dx, int dy)
    {
        int newX = m_offset.x() + dx;
        int newY = m_offset.y() + dy;

        // 边界检查 - 确保不会移出图片范围
        newX = qMax(0, newX);
        newY = qMax(0, newY);

        if (!m_background.isNull()) {
            if (width() > m_background.width()) {
                newX = (m_background.width() - width()) / 2; // 如果图片宽度小于窗口，居中显示
            } else {
                newX = qMin(newX, m_background.width() - width());
            }

            if (height() > m_background.height()) {
                newY = (m_background.height() - height()) / 2; // 如果图片高度小于窗口，居中显示
            } else {
                newY = qMin(newY, m_background.height() - height());
            }
        }

        // 仅在有实际移动时更新
        if (m_offset.x() != newX || m_offset.y() != newY) {
            m_offset.setX(newX);
            m_offset.setY(newY);
            update(); // 触发重绘
        }
    }

    // 添加 getOffset 方法获取当前偏移量
    QPoint getOffset() const {
        return m_offset;
    }

private:
    void createErrorImage()
    {
        m_background = QPixmap(400, 300);
        m_background.fill(QColor(80, 20, 30));  // 深红色背景

        QPainter painter(&m_background);
        painter.setRenderHint(QPainter::Antialiasing);

        // 画一个黄色叉叉
        painter.setPen(QPen(Qt::yellow, 8));
        painter.drawLine(50, 50, 350, 250);
        painter.drawLine(350, 50, 50, 250);

        // 添加错误文本
        painter.setFont(QFont("Arial", 24, QFont::Bold));
        painter.drawText(m_background.rect(), Qt::AlignCenter, "图片加载失败\n请检查文件路径");
    }

    QPixmap m_background;
    QPoint m_offset;
};

class NavigationWidget : public QWidget {
public:
    NavigationWidget(const QString& imagePath, QWidget* parent = nullptr)
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

        setWindowTitle("图片导航查看器");
        setStyleSheet("background-color: #35363f;");
        resize(800, 600);
    }

private:
    void createNavigationButtons()
    {
        // 四个方向按钮
        QPushButton* btnUp = new QPushButton(QString::fromUtf8("▲"), this);
        QPushButton* btnDown = new QPushButton(QString::fromUtf8("▼"), this);
        QPushButton* btnLeft = new QPushButton(QString::fromUtf8("◀"), this);
        QPushButton* btnRight = new QPushButton(QString::fromUtf8("▶"), this);

        // 设置按钮样式
        QString buttonStyle = QString(
            "QPushButton {"
            "   font-size: 28px;"
            "   min-width: 60px; min-height: 60px;"
            "   background-color: rgba(60, 90, 140, 220);"
            "   color: white;"
            "   border: none;"
            "   border-radius: 30px;"
            "}"
            "QPushButton:hover {"
            "   background-color: rgba(80, 120, 190, 235);"
            "}"
            "QPushButton:pressed {"
            "   background-color: rgba(40, 70, 120, 210);"
            "}"
            );

        btnUp->setStyleSheet(buttonStyle);
        btnDown->setStyleSheet(buttonStyle);
        btnLeft->setStyleSheet(buttonStyle);
        btnRight->setStyleSheet(buttonStyle);

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
        connect(btnUp, &QPushButton::pressed, [timerUp]() {
            timerUp->start(50);
        });
        connect(btnUp, &QPushButton::released, [timerUp]() {
            timerUp->stop();
        });

        connect(btnDown, &QPushButton::pressed, [timerDown]() {
            timerDown->start(50);
        });
        connect(btnDown, &QPushButton::released, [timerDown]() {
            timerDown->stop();
        });

        connect(btnLeft, &QPushButton::pressed, [timerLeft]() {
            timerLeft->start(50);
        });
        connect(btnLeft, &QPushButton::released, [timerLeft]() {
            timerLeft->stop();
        });

        connect(btnRight, &QPushButton::pressed, [timerRight]() {
            timerRight->start(50);
        });
        connect(btnRight, &QPushButton::released, [timerRight]() {
            timerRight->stop();
        });

        // 连接定时器到移动函数
        connect(timerUp, &QTimer::timeout, [this]() {
            m_imageViewer->moveView(0, -10);
        });
        connect(timerDown, &QTimer::timeout, [this]() {
            m_imageViewer->moveView(0, 10);
        });
        connect(timerLeft, &QTimer::timeout, [this]() {
            m_imageViewer->moveView(-10, 0);
        });
        connect(timerRight, &QTimer::timeout, [this]() {
            m_imageViewer->moveView(10, 0);
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
            "}"
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
        });

        connect(btnFullscreen, &QPushButton::clicked, [this]() {
            if (isFullScreen()) {
                showNormal();
            } else {
                showFullScreen();
            }
        });

        // 占位用，尚未实现
        connect(btnZoomIn, &QPushButton::clicked, []() {
            qDebug() << "放大功能尚未实现";
        });
        connect(btnZoomOut, &QPushButton::clicked, []() {
            qDebug() << "缩小功能尚未实现";
        });
    }

private:
    QGridLayout* m_layout;
    ImageViewer* m_imageViewer;
};

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // 尝试查找图片文件
    QString imagePath;

    // 尝试可能的图片位置
    QStringList possiblePaths = {
        "image.jpg",
        "map.jpg",
        "default.png",
        "background.jpg",
        "C:/Users/bhsf2/Desktop/Map/Map.jpg"
    };

    // 检查存在的文件
    for (const QString& path : possiblePaths) {
        if (QFile::exists(path)) {
            imagePath = path;
            qDebug() << "找到图片:" << imagePath;
            break;
        }
    }

    // 如果命令行提供了参数，则使用该图片
    if (argc > 1) {
        imagePath = argv[1];
        qDebug() << "使用命令行图片:" << imagePath;
    }

    // 创建主窗口
    NavigationWidget window(imagePath);
    window.show();

    return app.exec();
}
