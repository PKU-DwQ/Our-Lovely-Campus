#include "header_file/cloudanimation.h"
#include <QPixmap>
#include <QTimer>

CloudAnimation::CloudAnimation(QWidget *parent)
    : QObject(parent),
    m_cloudCoverLeft(new QLabel(parent)),
    m_cloudCoverRight(new QLabel(parent)),
    m_parentWidget(parent)
{
    initCloudCovers();
}

CloudAnimation::~CloudAnimation()
{
    // 清理资源（如果动画未执行完）
    if (m_cloudCoverLeft) m_cloudCoverLeft->deleteLater();
    if (m_cloudCoverRight) m_cloudCoverRight->deleteLater();
}

void CloudAnimation::initCloudCovers()
{
    // 设置云朵属性
    m_cloudCoverLeft->setAttribute(Qt::WA_TranslucentBackground);
    m_cloudCoverRight->setAttribute(Qt::WA_TranslucentBackground);

    // 加载云朵图片（确保资源文件已正确配置）
    QPixmap leftCloud(":/cloud/left.png");
    QPixmap rightCloud(":/cloud/right.png");

    // 放大云朵尺寸
    leftCloud = leftCloud.scaled(m_parentWidget->width()  , m_parentWidget->height() , Qt::KeepAspectRatioByExpanding);
    rightCloud = rightCloud.scaled(m_parentWidget->width() , m_parentWidget->height() , Qt::KeepAspectRatioByExpanding);

    // 应用云朵图像
    m_cloudCoverLeft->setPixmap(leftCloud);
    m_cloudCoverLeft->setScaledContents(true);
    m_cloudCoverRight->setPixmap(rightCloud);
    m_cloudCoverRight->setScaledContents(true);

    // 初始位置：在屏幕中央重叠
    int verticalOffset = 200;
    m_cloudCoverLeft->setGeometry(
        m_parentWidget->width() / 2 - m_parentWidget->width() / 2,
        verticalOffset,
        m_parentWidget->width() * 1.5,
        m_parentWidget->height() - verticalOffset
        );

    m_cloudCoverRight->setGeometry(
        m_parentWidget->width() / 2,
        verticalOffset,
        m_parentWidget->width() * 1.5,
        m_parentWidget->height() - verticalOffset
        );

    // 置于顶层
    m_cloudCoverLeft->raise();
    m_cloudCoverRight->raise();
}

void CloudAnimation::startCloudAnimation()
{
    QTimer::singleShot(1000, this, [this]() {
        QParallelAnimationGroup *animGroup = new QParallelAnimationGroup(this);

        // 左云朵向左滑动
        QPropertyAnimation *leftAnim = new QPropertyAnimation(m_cloudCoverLeft, "geometry");
        leftAnim->setDuration(3000);
        leftAnim->setStartValue(m_cloudCoverLeft->geometry());
        leftAnim->setEndValue(QRect(-m_parentWidget->width(), 0, m_parentWidget->width() , m_parentWidget->height()*2 ));
        leftAnim->setEasingCurve(QEasingCurve::OutCubic);

        // 右云朵向右滑动
        QPropertyAnimation *rightAnim = new QPropertyAnimation(m_cloudCoverRight, "geometry");
        rightAnim->setDuration(3000);
        rightAnim->setStartValue(m_cloudCoverRight->geometry());
        rightAnim->setEndValue(QRect(m_parentWidget->width(), 0, m_parentWidget->width() , m_parentWidget->height()*2 ));
        rightAnim->setEasingCurve(QEasingCurve::OutCubic);

        // 淡出效果
        QPropertyAnimation *fadeAnimLeft = new QPropertyAnimation(m_cloudCoverLeft, "windowOpacity");
        fadeAnimLeft->setDuration(1800);
        fadeAnimLeft->setStartValue(1.0);
        fadeAnimLeft->setEndValue(0.0);
        QPropertyAnimation *fadeAnimRight = new QPropertyAnimation(m_cloudCoverRight, "windowOpacity");
        fadeAnimRight->setDuration(1800);
        fadeAnimRight->setStartValue(1.0);
        fadeAnimRight->setEndValue(0.0);

        // 组合动画
        animGroup->addAnimation(leftAnim);
        animGroup->addAnimation(rightAnim);
        animGroup->addAnimation(fadeAnimLeft);
        animGroup->addAnimation(fadeAnimRight);


        // 动画结束后清理资源
        connect(animGroup, &QParallelAnimationGroup::finished, this, [this]() {
            m_cloudCoverLeft->deleteLater();
            m_cloudCoverRight->deleteLater();
            deleteLater();  // 删除自身对象
        });

        animGroup->start();
    });
}
