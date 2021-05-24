#ifndef CIRC_HITBOX_H_INCLUDED
#define CIRC_HITBOX_H_INCLUDED

#include "rect_hitbox.h"
#include <cmath>

enum CIRCLE_CONTACT{
    CIRCLE_CONTACT_NONE,
    CIRCLE_CONTACT_HORIZONTAL,
    CIRCLE_CONTACT_VERTICAL,
    CIRCLE_CONTACT_DIAGONAL,
    CIRCLE_CONTACT_TOTAL
};

class circle_hitbox : public hitbox{
public:
    circle_hitbox(int x, int y, int radius, int contact_id) : hitbox(contact_id){
        position = point(x, y);
        circle_hitbox::radius = radius;
    }

    ~circle_hitbox();

    void move_x(int add_x);
    void move_y(int add_y);
    void set_x(int new_x);
    void set_y(int new_y);
    void move_back();

    int get_x();
    int get_y();

    int get_x_moveback();
    int get_y_moveback();

    void set_radius(int new_radius);
    int get_radius();

    bool check_contact_with_rect(rect_hitbox* other_hitbox);
    bool check_contact_with_circle(circle_hitbox* other_hitbox);

    void set_contact_id(int new_id);
    int get_contact_id();

    int get_contact_hit();

private:
    point position;

    int radius;
};

#endif // CIRC_HITBOX_H_INCLUDED
