#ifndef MAPICON_H
#define MAPICON_H

#include <QPixmap>
#include <QPoint>
#include <QPainter>
#include <QDebug>
#include <QRect>
#include <QObject>

class MapIcon  : public QObject{
    Q_OBJECT
public:
    MapIcon(const QString& iconFilePath = "test",  const int normalNum = 20, const int clickNum = 0);
    void setPosition(int x, int y);
    void toggleVisibility();
    void setVisible(bool visible);
    bool isVisible() const;
    void draw(QPainter& painter, const QPoint& offset);
    QRect boundingRect(const QPoint& offset) const;
    bool containsPoint(const QPoint& point, const QPoint& offset) const;
    void onClicked();
    void switchIcon();
    QPixmap m_icon[100];
    QPoint m_position;
    bool m_visible;
    int current_icon_index;
    const QString& iconFilePath;
    const int normalNum;
    const int clickNum;
    mutable QRect m_actualRect; // 缓存实际显示的矩形
};

#endif // MAPICON_H
