#ifndef COVERWIDGET_H
#define COVERWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPushButton>
#include <QMediaPlayer>
#include <QAudioOutput>
class CoverWidget : public QWidget {
    Q_OBJECT
public:
    explicit CoverWidget(QWidget *parent = nullptr);  // 声明构造函数
    ~CoverWidget() = default;                        // 默认析构函数

protected:
    void paintEvent(QPaintEvent *event) override;     // 声明绘图事件

signals:
    void startNavigation();                           // 声明信号

private:
    QPixmap coverImage;                              // 成员变量：封面图片
    QPushButton *startButton;                        // 成员变量：开始按钮
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOutput;
};

#endif // COVERWIDGET_H
