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
#include "header_file/movingicon.h"
#include "header_file/cloudanimation.h"

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
    void setupMovingIcon();
    QPixmap m_background;
    QPoint m_offset;
    MovingIcon* turtle;
    MovingIcon* cat;
    MovingIcon* crane;
    MovingIcon* gecko;
    MovingIcon* pillar;
    QList<MovingIcon*> allIcon;
    QTimer* m_switchTimer;
    QTimer* m_moveTimer;
    CloudAnimation* cloud;
};

#endif // IMAGEVIEWER_H
