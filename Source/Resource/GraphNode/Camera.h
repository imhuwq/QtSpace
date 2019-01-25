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

    void ComputeTransformation() override;

    void Zoom(float distance);

    void Orbit(float around_y_angle, float around_x_angle);

private:
    float fov_;

    QVector3D target_;
    QVector3D direction_;
    QVector3D right_;
    QVector3D up_;

    void Rotate(float x, float y, float z) override;

    void Scale(float x, float y, float z) override;
};

typedef shared_ptr<Camera> CameraPtr;
typedef shared_ptr<const Camera> kCameraPtr;

#endif //QTSPACE_CAMERA_H
