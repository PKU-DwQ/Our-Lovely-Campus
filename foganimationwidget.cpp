#include "foganimationwidget.h"
#include <QPainter>
#include <QBitmap>
#include <QPropertyAnimation>
#include <QTimer>

FogAnimationWidget::FogAnimationWidget(QWidget *parent) : QWidget(parent),
    animationDuration(1500),
    startDelay(500)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);

    // 创建左右云雾部件
    leftFog = new QWidget(this);
    rightFog = new QWidget(this);

    // 设置云雾样式
    leftFog->setStyleSheet("background-color: rgba(255, 255, 255, 0.9);");
    rightFog->setStyleSheet("background-color: rgba(255, 255, 255, 0.9);");

    // 初始隐藏云雾
    leftFog->hide();
    rightFog->hide();

    // 创建动画
    leftFogAnim = new QPropertyAnimation(leftFog, "geometry", this);
    rightFogAnim = new QPropertyAnimation(rightFog, "geometry", this);

    // 设置动画参数
    leftFogAnim->setDuration(animationDuration);
    rightFogAnim->setDuration(animationDuration);

    // 连接动画结束信号
    connect(leftFogAnim, &QPropertyAnimation::finished, this, &FogAnimationWidget::onLeftFogAnimationFinished);
    connect(rightFogAnim, &QPropertyAnimation::finished, this, &FogAnimationWidget::onRightFogAnimationFinished);

    // 创建延迟计时器
    delayTimer = new QTimer(this);
    delayTimer->setSingleShot(true);
    connect(delayTimer, &QTimer::timeout, this, &FogAnimationWidget::startFogMovement);
}

FogAnimationWidget::~FogAnimationWidget()
{
}

void FogAnimationWidget::setAnimationDuration(int duration)
{
    animationDuration = duration;
    leftFogAnim->setDuration(animationDuration);
    rightFogAnim->setDuration(animationDuration);
}

void FogAnimationWidget::setStartDelay(int delay)
{
    startDelay = delay;
}

void FogAnimationWidget::startAnimation()
{
    // 重置云雾位置
    leftFog->hide();
    rightFog->hide();

    // 启动延迟计时器
    delayTimer->start(startDelay);
}

void FogAnimationWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    // 可添加自定义绘制，例如渐变云雾效果
}

void FogAnimationWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    // 更新云雾位置和大小
    if (leftFog->isVisible()) {
        int width = this->width() / 2;
        leftFog->setGeometry(0, 0, width, this->height());
        rightFog->setGeometry(width, 0, width, this->height());
    }
}

void FogAnimationWidget::startFogMovement()
{
    int width = this->width();
    int halfWidth = width / 2;
    int height = this->height();

    // 设置云雾初始位置
    leftFog->setGeometry(0, 0, halfWidth, height);
    rightFog->setGeometry(halfWidth, 0, halfWidth, height);

    leftFog->show();
    rightFog->show();

    // 设置动画起始和结束值
    leftFogAnim->setStartValue(QRect(0, 0, halfWidth, height));
    leftFogAnim->setEndValue(QRect(-halfWidth, 0, halfWidth, height));

    rightFogAnim->setStartValue(QRect(halfWidth, 0, halfWidth, height));
    rightFogAnim->setEndValue(QRect(width, 0, halfWidth, height));

    // 启动动画
    leftFogAnim->start();
    rightFogAnim->start();
}

void FogAnimationWidget::onLeftFogAnimationFinished()
{
    // 检查两个动画是否都完成
    if (leftFogAnim->state() == QAbstractAnimation::Stopped &&
        rightFogAnim->state() == QAbstractAnimation::Stopped) {
        leftFog->hide();
        rightFog->hide();
        emit animationFinished();
    }
}

void FogAnimationWidget::onRightFogAnimationFinished()
{
    // 检查两个动画是否都完成
    if (leftFogAnim->state() == QAbstractAnimation::Stopped &&
        rightFogAnim->state() == QAbstractAnimation::Stopped) {
        leftFog->hide();
        rightFog->hide();
        emit animationFinished();
    }
}
