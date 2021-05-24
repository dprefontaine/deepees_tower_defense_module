#ifndef TOWER_H_INCLUDED
#define TOWER_H_INCLUDED

#include "td_bullet.h"

#include "tower_data.h"

#include <sstream>

enum TARGET_BEHAVIOUR{
    TOWER_TARGET_FIRST,
    TOWER_TARGET_LAST,
    TOWER_TARGET_CLOSEST,
    TOWER_TARGET_FURTHEST
};

class tower{
public:
    tower(int x, int y, int radius, int index, int attack_rate, TARGET_BUILDOVER tile_type, int previous_tile_value, std::string display_name, std::string name, std::string image, tower_bullet_data resulting_bullet);
    ~tower();

    //void set_buffs(std::vector<td_buffs>* buffs);
    void set_bullets(bullet_space* bullets);
    void set_towers(std::vector<tower>* towers);
    void set_enemies(std::map<int, enemy>* enemies);
    void set_wave_size(unsigned int new_size);

    void add_tower_aura(buff_aura new_aura);

    void add_buff_to_queue(buff_data buff);

    void update(unsigned int ticks);

    circle_hitbox* get_range();
    std::vector<buff_aura> get_auras();
    std::string get_display_name();
    std::string get_name();
    std::string get_image();
    int get_damage();
    int get_attack_rate();
    TARGET_BUILDOVER get_buildover_type();
    int get_old_tile();

private:
    void update_buffs();
    void add_buff(std::string buff_name, buff_data buff);

    void set_target();
    bool target_within_range();

    void attacking();

    circle_hitbox tower_hitbox = circle_hitbox(0,0,0,0);
    std::string tower_name = "";
    std::string display_tower_name = "";
    std::string image_name = "";
    int tower_attack_rate = 0;
    int attack_cd;
    TARGET_BUILDOVER new_tower_tile = TOWER_UNPHASEABLE;
    int previous_tower_tile = 0;

    //BUFFS (HAVE TO TRACK OTHER TOWERS FOR THIS
    std::vector<tower>* towers = NULL;
    std::vector<buff_aura> auras;
    std::queue<buff_data> buffs_to_add;
    std::map<std::string, buff_data> td_buffs;

    //BULLETS
    bullet_space* td_bullets = NULL;
    tower_bullet_data tower_bullet;

    //TRACKING ENEMIES
    std::map<int, enemy>* td_enemies = NULL;
    unsigned int enemy_targeted = -1;
    unsigned int wave_size = 10;
};

#endif // TOWER_H_INCLUDED
