#include <QList>
#include <QPoint>
#include <QJsonObject>

class PathGenerator {
public:
    static QList<QPoint> generateFromJson(const QJsonObject& config);
};
