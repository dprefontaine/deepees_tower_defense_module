#include "td_module.h"

int determine_buildover(TARGET_BUILDOVER buildover, int grid_data){
    switch (buildover){
        case TOWER_PHASEABLE:
            if (grid_data == 1)
                return 0;
            else
                return 3;
        break;
        case TOWER_UNPHASEABLE:
            return 3;
        break;
        case TOWER_DIGGING:
            return 0;
        break;
    }

    return 0;
}

td_module::td_module(int cam_x_accel, int cam_y_accel, int max_x_vel, int max_y_vel){
    td_grid = grid_manager();
    enemies_to_spawn = std::stack<std::pair<int, enemy>>();
    td_enemies = std::map<int, enemy>();

    td_bullets = bullet_space();
    td_bullets.set_bullet_space(&td_bullets);
    td_bullets.set_enemy_space(&td_enemies);

    td_towers = std::vector<tower>();
    td_waves = std::queue<std::string>();

    td_resources = std::map<std::string, resource>();
    lives = resource(15, 15);
    load_waves();

    build_button_mappings = std::map<td_module_build_button_selection, std::string>();
    load_button_mapping();

    x_click = y_click = 0;
    control_state = MODULE_DEFAULT;
    level_playing = false;

    moving_up = moving_down = moving_left = moving_right = false;
    x_acc = cam_x_accel;
    y_acc = cam_y_accel;
    x_vel = y_vel = 0;
    x_vel_max = max_x_vel;
    y_vel_max = max_y_vel;

    //RESOURCES
    td_resources.insert(std::pair<std::string, resource>("Metal",resource(250,9999)));
    td_resources.insert(std::pair<std::string, resource>("Wood",resource(150,9999)));
    td_resources.insert(std::pair<std::string, resource>("Crystal",resource(15,9999)));

    td_bullets.set_resources(&td_resources);

    //NOTIFICATION
    notification_on = false;
    notification_message = "";
}

td_module::~td_module(){
    selected_tower_index = 0;

    std::map<int, enemy>().swap(td_enemies);
    std::vector<tower>().swap(td_towers);
    std::map<std::string, resource>().swap(td_resources);
    std::map<td_module_build_button_selection, std::string>().swap(build_button_mappings);
}

void td_module::update_td_module(unsigned int ticks){
    extern main_controller* game;

    //THE CAMERA AND NOTIFICATION ARE INDEPENDENT OF THE TICK SPEED
    if (ticks < 100){
        int vert_sign = 0;
        int horz_sign = 0;

        if (moving_down){
            //std::cout << "Moving down" << std::endl;
            vert_sign++;
        }

        if (moving_up){
            //std::cout << "Moving up" << std::endl;
            vert_sign--;
        }

        if (moving_right){
            //std::cout << "Moving right" << std::endl;
            horz_sign++;
        }

        if (moving_left){
            //std::cout << "Moving left" << std::endl;
            horz_sign--;
        }

        vert_accel = ticks/1000.f;
        vert_accel*=y_acc;

        if (vert_sign != 0){
            y_vel+=vert_accel;

            if (y_vel > y_vel_max)
                y_vel = y_vel_max;

        } else if (y_vel != 0){
            y_vel-=vert_accel;

            if (y_vel < 0)
                y_vel = 0;
        }

        horz_accel = ticks/1000.f;
        horz_accel*=x_acc;

        if (horz_sign != 0){
            x_vel+=horz_accel;

            if (x_vel > x_vel_max)
                x_vel = x_vel_max;

        } else if (x_vel != 0){
            x_vel-=horz_accel;

            if (x_vel < 0)
                x_vel = 0;
        }

        game->set_camera_position(0,1,x_vel*horz_sign, y_vel*vert_sign);

        if (notification_on){
            static int notification_threshold = 0;
            notification_threshold+=ticks;

            if (!game->get_active("Notification")){
                game->reload_as_text("Notification", "notification font", notification_message, false, 0);
                game->set_blend_mode("Notification", SDL_BLENDMODE_BLEND);
                game->set_active("Notification", true);
            }

            if (notification_threshold > 2000){
                notification_threshold = 0;
                notification_on = false;
                game->set_active("Notification", false);
            }
        }



        ///SPEED MULTIPLIER IS HERE
        ticks*=speed_multiplier;

        //UPDATING BULLETS
        td_bullets.update(ticks);
        draw_bullets();

        //UPDATING ANY MOVEMENTS BASED ON STATE OF THE MAP
        if (level_playing){
            //std::cout << "Level is playing!" << std::endl;

            if (remaining_enemies_to_spawn()){
                if (spawn_rate.alarm_set(ticks) > 0){
                    spawn_rate.reset_warning();
                    spawn_enemy();
                }
            }

            if (!(remaining_enemies_to_spawn()) && td_enemies.empty()){
                level_playing = false;
                increase_level();
            }
        }

        //UPDATING ENEMIES
        if (!td_enemies.empty()){
            std::map<int, enemy>::iterator enemy_iterator = td_enemies.begin();
            for (unsigned int i = 0; i < total_wave_enemies; i++){
                enemy_iterator = td_enemies.find(i);

                if (enemy_iterator != td_enemies.end())
                    //RETURNS TRUE IF ABOUT TO TERMINATE
                if (enemy_iterator->second.update(ticks)){
                    if (enemy_iterator->second.get_end_state() == ENEMY_KILLED){
                        enemy_bountied(enemy_iterator->first);
                    } else if (enemy_iterator->second.get_end_state() == ENEMY_FINISHED){
                        enemy_at_end(enemy_iterator->first);
                    }
                }
            }
        } else {
            total_enemies = 0;
        }

        draw_enemies();

        //UPDATING TOWERS
        if (!td_towers.empty()){
            //UPDATING TOWERS
            for (unsigned int i = 0; i < td_towers.size(); i++){
                td_towers.at(i).update(ticks);
            }
        }

        draw_board();
    }
}

