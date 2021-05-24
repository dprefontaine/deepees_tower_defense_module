#include "enemy.h"

///USE THIS FUNCTION FOR DETERMINING ARMOR-TO-DAMAGE SCALING
float type_scale(ENEMY_ARMOR_TYPE armor_type, BULLET_DAMAGE_TYPE damage_type){
    return 1.0f;
}

///USE THIS FUNCTION FOR REDUCTION SCALE
float reduction_scale(int armor){
    std::cout << armor << std::endl;

    if (armor < 0)
        return 1.5f;

    return 1;
}

enemy::enemy(int hp, int regen, int armor, ENEMY_ARMOR_TYPE armor_type, int speed, int x, int y, int radius, std::string spot_name, std::string image_name, int metal_bounty, int wood_bounty, int crystal_bounty, int contact_id){
    current_hp = max_hp = hp;
    enemy_regen = regen;
    enemy_armor = armor;
    enemy_armor_type = armor_type;
    x_velocity = y_velocity = speed;
    enemy_hitbox = circle_hitbox(x, y, radius, contact_id);
    enemy_image = image_name;
    x_velocity_directed = y_velocity_directed = 0;
    enemy_metal_bounty = metal_bounty;
    enemy_wood_bounty = wood_bounty;
    enemy_crystal_bounty = crystal_bounty;
    enemy_name = spot_name;
    previous_x_pos = x;
    previous_y_pos = y;
    debuffs_to_add = std::queue<debuff_data>();
    enemy_hp_bar_name = spot_name+"_hp_bar";

    add_enemy_image();
}

enemy::~enemy(){
    std::vector<point>().swap(positions_to);
    std::map<std::string, debuff_data>().swap(debuffs);
}

bool enemy::update(unsigned int ticks){
    if (!boundary_check()){
        std::cout << "enemy went out of bounds!" << std::endl;
        current_hp = 0;
        return is_dead();
    }

    if (current_hp > 0){
        //UPDATING VELOCITY
        x_mov_add+=x_velocity_directed*ticks/1000.f;
        y_mov_add+=y_velocity_directed*ticks/1000.f;

        if (abs(x_mov_add) > 1.f){
            previous_x_pos = enemy_hitbox.get_x();
            enemy_hitbox.move_x(x_mov_add);
            x_mov_add-=(int)x_mov_add;
        } else
            enemy_hitbox.move_x(0);

        if (abs(y_mov_add) > 1.f){
            previous_y_pos = enemy_hitbox.get_y();
            enemy_hitbox.move_y(y_mov_add);
            y_mov_add-=(int)y_mov_add;
        } else
            enemy_hitbox.move_y(0);

        if (has_reached_point()){
            x_mov_add = y_mov_add = 0;
            previous_x_pos = enemy_hitbox.get_x();
            previous_y_pos = enemy_hitbox.get_y();
            positions_to.erase(positions_to.begin());
            change_direction();
        }

        //UPDATING REGEN
        regen_timer.alarm_set(ticks);

        if (regen_timer.get_warning() > 0){
            regen_timer.reset_warning();
            current_hp+=enemy_regen;

            if (current_hp > max_hp){
                current_hp = max_hp;
            }
        }

        //CHECK IF THERE ARE DEBUFFS TO ADD
        while (!debuffs_to_add.empty()){
            add_debuff(debuffs_to_add.front().debuff_name, debuffs_to_add.front());
            debuffs_to_add.pop();
        }

        //UPDATING DEBUFFS AND STATS
        std::map<std::string, debuff_data>::iterator debuff_iterator = debuffs.begin(), next_debuff = debuff_iterator;

        for (;debuff_iterator != debuffs.end(); debuff_iterator = next_debuff){
            ++next_debuff;

            //CHECK IF DEBUFF HAS EXPIRED, REMOVE FROM MODIFIERS
            if (debuff_iterator->second.has_expired(ticks)){
                switch (debuff_iterator->second.debuff_stat){
                    case DEBUFF_MAX_HP:
                        max_hp+=debuff_iterator->second.degree;
                    break;
                    case DEBUFF_REGEN:
                        enemy_regen+=debuff_iterator->second.degree;
                    break;
                    case DEBUFF_SPEED:
                        x_velocity+=debuff_iterator->second.degree;
                        y_velocity = x_velocity;
                        change_direction();
                    break;
                    case DEBUFF_ARMOR:
                        enemy_armor+=debuff_iterator->second.degree;
                    break;
                }

                extern main_controller* game;

                //CLEAR DEBUFF IMAGE
                game->remove_image_copy(debuff_iterator->second.debuff_name);

                //ERASE DEBUFF
                debuffs.erase(debuff_iterator);
            }
        }

        return at_end();
    } else {
        return is_dead();
    }
}

