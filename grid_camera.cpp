#include "grid_camera.h"

grid_camera::grid_camera(){
    MOVE_UP = MOVE_DOWN = MOVE_LEFT = MOVE_RIGHT = false;
}

grid_camera::~grid_camera(){

}

int grid_camera::set_camera_move_up(){
    MOVE_UP = true;

    return 0;
}

int grid_camera::set_camera_move_down(){
    MOVE_DOWN = true;

    return 0;
}

int grid_camera::set_camera_move_left(){
    MOVE_LEFT = true;

    return 0;
}

int grid_camera::set_camera_move_right(){
    MOVE_RIGHT = true;

    return 0;
}

int grid_camera::release_camera_up(){
    MOVE_UP = false;

    return 0;
}

int grid_camera::release_camera_down(){
    MOVE_DOWN = false;

    return 0;
}

int grid_camera::release_camera_left(){
    MOVE_LEFT = false;

    return 0;
}

int grid_camera::release_camera_right(){
    MOVE_RIGHT = false;

    return 0;
}
