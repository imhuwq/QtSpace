#ifndef QTSPACE_CAMERA_H
#define QTSPACE_CAMERA_H

#include "Node.h"

class Camera : public Node {
public:
    Camera(const string &name,
           NodeType::Type node_type = NodeType::kCamera);

    float fov();

    void Translate(float x, float y, float z) override;

    void LookAt(float x, float y, float z);

private:
    float fov_;

    void Rotate(float x, float y, float z) override;

    void Scale(float x, float y, float z) override;
};

#endif //QTSPACE_CAMERA_H
