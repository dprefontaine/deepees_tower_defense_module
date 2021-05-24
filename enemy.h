#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "circ_hitbox.h"
#include "enemy_data.h"

//MODIFIED FROM MOVER MODULE

enum ENEMY_STATE{
    ENEMY_NOT_END,
    ENEMY_KILLED,
    ENEMY_FINISHED
};

enum ENEMY_DIRECTION{
    ENEMY_RIGHT,
    ENEMY_DOWN,
    ENEMY_LEFT,
    ENEMY_UP
};

float type_scale(ENEMY_ARMOR_TYPE armor_type, BULLET_DAMAGE_TYPE damage_type);
float reduction_scale(int armor);

class enemy{
public:
    enemy(int hp, int regen, int armor, ENEMY_ARMOR_TYPE armor_type, int speed, int x, int y, int radius, std::string spot_name, std::string image_name, int metal_bounty, int wood_bounty, int crystal_bounty, int contact_id);
    ~enemy();

    bool update(unsigned int ticks);

    void set_path(std::vector<point> path_points);

    circle_hitbox* get_hitbox();

    bool at_end();
    bool is_dead();

    void calculate_damage(int damage_taken, BULLET_DAMAGE_TYPE damage_type);
    void add_debuff_to_queue(debuff_data new_debuff);

    int get_current_hp();
    int get_max_hp();

    std::string get_name();
    std::string get_image();

    ENEMY_STATE get_end_state();

    int get_metal_bounty();
    int get_wood_bounty();
    int get_crystal_bounty();

    void create_hp_bar();

    void remove_enemy_image();
    void activate_enemy_image();

    void draw_enemy();

private:
    void update_position();

    bool boundary_check();

    //FOR THE DEBUFF QUEUE
    void add_debuff(std::string debuff_data_name, debuff_data new_debuff);

    //FOR THE HP BAR
    void draw_hp_bar();
    void clear_hp_bar();

    void change_direction();
    void change_direction_animation(ENEMY_DIRECTION direction);
    bool has_reached_point();

    void add_enemy_image();

    int current_hp, max_hp;

    int enemy_regen;
    alarm regen_timer = alarm(1000);

    int enemy_armor;
    ENEMY_ARMOR_TYPE enemy_armor_type;

    circle_hitbox enemy_hitbox = circle_hitbox(0,0,0,0);

    //POSITIONS TO GO TO
    std::vector<point> positions_to = std::vector<point>();
    bool following_position;

    //MOTION
    float x_velocity, y_velocity;
    float x_velocity_directed, y_velocity_directed;

    //For smoother updating
    int previous_x_pos, previous_y_pos;
    float x_mov_add, y_mov_add;

    //For direction when moving
    float x_direction, y_direction;

    std::string enemy_name;
    std::string enemy_image;
    std::string enemy_hp_bar_name;

    //DEBUFFS
    std::queue<debuff_data> debuffs_to_add;
    std::map<std::string, debuff_data> debuffs;

    //TICKS
    unsigned int ticks_passed = 0;

    //END STATES AND BOUNTY
    ENEMY_STATE ending_state = ENEMY_NOT_END;
    int enemy_metal_bounty, enemy_wood_bounty, enemy_crystal_bounty;
};

#endif // ENEMY_H_INCLUDED
