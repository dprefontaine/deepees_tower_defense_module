#ifndef TD_TABLE_H_INCLUDED
#define TD_TABLE_H_INCLUDED

//THIS IS FOR STORING TOWERS, TOWER BULLETS, ENEMIES, AND LEVELS

#include "grid_manager.h"

#include "enemy.h"
#include "tower.h"

enum td_module_build_button_selection{
    BUILD_BUTTON_ONE,
    BUILD_BUTTON_TWO,
    BUILD_BUTTON_THREE,
    BUILD_BUTTON_FOUR,
    BUILD_BUTTON_FIVE,
    BUILD_BUTTON_SIX,
    BUILD_BUTTON_SEVEN,
    BUILD_BUTTON_EIGHT,
    BUILD_BUTTON_NINE,
    BUILD_BUTTON_NONE
};

typedef std::pair<td_module_build_button_selection, std::string> TOWER_MAPPING;

struct td_level_loader{
public:
    td_level_loader();
    ~td_level_loader();

    void read_terrain(std::string terrain_name, std::string terrain_file_name);
    void set_map(std::queue<int>* map_to_load, std::string map_name);

    std::queue<std::string> get_wave(std::string wave_data_name);

    std::vector<TOWER_MAPPING> get_tower_race(std::string race_name);

    tower_data get_tower_data(std::string tower_data_name);
    tower_bullet_data get_bullet_data(std::string bullet_data_name);

    enemy_data get_enemy_data(std::string enemy_data_name);

private:
    void load_towers();
    void load_bullets();
    void load_debuffs();
    void load_auras();

    void load_tower_races();

    void load_enemy_types();
    void load_waves();

    void load_terrains();

    std::map<std::string, tower_data> td_tower_types;
    std::map<std::string, tower_bullet_data> td_tower_bullets;
    std::map<std::string, debuff_data> td_bullet_debuffs;
    std::map<std::string, buff_aura> buff_auras;

    std::map<std::string, std::vector<TOWER_MAPPING>> tower_races;

    std::map<std::string, enemy_data> td_enemy_types;
    std::map<std::string, std::queue<std::string>> td_enemy_waves;

    std::map<std::string, std::vector<int>> td_terrains;
};

#endif // TD_TABLE_H_INCLUDED
