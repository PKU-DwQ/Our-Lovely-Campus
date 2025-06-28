#include "imageviewer.h"
#include "movingicon.h"
#include"chatdialog.h"
#include <QFont>

void ImageViewer::focusInEvent(QFocusEvent* event) {
    Q_UNUSED(event);
    setFocus(); // 确保获得焦点
}

void ImageViewer::setupMovingIcon() {
    turtle = new MovingIcon("swan", 20, 11, 100, 50, 50); // 切换间隔1秒，移动间隔50毫秒

    // 初始化定时器
    m_switchTimer = new QTimer(this);
    m_moveTimer = new QTimer(this);

    // 连接信号和槽
    connect(m_switchTimer, &QTimer::timeout, this, [this]() {
        this->update();  // 明确调用无参版本
    });
    connect(m_switchTimer, &QTimer::timeout, turtle, &MovingIcon::switchIcon);
    connect(m_moveTimer, &QTimer::timeout, turtle, &MovingIcon::moveAlongPath);

    // 启动定时器
    m_switchTimer->start(50);
    m_moveTimer->start(50);

}

ImageViewer::ImageViewer(const QString& imagePath, QWidget* parent)
    : QWidget(parent), m_offset(600, 700) // 初始地点:未名湖畔m_offset(780, 1080)
{
    m_background.load(imagePath);
    setMinimumSize(600, 300);
    setFocusPolicy(Qt::StrongFocus); // 允许接收键盘事件
    setMouseTracking(true); // 默认不跟踪鼠标 设置为跟踪
    setupMovingIcon(); //这里修改参数
}


void ImageViewer::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    // 绘制背景
    painter.fillRect(rect(), QColor(50,50,60));
    // 计算实际显示区域
    int drawWidth = qMin(width(), m_background.width());
    int drawHeight = qMin(height(), m_background.height());
    painter.drawPixmap(0, 0, drawWidth, drawHeight, m_background,
                       m_offset.x(), m_offset.y(), drawWidth, drawHeight);

    // 绘制地图图标 信息栏
    // 绘制移动图标
    if (turtle) {
        turtle->draw(painter, m_offset);
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
    // 检查是否点击在图标上
    // 检查是否点击在图标上
    if (turtle->containsPoint(event->pos(), m_offset)) {
        //qDebug() << "Mouse click pos:" << event->pos();
        ChatDialog *chatDialog = new ChatDialog(":/test/1.png",
                                                "这是pku一只可爱的小乌龟,在未名湖里游啊游。",
                                                this);
        chatDialog->setAttribute(Qt::WA_DeleteOnClose);
        chatDialog->show();
        update();
        event->accept(); // 消耗事件，表示已处理
    }
    else {
        QWidget::mousePressEvent(event);
    }
}

void ImageViewer::mouseMoveEvent(QMouseEvent* event) {
    //qDebug() << "Mouse move pos:" << event->pos();  // 假设是 QGraphicsItem
    if (turtle->containsPoint(event->pos(), m_offset)) {
        //qDebug() << "Hovering over icon";
        turtle->setNormal(false);
        update();
        event->accept(); // 消耗事件，表示已处理
    }
    else{
        turtle->setNormal(true);
        event->accept();
    }
}

void ImageViewer::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Space) {
        // 计算图片中心位置
        //int centerX = m_offset.x() + width() / 2;
        //int centerY = m_offset.y() + height() / 2;

        // 设置图标位置
        //m_mapIcon.setPosition(centerX, centerY);

        // 切换图标可见性
       // m_mapIcon.toggleVisibility();

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