void enemy::set_path(std::vector<point> path_points){
    positions_to = path_points;

    std::cout << path_points.size() << std::endl;

    if (positions_to.front().get_x() == enemy_hitbox.get_x() &&
        positions_to.front().get_x() == enemy_hitbox.get_y())
        positions_to.erase(positions_to.begin());

    change_direction();
}

void enemy::change_direction(){
    if (!positions_to.empty()){
        float run, rise, x_sign, y_sign, hypotenuse;

        //determine rise difference
        rise = positions_to.front().get_y() - enemy_hitbox.get_y();

        //determine run difference
        run = positions_to.front().get_x() - enemy_hitbox.get_x();

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

                //std::cout << "Angles " << x_direction << " " << y_direction << std::endl;

                x_velocity_directed = x_direction*abs(x_velocity);
                y_velocity_directed = y_direction*abs(y_velocity);

                //std::cout << "Angles " << x_max_velocity_directed << " " << y_max_velocity_directed << std::endl;

                if (x_velocity_directed > 5)
                    change_direction_animation(ENEMY_RIGHT);
                else if (x_velocity_directed < -5)
                    change_direction_animation(ENEMY_LEFT);
                else if (y_velocity_directed > 5)
                    change_direction_animation(ENEMY_DOWN);
                else if (y_velocity_directed < -5)
                    change_direction_animation(ENEMY_UP);
            }
    } else {
        x_direction = y_direction = 0;
        x_velocity_directed = y_velocity_directed = 0;
    }
}

void enemy::change_direction_animation(ENEMY_DIRECTION direction){
    extern main_controller* game;

    switch (direction){
    case ENEMY_RIGHT:
        game->set_animation_state(enemy_name, "scrabbling right");
    break;
    case ENEMY_DOWN:
        game->set_animation_state(enemy_name, "scrabbling down");
    break;
    case ENEMY_LEFT:
        game->set_animation_state(enemy_name, "scrabbling left");
    break;
    case ENEMY_UP:
        game->set_animation_state(enemy_name, "scrabbling up");
    break;
    }
}

bool enemy::has_reached_point(){
    if (!positions_to.empty()){
        int previous_x_pos_segment = positions_to.front().get_x() - previous_x_pos;
        int previous_y_pos_segment = positions_to.front().get_y() - previous_y_pos;

        //ALREADY ASSUMING RISE AND RUN IS IN PROPORTION TO CURRENT VELOCITY

        //CHECKING IF PASSED OVER
        if (abs(previous_y_pos_segment) <= abs(y_velocity_directed/20) &&
            abs(previous_x_pos_segment) <= abs(x_velocity_directed/20)){
            enemy_hitbox.set_x(positions_to.front().get_x());
            enemy_hitbox.set_y(positions_to.front().get_y());
            return true;
        }


        /*
        if (positions_to.front().get_x() > (enemy_hitbox.get_x() - 5) && positions_to.front().get_x() < (enemy_hitbox.get_x() + 5) &&
            positions_to.front().get_y() > (enemy_hitbox.get_y() - 5) && positions_to.front().get_y() < (enemy_hitbox.get_y() + 5)){
            enemy_hitbox.set_x(positions_to.front().get_x());
            enemy_hitbox.set_y(positions_to.front().get_y());
            std::cout << "pee" <<std::endl;
            return true;
        }
        */
    }

    return false;
}

circle_hitbox* enemy::get_hitbox(){
    return &enemy_hitbox;
}

bool enemy::at_end(){
    if (positions_to.empty()){
        ending_state = ENEMY_FINISHED;

        //ERASING DEBUFF IMAGES
        for (std::map<std::string, debuff_data>::iterator debuff_iterator = debuffs.begin(); debuff_iterator != debuffs.end(); debuff_iterator++){
            extern main_controller* game;

            //CLEAR DEBUFF IMAGE
            game->remove_image_copy(debuff_iterator->second.debuff_name);
        }

        //DESTROY THE HP BAR
        clear_hp_bar();

        return true;
    }

    return false;
}

