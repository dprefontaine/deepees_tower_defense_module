#ifndef BUFF_AURA_H_INCLUDED
#define BUFF_AURA_H_INCLUDED

#include "tower_bullet_data.h"
#include "resource.h"

struct buff_aura{
public:
    buff_aura(){};

    buff_data buff_to_give = buff_data(0,0,BUFF_ATTACK);

    circle_hitbox aura_hitbox = circle_hitbox(0,0,0,0);
};

#endif // BUFF_AURA_H_INCLUDED
