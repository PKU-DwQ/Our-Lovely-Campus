#include "head_file/pathgenerator.h"
#include <QJsonArray>
#include <cmath> // 用于圆形路径计算
#include <QJsonValue>
QList<QPoint> PathGenerator::generateFromJson(const QJsonObject& config) {
    QList<QPoint> path;
    QJsonObject pathSettings = config["pathSettings"].toObject();
    QString type = pathSettings["type"].toString();

    if (type == "rectangle") {
        // 矩形路径
        QPoint start(pathSettings["startPoint"].toArray()[0].toInt(),
                     pathSettings["startPoint"].toArray()[1].toInt());
        int width = pathSettings["width"].toInt();
        int height = pathSettings["height"].toInt();
        int step = pathSettings["step"].toInt();
        bool clockwise = (pathSettings["direction"].toString() == "clockwise");

        int x = start.x();
        int y = start.y();

        if (clockwise) {
            // 顺时针方向
            // 上边
            for (int i = 0; i <= width; i += step) {
                path << QPoint(x + i, y);
            }
            // 右边
            for (int i = 0; i <= height; i += step) {
                path << QPoint(x + width, y + i);
            }
            // 下边
            for (int i = width; i >= 0; i -= step) {
                path << QPoint(x + i, y + height);
            }
            // 左边
            for (int i = height; i >= 0; i -= step) {
                path << QPoint(x, y + i);
            }
        } else {
            // 逆时针方向
            // 左边
            for (int i = 0; i <= height; i += step) {
                path << QPoint(x, y + i);
            }
            // 下边
            for (int i = 0; i <= width; i += step) {
                path << QPoint(x + i, y + height);
            }
            // 右边
            for (int i = height; i >= 0; i -= step) {
                path << QPoint(x + width, y + i);
            }
            // 上边
            for (int i = width; i >= 0; i -= step) {
                path << QPoint(x + i, y);
            }
        }
    }
    else if (type == "circle") {
        // 圆形路径生成
        QPoint center(pathSettings["center"].toArray()[0].toInt(),
                      pathSettings["center"].toArray()[1].toInt());
        int radius = pathSettings["radius"].toInt();
        int points = pathSettings.value("points").toInt(36); // 默认36个点
        bool clockwise = (pathSettings["direction"].toString() == "clockwise");

        for (int i = 0; i < points; ++i) {
            double angle = 2 * M_PI * i / points;
            if (!clockwise) angle = -angle;
            int x = center.x() + radius * cos(angle);
            int y = center.y() + radius * sin(angle);
            path << QPoint(x, y);
        }
    }
    else if (type == "diagonal") {
        // 对角线路径
        QPoint start(pathSettings["startPoint"].toArray()[0].toInt(),
                     pathSettings["startPoint"].toArray()[1].toInt());
        QPoint end(pathSettings["endPoint"].toArray()[0].toInt(),
                   pathSettings["endPoint"].toArray()[1].toInt());
        int step = pathSettings.value("step").toInt(5); // 默认步长5像素

        int dx = end.x() - start.x();
        int dy = end.y() - start.y();
        int steps = qMax(abs(dx), abs(dy)) / step;

        for (int i = 0; i <= steps; ++i) {
            float ratio = static_cast<float>(i) / steps;
            int x = start.x() + dx * ratio;
            int y = start.y() + dy * ratio;
            path << QPoint(x, y);
        }
    }

    return path;
}
