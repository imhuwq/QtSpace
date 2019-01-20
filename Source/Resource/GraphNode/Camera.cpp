#include "Camera.h"
#include "Common/Consts.h"

Camera::Camera(const string &name, const QVector3D &target) : Node(name, NodeType::kCamera),
                                                              target_(target),
                                                              fov_(12.0f) {
    Translate(0, 0, 25);
    move_speed_ = 2.0f;
}

float Camera::fov() const { return fov_; }

QVector3D Camera::target() const { return target_; }

void Camera::Translate(float x, float y, float z) { Node::Translate(-x, -y, -z); }

QVector3D Camera::direction() const {
    QVector3D dir = QVector3D(0, 0, 0) - translation_;
    dir.normalize();
    return dir;
}

QVector3D Camera::right() const {
    QVector3D dir = QVector3D(0, 0, 0) - translation_;
    QVector3D rt = QVector3D::crossProduct(QVector3D(0, 1, 0), dir);
    rt.normalize();
    return rt;
}

QVector3D Camera::up() const {
    QVector3D dir = QVector3D(0, 0, 0) - translation_;
    QVector3D rt = QVector3D::crossProduct(QVector3D(0, 1, 0), dir);
    QVector3D u = QVector3D::crossProduct(dir, rt);
    u.normalize();
    return u;
}

void Camera::ComputeTransformation() {LookAt(target_);}

void Camera::LookAt(const QVector3D &target) {
    transformation_.setToIdentity();
    transformation_.lookAt(translation_, target, Vector3D::Up);
    dirty_ = false;
    target_ = target;
}

void Camera::OrbitAround(const QVector3D &target, float axis_y_angle, float axis_x_angle) {
    // FIXME: 绕 x 轴旋转的问题
    qDebug() << translation() << transformation();
    static QMatrix4x4 y_axis_rotation_matrix, x_axis_rotation_matrix;

    y_axis_rotation_matrix.setToIdentity();
    x_axis_rotation_matrix.setToIdentity();
    y_axis_rotation_matrix.rotate(axis_y_angle, Vector3D::Up);
    x_axis_rotation_matrix.rotate(axis_x_angle, Vector3D::Right);

    QVector3D camera_direction = translation() - Vector3D::Origin;
    camera_direction = y_axis_rotation_matrix * x_axis_rotation_matrix * camera_direction;
    QVector3D camera_translation = camera_direction + Vector3D::Origin;
    TranslateTo(camera_translation.x(), camera_translation.y(), camera_translation.z());
    LookAt(Vector3D::Origin);
}

void Camera::Rotate(float x, float y, float z) {}

void Camera::Scale(float x, float y, float z) {}
