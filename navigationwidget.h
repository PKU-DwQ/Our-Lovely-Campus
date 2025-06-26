#ifndef NAVIGATIONWIDGET_H
#define NAVIGATIONWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QTimer>
#include "imageviewer.h"

class NavigationWidget : public QWidget {
    Q_OBJECT
public:
    explicit NavigationWidget(const QString& imagePath, QWidget* parent = nullptr);

private:
    void createNavigationButtons();
    QGridLayout* m_layout;
    ImageViewer* m_imageViewer;
};

#endif // NAVIGATIONWIDGET_H
