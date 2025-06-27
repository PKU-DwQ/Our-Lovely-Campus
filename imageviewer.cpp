#include "imageviewer.h"
#include "movingicon.h"
#include <QLabel>
#include <QFont>

void ImageViewer::focusInEvent(QFocusEvent* event) {
    Q_UNUSED(event);
    setFocus(); // 确保获得焦点
}

void ImageViewer::setupMovingIcon(const QString& iconFilePath, const int normalNum, const int clickNum, const QList<QPoint>& path) {
    m_movingIcon = new MovingIcon(iconFilePath, normalNum, clickNum, 50, 50); // 切换间隔1秒，移动间隔50毫秒
    m_movingIcon->setPath(path);

    // 初始化定时器
    m_switchTimer = new QTimer(this);
    m_moveTimer = new QTimer(this);

    // 连接信号和槽
    connect(m_switchTimer, &QTimer::timeout, this, [this]() {
        this->update();  // 明确调用无参版本
    });
    connect(m_switchTimer, &QTimer::timeout, m_movingIcon, &MovingIcon::switchIcon);
    connect(m_moveTimer, &QTimer::timeout, m_movingIcon, &MovingIcon::moveAlongPath);

    // 启动定时器
    m_switchTimer->start(50);
    m_moveTimer->start(50);
}

ImageViewer::ImageViewer(const QString& imagePath, QWidget* parent)
    : QWidget(parent), m_offset(0, 0), m_mapIcon() // 初始地点:未名湖畔m_offset(780, 1080)
{
    if (!m_background.load(imagePath)) {
        qDebug() << "无法加载图片:" << imagePath;
        createErrorImage();
    }
    setMinimumSize(600, 300);
    setFocusPolicy(Qt::StrongFocus); // 允许接收键盘事件
    setMouseTracking(true); // 默认不跟踪鼠标

    // 设置移动图标
    QList<QPoint> path;
    for (int i=800;i<900;i=i+2){
        path << QPoint(i, 800);}
    for (int j=800;j<900;j+=2){
        path<<QPoint(900,j);
    }
    for (int i=900;i>800;i-=2){
        path<<QPoint(i,900);
    }
    for (int j=900;j>800;j-=2){
        path<<QPoint(800,j);
    }
    setupMovingIcon("test", 20, 0, path);
}


void ImageViewer::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    // 绘制背景
    painter.fillRect(rect(), QColor(50,50,60));
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
    // 绘制地图图标
    m_mapIcon.draw(painter, m_offset);
    // 绘制新的湖图标
    m_lakeIcon.draw(painter, m_offset);
    // 绘制信息栏
    // 绘制移动图标
    if (m_movingIcon) {
        m_movingIcon->draw(painter, m_offset);
    }
    painter.fillRect(0, 0, width(), 30, QColor(0, 0, 0, 150));
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 10));
    painter.drawText(15, 22, QString("图片视图 - 偏移(%1, %2)").arg(m_offset.x()).arg(m_offset.y()));
}

void ImageViewer::moveView(int dx, int dy)
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
    m_offset.setX(newX);
    m_offset.setY(newY);
    update(); // 触发重绘
}

QPoint ImageViewer::getOffset() const {
    return m_offset;
}

