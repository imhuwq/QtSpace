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
                                                                   children_(0),
                                                                   position_(0, 0, 0),
                                                                   rotation_(0, 0, 0),
                                                                   scale_(1, 1, 1) {
        uuid_ = QUuid::createUuid().toString().toStdString();
        transformation_.setToIdentity();
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

    QMatrix4x4 transformation() const { return transformation_; }

    virtual ~Node() {}

protected:
    string name_;
    string uuid_;
    NodeType::Type node_type_;
    vector<NodePtr> children_;

    QVector3D position_;
    QVector3D rotation_;
    QVector3D scale_;
    QMatrix4x4 transformation_;
};

#endif //QTSPACE_NODE_H
