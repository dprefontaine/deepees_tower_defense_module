#ifndef TOWER_BULLET_DATA_H_INCLUDED
#define TOWER_BULLET_DATA_H_INCLUDED

#include "enemy.h"

//BLUEPRINT FOR BULLETS

enum BULLET_TYPE{
    BULLET_TYPE_TARGET,
    BULLET_TYPE_HITBOX,
    BULLET_TYPE_HITBOX_DIRECTED,
    BULLET_TYPE_INCOME
};

struct tower_bullet_data{
public:
    tower_bullet_data(){};
    ~tower_bullet_data(){};

    int get_attack(){
        int stat_to_return;

        if (bullet_type == BULLET_TYPE_INCOME){
            stat_to_return = 0;
        } else {
            stat_to_return = bullet_damage;
        }

        if (!bullets_to_create_after.empty()){
            for (unsigned int i = 0; i < bullets_to_create_after.size(); i++){
                stat_to_return+=bullets_to_create_after.at(i).get_attack();
            }
        }

        return stat_to_return;
    };

    void update_attack(int degree){
        if (bullet_damage != 0)
            bullet_damage+=degree;

        if (!bullets_to_create_after.empty()){
            for (unsigned int i = 0; i < bullets_to_create_after.size(); i++){
                bullets_to_create_after.at(i).update_attack(degree);
            }
        }
    };

    std::string bullet_name = "";
    std::string bullet_image = "";

    int bullet_damage = 0;
    BULLET_DAMAGE_TYPE bullet_damage_type = DAMAGE_TYPE_NORMAL;
    BULLET_TYPE bullet_type = BULLET_TYPE_TARGET;

    int bullet_speed = 0;

    int bullet_radius = 0;

    //FOR HITBOX BULLETS
    int bullet_x_speed = 0;
    int bullet_y_speed = 0;

    unsigned int duration = 0;

    int threshold_hits = 100;

    //FOR BULLET EFFECTS
    std::vector<debuff_data> bullet_debuffs = std::vector<debuff_data>();
    std::vector<tower_bullet_data> bullets_to_create_after = std::vector<tower_bullet_data>();
};

#endif // TOWER_BULLET_DATA_H_INCLUDED
