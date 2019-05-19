#ifndef QTSPACE_CAMERA_H
#define QTSPACE_CAMERA_H

#include "Node.h"
#include "Common/Consts.h"
#include "Common/TypeDef.h"

class Camera : public Node {
public:
    Camera(const std::string &name, const QVector3D &target = Vector3D::Origin);

    float fov() const;

    QVector3D target() const;

    float target_distance() const;

    virtual void ComputeTransformation();

    void Zoom(float distance);

    void ReSet();

    void Orbit(float pitch, float yaw, float roll);

private:
    static constexpr float max_pitch_ = 89.0f;
    static constexpr float min_pitch_ = -89.0f;

    float fov_;
    QVector3D target_;
    float target_distance_;
    QVector3D angel_;
    QVector3D init_direction_;
    QQuaternion quaternion_;

    void Rotate(float x, float y, float z) override;

    void Scale(float x, float y, float z) override;
};

#endif //QTSPACE_CAMERA_H
