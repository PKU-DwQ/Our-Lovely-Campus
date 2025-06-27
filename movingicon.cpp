#include "movingicon.h"

MovingIcon::MovingIcon(const QString& iconFilePath,  const int normalNum, const int clickNum, int iconsize, int switchInterval, int moveInterval)
    : MapIcon(iconFilePath, normalNum, clickNum, iconsize),
    m_currentPathIndex(0),
    m_switchInterval(switchInterval),
    m_moveInterval(moveInterval)
{
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
    setPath(path);
}

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

void MovingIcon::moveAlongPath() {
    if (m_path.isEmpty()) return;
    if (!isnormal) return;
    if (current_icon_index > normalNum) return;
    m_position = m_path[m_currentPathIndex];
    m_currentPathIndex = (m_currentPathIndex + 1) % m_path.size();
}
