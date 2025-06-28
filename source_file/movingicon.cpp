#include "header_file/movingicon.h"
#include "header_file/pathgenerator.h"
#include <QFile>
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QPoint>

MovingIcon::MovingIcon(const QString& iconFilePath,  const int normalNum, const int clickNum, int iconsize, int switchInterval, int moveInterval)
    : MapIcon(iconFilePath, normalNum, clickNum, iconsize),
    m_currentPathIndex(0),
    m_switchInterval(switchInterval),
    m_moveInterval(moveInterval)
{
    qDebug() << "Loading icon:" << iconFilePath << "success";
    QString configPath = ":/icon/" + iconFilePath + "/path.json";
    QFile configFile(configPath);
    if (configFile.open(QIODevice::ReadOnly)) {
        QJsonDocument configDoc = QJsonDocument::fromJson(configFile.readAll());
        QList<QPoint> path = PathGenerator::generateFromJson(configDoc.object());
        setPath(path);
    }
    else {
        QList<QPoint> path;
        int a = 1000, b = 1100;
        for (int i=a;i<b;i=i+2){
            path << QPoint(i, a);}
        for (int j=a;j<b;j+=2){
            path<<QPoint(b,j);
        }
        for (int i=b;i>a;i-=2){
            path<<QPoint(i,b);
        }
        for (int j=b;j>a;j-=2){
            path<<QPoint(a,j);
        }
        setPath(path);
    }
}

void MovingIcon::start() {/*
    if (!m_switchTimer->isActive()) {
        m_switchTimer->start(m_switchInterval);
    }
    if (!m_moveTimer->isActive()) {
        m_moveTimer->start(m_moveInterval);
    }*/
}

void MovingIcon::stop() {

}
void MovingIcon::setPath(const QList<QPoint>& path) {
    m_path = path;
    m_currentPathIndex = 0;
}

void MovingIcon::moveAlongPath() {
    if (m_path.isEmpty()) return;
    if (!isnormal) return;
    if (current_icon_index > normalNum) return;
    m_position = m_path[m_currentPathIndex];
    m_currentPathIndex = (m_currentPathIndex + 1) % m_path.size();
}