int td_module::toggling_speed(){
    if (speed_multiplier == 1){
        speed_multiplier = 2;
        return 1;
    } else if (speed_multiplier == 2) {
        speed_multiplier = 4;
        return 2;
    } else {
        speed_multiplier = 1;
        return 0;
    }
}

void td_module::increase_level(){
    if (!level.add_to_resource(1)){
        notification_message = "You won the game!";
        notification_on = true;
    }
}

void td_module::remove_life(){
    if (!lives.use_resource(1) || lives.get_resource() == 0){
        notification_message = "You lost the game!";
        notification_on = true;
    }
}

void td_module::click_on_grid(unsigned int x_click, unsigned int y_click){
    td_module::x_click = x_click/SQUARE_SIZE;
    td_module::y_click = y_click/SQUARE_SIZE;

    //std::cout << "X: " << td_module::x_click << " Y: " << td_module::y_click << std::endl;

    td_grid.set_grid_point(td_module::x_click, td_module::y_click);

    switch(control_state){
        case MODULE_DEFAULT:
            observe_grid_click();
        break;
        case MODULE_BUILD:
            build_tower_click();
        break;
    }

    set_state(MODULE_DEFAULT);
}

void td_module::over_grid(unsigned int x_over, unsigned int y_over){
    x_click = x_over/SQUARE_SIZE;
    y_click = y_over/SQUARE_SIZE;

    //std::cout << td_module::x_click << " " << td_module::y_click << std::endl;

    td_grid.set_grid_point(x_click, y_click);

    switch(control_state){
        case MODULE_DEFAULT:
            observe_grid_over();
        break;
        case MODULE_BUILD:
            build_tower_over();
        break;
    }
}

void td_module::set_build_click(td_module_build_button_selection new_state){
    if (build_data_select == new_state){
        set_state(MODULE_DEFAULT);
        build_data_select = BUILD_BUTTON_NONE;
        deactivate_selection();
    } else if (new_state == BUILD_BUTTON_NONE) {
        set_state(MODULE_DEFAULT);
        build_data_select = BUILD_BUTTON_NONE;
    } else {
        extern main_controller* game;
        extern td_level_loader* table;

        set_state(MODULE_BUILD);
        build_data_select = new_state;

        ///GET THE NAME OF THE DATA THIS BUTTON IS ASSOCIATED WITH
        tower_data_name = build_button_mappings.at(build_data_select);

        ///SETTING THE TOWER IMAGE
        game->reload_as_image("Tower Select", table->get_tower_data(tower_data_name).tower_image_link, {0,0,90,90});
        game->set_alpha("Tower Select", 0xAA);
        game->set_blend_mode("Tower Select", SDL_BLENDMODE_BLEND);
        activate_selection(true, false);
    }
}

td_module_build_button_selection td_module::get_build_click(){
    return build_data_select;
}

void td_module::set_button_data_set(){
    extern main_controller* game;
    extern td_level_loader* table;

    game->reload_as_image("Build Icon One", table->get_tower_data(build_button_mappings.at(BUILD_BUTTON_ONE)).tower_icon_name, {0,0,95,95});
    game->reload_as_image("Build Icon Two", table->get_tower_data(build_button_mappings.at(BUILD_BUTTON_TWO)).tower_icon_name, {0,0,95,95});
    game->reload_as_image("Build Icon Three", table->get_tower_data(build_button_mappings.at(BUILD_BUTTON_THREE)).tower_icon_name, {0,0,95,95});
    game->reload_as_image("Build Icon Four", table->get_tower_data(build_button_mappings.at(BUILD_BUTTON_FOUR)).tower_icon_name, {0,0,95,95});
    game->reload_as_image("Build Icon Five", table->get_tower_data(build_button_mappings.at(BUILD_BUTTON_FIVE)).tower_icon_name, {0,0,95,95});
    game->reload_as_image("Build Icon Six", table->get_tower_data(build_button_mappings.at(BUILD_BUTTON_SIX)).tower_icon_name, {0,0,95,95});
    game->reload_as_image("Build Icon Seven", table->get_tower_data(build_button_mappings.at(BUILD_BUTTON_SEVEN)).tower_icon_name, {0,0,95,95});
    game->reload_as_image("Build Icon Eight", table->get_tower_data(build_button_mappings.at(BUILD_BUTTON_EIGHT)).tower_icon_name, {0,0,95,95});
    game->reload_as_image("Build Icon Nine", table->get_tower_data(build_button_mappings.at(BUILD_BUTTON_NINE)).tower_icon_name, {0,0,95,95});
}

