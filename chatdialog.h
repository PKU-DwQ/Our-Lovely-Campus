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
#include <Qlabel>
#include <QFile>
#include <QSizePolicy>

class ChatDialog : public QDialog {
    Q_OBJECT
public:
    explicit ChatDialog(QWidget *parent = nullptr);
    void addMessage(const QString &sender, const QString &message);
    void paintEvent(QPaintEvent *event);
private slots:
    void sendMessage();
    void handleApiResponse(QNetworkReply *reply);

private:
    QLabel *headerLabel;
    QLabel *imageLabel;
    QTextEdit *chatHistory;
    QLineEdit *userInput;
    QPushButton *sendButton;
    QNetworkAccessManager *networkManager;
};

#endif // CHATDIALOG_H
