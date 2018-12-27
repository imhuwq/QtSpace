#include "Resource/GraphNode/Camera.h"

Camera::Camera(const string &name,
               NodeType::Type node_type) : Node(name, node_type),
                                           fov_(12.0f) {
    Translate(0, 0, 25);
}

float Camera::fov() { return fov_; }

void Camera::Translate(float x, float y, float z) { Node::Translate(-x, -y, -z); }

void Camera::LookAt(float x, float y, float z) {
    transformation_.setToIdentity();
    transformation_.lookAt(translation_, QVector3D(x, y, z), QVector3D(0, 1, 0));
    dirty_ = false;
}

void Camera::Rotate(float x, float y, float z) {}

void Camera::Scale(float x, float y, float z) {}
