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

    static const QVector3D X = QVector3D(1, 0, 0);

    static const QVector3D Y = QVector3D(0, 1, 0);

    static const QVector3D Z = QVector3D(0, 0, 1);

};

namespace VertexPropertyType {
    enum Type {
        kGeneral = 0,
        kPosition,
        kNormal,
        kUV0,
        kUV1,
        kColors,
        kTangent0,
        kTangent1,
        kNumType
    };
}

namespace VertexPropertySize {
    enum Size {
        kGeneral = 0,
        kPosition = 3,
        kNormal = 3,
        kUV0 = 2,
        kUV1 = 2,
        kColor = 4,
        kTangent0 = 3,
        kTangent1 = 3,
        kNumSize
    };
}

namespace VertexAttributeLocation {
    enum Location {
        kPosition = 0,
        kNormal = 1,
        kUV0 = 2,
        kUV1 = 3,
        kColor = 4,
        kNumLocation
    };
}

namespace TextureUnitLocation {
    enum Location {
        kAmbient = 0,
        kDiffuse = 1,
        kSpecular = 2,
        kCubemap = 3,
        kNumLocation
    };
}

namespace CubemapLocation {
	enum Location {
		kFront = 0,
		kBack = 1,
		kLeft = 2,
		kRight = 3,
		kUp = 4,
		kDown = 5,
		kNumCubemapLocation
	};
}

namespace NodeType {
    enum Type {
        kGeneral = 0,
        kCamera,
        kLight,
        kMeshInstance,
        kNumType
    };
}

namespace LightType {
    enum Type {
        kGeneralLight = 0,
        kDotLight,
        kSpotLight,
        kDirectionLight,
        kNumType
    };
}

namespace CubemapFace {
    enum Face {
        kRight = 0,
        kLeft = 1,
        kUp = 2,
        kDown = 3,
        kBack = 4,
        kFront = 5,
        kNumFace
    };
}

#endif //QTSPACE_CONSTS_H
