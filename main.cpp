#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QGridLayout>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QPoint>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QHoverEvent>
#include <QWindow>
#include <QLabel>
#include "mapicon.h"
#include "imageviewer.h"
#include "navigationwidget.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // 尝试查找图片文件
    QString imagePath = ":/map.jpg";

    // 创建主窗口
    NavigationWidget window(imagePath);
    window.show();

    return app.exec();
}
