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
    MapIcon(QString iconFilePath,  const int normalNum = 20, const int clickNum = 11, int iconsize = 80);
    void setPosition(int x, int y);
    void setVisible(bool visible);
    bool isVisible() const;
    void draw(QPainter& painter, const QPoint& offset);
    QRect boundingRect(const QPoint& offset) const;
    bool containsPoint(const QPoint& point) const;
    void onClicked();
    void switchIcon();
    void setNormal(bool normal);
    QPixmap m_icon[100];
    QPoint m_position;
    bool m_visible;
    int current_icon_index;
    int iconsize;
    QString iconFilePath;
    const int normalNum;
    const int clickNum;
    const int maxIndx;
    mutable QRect m_actualRect; // 缓存实际显示的矩形
    bool isnormal;
};

#endif // MAPICON_H
