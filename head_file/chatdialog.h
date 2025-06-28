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
#include <QLabel>
#include <QFile>
#include <QDir>
#include <QTimer>
#include <QPixmap>
#include "head_file/imagewidget.h"
#include "head_file/imageviewer.h"


class ChatDialog : public QDialog {
    Q_OBJECT
public:
    explicit ChatDialog(const QString& imagePath, int imagenum, const QString& infoText,
                        const QString& welcome, const QString& identity, const QString&name, QWidget *parent = nullptr);
    void updateImage();
    void addMessage(const QString &sender, const QString &message);

private slots:
    void sendMessage();
    void handleApiResponse(QNetworkReply *reply);
    void prevImage();
    void nextImage();

private:
    void loadCurrentImage();

    QString m_imagePath;
    QString m_infoText;
    int m_currentImageIndex;
    int m_imagenum;
    QPushButton *m_prevButton;
    QPushButton *m_nextButton;
    QLabel *m_pageLabel;
    QLabel *m_infoLabel;
    ImageWidget *m_imageContainer;
    QTextEdit *chatHistory;
    QLineEdit *userInput;
    QPushButton *sendButton;
    QNetworkAccessManager *networkManager;
    QJsonArray m_chatHistory;
    QString welcomewords;
    QString Defaultidentity;
    QString name;
};
ChatDialog* makeChatDialog(QString name, ImageViewer* p);
#endif // CHATDIALOG_H
