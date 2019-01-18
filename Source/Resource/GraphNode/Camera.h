#ifndef QTSPACE_CAMERA_H
#define QTSPACE_CAMERA_H

#include "Node.h"

class Camera : public Node {
public:
    Camera(const string &name);

    float fov();

    void Translate(float x, float y, float z) override;

    QVector3D direction() const;

    QVector3D up() const;

    QVector3D right() const;

    void LookAt(float x, float y, float z);

private:
    float fov_;

    void Rotate(float x, float y, float z) override;

    void Scale(float x, float y, float z) override;
};

#endif //QTSPACE_CAMERA_H
