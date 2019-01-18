#ifndef QTSPACE_CONSTS_H
#define QTSPACE_CONSTS_H

#include <QVector3D>

struct Vector3D {
    static QVector3D Left() {
        static const QVector3D val = QVector3D(-1, 0, 0);
        return val;
    }

    static QVector3D Right() {
        static const QVector3D val = QVector3D(1, 0, 0);
        return val;
    }

    static QVector3D Up() {
        static const QVector3D val = QVector3D(0, 1, 0);
        return val;
    }

    static QVector3D Down() {
        static const QVector3D val = QVector3D(0, -1, 0);
        return val;
    }

    static QVector3D Forward() {
        static const QVector3D val = QVector3D(0, 0, -1);
        return val;
    }

    static QVector3D Backward() {
        static const QVector3D val = QVector3D(0, 0, 1);
        return val;
    }
};

#endif //QTSPACE_CONSTS_H
