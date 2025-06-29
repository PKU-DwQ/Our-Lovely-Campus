#include "header_file/imagewidget.h"
ImageWidget::ImageWidget(QWidget* parent) : QWidget(parent) {}

void ImageWidget::setPixmap(const QPixmap& pix) {
    m_pixmap = pix;
    update();
}

void ImageWidget::setScaledSize(int width, int height) {
    // 允许动态调整缩放尺寸
    m_scaledWidth = width;
    m_scaledHeight = height;
    update();
}

void ImageWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制白色背景
    painter.fillRect(rect(), Qt::white);

    // 绘制边框
    painter.setPen(QPen(QColor(145, 213, 255), 1));
    painter.drawRect(rect().adjusted(0, 0, -1, -1));

    if(!m_pixmap.isNull()) {
        // 缩放图片并保持宽高比
        QPixmap scaled = m_pixmap.scaled(m_scaledWidth, m_scaledHeight,
                                         Qt::KeepAspectRatio,
                                         Qt::SmoothTransformation);
        // 居中绘制
        int x = (width() - scaled.width()) / 2;
        int y = (height() - scaled.height()) / 2;
        painter.drawPixmap(x, y, scaled);
    } else {
        // 图片加载失败提示
        painter.setPen(Qt::gray);
        painter.drawText(rect(), Qt::AlignCenter, "图片加载中...");
    }
}
