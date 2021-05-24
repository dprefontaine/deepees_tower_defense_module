#ifndef RECT_HITBOX_H_INCLUDED
#define RECT_HITBOX_H_INCLUDED

#include "hitbox.h"

class rect_hitbox: public hitbox{
public:
    rect_hitbox(int x, int y, int w, int h, int contact_id) : hitbox(contact_id){
        rect_box = {x, y, w, h};
    }

    ~rect_hitbox();

    void set_rect();
    SDL_Rect* get_rect();

    bool check_contact_with_rect(rect_hitbox* other_hitbox);

private:
    SDL_Rect rect_box;
};

#endif // RECT_HITBOX_H_INCLUDED
