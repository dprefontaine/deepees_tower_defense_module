#include "hitbox.h"

hitbox::hitbox(int contact_id){
    hitbox::contact_id = contact_id;
    hit_id = 0;
}

hitbox::~hitbox(){

}

void hitbox::set_contact_id(int new_id){
    contact_id = new_id;
}

int hitbox::get_contact_id(){
    return contact_id;
}

int hitbox::get_contact_hit(){
    return hit_id;
}
