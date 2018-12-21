#ifndef QTSPACE_CAMERA_H
#define QTSPACE_CAMERA_H

#include "Resource/GraphNode/Node.h"

class Camera : public Node {
public:
    Camera(const string &name,
           NodeType::Type node_type = NodeType::kCamera) : Node(name, node_type),
                                                           fov_(12.0f) {
        Translate(0, 0, 25);
    }

    float fov() { return fov_; }

    void Translate(float x, float y, float z) { Node::Translate(-x, -y, -z); }

    void LookAt(float x, float y, float z) {
        transformation_.setToIdentity();
        transformation_.lookAt(translation_, QVector3D(x, y, z), QVector3D(0, 1, 0));
        dirty_ = false;
    }

private:
    float fov_;

    void Rotate(float x, float y, float z) {}

    void Scale(float x, float y, float z) {}
};

#endif //QTSPACE_CAMERA_H