void td_module::draw_grid(){
    extern main_controller* game;

    //THIS SHOULD STAY THE SAME, SO IT'S NO BIG DEAL
    int grid_data = 0;

    //START FROM THE TOP
    td_grid.set_grid_point(0,0);

    game->clear_points("Grey Tile");
    game->clear_points("Pink Tile");
    game->clear_points("Orange Tile");
    game->clear_points("Blue Tile");

    do {
        //GET DATA OF THAT POINT
        ///FOR REFERENCE:
        //GREY IS CROSSABLE AND NOT BUILDABLE
        //PINK IS CROSSABLE AND BUILDABLE
        //ORANGE IS NOT CROSSABLE AND BUILDABLE

        grid_data = td_grid.get_grid_data_at_current_point();

        switch (grid_data){
        case 0:
            //Draw grey
            game->add_point("Grey Tile", td_grid.get_grid_x_current_point()*SQUARE_SIZE+SQUARE_SIZE/2, td_grid.get_grid_y_current_point()*SQUARE_SIZE+SQUARE_SIZE/2);
            break;
        case 1:
            //Draw pink
            game->add_point("Pink Tile", td_grid.get_grid_x_current_point()*SQUARE_SIZE+SQUARE_SIZE/2, td_grid.get_grid_y_current_point()*SQUARE_SIZE+SQUARE_SIZE/2);
            break;
        case 2:
            //Draw orange
            game->add_point("Orange Tile", td_grid.get_grid_x_current_point()*SQUARE_SIZE+SQUARE_SIZE/2, td_grid.get_grid_y_current_point()*SQUARE_SIZE+SQUARE_SIZE/2);
            break;
        case 3:
            //
            game->add_point("Blue Tile", td_grid.get_grid_x_current_point()*SQUARE_SIZE+SQUARE_SIZE/2, td_grid.get_grid_y_current_point()*SQUARE_SIZE+SQUARE_SIZE/2);
        }

    } while (td_grid.inc_grid_point());


}

void td_module::draw_board(){
    extern main_controller* game;

    static std::stringstream ss = std::stringstream();

    //GET THE MONEY AND DISPLAY IT

    ss << td_resources.at("Metal").get_resource();

    game->reload_as_text("Metal", "base font", ss.str(), false, 0);
    game->set_point("Metal", 0, 70+game->get_spot("Metal").w/2, 30);

    ss.str("");

    ss << td_resources.at("Wood").get_resource();

    game->reload_as_text("Wood", "base font", ss.str(), false, 0);
    game->set_point("Wood", 0, 230+game->get_spot("Wood").w/2, 30);

    ss.str("");

    ss << td_resources.at("Crystal").get_resource();

    game->reload_as_text("Crystal", "base font", ss.str(), false, 0);
    game->set_point("Crystal", 0, 390+game->get_spot("Crystal").w/2, 30);

    ss.str("");

    //GET THE LEVEL AND DISPLAY IT
    ss << level.get_resource();

    game->reload_as_text("Level", "base font", ss.str(), false, 0);
    game->set_point("Level", 0, 555+game->get_spot("Level").w/2, 30);

    ss.str("");

    //GET THE LIVES AND DISPLAY THEM
    ss << lives.get_resource();

    game->reload_as_text("Lives", "base font", ss.str(), false, 0);
    game->set_point("Lives", 0, 940+game->get_spot("Lives").w/2, 30);

    ss.str("");
}

void td_module::draw_points(){
    extern main_controller* game;

    game->add_point("Start Portal", START_POINT_X*SQUARE_SIZE+SQUARE_SIZE/2, START_POINT_Y*SQUARE_SIZE+SQUARE_SIZE/2);
    game->add_point("Move Point One", ONE_POINT_X*SQUARE_SIZE+SQUARE_SIZE/2, ONE_POINT_Y*SQUARE_SIZE+SQUARE_SIZE/2);
    game->add_point("Move Point Two", TWO_POINT_X*SQUARE_SIZE+SQUARE_SIZE/2, TWO_POINT_Y*SQUARE_SIZE+SQUARE_SIZE/2);
    game->add_point("House", END_POINT_X*SQUARE_SIZE+SQUARE_SIZE/2, END_POINT_Y*SQUARE_SIZE+SQUARE_SIZE/2);
}

void td_module::add_tower_image(std::string tower_image_spot, std::string tower_image_source){
    extern main_controller* game;

    game->create_image(tower_image_spot, tower_image_source, {0,0,90,90});
    game->set_active(tower_image_spot, true);
}

void td_module::remove_tower_image(std::string tower_image_spot){
    extern main_controller* game;

    game->set_active(tower_image_spot, false);
    game->clear_points(tower_image_spot);
    game->remove_image_copy(tower_image_spot);
    draw_towers();
}

void td_module::draw_towers(){
    extern main_controller* game;

    //draw all the currently build towers
    for (unsigned int i = 0; i < td_towers.size(); i++){
        game->clear_points(td_towers.at(i).get_name());
        game->add_point(td_towers.at(i).get_name(), td_towers.at(i).get_range()->get_x(), td_towers.at(i).get_range()->get_y());
    }
}

