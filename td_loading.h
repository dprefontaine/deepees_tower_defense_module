#ifndef TD_LOADING_H_INCLUDED
#define TD_LOADING_H_INCLUDED

#include "td_module.h"

//FOR UI
void load_resource_icons();
void load_resource_icon(std::string icon_name, std::string icon_link, int x_pos, int y_pos);

void load_grid_tiles();

void load_destination_points();

void load_enemies();
void load_enemy(std::string enemy_name, std::string enemy_image_directory);

void load_towers();
void load_tower_selection();
void load_tower(std::string tower_name, std::string tower_image_directory);

void load_bullets();
void load_bullet(std::string bullet_name, std::string bullet_image_directory);

void load_debuffs();
void load_debuff(std::string debuff_name, std::string debuff_image_directory);

#endif // TD_LOADING_H_INCLUDED
