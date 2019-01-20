#ifndef QTSPACE_CAMERA_H
#define QTSPACE_CAMERA_H

#include "Node.h"
#include "Common/Consts.h"


class Camera : public Node {
public:
    Camera(const string &name, const QVector3D &target = Vector3D::Origin);

    float fov() const;

    QVector3D target() const;

    void Translate(float x, float y, float z) override;

    QVector3D direction() const;

    QVector3D up() const;

    QVector3D right() const;

    void ComputeTransformation() override;

    void LookAt(const QVector3D &target);

    void OrbitAround(const QVector3D &target, float axis_y_angle, float axis_x_angle);

private:
    float fov_;

    QVector3D target_;

    void Rotate(float x, float y, float z) override;

    void Scale(float x, float y, float z) override;
};

#endif //QTSPACE_CAMERA_H
