#ifndef FOGANIMATIONWIDGET_H
#define FOGANIMATIONWIDGET_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QTimer>

class FogAnimationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FogAnimationWidget(QWidget *parent = nullptr);
    ~FogAnimationWidget();

    // 设置动画参数
    void setAnimationDuration(int duration);
    void setStartDelay(int delay);

    // 启动动画
    void startAnimation();

signals:
    void animationFinished();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onLeftFogAnimationFinished();
    void onRightFogAnimationFinished();
    void startFogMovement();

private:
    QWidget *leftFog;
    QWidget *rightFog;
    QPropertyAnimation *leftFogAnim;
    QPropertyAnimation *rightFogAnim;
    QTimer *delayTimer;

    int animationDuration;
    int startDelay;
};

#endif // FOGANIMATIONWIDGET_H
