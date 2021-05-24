#include "td_bullet.h"

td_bullet::td_bullet(int damage, BULLET_DAMAGE_TYPE damage_type, BULLET_TYPE type, int speed, int initial_x, int initial_y, int radius, int targeted_enemy,
                     std::string name, std::string image, std::vector<tower_bullet_data> after_bullets,
                     bullet_space* bullets, std::map<int, enemy>* enemies){

    bullet_damage = damage;
    bullet_damage_type = damage_type;
    bullet_type = type;
    bullet_speed = speed;
    target_enemy = targeted_enemy;
    bullet_hitbox = circle_hitbox(initial_x, initial_y, radius, 0);
    bullets_after_data = after_bullets;
    td_bullets = bullets;
    td_enemies = enemies;

    x_velocity_directed = y_velocity_directed = 0;

    x_mov_add = y_mov_add = 0;

    x_direction = y_direction = 0;

    bullet_spot_name = name;
    bullet_image = image;
}

td_bullet::~td_bullet(){
    std::vector<tower_bullet_data>().swap(bullets_after_data);
    std::map<std::string, debuff_data>().swap(bullet_debuffs);
    std::vector<int>().swap(hit_enemies);
    td_bullets = NULL;
    td_enemies = NULL;
}

void td_bullet::insert_debuff(debuff_data debuff_to_insert){
    bullet_debuffs.insert(std::pair<std::string, debuff_data>(debuff_to_insert.debuff_name, debuff_to_insert));
}

void td_bullet::set_velocity(int x_vel, int y_vel){
    x_velocity_directed = x_vel;
    y_velocity_directed = y_vel;
}

void td_bullet::set_expiration(unsigned int ticks){
    if (ticks == 0)
        bullet_expiration.set_threshold(1);
    else
        bullet_expiration.set_threshold(ticks);
}

void td_bullet::set_target_enemy(){

}

void td_bullet::set_hit_threshold(int new_threshold_hits){
    max_hits = new_threshold_hits;
}

bool td_bullet::update(unsigned int ticks){
    //MAKING SURE ENEMY IS NOT TERMINATED OR THE BULLET HAS NOT REACHED THE ENEMY
    switch (bullet_type){
        //BEHAVE AS A TARGET BULLET
        case (BULLET_TYPE_TARGET):
            if (!has_reached_enemy()){
                //HOMING IN ON ENEMY
                update_direction();

                //UPDATING VELOCITY
                x_mov_add+=x_velocity_directed*ticks/1000.f;
                y_mov_add+=y_velocity_directed*ticks/1000.f;

                if (abs(x_mov_add) > 1.f){
                    bullet_hitbox.move_x(x_mov_add);
                    x_mov_add-=(int)x_mov_add;
                } else
                    bullet_hitbox.move_x(0);

                if (abs(y_mov_add) > 1.f){
                    bullet_hitbox.move_y(y_mov_add);
                    y_mov_add-=(int)y_mov_add;
                } else
                    bullet_hitbox.move_y(0);

                return false;
            } else {
                deal_damage();
                return true;
            }
        break;

        ///THE OTHER TWO BULLETS ARE BASED ON DURATION TO EXPIRE
        //BEHAVE IS A BOX BULLET
        case (BULLET_TYPE_HITBOX):
        case (BULLET_TYPE_HITBOX_DIRECTED):
            bullet_expiration.alarm_set(ticks);

            if (!has_expired()){
                //UPDATE VELOCITY (NO NEED TO UPDATE DIRECTION TO HOME IN)
                x_mov_add+=x_velocity_directed*ticks/1000.f;
                y_mov_add+=y_velocity_directed*ticks/1000.f;

                if (abs(x_mov_add) > 1.f){
                    bullet_hitbox.move_x(x_mov_add);
                    x_mov_add-=(int)x_mov_add;
                } else
                    bullet_hitbox.move_x(0);

                if (abs(y_mov_add) > 1.f){
                    bullet_hitbox.move_y(y_mov_add);
                    y_mov_add-=(int)y_mov_add;
                } else
                    bullet_hitbox.move_y(0);

                ///CATCH HOW MANY ENEMIES HAVE FALLEN UNDER ITS HITBOX

                //CHANGE TARGET TO EACH
                for (std::map<int, enemy>::iterator i = td_enemies->begin(); i != td_enemies->end(); ++i){
                    //CHECK IF A REGISTERED ENEMY HAS BEEN HIT BEFORE
                    if (std::find(hit_enemies.begin(), hit_enemies.end(), i->first) == hit_enemies.end()){
                        target_enemy = i->first;

                        if (has_reached_enemy()){
                            deal_damage();

                            //FOR DEBOUNCE
                            hit_enemies.push_back(i->first);
                            //std::cout << "hitting enemy " << i->first << std::endl;
                        }
                    }
                }

                if (hit_enemies.size() < max_hits)
                    return false;
                else {
                    hit_enemies.clear();
                    return true;
                }
            } else {
                //std::cout << "piss" << std::endl;
                hit_enemies.clear();
                return true;
            }
        break;

        ///INCOME
        case (BULLET_TYPE_INCOME):
            end_state = BULLET_IS_INCOME;
            return true;
        break;

        //DEFAULT
        default:
            return false;
        break;
    }
}

