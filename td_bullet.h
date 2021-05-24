#ifndef TD_BULLET_H_INCLUDED
#define TD_BULLET_H_INCLUDED

#include "buff_aura.h"

enum BULLET_STATE{
    BULLET_NOT_AT_END,
    BULLET_REACHED_ENEMY,
    BULLET_ENEMY_GONE,
    BULLET_IS_INCOME
};

//NEED TO DECLARE BEFOREHAND SINCE BOTH CLASSES ARE INTERDEPENDENT ON EACHOTHER
class bullet_space;

class td_bullet{
public:
    //FOR HOMING BULLET
    td_bullet(int damage, BULLET_DAMAGE_TYPE damage_type, BULLET_TYPE type, int speed, int initial_x, int initial_y, int radius, int targeted_enemy,
              std::string name, std::string image,
              std::vector<tower_bullet_data> after_bullets,
              bullet_space* bullets, std::map<int, enemy>* enemies);

    ~td_bullet();

    //FOR ADDING DEBUFFS
    void insert_debuff(debuff_data debuff_to_insert);

    //FOR HITBOX
    void set_velocity(int x_vel, int y_vel);
    void set_expiration(unsigned int ticks);
    void set_hit_threshold(int new_threshold_hits);

    //ORIGINALLY PRIVATE, BUT MADE IT PUBLIC FOR DIRECTED HITBOX
    void update_direction();

    void set_target_enemy();

    bool update(unsigned int ticks);
    void deal_damage();

    void destroy_bullet();

    int get_income();
    BULLET_DAMAGE_TYPE get_income_type();

    circle_hitbox* get_hitbox();

    BULLET_STATE get_end_state();

    std::string get_name();
    std::string get_image();

private:
    bool has_reached_enemy();
    bool has_expired();
    void create_after_bullets();

    int bullet_damage;
    BULLET_DAMAGE_TYPE bullet_damage_type;

    BULLET_TYPE bullet_type;

    int bullet_speed;

    //THESE ARE PRIMARILY FOR THE HITBOX BULLET
    alarm bullet_expiration = alarm(1);
    std::vector<int> hit_enemies = std::vector<int>();
    unsigned int max_hits = 0;

    //MOTION
    float x_velocity_directed, y_velocity_directed;

    //For smoother updating
    float x_mov_add, y_mov_add;

    //For direction when moving
    float x_direction, y_direction;

    circle_hitbox bullet_hitbox = circle_hitbox(0,0,0,0);

    std::string bullet_spot_name;
    std::string bullet_image;

    std::vector<tower_bullet_data> bullets_after_data = std::vector<tower_bullet_data>();

    std::map<std::string, debuff_data> bullet_debuffs;

    bullet_space* td_bullets = NULL;
    std::map<int, enemy>* td_enemies;
    int target_enemy;

    //td_impact bullet_impact;

    BULLET_STATE end_state = BULLET_NOT_AT_END;
};

class bullet_space{
public:
    bullet_space(){total_bullets = 0;
                   bullets = std::vector<td_bullet>();};
    ~bullet_space(){std::vector<td_bullet>().swap(bullets);
                    td_bullets = NULL;
                    td_enemies = NULL;
                    td_resources = NULL;};

    void update(unsigned int ticks){
        while (!bullets_to_add.empty()){
            bullets.push_back(bullets_to_add.front());
            bullets_to_add.pop();
        }

        if (!bullets.empty()){
            for (unsigned int i = 0; i < bullets.size(); i++){
                //RETURNS TRUE IF ABOUT TO TERMINATE
                if (bullets.at(i).update(ticks)){

                    //ADD INCOME IF AN INCOME BULLET
                    if (bullets.at(i).get_end_state() == BULLET_IS_INCOME){
                        get_income(i);
                    }

                    kill_bullet(i);
                }
            }
        }
    }

    void create_bullet(tower_bullet_data bullet_data, int enemy_targeted, int x_pos, int y_pos){
        extern main_controller* game;

        std::stringstream ss;

        ss << bullet_data.bullet_name << " " << total_bullets;

        //std::cout << "Attacking enemy " << enemy_targeted << " with " << ss.str() << std::endl;

        //CREATING BULLET
        td_bullet new_bullet = td_bullet(bullet_data.bullet_damage, bullet_data.bullet_damage_type,
                                        bullet_data.bullet_type,
                                        bullet_data.bullet_speed,
                                        x_pos, y_pos,
                                        bullet_data.bullet_radius, enemy_targeted,
                                        ss.str(), bullet_data.bullet_image, bullet_data.bullets_to_create_after,
                                        td_bullets, td_enemies);

        if (bullet_data.bullet_type == BULLET_TYPE_HITBOX){
            new_bullet.set_expiration(bullet_data.duration);
            new_bullet.set_velocity(bullet_data.bullet_x_speed, bullet_data.bullet_y_speed);
            new_bullet.set_hit_threshold(bullet_data.threshold_hits);
        } else if (bullet_data.bullet_type == BULLET_TYPE_HITBOX_DIRECTED){
            new_bullet.set_expiration(bullet_data.duration);
            new_bullet.update_direction();
            new_bullet.set_hit_threshold(bullet_data.threshold_hits);
        }

        //ADDING DEBUFFS
        if (!bullet_data.bullet_debuffs.empty()){
            for (unsigned int debuff_index = 0; debuff_index < bullet_data.bullet_debuffs.size(); debuff_index++){
                new_bullet.insert_debuff(bullet_data.bullet_debuffs.at(debuff_index));
            }
        }

        bullets_to_add.push(new_bullet);

        //ADDING BULLET IMAGE
        game->create_image(ss.str(), bullet_data.bullet_image, {0,0,bullet_data.bullet_radius*2,bullet_data.bullet_radius*2});
        game->set_active(ss.str(), true);

        total_bullets++;
    };

    void set_bullet_space(bullet_space* space){
        td_bullets = space;
    }

    void set_enemy_space(std::map<int, enemy>* new_enemy_space){
        td_enemies = new_enemy_space;
    };

    void set_resources(std::map<std::string, resource>* resources){
        td_resources = resources;
    }

    std::vector<td_bullet> bullets;

private:
    void get_income(unsigned int bullet_index){
        switch (bullets.at(bullet_index).get_income_type()){
            case INCOME_TYPE_METAL:
                td_resources->at("Metal").add_to_resource(bullets.at(bullet_index).get_income());
            break;
            case INCOME_TYPE_WOOD:
                td_resources->at("Wood").add_to_resource(bullets.at(bullet_index).get_income());
            break;
            case INCOME_TYPE_CRYSTAL:
                td_resources->at("Crystal").add_to_resource(bullets.at(bullet_index).get_income());
            break;
            default:
            break;
        }
    }

    void kill_bullet(unsigned int bullet_index){
        if (is_within_index(bullets.size(), bullet_index)){
            remove_bullet_image(bullets.at(bullet_index).get_name());
            bullets.erase(bullets.begin() + bullet_index);
        }
    }

    void remove_bullet_image(std::string bullet_image_spot){
        extern main_controller* game;

        game->set_active(bullet_image_spot, false);
        game->clear_points(bullet_image_spot);
        game->remove_image_copy(bullet_image_spot);
    }

    int total_bullets;
    bullet_space* td_bullets = NULL;
    std::queue<td_bullet> bullets_to_add = std::queue<td_bullet>();

    std::map<int, enemy>* td_enemies = NULL;
    std::map<std::string, resource>* td_resources = NULL;
};

#endif // TD_BULLET_H_INCLUDED
