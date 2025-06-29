#ifndef CLOUDANIMATION_H
#define CLOUDANIMATION_H

#include <QObject>
#include <QLabel>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

class CloudAnimation : public QObject
{
    Q_OBJECT

public:
    explicit CloudAnimation(QWidget *parent = nullptr);
    ~CloudAnimation();

    void initCloudCovers();          // 初始化云朵
    void startCloudAnimation();      // 启动动画

private:
    QLabel *m_cloudCoverLeft;       // 左云朵
    QLabel *m_cloudCoverRight;      // 右云朵
    QWidget *m_parentWidget;        // 父窗口（用于计算位置）
};

#endif // CLOUDANIMATION_H
