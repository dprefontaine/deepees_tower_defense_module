#ifndef GRID_CAMERA_H_INCLUDED
#define GRID_CAMERA_H_INCLUDED

class grid_camera{
public:
    grid_camera();
    ~grid_camera();

    int set_camera_move_up();
    int set_camera_move_down();
    int set_camera_move_left();
    int set_camera_move_right();

    int release_camera_up();
    int release_camera_down();
    int release_camera_left();
    int release_camera_right();

private:
    bool MOVE_UP;
    bool MOVE_DOWN;
    bool MOVE_LEFT;
    bool MOVE_RIGHT;
};

#endif // GRID_CAMERA_H_INCLUDED
