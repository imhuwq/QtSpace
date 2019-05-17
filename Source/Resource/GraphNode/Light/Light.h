#ifndef QTSPACE_LIGHT_H
#define QTSPACE_LIGHT_H

#include <QColor>

#include "Common/Consts.h"
#include "Common/TypeDef.h"
#include "Resource/GraphNode/Node.h"

class Light : public Node {
public:
    Light(const std::string &name, LightType::Type light_type);

    LightType::Type light_type() const;

	std::vector<float> color() const;

    void SetColor(float r, float g, float b);

    float strength() const;

    void SetStrength(float strength);

    virtual ~Light() = 0;

protected:
    LightType::Type light_type_;
	std::vector<float> color_;
    float strength_;
};

#endif //QTSPACE_LIGHT_H
