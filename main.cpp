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
#include "coverwidget.h"
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // 1. 创建封面窗口
    CoverWidget cover;
    cover.setWindowTitle("北大校园 - 图片导航");
    cover.resize(800, 600);
    cover.show();

    // 2. 创建导航窗口（延迟加载）
    NavigationWidget* navigation = nullptr;

    // 3. 点击封面按钮后切换窗口
    QObject::connect(&cover, &CoverWidget::startNavigation, [&]() {
        cover.hide();  // 隐藏封面窗口（非关闭，避免内存问题）
        // 尝试查找图片文件
        QString imagePath = ":/image_database/map.jpg";

        // 创建导航窗口
        navigation = new NavigationWidget(imagePath);
        //navigation->setWindowTitle("图片导航查看器");
        navigation->show();
        //navigation->showMaximized();  // 全屏显示
    });

    return app.exec();
}
