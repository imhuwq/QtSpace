#ifndef QTSPACE_SCENEANIMATOR_H
#define QTSPACE_SCENEANIMATOR_H

#include "Common/TypeDef.h"
#include "Resource/Scene.h"
#include "GLRender/MainLoop.h"

using namespace std;

class SceneAnimator {
public:
	explicit SceneAnimator(ScenePtr scene);

	void Animate(kStatePtr state, int frame_time_delta, QOpenGLFunctionsPtr gl_functions_);

private:
	ScenePtr scene_ = nullptr;
	QTimePtr anim_timer_ = nullptr;
	int current_anim_time_ = 0;
	int last_anim_time_ = 0;
};

#endif // QTSPACE_SCENEANIMATOR_H