void td_module::set_points(){
    td_grid.set_grid_point(START_POINT_X, START_POINT_Y);
    td_grid.set_start_on_point();

    td_grid.add_destination(0, ONE_POINT_X, ONE_POINT_Y);
    td_grid.add_destination(1, TWO_POINT_X, TWO_POINT_Y);
    td_grid.add_destination(2, END_POINT_X, END_POINT_Y);
}

void td_module::load_map(){
    extern td_level_loader* table;

    td_grid.set_grid_point(0,0);

    std::queue<int> map_stream = std::queue<int>();

    table->set_map(&map_stream, selected_map);

    if (!map_stream.empty())
        do {
            td_grid.set_grid_data(map_stream.front());
            map_stream.pop();
        } while (td_grid.inc_grid_point() && !map_stream.empty());
}

void td_module::set_state(td_module_state new_state){
    extern main_controller* game;

    control_state = new_state;

    if (control_state == MODULE_DEFAULT)
        game->clear_points("Tower Select");
}

td_module_state td_module::get_state(){
    return control_state;
}

void td_module::tower_found(){
    extern main_controller* game;

    //ASSUMING OVER A POINT FOR WHATEVER REASON

    //CHECK IF ANY TOWER FALLS UNDER THE COORDINATES OF BEING CLICKED
    bool click_flag = false;
    int i = 0;

    while (i < (int)td_towers.size() && !click_flag){
        if ((int)td_towers.at(i).get_range()->get_x()/(int)SQUARE_SIZE == x_click &&
            (int)td_towers.at(i).get_range()->get_y()/(int)SQUARE_SIZE == y_click){
            game->add_point("Circle Selected", x_click*SQUARE_SIZE+SQUARE_SIZE/2, y_click*SQUARE_SIZE+SQUARE_SIZE/2);
            selected_tower_index = i;
            click_flag = true;
        }

        i++;
    }

    if (!click_flag){
        selected_tower_index = i = -1;
    }
}

void td_module::observe_grid_click(){
    extern main_controller* game;

    //COME HERE FROM DEFAULT STATE
    game->clear_points("Circle Selected");

    tower_found();

    if (selected_tower_index != -1){
        //std::cout << "Displaying the selected tower" << std::endl;
        //std::cout << "Single Target Type" << std::endl;
        //std::cout << "Attack: " << td_towers.at(selected_tower_index).get_damage() << std::endl;
        //std::cout << "Range: " << td_towers.at(selected_tower_index).get_range()->get_radius() << std::endl;
        tower_data_name = td_towers.at(selected_tower_index).get_display_name();
        activate_selection(false, true);
    } else {
        deactivate_selection();
    }
}

void td_module::activate_selection(bool is_building, bool is_selling){
    extern main_controller* game;
    extern td_level_loader* table;

    game->set_active("Tower Name", true);
    game->set_active("Attack", true);
    game->set_active("Range", true);
    game->set_active("Rate", true);
    game->set_active("Tower Description", true);

    game->set_active("Select", false);

    //ACTIVATING BUTTONS FIRST
    if (is_building){
        game->set_active("Cost Display", true);
        game->set_active("Upgrade Button", false);
        game->set_button_active("Upgrade Button", false);
        game->set_active("Blank Upgrade Button", false);

        //BUILD STRINGS FOR DISPLAYING THE BUILDING COST
    } else {
        game->set_active("Cost Display", false);

        //CHECK IF THE SELECTED TOWER HAS AN AVAILABLE UPGRADE
        if (table->get_tower_data(td_towers.at(selected_tower_index).get_display_name()).has_upgrade){
            game->set_active("Blank Upgrade Button", false);
            game->set_active("Upgrade Button", true);
            game->set_button_active("Upgrade Button", true);

            //BUILD STRINGS FOR DISPLAYING THE UPGRADE COST
            //std::string upgrade_tower_name = table->get_tower_data(td_towers.at(selected_tower_index).get_display_name()).upgrade_name;
            //tower_data upgrade_tower_data = table->get_tower_data(upgrade_tower_name);

        } else {
            game->set_active("Blank Upgrade Button", true);
            game->set_active("Upgrade Button", false);
            game->set_button_active("Upgrade Button", false);
        }
    }

    game->set_active("Button Metal", true);
    game->set_active("Button Wood", true);
    game->set_active("Button Crystal", true);

    if (is_selling){
        game->set_active("Sell Button", true);
        game->set_active("Sell Button Metal", true);
        game->set_active("Sell Button Wood", true);
        game->set_active("Sell Button Crystal", true);
        game->set_button_active("Sell Button", true);
        game->set_active("Blank Sell Button", false);
    } else {
        game->set_active("Blank Sell Button", true);
        game->set_button_active("Sell Button", false);
        game->set_active("Sell Button Metal", false);
        game->set_active("Sell Button Wood", false);
        game->set_active("Sell Button Crystal", false);
        game->set_button_active("Sell Button", false);
    }

    //UPDATING DISPLAYS
    draw_selection(is_building, is_selling);
}