bool enemy::is_dead(){
    if (current_hp < 1){
        ending_state = ENEMY_KILLED;

        //ERASING DEBUFF IMAGES
        for (std::map<std::string, debuff_data>::iterator debuff_iterator = debuffs.begin(); debuff_iterator != debuffs.end(); debuff_iterator++){
            extern main_controller* game;

            //CLEAR DEBUFF IMAGE
            game->remove_image_copy(debuff_iterator->second.debuff_name);
        }

        //DESTROY THE HP BAR
        clear_hp_bar();
    }

    return current_hp < 1;
}

ENEMY_STATE enemy::get_end_state(){
    return ending_state;
}

void enemy::calculate_damage(int damage_taken, BULLET_DAMAGE_TYPE damage_type){
    //GET TYPE RELATION
    float type_calculator = type_scale(enemy_armor_type, damage_type);

    //COMPARE DAMAGE TO ARMOR
    float reduction = reduction_scale(enemy_armor);

    //CALCULATE FINAL DAMAGE WITH ARMOR REDUCTION/MULTIPLICATION (damage taken*type calculator)

    std::cout << reduction << " " << damage_taken << std::endl;

    current_hp-=damage_taken*type_calculator*reduction;
}

void enemy::add_debuff_to_queue(debuff_data new_debuff){
    debuffs_to_add.push(new_debuff);
}

void enemy::add_debuff(std::string debuff_data_name, debuff_data new_debuff){
    //CHECK IF NOT REGISTERED YET
    if (debuffs.find(debuff_data_name) == debuffs.end()){
        //ADD IT
        debuffs.insert(std::pair<std::string, debuff_data>(debuff_data_name, new_debuff));

        //ADD REDUCTION ONTO ENEMY STATS
        switch (new_debuff.debuff_stat){
            case DEBUFF_MAX_HP:
                max_hp-=new_debuff.degree;
            break;
            case DEBUFF_REGEN:
                enemy_regen-=new_debuff.degree;
            break;
            case DEBUFF_SPEED:
                x_velocity-=new_debuff.degree;
                y_velocity = x_velocity;
                change_direction();
            break;
            case DEBUFF_ARMOR:
                enemy_armor-=new_debuff.degree;
            break;
        }

        //CREATE A DEBUFF IMAGE
        extern main_controller* game;

        static std::stringstream ss;
        ss << debuffs.at(debuff_data_name).debuff_name << " " << enemy_name;
        debuffs.at(debuff_data_name).debuff_name = ss.str();

        game->create_image(debuffs.at(debuff_data_name).debuff_name, debuffs.at(debuff_data_name).debuff_image, {0,0,90,90});
        game->add_point(debuffs.at(debuff_data_name).debuff_name, enemy_hitbox.get_x(), enemy_hitbox.get_y());
        game->set_active(debuffs.at(debuff_data_name).debuff_name, true);

        ss.clear();
    } else {
        debuffs.at(debuff_data_name).reset_ticks();
    }
}

void enemy::create_hp_bar(){
    extern main_controller* game;

    game->new_blank_image(enemy_hp_bar_name, SDL_TEXTUREACCESS_STREAMING, 0, 1, enemy_hitbox.get_radius()*2 - 10, 4);
    game->add_point(enemy_hp_bar_name, enemy_hitbox.get_x(), enemy_hitbox.get_y());
    game->set_active(enemy_hp_bar_name, true);
}

void enemy::draw_hp_bar(){
    extern main_controller* game;

    game->set_point(enemy_hp_bar_name, 0, enemy_hitbox.get_x(), enemy_hitbox.get_y() + enemy_hitbox.get_radius() + 5);

    game->lock_image(enemy_hp_bar_name, true);

    int hp_ratio = ((enemy_hitbox.get_radius()*2 - 10) * (current_hp))/max_hp;

    for (int i = 0; i < (enemy_hitbox.get_radius()*2 - 10)*4; i++){
        if (hp_ratio > i%(enemy_hitbox.get_radius()*2 - 10))
            game->set_pixel(enemy_hp_bar_name, 0x00FF00FF, i%(enemy_hitbox.get_radius()*2 - 10), i/(enemy_hitbox.get_radius()*2 - 10));
        else
            game->set_pixel(enemy_hp_bar_name, 0xFF0000FF, i%(enemy_hitbox.get_radius()*2 - 10), i/(enemy_hitbox.get_radius()*2 - 10));
    }

    game->lock_image(enemy_hp_bar_name, false);
}

