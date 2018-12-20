#ifndef QTSPACE_NODE_H
#define QTSPACE_NODE_H

#include <string>
#include <vector>
#include <memory>

#include <QUuid>
#include <QMatrix4x4>
#include <QVector3D>

#include "Resource/Resource.h"

using namespace std;

class Node;

typedef shared_ptr<Node> NodePtr;
typedef shared_ptr<const Node> kNodePtr;

namespace NodeType {
    enum Type {
        kGeneral = 0,
        kCamera,
        kLight,
        kMeshInstance,
        kNumGraphNodeType
    };
}


class Node : public Resource {
public:
    explicit Node(const string &name,
                  NodeType::Type node_type = NodeType::kGeneral) : name_(name),
                                                                   node_type_(node_type),
                                                                   dirty_(false),
                                                                   children_(0),
                                                                   translation_(0, 0, 0),
                                                                   rotation_(0, 0, 0),
                                                                   scale_(1, 1, 1) {
        uuid_ = QUuid::createUuid().toString().toStdString();
        ComputeTransformation();
    }

    const NodeType::Type node_type() const { return node_type_; }

    const string name() const { return name_; }

    string uuid() const { return uuid_; }

    size_t children_size() const { return children_.size(); }

    kNodePtr GetChild(size_t index) const {
        if (index > children_.size() - 1) return nullptr;
        return children_[index];
    }

    void AddChild(const NodePtr &child) { children_.push_back(child); }

    void ComputeTransformation() {
        transformation_.setToIdentity();
        transformation_.translate(translation_);
        transformation_.rotate(QQuaternion::fromEulerAngles(rotation_));
        transformation_.scale(scale_);
        dirty_ = false;
    }

    QMatrix4x4 transformation() const {
        if (dirty_) const_cast<Node *>(this)->ComputeTransformation();
        return transformation_;
    }

    void Translate(float x, float y, float z) {
        translation_ += QVector3D(x, y, z);
        dirty_ = true;
    }

    void Scale(float x, float y, float z) {
        scale_ *= QVector3D(x, y, x);
        dirty_ = true;
    }

    void Rotate(float x, float y, float z) {
        rotation_ = QQuaternion::fromEulerAngles(QVector3D(x, y, z)).rotatedVector(rotation_);
        dirty_ = true;
    }

    virtual ~Node() {}

protected:
    string name_;
    string uuid_;
    NodeType::Type node_type_;
    vector<NodePtr> children_;

    bool dirty_;
    QVector3D translation_;
    QVector3D rotation_;
    QVector3D scale_;
    QMatrix4x4 transformation_;
};

#endif //QTSPACE_NODE_H
