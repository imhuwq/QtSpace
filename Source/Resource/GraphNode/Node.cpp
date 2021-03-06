#include "Node.h"

using namespace std;

Node::Node(const string &name,
           NodeType::Type node_type) : name_(name),
                                       node_type_(node_type),
                                       dirty_(false),
                                       nodes_(0),
                                       translation_(0, 0, 0),
                                       rotation_(0, 0, 0),
                                       scale_(1, 1, 1),
                                       move_speed_(0),
                                       Resource() {
    ComputeTransformation();
}

const NodeType::Type Node::node_type() const { return node_type_; }

const string Node::name() const { return name_; }

size_t Node::node_size() const { return nodes_.size(); }

vector<kNodePtr> Node::nodes() const {
    vector<kNodePtr> nodes_vec;
    for (auto node: nodes_) nodes_vec.push_back(node);
    return nodes_vec;
}

vector<NodePtr> Node::nodes() { return nodes_; }

void Node::AddNode(const NodePtr &child) { nodes_.push_back(child); }

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

void Node::TranslateTo(const QVector3D &translation) {
    translation_ = translation;
    dirty_ = true;
}

void Node::TranslateTo(float x, float y, float z) {
    translation_ = QVector3D(x, y, z);
    dirty_ = true;
}

void Node::Scale(float x, float y, float z) {
    scale_ *= QVector3D(x, y, x);
    dirty_ = true;
}

void Node::ScaleTo(float x, float y, float z) {
    scale_ = QVector3D(x, y, z);
    dirty_ = true;
}

void Node::Rotate(float pitch, float yaw, float row) {
    rotation_ += QVector3D(pitch, yaw, row);
    dirty_ = true;
}

void Node::RotateTo(float pitch, float yaw, float row) {
    rotation_ = QVector3D(pitch, yaw, row);
    dirty_ = true;
}

QVector3D Node::translation() const { return translation_; }

QVector3D Node::rotation() const { return rotation_; }

QVector3D Node::scale() const { return scale_; }

float Node::move_speed() const { return move_speed_; }

Node::~Node() {}
