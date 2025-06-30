#include <QApplication>
#include <QWidget>
//#include "mapicon.h"
//#include "imageviewer.h"
#include "header_file/navigationwidget.h"
#include "header_file/coverwidget.h"
#include <QMediaPlayer>
#include <QAudioOutput>


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QMediaPlayer *musicPlayer = new QMediaPlayer();
    QAudioOutput *audioOutput = new QAudioOutput();
    musicPlayer->setAudioOutput(audioOutput);
    musicPlayer->setSource(QUrl("qrc:/music/1.mp3"));
    audioOutput->setVolume(50);
    musicPlayer->setLoops(QMediaPlayer::Infinite);  // 循环播放
    musicPlayer->play();

    // 1. 创建封面窗口
    CoverWidget cover;
    cover.setWindowTitle("北大校园");
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
        //navigation->show();
        navigation->showMaximized();  // 全屏显示
    });

    int result = app.exec();

    // 清理音乐播放器
    musicPlayer->stop();
    delete musicPlayer;
    delete audioOutput;

    return result;
}