void enemy::clear_hp_bar(){
    extern main_controller* game;

    game->remove_image_copy(enemy_hp_bar_name);
}

std::string enemy::get_name(){
    return enemy_name;
}

std::string enemy::get_image(){
    return enemy_image;
}

void enemy::add_enemy_image(){
    extern main_controller* game;

    std::string name = game->create_image(enemy_name, enemy_image, {0,0,90,90});
    game->add_point(enemy_name,0,0);

    game->add_animation_set_to_image(name);

    game->add_animation_state_to_image(name, "scrabbling right", true, true);
    game->add_animation_frame_to_image(name, "scrabbling right", 20, {0,0,90,90});
    game->add_animation_frame_to_image(name, "scrabbling right", 50, {90,0,90,90});
    game->add_animation_frame_to_image(name, "scrabbling right", 20, {180,0,90,90});

    game->add_animation_state_to_image(name, "scrabbling down", true, true);
    game->add_animation_frame_to_image(name, "scrabbling down", 20, {0,90,90,90});
    game->add_animation_frame_to_image(name, "scrabbling down", 50, {90,90,90,90});
    game->add_animation_frame_to_image(name, "scrabbling down", 20, {180,90,90,90});

    game->add_animation_state_to_image(name, "scrabbling left", true, true);
    game->add_animation_frame_to_image(name, "scrabbling left", 20, {0,180,90,90});
    game->add_animation_frame_to_image(name, "scrabbling left", 50, {90,180,90,90});
    game->add_animation_frame_to_image(name, "scrabbling left", 20, {180,180,90,90});

    game->add_animation_state_to_image(name, "scrabbling up", true, true);
    game->add_animation_frame_to_image(name, "scrabbling up", 20, {0,270,90,90});
    game->add_animation_frame_to_image(name, "scrabbling up", 50, {90,270,90,90});
    game->add_animation_frame_to_image(name, "scrabbling up", 20, {180,270,90,90});

    game->set_animation_state(name, "scrabbling down");
}

void enemy::activate_enemy_image(){
    extern main_controller* game;

    game->set_active(enemy_name, true);
    game->set_animation_active(enemy_name, true);
}

void enemy::remove_enemy_image(){
    extern main_controller* game;

    game->clear_points(enemy_name);
    game->set_active(enemy_name, false);
    game->remove_image_copy(enemy_name);
}

int enemy::get_metal_bounty(){
    return enemy_metal_bounty;
}

int enemy::get_wood_bounty(){
    return enemy_wood_bounty;
}

int enemy::get_crystal_bounty(){
    return enemy_crystal_bounty;
}

void enemy::draw_enemy(){
    extern main_controller* game;

    //SET ENEMY POINT ITSELF
    game->set_point(enemy_name, 0, enemy_hitbox.get_x(), enemy_hitbox.get_y());

    //SET DEBUFF POINTS
    for (std::map<std::string, debuff_data>::iterator debuff_iterator = debuffs.begin(); debuff_iterator != debuffs.end(); ++debuff_iterator){
        game->set_point(debuff_iterator->second.debuff_name, 0, enemy_hitbox.get_x(), enemy_hitbox.get_y());
    }

    //SETTING HP BAR
    draw_hp_bar();
}


///IN CASE THE ENEMY GOES OUTSIDE OF THE MAP FOR WHATEVER REASON
bool enemy::boundary_check(){
    extern const unsigned int SQUARE_SIZE, GRID_SIZE_X, GRID_SIZE_Y;

    return (enemy_hitbox.get_x() > 0 && enemy_hitbox.get_x() < (int)(SQUARE_SIZE*GRID_SIZE_X) &&
            enemy_hitbox.get_y() > 0 && enemy_hitbox.get_y() < (int)(SQUARE_SIZE*GRID_SIZE_Y));
}
