#include "header_file/mapicon.h"

MapIcon::MapIcon(QString iconFilePath,  const int normalNum, const int clickNum, int iconsize) :
    m_visible(false), current_icon_index{}, iconsize(iconsize), iconFilePath(iconFilePath), normalNum(normalNum), clickNum(clickNum),
    maxIndx(clickNum + normalNum - 1), isnormal(true){ //isnormal初始化成立false 所以猫猫没动!
    // 尝试加载图标
    for (int i = 0; i < normalNum + clickNum; i++){
        QString iconPath = ":/icon/" + iconFilePath + "/" + QString::number(i) +".png";
        if (!m_icon[i].load(iconPath)) {
           qDebug() << iconFilePath << " can't load icon" << i;
        }
    }
    m_visible=true;
}

void MapIcon::setPosition(int x, int y) {
    m_position = QPoint(x, y);
}

void MapIcon::setNormal(bool normal) {
    isnormal = normal;
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
    QSize targetSize(iconsize, iconsize);
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

bool MapIcon::containsPoint(const QPoint& point) const {
    return m_actualRect.contains(point);
}

void MapIcon::onClicked() {
    qDebug() << "Icon clicked";
}

void MapIcon::switchIcon() {
    if (isnormal){
        //qDebug() << iconFilePath << "switch icon"; // iconFilePath不能是const string &?  主线程
        if (current_icon_index > normalNum) {
            current_icon_index--;
        }
        else {
            current_icon_index = (current_icon_index + 1) % normalNum;
        }
    }
    else {
        current_icon_index = maxIndx > (current_icon_index + 1) ? current_icon_index + 1 : maxIndx;
    }
}
