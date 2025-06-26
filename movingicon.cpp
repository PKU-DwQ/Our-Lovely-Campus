#include "movingicon.h"

MovingIcon::MovingIcon(const QString& icon1Path, const QString& icon2Path, int switchInterval, int moveInterval)
    : MapIcon(),
    m_switchInterval(switchInterval),
    m_moveInterval(moveInterval),
    m_currentPathIndex(0)
{
    // 尝试加载图标
    if (!m_icon1.load(icon1Path)) {
        qDebug() << "无法加载图标:" << icon1Path;
        createDefaultIcon1();
    }
    if (!m_icon2.load(icon2Path)) {
        qDebug() << "无法加载图标:" << icon2Path;
        createDefaultIcon2();
    }

    // 初始化定时器
    m_switchTimer = new QTimer(this);
    m_moveTimer = new QTimer(this);

    // 连接信号和槽
    connect(m_switchTimer, &QTimer::timeout, this, &MovingIcon::switchIcon);
    connect(m_moveTimer, &QTimer::timeout, this, &MovingIcon::moveAlongPath);
    m_visible=true;
}

void MovingIcon::start() {
    m_switchTimer->start(m_switchInterval);
    m_moveTimer->start(m_moveInterval);
}

void MovingIcon::stop() {
    m_switchTimer->stop();
    m_moveTimer->stop();
}

void MovingIcon::setPath(const QList<QPoint>& path) {
    m_path = path;
    m_currentPathIndex = 0;
}

void MovingIcon::setSwitchInterval(int interval) {
    m_switchInterval = interval;
    if (m_switchTimer->isActive()) {
        m_switchTimer->stop();
        m_switchTimer->start(m_switchInterval);
    }
}

void MovingIcon::setMoveInterval(int interval) {
    m_moveInterval = interval;
    if (m_moveTimer->isActive()) {
        m_moveTimer->stop();
        m_moveTimer->start(m_moveInterval);
    }
}

void MovingIcon::switchIcon() {
}

void MovingIcon::moveAlongPath() {
    if (m_path.isEmpty()) return;

    m_position = m_path[m_currentPathIndex];
    m_currentPathIndex = (m_currentPathIndex + 1) % m_path.size();
}
