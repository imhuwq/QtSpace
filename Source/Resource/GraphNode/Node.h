#ifndef QTSPACE_NODE_H
#define QTSPACE_NODE_H

#include <string>

#include <QUuid>
#include <QMatrix4x4>
#include <QVector3D>

#include "Common/Consts.h"
#include "Common/TypeDef.h"
#include "Resource/Resource.h"

class Node : public Resource {
public:
    explicit Node(const std::string &name,
                  NodeType::Type node_type = NodeType::kGeneral);

    const NodeType::Type node_type() const;

    const std::string name() const;

    size_t node_size() const;

	std::vector<kNodePtr> nodes() const;

	std::vector<NodePtr> nodes();

    void AddNode(const NodePtr &child);

    virtual void ComputeTransformation();

    QMatrix4x4 transformation() const;

    virtual void Translate(float x, float y, float z);

    void TranslateTo(const QVector3D& translation);

    void TranslateTo(float x, float y, float z);

    virtual void Scale(float x, float y, float z);

    void ScaleTo(float x, float y, float z);

    virtual void Rotate(float pitch, float yaw, float row);

    virtual void RotateTo(float pitch, float yaw, float row);

    QVector3D translation() const;

    QVector3D rotation() const;

    QVector3D scale() const;

    float move_speed() const;

    virtual ~Node();

protected:
	std::string name_;
    NodeType::Type node_type_;
	std::vector<NodePtr> nodes_;

    bool dirty_;
    QVector3D translation_;
    QVector3D rotation_;
    QVector3D scale_;
    QMatrix4x4 transformation_;

    float move_speed_;
};

#endif //QTSPACE_NODE_H
