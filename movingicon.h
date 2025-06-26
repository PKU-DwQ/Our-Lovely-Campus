#ifndef MOVINGICON_H
#define MOVINGICON_H

#include <QObject>
#include <QTimer>
#include <QList>
#include "mapicon.h"

class MovingIcon : public MapIcon {
    Q_OBJECT // 确保包含 Q_OBJECT 宏
public:
    MovingIcon(const QString& icon1Path, const QString& icon2Path, int switchInterval = 1000, int moveInterval = 50);

    void start();
    void stop();
    void setPath(const QList<QPoint>& path);
    void setSwitchInterval(int interval);
    void setMoveInterval(int interval);

private slots:
    void switchIcon();
    void moveAlongPath();

private:
    QTimer* m_switchTimer;
    QTimer* m_moveTimer;
    QList<QPoint> m_path;
    int m_currentPathIndex;
    int m_switchInterval;
    int m_moveInterval;
    bool m_currentIcon; // 新增变量：用于跟踪当前显示哪个图标
};

#endif // MOVINGICON_H