void td_module::deactivate_selection(){
    extern main_controller* game;

    game->set_active("Blank Upgrade Button", false);
    game->set_active("Blank Sell Button", false);

    game->set_active("Cost Display", false);
    game->set_active("Upgrade Button", false);
    game->set_active("Button Metal", false);
    game->set_active("Button Wood", false);
    game->set_active("Button Crystal", false);

    game->set_active("Sell Button", false);
    game->set_active("Sell Button Metal", false);
    game->set_active("Sell Button Wood", false);
    game->set_active("Sell Button Crystal", false);

    game->set_active("Blank Button", false);

    game->set_button_active("Upgrade Button", false);
    game->set_button_active("Sell Button", false);

    game->set_active("Tower Name", false);
    game->set_active("Attack", false);
    game->set_active("Range", false);
    game->set_active("Rate", false);
    game->set_active("Tower Description", false);
    game->set_active("Select", true);
}

void td_module::draw_selection(bool is_building, bool is_selling){
    extern main_controller* game;
    extern td_level_loader* table;

    //GETTING DATA
    tower_data selection_data = table->get_tower_data(tower_data_name);
    tower_bullet_data bullet_selection_data = table->get_bullet_data(selection_data.bullet_data_name);

    std::stringstream stat_stream = std::stringstream();


    //SETTING NAME
    game->reload_as_text("Tower Name", "display font header", selection_data.tower_name, false, 0);
    game->set_blend_mode("Tower Name", SDL_BLENDMODE_BLEND);

    stat_stream.str("");

    //GET THE ATTACK AND DISPLAY IT

    stat_stream << "Attack: " << bullet_selection_data.get_attack();

    game->reload_as_text("Attack", "display font stats", stat_stream.str(), false, 0);
    game->set_point("Attack", 0, 20+game->get_spot("Attack").w/2, 90);

    stat_stream.str("");

    //GET THE LEVEL AND DISPLAY IT
    stat_stream << "Range: " << selection_data.attack_range;

    game->reload_as_text("Range", "display font stats", stat_stream.str(), false, 0);
    game->set_point("Range", 0, 20+game->get_spot("Range").w/2, 130);

    stat_stream.str("");

    //GET THE LIVES AND DISPLAY THEM
    stat_stream << "Rate: " << selection_data.attack_rate;

    game->reload_as_text("Rate", "display font stats", stat_stream.str(), false, 0);
    game->set_point("Rate", 0, 20+game->get_spot("Rate").w/2, 170);

    stat_stream.str("");

    //GET THE DESCRIPTION
    std::string tower_description = selection_data.description;

    game->reload_as_text("Tower Description", "display font description", tower_description, true, 220);
    game->set_spot("Tower Description", {0,0,game->get_image_x_size("Tower Description"), game->get_image_y_size("Tower Description")});
    game->set_point("Tower Description", 0, 20+game->get_spot("Tower Description").w/2, 200+game->get_spot("Tower Description").h/2);

    //GET THE UPGRADE/BUILD COST/SELLING COST
    if (is_building){
        stat_stream << selection_data.metal_use;
        game->reload_as_text("Metal Cost", "display font costs", stat_stream.str(), false, 0);
        game->set_point("Metal Cost", 0, 32+game->get_spot("Metal Cost").w/2, 552);
        game->set_active("Metal Cost", true);
        stat_stream.str("");

        stat_stream << selection_data.wood_use;
        game->reload_as_text("Wood Cost", "display font costs", stat_stream.str(), false, 0);
        game->set_point("Wood Cost", 0, 109+game->get_spot("Wood Cost").w/2, 552);
        game->set_active("Wood Cost", true);
        stat_stream.str("");

        stat_stream << selection_data.crystal_use;
        game->reload_as_text("Crystal Cost", "display font costs", stat_stream.str(), false, 0);
        game->set_point("Crystal Cost", 0, 186+game->get_spot("Crystal Cost").w/2, 552);
        game->set_active("Crystal Cost", true);
        stat_stream.str("");

        game->set_active("Metal Upgrade Cost", false);
        game->set_active("Wood Upgrade Cost", false);
        game->set_active("Crystal Upgrade Cost", false);
    } else {
        game->set_active("Metal Cost", false);
        game->set_active("Wood Cost", false);
        game->set_active("Crystal Cost", false);

        //CHECK IF UPGRADABLE
        if (selection_data.has_upgrade){
            //GET THE COST OF THE UPGRADE
            tower_data upgrade_selection = table->get_tower_data(selection_data.upgrade_name);

            stat_stream << upgrade_selection.metal_use;
            game->reload_as_text("Metal Cost", "display font costs", stat_stream.str(), false, 0);
            game->set_point("Metal Cost", 0, 32+game->get_spot("Metal Cost").w/2, 552);
            game->set_active("Metal Cost", true);
            stat_stream.str("");

            stat_stream << upgrade_selection.wood_use;
            game->reload_as_text("Wood Cost", "display font costs", stat_stream.str(), false, 0);
            game->set_point("Wood Cost", 0, 109+game->get_spot("Wood Cost").w/2, 552);
            game->set_active("Wood Cost", true);
            stat_stream.str("");

            stat_stream << upgrade_selection.crystal_use;
            game->reload_as_text("Crystal Cost", "display font costs", stat_stream.str(), false, 0);
            game->set_point("Crystal Cost", 0, 186+game->get_spot("Crystal Cost").w/2, 552);
            game->set_active("Crystal Cost", true);
            stat_stream.str("");
        }
    }

    if (is_selling){
        stat_stream << selection_data.metal_sell;
        game->reload_as_text("Sell Metal Cost", "display font costs", stat_stream.str(), false, 0);
        game->set_point("Sell Metal Cost", 0, 32+game->get_spot("Sell Metal Cost").w/2, 622);
        game->set_active("Sell Metal Cost", true);
        stat_stream.str("");

        stat_stream << selection_data.wood_sell;
        game->reload_as_text("Sell Wood Cost", "display font costs", stat_stream.str(), false, 0);
        game->set_point("Sell Wood Cost", 0, 109+game->get_spot("Sell Wood Cost").w/2, 622);
        game->set_active("Sell Wood Cost", true);
        stat_stream.str("");

        stat_stream << selection_data.crystal_sell;
        game->reload_as_text("Sell Crystal Cost", "display font costs", stat_stream.str(), false, 0);
        game->set_point("Sell Crystal Cost", 0, 186+game->get_spot("Sell Crystal Cost").w/2, 622);
        game->set_active("Sell Crystal Cost", true);
        stat_stream.str("");
    } else {
        game->set_active("Sell Metal Cost", false);
        game->set_active("Sell Wood Cost", false);
        game->set_active("Sell Crystal Cost", false);
    }
}

