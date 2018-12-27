#include "Resource/GraphNode/Node.h"

Node::Node(const string &name,
           NodeType::Type node_type) : name_(name),
                                       node_type_(node_type),
                                       dirty_(false),
                                       children_(0),
                                       translation_(0, 0, 0),
                                       rotation_(0, 0, 0),
                                       scale_(1, 1, 1),
                                       Resource() {
    ComputeTransformation();
}

const NodeType::Type Node::node_type() const { return node_type_; }

const string Node::name() const { return name_; }

size_t Node::children_size() const { return children_.size(); }

kNodePtr Node::GetChild(size_t index) const {
    if (index > children_.size() - 1) return nullptr;
    return children_[index];
}

void Node::AddChild(const NodePtr &child) { children_.push_back(child); }

void Node::ComputeTransformation() {
    transformation_.setToIdentity();
    transformation_.translate(translation_);
    transformation_.rotate(QQuaternion::fromEulerAngles(rotation_));
    transformation_.scale(scale_);
    dirty_ = false;
}

QMatrix4x4 Node::transformation() const {
    if (dirty_) const_cast<Node *>(this)->ComputeTransformation();
    return transformation_;
}

void Node::Translate(float x, float y, float z) {
    translation_ += QVector3D(x, y, z);
    dirty_ = true;
}

void Node::Scale(float x, float y, float z) {
    scale_ *= QVector3D(x, y, x);
    dirty_ = true;
}

void Node::Rotate(float x, float y, float z) {
    rotation_ = QQuaternion::fromEulerAngles(QVector3D(x, y, z)).rotatedVector(rotation_);
    dirty_ = true;
}

Node::~Node() {}