void td_bullet::deal_damage(){
    if (end_state == BULLET_REACHED_ENEMY){
        try {
            td_enemies->at(target_enemy).calculate_damage(bullet_damage, bullet_damage_type);

            //ADD DEBUFFS TO ENEMY
            if (!bullet_debuffs.empty()){
                for (std::map<std::string, debuff_data>::iterator debuff_iterator = bullet_debuffs.begin(); debuff_iterator != bullet_debuffs.end(); debuff_iterator++){
                    td_enemies->at(target_enemy).add_debuff_to_queue(debuff_iterator->second);
                }
            }
        } catch (std::out_of_range e){
                //std::cout << "No bullet!" << std::endl;
        }

        //CREATE AFTER BULLETS
        if (!bullets_after_data.empty())
            create_after_bullets();
    }
}

///PRIMARILY USING THIS TO GET INCOME AS GOOFY AS IT SOUNDS :P
int td_bullet::get_income(){
    return bullet_damage;
}

BULLET_DAMAGE_TYPE td_bullet::get_income_type(){
    return bullet_damage_type;
}

bool td_bullet::has_reached_enemy(){
    //SEEING IF BULLET HAS CONTACTED THE ENEMY'
    try {
        if (bullet_hitbox.check_contact_with_circle(td_enemies->at(target_enemy).get_hitbox())){
            end_state = BULLET_REACHED_ENEMY;
            return true;
        } else {
            return false;
        }
    } catch (std::out_of_range e){
        end_state = BULLET_ENEMY_GONE;
        return true;
    }
}

bool td_bullet::has_expired(){
    return bullet_expiration.get_warning() > 0;
}

void td_bullet::destroy_bullet(){
    //THIS IS TO ADD ANY ADDITIONAL DATA ONTO THE BULLET
}

circle_hitbox* td_bullet::get_hitbox(){
    return &bullet_hitbox;
}

BULLET_STATE td_bullet::get_end_state(){
    return end_state;
}

void td_bullet::update_direction(){
    //THIS IS SUPPOSING THE ENEMY STILL EXISTS
    bool enemy_exists = true;
    float run, rise, x_sign, y_sign, hypotenuse;

    try {
        //determine rise difference
        rise = td_enemies->at(target_enemy).get_hitbox()->get_y() - bullet_hitbox.get_y();

        //determine run difference
        run = td_enemies->at(target_enemy).get_hitbox()->get_x() - bullet_hitbox.get_x();
    } catch (std::out_of_range e){
        enemy_exists = false;
    }

    if (enemy_exists){

        if (run < 0)
            x_sign = -1.f;
        else
            x_sign = 1.f;

        if (rise < 0)
            y_sign = -1.f;
        else
            y_sign = 1.f;

        if (rise == 0 && run == 0) {
            x_direction = y_direction = x_velocity_directed = y_velocity_directed = 0;
        } else {
            hypotenuse = (abs(rise)+abs(run))*(abs(rise)+abs(run));
            x_direction = x_sign*sqrt(run*run/hypotenuse);
            y_direction = y_sign*sqrt(rise*rise/hypotenuse);

            //std::cout << "Angles " << x_direction << " " << y_direction << " " << atan(y_direction/x_direction)*100 << " " << bullet_image << std::endl;

            x_velocity_directed = x_direction*abs(bullet_speed);
            y_velocity_directed = y_direction*abs(bullet_speed);

            //std::cout << "Angles " << x_max_velocity_directed << " " << y_max_velocity_directed << std::endl;

            ///SETTING BULLET ROTATION
            extern main_controller* game;

            game->set_rotation(bullet_spot_name, atan(y_direction/x_direction)*100);

            if (x_direction < 0)
                game->set_flip(bullet_spot_name, SDL_FLIP_HORIZONTAL);
            else
                game->set_flip(bullet_spot_name, SDL_FLIP_NONE);
        }
    } else {
        destroy_bullet();
    }
}

void td_bullet::create_after_bullets(){
    //CREATE MORE BULLETS (DATA SHOULD BE CARRIED FROM THE TABLE)
    for (std::vector<tower_bullet_data>::iterator bullet_index = bullets_after_data.begin(); bullet_index != bullets_after_data.end(); bullet_index++){

        ///DECIDE ON A TARGET

        try {
            //CREATING BULLET
            td_bullets->create_bullet(*bullet_index, target_enemy, bullet_hitbox.get_x(), bullet_hitbox.get_y());
        } catch (std::bad_alloc e){
            //std::cout << "You suck " << std::endl;
        }
    }
}

std::string td_bullet::get_name(){
    return bullet_spot_name;
}

std::string td_bullet::get_image(){
    return bullet_image;
}
