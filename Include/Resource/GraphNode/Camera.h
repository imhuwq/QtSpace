#ifndef QTSPACE_CAMERA_H
#define QTSPACE_CAMERA_H

#include "Resource/GraphNode/Node.h"

class Camera : public Node {
public:
    Camera(const string &name,
           NodeType::Type node_type = NodeType::kCamera) : Node(name, node_type),
                                                           fov_(45.0f) {}

private:
    float fov_;
};

#endif //QTSPACE_CAMERA_H
