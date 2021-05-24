#ifndef ENEMY_DATA_H_INCLUDED
#define ENEMY_DATA_H_INCLUDED

#include "buff_data.h"

//SERVES AS A BLUEPRINT FOR ENEMIES
enum ENEMY_ARMOR_TYPE {
    ARMOR_TYPE_BASIC,
    ARMOR_TYPE_FIRE,
    ARMOR_TYPE_ICE,
    ARMOR_TYPE_WIND,
    ARMOR_TYPE_ELECTRIC,
    ARMOR_TYPE_MAGIC,
    ARMOR_TYPE_DIVINE
};

enum BULLET_DAMAGE_TYPE{
    DAMAGE_TYPE_NORMAL,
    DAMAGE_TYPE_FIRE,
    INCOME_TYPE_METAL,
    INCOME_TYPE_WOOD,
    INCOME_TYPE_CRYSTAL
};

struct enemy_data{
public:
    enemy_data(){}
    ~enemy_data(){}

    int enemy_hp_base = 0;
    int enemy_hp_scale = 0;
    int enemy_regen_base = 0;  ///THIS IS PER SECOND
    int enemy_regen_scale = 0;

    int enemy_speed_base = 0;
    int enemy_speed_scale = 0;

    int enemy_armor_base = 0;
    int enemy_armor_scale = 0;
    ENEMY_ARMOR_TYPE enemy_armor_type = ARMOR_TYPE_BASIC;

    int enemy_metal_bounty_base = 0;
    int enemy_metal_bounty_scale = 0;

    int enemy_wood_bounty_base = 0;
    int enemy_wood_bounty_scale = 0;

    int enemy_crystal_bounty_base = 0;
    int enemy_crystal_bounty_scale = 0;

    std::string enemy_name = "";
    std::string enemy_image_source = "";
};


#endif // ENEMY_DATA_H_INCLUDED
