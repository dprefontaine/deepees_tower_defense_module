#include "circ_hitbox.h"

circle_hitbox::~circle_hitbox(){

}

void circle_hitbox::move_x(int add_x){
    position.set_x(position.get_x()+add_x);
}

void circle_hitbox::move_y(int add_y){
    position.set_y(position.get_y()+add_y);
}

void circle_hitbox::move_back(){
    move_x(moveback.get_x());
    move_y(moveback.get_y());
}

void circle_hitbox::set_x(int new_x){
    position.set_x(new_x);
}

void circle_hitbox::set_y(int new_y){
    position.set_y(new_y);
}

int circle_hitbox::get_x(){
    return position.get_x();
}

int circle_hitbox::get_y(){
    return position.get_y();
}

int circle_hitbox::get_x_moveback(){
    return moveback.get_x();
}

int circle_hitbox::get_y_moveback(){
    return moveback.get_y();
}

void circle_hitbox::set_radius(int new_radius){
    radius = new_radius;
}

int circle_hitbox::get_radius(){
    return radius;
}

bool circle_hitbox::check_contact_with_rect(rect_hitbox* other_hitbox){
    //find closest point
    int other_x, other_y, magnitude_x, magnitude_y;
    CIRCLE_CONTACT contact_flag = CIRCLE_CONTACT_NONE;

    //DETERMINING RELATIVE SIDES FACING
    bool to_left = false;
    bool to_top = false;

    int horz_sign = 1;
    int vert_sign = 1;

    //CHECK X BOUNDS
    if (position.get_x() > other_hitbox->get_rect()->x){
        if (position.get_x() < (other_hitbox->get_rect()->x + other_hitbox->get_rect()->w)){
            other_x = position.get_x();
            contact_flag = CIRCLE_CONTACT_VERTICAL;
        } else
            other_x = (other_hitbox->get_rect()->x + other_hitbox->get_rect()->w);
    } else {
        other_x = other_hitbox->get_rect()->x;
        to_left = true;
    }

    //CHECK Y BOUNDS
    if (position.get_y() > other_hitbox->get_rect()->y){
        if (position.get_y() < (other_hitbox->get_rect()->y + other_hitbox->get_rect()->h)){
            other_y = position.get_y();

            if (contact_flag == CIRCLE_CONTACT_VERTICAL)
                contact_flag = CIRCLE_CONTACT_DIAGONAL;
            else
                contact_flag = CIRCLE_CONTACT_HORIZONTAL;

        } else
            other_y = (other_hitbox->get_rect()->y + other_hitbox->get_rect()->h);
    } else {
        other_y = other_hitbox->get_rect()->y;
        to_top = true;
    }

    //GETTING SQUARES
    magnitude_x = abs((position.get_x()-other_x)*(position.get_x()-other_x));
    magnitude_y = abs((position.get_y()-other_y)*(position.get_y()-other_y));

    //CHECK CONTACT
    if (!((magnitude_x + magnitude_y) < (radius*radius))){
        contact_flag = CIRCLE_CONTACT_NONE;
    } else {
        //SET HIT TO WHATEVER THE OTHER OBJECT'S ID WAS
        hit_id = other_hitbox->get_contact_id();
    }

    //SETTING MOVE BACK IF CONTACTED
    if (contact_flag != CIRCLE_CONTACT_NONE){
        if (to_left)
            horz_sign = -1;

        if (to_top)
            vert_sign = -1;

        switch (contact_flag){
        case CIRCLE_CONTACT_DIAGONAL:
            moveback.set_x((horz_sign*radius - (position.get_x()-other_x)));
            moveback.set_y((vert_sign*radius - (position.get_y()-other_y)));
            break;
        case CIRCLE_CONTACT_VERTICAL:
            moveback.set_x(0);
            moveback.set_y((vert_sign*radius - (position.get_y()-other_y)));
            break;
        case CIRCLE_CONTACT_HORIZONTAL:
            moveback.set_x((horz_sign*radius - (position.get_x()-other_x)));
            moveback.set_y(0);
            break;
        case CIRCLE_CONTACT_NONE:
        case CIRCLE_CONTACT_TOTAL:
            break;
        }
    }

    return (contact_flag != CIRCLE_CONTACT_NONE);
}

bool circle_hitbox::check_contact_with_circle(circle_hitbox* other_hitbox){
    //GET THE MAGNITUDE BETWEEN BOTH POINTS FIRST
    int diff_x, diff_y;
    diff_x = get_x() - other_hitbox->get_x();
    diff_y = get_y() - other_hitbox->get_y();

    int point_magnitude = abs(diff_x*diff_x+diff_y*diff_y);

    if (point_magnitude != 0){
        point_magnitude = sqrt(point_magnitude);

        //reduce by other distance
        point_magnitude-=other_hitbox->get_radius();

        return (radius >= point_magnitude);
    } else
        return true;
}

void circle_hitbox::set_contact_id(int new_id){
    contact_id = new_id;
}

int circle_hitbox::get_contact_id(){
    return contact_id;
}

int circle_hitbox::get_contact_hit(){
    return hit_id;
}
