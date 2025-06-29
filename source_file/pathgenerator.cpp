#include "header_file/pathgenerator.h"
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
        for (int i = steps; i >= 0; --i) {
            float ratio = static_cast<float>(i) / steps;
            int x = start.x() + dx * ratio;
            int y = start.y() + dy * ratio;
            path << QPoint(x, y);
        }
    }
    else if (type == "polyline") {
<<<<<<< HEAD
        // 折线路径生成
        QPoint start(pathSettings["startPoint"].toArray()[0].toInt(),
                     pathSettings["startPoint"].toArray()[1].toInt());
        QPoint end(pathSettings["endPoint"].toArray()[0].toInt(),
                   pathSettings["endPoint"].toArray()[1].toInt());
        int step = pathSettings.value("step").toInt(5);
        bool closed = pathSettings.value("closed").toBool(false);

        QList<QPoint> allPoints;
=======
    // 折线路径生成
    QPoint start(pathSettings["startPoint"].toArray()[0].toInt(),
                 pathSettings["startPoint"].toArray()[1].toInt());
    QPoint end(pathSettings["endPoint"].toArray()[0].toInt(),
               pathSettings["endPoint"].toArray()[1].toInt());
    int step = pathSettings.value("step").toInt(5);
    bool closed = pathSettings.value("closed").toBool(false);

    QList<QPoint> allPoints;
    allPoints << start;

    // 添加所有途径点
    QJsonArray wayPoints = pathSettings["wayPoints"].toArray();
    for (const QJsonValue& point : wayPoints) {
        allPoints << QPoint(point.toArray()[0].toInt(),
                            point.toArray()[1].toInt());
    }

    allPoints << end;

    // 如果路径是闭合的，添加回到起点的线段
    if (closed) {
>>>>>>> b14541bae80a45de4be468db8ca4d936e48b5905
        allPoints << start;

        // 添加所有途径点
        QJsonArray wayPoints = pathSettings["wayPoints"].toArray();
        for (const QJsonValue& point : wayPoints) {
            allPoints << QPoint(point.toArray()[0].toInt(),
                                point.toArray()[1].toInt());
        }

        allPoints << end;

        // 如果路径是闭合的，添加回到起点的线段
        if (closed) {
            allPoints << start;
        }

        // 生成路径上的所有点
        for (int i = 0; i < allPoints.size() - 1; ++i) {
            QPoint current = allPoints[i];
            QPoint next = allPoints[i + 1];

            int dx = next.x() - current.x();
            int dy = next.y() - current.y();
            int steps = qMax(abs(dx), abs(dy)) / step;

            for (int j = 0; j <= steps; ++j) {
                float ratio = static_cast<float>(j) / steps;
                int x = current.x() + dx * ratio;
                int y = current.y() + dy * ratio;
                path << QPoint(x, y);
            }
        }
    }
<<<<<<< HEAD
    else if (type == "static") {
        // 静态路径（保持原地不动）
        QPoint position(
            pathSettings["position"].toArray()[0].toInt(),
            pathSettings["position"].toArray()[1].toInt()
            );

        // 默认生成 1 个点（原地不动）
        path << position;

        // 可选：如果指定了 duration，可以生成多个相同的点来模拟时间
        if (pathSettings.contains("duration")) {
            int duration = pathSettings["duration"].toInt();
            int steps = duration / 10; // 假设每 10ms 一个点（可调整）
            for (int i = 0; i < steps; ++i) {
                path << position;
            }
        }
    }
    return path;
=======
    }return path;
>>>>>>> b14541bae80a45de4be468db8ca4d936e48b5905
}