void td_module::build_tower_click(){
    //COME HERE FROM BUILD STATE

    //CHECK IF THE POINT IS BUILDABLE FIRST
    tower_found();

    if (can_build_on_point() && !level_playing && selected_tower_index == -1){
        //CHECK IF RESOURCES ARE AVAILABLE


        //RESOURCE CHECKING IN A SEPARATE FUNCTION BECAUSE OF UGLY NESTING REQUIRED
        if (have_resources()){

            //BUILD THE TOWER AT THAT POINT
            //std::cout << "Building tower..." << std::endl;

            //adding the tower
            create_tower();

            draw_grid();

            //selecting the new tower
            observe_grid_click();

            draw_towers();

            //UPDATE THE BOARD
            draw_board();
        }
        //NOTIFY THERE IS NOT ENOUGH OF THE GIVEN RESOURCES

    } else {
        //NOTIFY THE POINT CANNOT BE BUILT ON
        //std::cout << "Can't build there!" << std::endl;

        notification_message = "Can't build there!";
        notification_on = true;
    }

    if (level_playing){
        notification_message = "Can't build while level is playing!";
    }

    extern main_controller* game;
    game->clear_points("Tower Select");

    set_build_click(BUILD_BUTTON_NONE);
}

bool td_module::have_resources(){
    extern td_level_loader* table;

    int metal_to_use = table->get_tower_data(tower_data_name).metal_use;
    int wood_to_use = table->get_tower_data(tower_data_name).wood_use;
    int crystal_to_use = table->get_tower_data(tower_data_name).crystal_use;

    if (td_resources.at("Metal").use_resource(metal_to_use)){
        if (td_resources.at("Wood").use_resource(wood_to_use)){
            if (td_resources.at("Crystal").use_resource(crystal_to_use)){
                return true;
            } else {
                //REFUND
                td_resources.at("Metal").add_to_resource(metal_to_use);
                td_resources.at("Wood").add_to_resource(metal_to_use);

                //NOTIFY
                notification_message = "Not enough crystal!";
                notification_on = true;
            }
        } else {
            //REFUND
            td_resources.at("Metal").add_to_resource(metal_to_use);

            //NOTIFY
            notification_message = "Not enough lumber!";
            notification_on = true;
        }
    } else {
        //NOTIFY
        notification_message = "Not enough metal!";
        notification_on = true;
    }

    return false;
}

void td_module::create_tower(){
    ///GET THE TOWER DATA FROM THE TABLE FIRST
    extern td_level_loader* table;

    tower_data tower_to_create = table->get_tower_data(tower_data_name);
    tower_bullet_data bullet_to_create = table->get_bullet_data(tower_to_create.bullet_data_name);

    std::stringstream ss;
    ss << tower_to_create.tower_name << total_towers;

    td_towers.push_back(tower(x_click*SQUARE_SIZE+SQUARE_SIZE/2, y_click*SQUARE_SIZE+SQUARE_SIZE/2, tower_to_create.attack_range, 1,
                              tower_to_create.attack_rate,
                              tower_to_create.new_tile, td_grid.get_grid_data_at_current_point(),
                              tower_data_name, ss.str(), tower_to_create.tower_image, bullet_to_create));

    //ADDING AURAS IF NEEDED
    if (!tower_to_create.auras.empty()){
        for (unsigned int i = 0; i < tower_to_create.auras.size(); i++)
            td_towers.back().add_tower_aura(tower_to_create.auras.at(i));
    }

    td_towers.back().set_towers(&td_towers);
    td_towers.back().set_bullets(&td_bullets);
    td_towers.back().set_enemies(&td_enemies);

    //std::cout << td_towers.back().get_name() << std::endl;

    add_tower_image(ss.str(), tower_to_create.tower_image);

    //setting tower base
    //determining what to set for that grid point first
    int buildover_tile = determine_buildover(td_towers.back().get_buildover_type(), td_grid.get_grid_data_at_current_point());
    td_grid.set_grid_data(buildover_tile);

    total_towers++;
}

