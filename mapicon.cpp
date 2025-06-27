#include "mapicon.h"

MapIcon::MapIcon(const QString& iconFilePath,  const int normalNum, const int clickNum) :
    m_visible(false), current_icon_index{}, iconFilePath(iconFilePath), normalNum(normalNum), clickNum(clickNum) {
    // 尝试加载默认图标
    if (!m_icon[1].load(":/test/1.jpg")) {
        qDebug() << "无法加载图标1.jpg";
    }
    // 尝试加载新图标
    if (!m_icon[2].load(":/icon/2.jpg")) {
        qDebug() << "无法加载图标2.jpg";
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


void MapIcon::draw(QPainter& painter, const QPoint& offset) {
    if (!m_visible) return;

    int iconX = m_position.x() - offset.x();
    int iconY = m_position.y() - offset.y();
    QPixmap currentIcon = m_icon[current_icon_index];

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
        m_icon[1].width(),
        m_icon[1].height()
        );
}

bool MapIcon::containsPoint(const QPoint& point, const QPoint& offset) const {
    return m_actualRect.contains(point);
}

void MapIcon::onClicked() {
    qDebug() << "图标被点击了";
}

