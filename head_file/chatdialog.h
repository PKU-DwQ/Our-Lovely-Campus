#ifndef CHATDIALOG_H
#define CHATDIALOG_H

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
#include <QTimer>
#include <QApplication>
#include <QStyle>
#include <QLabel>
#include <QFile>
#include <QSizePolicy>
#include <QMouseEvent>

class ChatDialog : public QDialog {
    Q_OBJECT
public:
    explicit ChatDialog(const QString& imagePath,int imagenum, const QString& infoText, QWidget *parent = nullptr);
    void updateImage();
    void addMessage(const QString &sender, const QString &message);
    void paintEvent(QPaintEvent *event) override;

private slots:
    void sendMessage();
    void handleApiResponse(QNetworkReply *reply);
    void prevImage();
    void nextImage();

private:
    QString m_imagePath;
    QString m_infoText;
    int m_currentImageIndex = 0;
    int m_imagenum;
    QPushButton *m_prevButton;
    QPushButton *m_nextButton;
    QLabel *m_pageLabel;
    QLabel *m_infoLabel;
    QWidget *m_imageContainer;  // 图片容器
    QTextEdit *chatHistory;
    QLineEdit *userInput;
    QPushButton *sendButton;
    QNetworkAccessManager *networkManager;
};

#endif // CHATDIALOG_H