void ImageViewer::mousePressEvent(QMouseEvent* event) {
    if (!m_mapIcon.isVisible() && !m_lakeIcon.isVisible()) {
        QWidget::mousePressEvent(event); // 如果图标不可见，传递事件给父类
        return;
    }

    // 检查是否点击在图标上
    if (m_mapIcon.containsPoint(event->pos(), m_offset)) {
        QWidget* newWindow = new QWidget();
        newWindow->setWindowTitle("新窗口");
        newWindow->resize(400, 300);

        // 在新窗口中绘制内容
        QLabel* label = new QLabel("这是新窗口的内容", newWindow);
        label->setAlignment(Qt::AlignCenter);
        label->setFont(QFont("Arial", 16));

        newWindow->show();

        m_mapIcon.onClicked();
        update();
        event->accept(); // 消耗事件，表示已处理
    }
    // 检查是否点击在湖图标上
    else if (m_lakeIcon.containsPoint(event->pos(), m_offset)) {
        QWidget* newWindow = new QWidget();
        newWindow->setWindowTitle("湖详情");
        newWindow->resize(400, 300);

        // 在新窗口中绘制内容
        QLabel* label = new QLabel("这是湖的详情窗口", newWindow);
        label->setAlignment(Qt::AlignCenter);
        label->setFont(QFont("Arial", 16));

        newWindow->show();

        m_lakeIcon.onClicked();
        update();
        event->accept(); // 消耗事件，表示已处理
    } // 检查是否点击在移动图标上
    else if (m_movingIcon->containsPoint(event->pos(), m_offset)) {
        QWidget* newWindow = new QWidget();
        newWindow->setWindowTitle("移动图标详情");
        newWindow->resize(400, 300);

        QLabel* label = new QLabel("这是移动图标的详情窗口", newWindow);
        label->setAlignment(Qt::AlignCenter);
        label->setFont(QFont("Arial", 16));

        newWindow->show();

        m_movingIcon->onClicked();
        update();
        event->accept();
    } else {
        QWidget::mousePressEvent(event);
    }
}

void ImageViewer::mouseMoveEvent(QMouseEvent* event) {/*
    QWidget::mouseMoveEvent(event);
    bool isHoveredMap = m_mapIcon.containsPoint(event->pos(), m_offset);
    bool isHoveredLake = m_lakeIcon.containsPoint(event->pos(), m_offset);

    if (isHoveredMap != m_mapIcon.isHovered()) {
        m_mapIcon.setIsHovered(isHoveredMap);
        update();
    }
    if (isHoveredLake != m_lakeIcon.isHovered()) {
        m_lakeIcon.setIsHovered(isHoveredLake);
        update();
    }*/
}

void ImageViewer::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Space) {
        // 计算图片中心位置
        int centerX = m_offset.x() + width() / 2;
        int centerY = m_offset.y() + height() / 2;

        // 设置图标位置
        m_mapIcon.setPosition(centerX, centerY);

        // 切换图标可见性
        m_mapIcon.toggleVisibility();

        update(); // 重绘
    }
    else if (event->key() == Qt::Key_Up) {
        this->moveView(0, -10);
    }
    else if (event->key() == Qt::Key_Down) {
        this->moveView(0, 10);
    }
    else if (event->key() == Qt::Key_Left) {
        this->moveView(-10, 0);
    }
    else if (event->key() == Qt::Key_Right) {
        this->moveView(10, 0);
    }
}

void ImageViewer::setLakeIconPosition(int x, int y) {
    m_lakeIcon.setPosition(x, y);
    m_lakeIcon.setVisible(true);
}

void ImageViewer::loadLakeIconImages(const QString& normalPath, const QString& hoverPath) {
    // 尝试加载普通状态图片
    if (!m_lakeIcon.m_icon[1].load(normalPath)) {
        qDebug() << "无法加载湖图标普通状态图片:" << normalPath;
        // 创建简单的默认图标
        m_lakeIcon.m_icon[1] = QPixmap(32, 32);
        m_lakeIcon.m_icon[1].fill(Qt::transparent);
        QPainter painter(&m_lakeIcon.m_icon[1]);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(QPen(Qt::blue, 2));
        painter.setBrush(QBrush(QColor(100, 200, 255, 180)));
        painter.drawEllipse(4, 4, 24, 24);
    }
    // 尝试加载悬停状态图片
    if (!m_lakeIcon.m_icon[2].load(hoverPath)) {
        qDebug() << "无法加载湖图标悬停状态图片:" << hoverPath;
        // 创建简单的默认图标
        m_lakeIcon.m_icon[2] = QPixmap(32, 32);
        m_lakeIcon.m_icon[2].fill(Qt::transparent);
        QPainter painter(&m_lakeIcon.m_icon[2]);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(QPen(Qt::red, 2));
        painter.setBrush(QBrush(QColor(255, 100, 100, 180)));
        painter.drawRect(4, 4, 24, 24);
    }
}

void ImageViewer::createErrorImage()
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


