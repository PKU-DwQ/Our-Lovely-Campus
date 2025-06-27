#include "movingicon.h"

MovingIcon::MovingIcon(const QString& iconFilePath,  const int normalNum, const int clickNum, int switchInterval, int moveInterval)
    : MapIcon(iconFilePath, normalNum, clickNum),
    m_currentPathIndex(0),
    m_switchInterval(switchInterval),
    m_moveInterval(moveInterval)
{}

void MovingIcon::start() {/*
    if (!m_switchTimer->isActive()) {
        m_switchTimer->start(m_switchInterval);
    }
    if (!m_moveTimer->isActive()) {
        m_moveTimer->start(m_moveInterval);
    }*/
}

void MovingIcon::stop() {

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


void MovingIcon::moveAlongPath() {
    if (m_path.isEmpty()) return;

    m_position = m_path[m_currentPathIndex];
    m_currentPathIndex = (m_currentPathIndex + 1) % m_path.size();
}
