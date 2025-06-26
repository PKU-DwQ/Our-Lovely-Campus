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
public:
    void focusInEvent(QFocusEvent* event) override;
    explicit ImageViewer(const QString& imagePath, QWidget* parent = nullptr);
    void paintEvent(QPaintEvent* event) override;
    void moveView(int dx, int dy);
    QPoint getOffset() const;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void setLakeIconPosition(int x, int y);
    void loadLakeIconImages(const QString& normalPath, const QString& hoverPath);
    void setupMovingIcon(const QString& icon1Path, const QString& icon2Path, const QList<QPoint>& path);

private:
    void createErrorImage();
    QPixmap m_background;
    QPoint m_offset;
    MapIcon m_mapIcon;
    MapIcon m_lakeIcon;
    MovingIcon* m_movingIcon;
};

#endif // IMAGEVIEWER_H
