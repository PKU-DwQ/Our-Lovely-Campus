#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QPixmap>
#include <QPoint>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QFocusEvent>
#include <QDebug>
#include "mapicon.h"
#include "movingicon.h"

class ImageViewer : public QWidget {
    Q_OBJECT
public:
    void focusInEvent(QFocusEvent* event) override;
    explicit ImageViewer(const QString& imagePath, QWidget* parent = nullptr);
    void paintEvent(QPaintEvent* event) override;
    void moveView(int dx, int dy);
    QPoint getOffset() const;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void setupMovingIcon(const QString& iconFilePath, const int normalNum, const int clickNum, const QList<QPoint>& path);
    QPixmap m_background;
    QPoint m_offset;
    MapIcon m_mapIcon;
    MapIcon m_lakeIcon;
    MovingIcon* m_movingIcon;
    QTimer* m_switchTimer;
    QTimer* m_moveTimer;
};

#endif // IMAGEVIEWER_H
