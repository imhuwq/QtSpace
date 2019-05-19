#ifndef QTSPACE_STATE_H
#define QTSPACE_STATE_H

#include "Common/TypeDef.h"

class State{
public:
    State();
    int window_width = 1000;
    int window_height = 1000;

    bool left_mouse_pressed = false;
    bool mid_mouse_pressed = false;
    bool right_mouse_pressed = false;

    int mouse_x_last = 0;
    int mouse_y_last = 0;
    int mouse_x_delta = 0;
    int mouse_y_delta = 0;
    int mouse_z_delta = 0;

    bool animating = false;
    bool camera_orbiting = false;
    bool camera_zooming = false;
    bool camera_resetting = false;
};


#endif //QTSPACE_STATE_H
