#ifndef QTSPACE_CONSTS_H
#define QTSPACE_CONSTS_H

#include <QVector3D>

namespace Vector3D {
    static const QVector3D Origin = QVector3D(0, 0, 0);

    static const QVector3D Left = QVector3D(-1, 0, 0);

    static const QVector3D Right = QVector3D(1, 0, 0);

    static const QVector3D Up = QVector3D(0, 1, 0);

    static const QVector3D Down = QVector3D(0, -1, 0);

    static const QVector3D Forward = QVector3D(0, 0, -1);

    static const QVector3D Backward = QVector3D(0, 0, 1);
};

#endif //QTSPACE_CONSTS_H
