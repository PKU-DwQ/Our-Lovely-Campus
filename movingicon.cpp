#include "movingicon.h"

MovingIcon::MovingIcon(const QString& iconFilePath,  const int normalNum, const int clickNum, int switchInterval, int moveInterval)
    : MapIcon(),
    m_currentPathIndex(0),
    m_switchInterval(switchInterval),
    m_moveInterval(moveInterval)
{
    // 尝试加载图标
    for (int i = 1; i <= normalNum; i++){
        QString iconPath = ":/" + iconFilePath + "/" + QString::number(i) +".png";
        if (!m_icon[i].load(iconPath)) {
            qDebug() << "无法加载图标" << i;
        }
    }
    m_visible=true;
}

void MovingIcon::start() {/*
    if (!m_switchTimer->isActive()) {
        m_switchTimer->start(m_switchInterval);
    }
    if (!m_moveTimer->isActive()) {
        m_moveTimer->start(m_moveInterval);
    }*/
}

void MovingIcon::stop() {/*
    m_switchTimer->stop();
    m_moveTimer->stop();*/
}
void MovingIcon::setPath(const QList<QPoint>& path) {
    m_path = path;
    m_currentPathIndex = 0;
}

void MovingIcon::setSwitchInterval(int interval) {
    m_switchInterval = interval;/*
    if (m_switchTimer->isActive()) {
        m_switchTimer->stop();
        m_switchTimer->start(m_switchInterval);
    }*/
}

void MovingIcon::setMoveInterval(int interval) {
    m_moveInterval = interval;/*
    if (m_moveTimer->isActive()) {
        m_moveTimer->stop();
        m_moveTimer->start(m_moveInterval);
    }*/
}

void MovingIcon::switchIcon() {
    m_isHovered=!m_isHovered;
}

void MovingIcon::moveAlongPath() {
    if (m_path.isEmpty()) return;

    m_position = m_path[m_currentPathIndex];
    m_currentPathIndex = (m_currentPathIndex + 1) % m_path.size();
}
