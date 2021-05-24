#include "rect_hitbox.h"

rect_hitbox::~rect_hitbox(){

}

SDL_Rect* rect_hitbox::get_rect(){
    return &rect_box;
}

bool rect_hitbox::check_contact_with_rect(rect_hitbox* other_hitbox){
    SDL_Rect* other_rect = other_hitbox->get_rect();
    bool x_contact, y_contact;
    x_contact = y_contact = false;

    //CHECK IF X SPANS ARE IN BOUND OF EACHOTHER
    if ((rect_box.x > other_rect->x && rect_box.x < (other_rect->x + other_rect->w))){
        //SET UP X DISTANCE
        x_contact = true;
        moveback.set_x(rect_box.x - (other_rect->x + other_rect->w/2));

    } else if ((rect_box.x + rect_box.w) > other_rect->x && (rect_box.x + rect_box.w) < (other_rect->x + other_rect->w)){
        x_contact = true;
        moveback.set_x((rect_box.x + rect_box.w) - (other_rect->x + other_rect->w/2));
    }

    //CHECK Y SPAN
    if ((rect_box.y > other_rect->y && rect_box.y < (other_rect->y + other_rect->h))){
        //SET UP Y DISTANCE
        y_contact = true;
        moveback.set_y(rect_box.y - (other_rect->y + other_rect->h/2));
    } else if (((rect_box.y + rect_box.h) > other_rect->y && (rect_box.y + rect_box.h) < (other_rect->y + other_rect->h))){
        y_contact = true;
        moveback.set_y((rect_box.y + rect_box.h) - (other_rect->y + other_rect->h/2));
    }

    other_rect = NULL;

    return (x_contact && y_contact);
}