void td_module::observe_grid_over(){
    extern main_controller* game;

    //FROM DEFAULT STATE
    game->clear_points("Circle Select");

    //CHECK IF ANY TOWER FALLS UNDER THE COORDINATES OF BEING CLICKED
    for (unsigned int i = 0; i < td_towers.size(); i++)
        if (td_towers.at(i).get_range()->get_x()/90 == x_click &&
            td_towers.at(i).get_range()->get_y()/90 == y_click)
            game->add_point("Circle Select", x_click*SQUARE_SIZE+SQUARE_SIZE/2, y_click*SQUARE_SIZE+SQUARE_SIZE/2);
}

void td_module::build_tower_over(){
    extern main_controller* game;

    //FROM BUILD STATE
    game->clear_points("Tower Select");
    game->add_point("Tower Select",x_click*SQUARE_SIZE+45,y_click*SQUARE_SIZE+45);
    tower_found();


    //NOTIFY IF A BUILDABLE SPOT BY CHANGING TOWER SELECT COLOR
    if (can_build_on_point() && selected_tower_index == -1){
        game->set_color("Tower Select", {0x33,0xFF,0x33,0x00});
    } else {
        game->set_color("Tower Select", {0xFF,0x33,0x33,0x00});
    }

    game->clear_points("Circle Selected");
}

bool td_module::over_tower_on_point(){
    return true;
}

bool td_module::can_build_on_point(){
    int point_data = td_grid.get_grid_data_at_current_point();

    return (point_data != 0 && point_data != 3);
}

void td_module::upgrade_tower(){
    if (selected_tower_index > -1 && !level_playing){
        //extern main_controller* game;
        extern td_level_loader* table;

        //GETTING TOWER DATA
        tower_data tower_to_upgrade_into_data = table->get_tower_data(td_towers.at(selected_tower_index).get_display_name());

        //CHECK IF THERE IS ACTUALLY AN UPGRADE
        if (tower_to_upgrade_into_data.has_upgrade){
            tower_data_name = tower_to_upgrade_into_data.upgrade_name;

            if (have_resources()){
                //STORING THE CURRENT POINT BEFOREHAND
                x_click = td_towers.at(selected_tower_index).get_range()->get_x()/90;
                y_click = td_towers.at(selected_tower_index).get_range()->get_y()/90;

                //CLEARING PREVIOUS TOWER
                erase_tower();

                td_grid.set_grid_point(x_click, y_click);

                //GETTING THE TOWER UPGRADE
                create_tower();
                draw_towers();
                draw_board();
                draw_grid();

                selected_tower_index = td_towers.size()-1;
                observe_grid_click();
            }
        }
    }

    if (level_playing){
        notification_message = "Can't upgrade while level is playing!";
        notification_on = true;
    }
}

void td_module::sell_tower(){
    if (selected_tower_index > -1 && !level_playing){
        extern main_controller* game;
        extern td_level_loader* table;

        //GETTING TOWER DATA
        tower_data tower_to_sell_data = table->get_tower_data(td_towers.at(selected_tower_index).get_display_name());

        td_resources.at("Metal").add_to_resource(tower_to_sell_data.metal_sell);
        td_resources.at("Wood").add_to_resource(tower_to_sell_data.wood_sell);
        td_resources.at("Crystal").add_to_resource(tower_to_sell_data.crystal_sell);

        erase_tower();
        draw_towers();
        draw_board();
        draw_grid();
        game->clear_points("Circle Selected");
        observe_grid_click();
    }

    if (level_playing){
        notification_message = "Can't sell while level is playing!";
        notification_on = true;
    }
}

void td_module::erase_tower(){
    remove_tower_image(td_towers.at(selected_tower_index).get_name());
    td_grid.set_grid_point(td_towers.at(selected_tower_index).get_range()->get_x()/SQUARE_SIZE, td_towers.at(selected_tower_index).get_range()->get_y()/SQUARE_SIZE);
    td_grid.set_grid_data(td_towers.at(selected_tower_index).get_old_tile());
    td_towers.erase(td_towers.begin()+selected_tower_index);
    selected_tower_index = -1;
    draw_grid();
}

void td_module::move_up(bool move_state){
    moving_up = move_state;
}

void td_module::move_down(bool move_state){
    moving_down = move_state;
}

void td_module::move_left(bool move_state){
    moving_left = move_state;
}

void td_module::move_right(bool move_state){
    moving_right = move_state;
}

void td_module::start_level(){
    if (!level_playing && !td_waves.empty()){
        extern td_level_loader* table;

        std::vector<grid_node<int>> final_path = td_grid.create_path();
        level_path.clear();

        ///GET THE WAVE FROM THE QUEUE
        std::queue<std::string> wave_to_load = table->get_wave(td_waves.front());
        total_wave_enemies = wave_to_load.size();
        td_waves.pop();

        unsigned int final_path_index = 0;

        while (final_path_index < final_path.size()){
            std::cout << "(" << final_path.at(final_path_index).x_coord << ", " << final_path.at(final_path_index).y_coord << ") ";
            level_path.push_back(point(final_path.at(final_path_index).x_coord*90+45, final_path.at(final_path_index).y_coord*90+45));
            final_path_index++;
        }


        //CHECK IF REACHES THE END
        if (!level_path.empty()){
            level_playing = true;

            //ADD THE ENEMIES
            while (!wave_to_load.empty()){
                enemy_data_name = wave_to_load.front();
                create_enemy();
                wave_to_load.pop();
            }

            //SET THE WAVE SIZE FOR TOWERS TO CONSIDER
            for (unsigned int i = 0; i < td_towers.size(); i++){
                td_towers.at(i).set_wave_size(total_wave_enemies);
            }

        } else {
            //NOTIFY THE PATH IS BLOCKED
            notification_message = "The path is blocked!";
            notification_on = true;
        }
    }
}

