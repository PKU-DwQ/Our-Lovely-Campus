#include "mapicon.h"

MapIcon::MapIcon() : m_visible(false), m_isHovered(false) {
    // 尝试加载默认图标
    if (!m_icon1.load(":/icon/1.jpg")) {
        qDebug() << "无法加载图标1.jpg";
        createDefaultIcon1();
    }
    // 尝试加载新图标
    if (!m_icon2.load(":/icon/2.jpg")) {
        qDebug() << "无法加载图标2.jpg";
        createDefaultIcon2();
    }
}

void MapIcon::setPosition(int x, int y) {
    m_position = QPoint(x, y);
}

void MapIcon::toggleVisibility() {
    m_visible = !m_visible;
}

void MapIcon::setVisible(bool visible) {
    m_visible = visible;
}

bool MapIcon::isVisible() const {
    return m_visible;
}

void MapIcon::setIsHovered(bool isHovered) {
    m_isHovered = isHovered;
}

bool MapIcon::isHovered() const {
    return m_isHovered;
}

void MapIcon::draw(QPainter& painter, const QPoint& offset) {
    if (!m_visible) return;

    int iconX = m_position.x() - offset.x();
    int iconY = m_position.y() - offset.y();
    QPixmap currentIcon = !m_isHovered ? m_icon1 : m_icon2;

    // 定义目标大小（例如 64x64）
    QSize targetSize(128, 128);
    QPixmap scaledIcon = currentIcon.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 绘制图标
    painter.drawPixmap(iconX, iconY, scaledIcon);

    // 更新实际显示的边界矩形（仅用于悬停检测）
    m_actualRect = QRect(iconX, iconY, scaledIcon.width(), scaledIcon.height());
}

QRect MapIcon::boundingRect(const QPoint& offset) const {
    if (!isVisible()) return QRect();
    // 计算实际显示的图标区域
    return QRect(
        m_position.x() - offset.x(),
        m_position.y() - offset.y(),
        m_icon1.width(),
        m_icon1.height()
        );
}

bool MapIcon::containsPoint(const QPoint& point, const QPoint& offset) const {
    return m_actualRect.contains(point);
}

void MapIcon::onClicked() {
    qDebug() << "图标被点击了";
}

void MapIcon::createDefaultIcon1() {
    // 创建默认图标1
    m_icon1 = QPixmap(32, 32);
    m_icon1.fill(Qt::transparent);
    QPainter painter(&m_icon1);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::blue, 2));
    painter.setBrush(QBrush(QColor(100, 200, 255, 180)));
    painter.drawEllipse(4, 4, 24, 24);
}

void MapIcon::createDefaultIcon2() {
    // 创建默认图标2（不同样式）
    m_icon2 = QPixmap(32, 32);
    m_icon2.fill(Qt::transparent);
    QPainter painter(&m_icon2);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::red, 2));
    painter.setBrush(QBrush(QColor(255, 100, 100, 180)));
    painter.drawRect(4, 4, 24, 24);
}
