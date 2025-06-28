#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QMainWindow>
#include <QDialog>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollBar>
#include <QLabel>
#include <QFile>
#include <QPainter>
#include <QDir>
#include <QPixmap>

// 新增图片显示控件类
class ImageWidget : public QWidget {
    Q_OBJECT
public:
    explicit ImageWidget(QWidget* parent = nullptr);
    void setPixmap(const QPixmap& pix);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QPixmap m_pixmap;
};

#endif // IMAGEWIDGET_H