void td_module::create_enemy(){
    extern td_level_loader* table;

    ///GET THE ENEMY DATA FIRST
    enemy_data enemy_to_create = table->get_enemy_data(enemy_data_name);

    //std::cout << "ADDING ENEMY TO THE SPAWN" << std::endl;
    std::stringstream ss;
    ss << enemy_to_create.enemy_name << total_enemies;

    std::cout << ss.str() << std::endl;

    enemies_to_spawn.push(std::pair<int, enemy>(total_enemies, enemy(enemy_to_create.enemy_hp_base + enemy_to_create.enemy_hp_scale*level.get_resource(),
                                                                     enemy_to_create.enemy_regen_base + enemy_to_create.enemy_regen_scale*level.get_resource(),
                                                                     enemy_to_create.enemy_armor_base + enemy_to_create.enemy_armor_scale*level.get_resource(),
                                                                     enemy_to_create.enemy_armor_type,
                                                                     enemy_to_create.enemy_speed_base + enemy_to_create.enemy_speed_scale*level.get_resource(),
                                                                     level_path.front().get_x(), level_path.front().get_y(), SQUARE_SIZE/2,
                                                                     ss.str(), enemy_to_create.enemy_image_source,
                                                                     enemy_to_create.enemy_metal_bounty_base + enemy_to_create.enemy_metal_bounty_scale*level.get_resource(),
                                                                     enemy_to_create.enemy_wood_bounty_base + enemy_to_create.enemy_wood_bounty_scale*level.get_resource(),
                                                                     enemy_to_create.enemy_crystal_bounty_base + enemy_to_create.enemy_crystal_bounty_scale*level.get_resource(),
                                                                     enemies_to_spawn.size())));

    //ADDING TRAVEL PATHS
    enemies_to_spawn.top().second.set_path(level_path);

    total_enemies++;
}

bool td_module::remaining_enemies_to_spawn(){
    return !enemies_to_spawn.empty();
}

void td_module::spawn_enemy(){
    int spawn_index;
    td_enemies.insert(std::pair<int, enemy>(spawn_index = enemies_to_spawn.top().first, enemies_to_spawn.top().second));
    td_enemies.at(spawn_index).activate_enemy_image();
    td_enemies.at(spawn_index).create_hp_bar();

    enemies_to_spawn.pop();
}

void td_module::draw_bullets(){
        extern main_controller* game;


    if (!td_bullets.bullets.empty()){
        unsigned int i = 0;

        while (i < td_bullets.bullets.size()){
            game->clear_points(td_bullets.bullets.at(i).get_name());
            game->add_point(td_bullets.bullets.at(i).get_name(), td_bullets.bullets.at(i).get_hitbox()->get_x(), td_bullets.bullets.at(i).get_hitbox()->get_y());
            i++;

        }
    }
}

void td_module::draw_enemies(){
    for (std::map<int, enemy>::iterator enemy_iterator = td_enemies.begin(); enemy_iterator != td_enemies.end(); ++enemy_iterator){
        enemy_iterator->second.draw_enemy();
    }
}

void td_module::enemy_bountied(int enemy_index){
    td_resources.at("Metal").add_to_resource(td_enemies.at(enemy_index).get_metal_bounty());
    td_resources.at("Wood").add_to_resource(td_enemies.at(enemy_index).get_wood_bounty());
    td_resources.at("Crystal").add_to_resource(td_enemies.at(enemy_index).get_crystal_bounty());

    kill_enemy(enemy_index);
    draw_board();
}

void td_module::enemy_at_end(int enemy_index){
    remove_life();
    kill_enemy(enemy_index);
    draw_board();
}

void td_module::kill_enemy(int enemy_index){
    if (td_enemies.find(enemy_index) != td_enemies.end()){
        //ERASE THAT ENEMY
        td_enemies.at(enemy_index).remove_enemy_image();
        td_enemies.erase(enemy_index);
    }
}

void td_module::set_selected_map(std::string new_map){
    selected_map = new_map;
}

std::string td_module::get_selected_map(){
    return selected_map;
}

void td_module::set_build_race_one(std::string new_race_one){
    build_race_1 = new_race_one;
}

void td_module::set_build_race_two(std::string new_race_two){
    build_race_2 = new_race_two;
}

void td_module::set_to_race_one(){
    load_button_mapping(BUILD_RACE_ONE);
    set_button_data_set();
}

void td_module::set_to_race_two(){
    load_button_mapping(BUILD_RACE_TWO);
    set_button_data_set();
}

void td_module::set_tower_data_to_look_up(std::string new_tower_data_name){
    tower_data_name = new_tower_data_name;
}

void td_module::set_enemy_data_to_look_up(std::string new_enemy_data_name){
    enemy_data_name = new_enemy_data_name;
}
