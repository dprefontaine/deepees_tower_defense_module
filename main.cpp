#include "main.h"

void creating_td_clicker(){
    //grid click
    std::vector<SDL_Rect> grid_button = std::vector<SDL_Rect>();
    grid_button.push_back({0,0,GRID_SIZE_X*SQUARE_SIZE, GRID_SIZE_Y*SQUARE_SIZE});
    game->new_button("TD Grid", 0, 1, grid_button);
    game->set_button_active("TD Grid", true);

    //EVENT WHEN CLICKING THE GRID
    game->add_mouse_procedure(room_procedure(grid_click, true, false, 2, 1), 0, 1);

    //EVENT WHEN OVER THE GRID
    game->add_mouse_procedure(room_procedure(grid_over, true, false, 3, 1), 0, 1);
}

int build_button_clear_set(){
    build_button_one_push_up();
    build_button_two_push_up();
    build_button_three_push_up();
    build_button_four_push_up();
    build_button_five_push_up();
    build_button_six_push_up();
    build_button_seven_push_up();
    build_button_eight_push_up();
    build_button_nine_push_up();


    return 0;
}

int build_button_one_push_down(){
    module->set_build_click(BUILD_BUTTON_ONE);

    build_button_clear_set();

    game->set_spot("Build Icon One", {95,0,95,95});


    return 0;
}

int build_button_one_push_up(){
    if (module->get_state() != MODULE_BUILD || module->get_build_click() != BUILD_BUTTON_ONE)
        game->set_spot("Build Icon One", {0,0,95,95});
    else if (module->get_build_click() == BUILD_BUTTON_ONE)
        game->set_spot("Build Icon One", {190,0,95,95});

    return 0;
}

int build_button_two_push_down(){
    module->set_build_click(BUILD_BUTTON_TWO);

    build_button_clear_set();

    game->set_spot("Build Icon Two", {95,0,95,95});

    return 0;
}

int build_button_two_push_up(){
    if (module->get_state() != MODULE_BUILD || module->get_build_click() != BUILD_BUTTON_TWO)
        game->set_spot("Build Icon Two", {0,0,95,95});
    else if (module->get_build_click() == BUILD_BUTTON_TWO)
        game->set_spot("Build Icon Two", {190,0,95,95});

    return 0;
}

int build_button_three_push_down(){
    module->set_build_click(BUILD_BUTTON_THREE);

    build_button_clear_set();

    game->set_spot("Build Icon Three", {95,0,95,95});

    return 0;
}

int build_button_three_push_up(){
    if (module->get_state() != MODULE_BUILD || module->get_build_click() != BUILD_BUTTON_THREE)
        game->set_spot("Build Icon Three", {0,0,95,95});
    else if (module->get_build_click() == BUILD_BUTTON_THREE)
        game->set_spot("Build Icon Three", {190,0,95,95});

    return 0;
}

int build_button_four_push_down(){
    module->set_build_click(BUILD_BUTTON_FOUR);

    build_button_clear_set();

    game->set_spot("Build Icon Four", {95,0,95,95});

    return 0;
}

int build_button_four_push_up(){
    if (module->get_state() != MODULE_BUILD || module->get_build_click() != BUILD_BUTTON_FOUR)
        game->set_spot("Build Icon Four", {0,0,95,95});
    else if (module->get_build_click() == BUILD_BUTTON_FOUR)
        game->set_spot("Build Icon Four", {190,0,95,95});

    return 0;
}

int build_button_five_push_down(){
    module->set_build_click(BUILD_BUTTON_FIVE);

    build_button_clear_set();

    game->set_spot("Build Icon Five", {95,0,95,95});

    return 0;
}

int build_button_five_push_up(){
    if (module->get_state() != MODULE_BUILD || module->get_build_click() != BUILD_BUTTON_FIVE)
        game->set_spot("Build Icon Five", {0,0,95,95});
    else if (module->get_build_click() == BUILD_BUTTON_FIVE)
        game->set_spot("Build Icon Five", {190,0,95,95});

    return 0;
}

int build_button_six_push_down(){
    module->set_build_click(BUILD_BUTTON_SIX);

    build_button_clear_set();

    game->set_spot("Build Icon Six", {95,0,95,95});

    return 0;
}

int build_button_six_push_up(){
    if (module->get_state() != MODULE_BUILD || module->get_build_click() != BUILD_BUTTON_SIX)
        game->set_spot("Build Icon Six", {0,0,95,95});
    else if (module->get_build_click() == BUILD_BUTTON_SIX)
        game->set_spot("Build Icon Six", {190,0,95,95});

    return 0;
}

int build_button_seven_push_down(){
    module->set_build_click(BUILD_BUTTON_SEVEN);

    build_button_clear_set();

    game->set_spot("Build Icon Seven", {95,0,95,95});

    return 0;
}

int build_button_seven_push_up(){
    if (module->get_state() != MODULE_BUILD || module->get_build_click() != BUILD_BUTTON_SEVEN)
        game->set_spot("Build Icon Seven", {0,0,95,95});
    else if (module->get_build_click() == BUILD_BUTTON_SEVEN)
        game->set_spot("Build Icon Seven", {190,0,95,95});

    return 0;
}

int build_button_eight_push_down(){
    module->set_build_click(BUILD_BUTTON_EIGHT);

    build_button_clear_set();

    game->set_spot("Build Icon Eight", {95,0,95,95});

    return 0;
}

int build_button_eight_push_up(){
    if (module->get_state() != MODULE_BUILD || module->get_build_click() != BUILD_BUTTON_EIGHT)
        game->set_spot("Build Icon Eight", {0,0,95,95});
    else if (module->get_build_click() == BUILD_BUTTON_EIGHT)
        game->set_spot("Build Icon Eight", {190,0,95,95});

    return 0;
}

int build_button_nine_push_down(){
    module->set_build_click(BUILD_BUTTON_NINE);

    build_button_clear_set();

    game->set_spot("Build Icon Nine", {95,0,95,95});

    return 0;
}

int build_button_nine_push_up(){
    if (module->get_state() != MODULE_BUILD || module->get_build_click() != BUILD_BUTTON_NINE)
        game->set_spot("Build Icon Nine", {0,0,95,95});
    else if (module->get_build_click() == BUILD_BUTTON_NINE)
        game->set_spot("Build Icon Nine", {190,0,95,95});

    return 0;
}

int build_set_button_one_push_down(){
    game->set_spot("Set Icon One", {50,0,50,46});
    game->set_spot("Set Icon Two", {0,0,50,46});

    module->set_to_race_one();

    return 0;
}

int build_set_button_one_push_up(){
    //game->set_spot("Set Icon One", {0,0,50,46});

    return 0;
}

int build_set_button_two_push_down(){
    game->set_spot("Set Icon One", {0,0,50,46});
    game->set_spot("Set Icon Two", {50,0,50,46});

    module->set_to_race_two();

    return 0;
}

int build_set_button_two_push_up(){
    //game->set_spot("Set Icon Two", {0,0,50,46});

    return 0;
}

int start_button_push_down(){
    game->set_spot("Start Button", {250,0,250,70});

    module->start_level();

    return 0;
}

int start_button_push_up(){
    game->set_spot("Start Button", {0,0,250,70});

    return 0;
}

int speed_button_push_down(){
    int speed_state = module->toggling_speed();
    game->set_spot("Speed Button", {66*speed_state,0,66,66});

    return 0;
}

void creating_td_ui(){
    //creating UI backgrounds
    game->new_image("Top UI Background", "images/top_ui.png", 0, 0);
    game->set_active("Top UI Background", true);
    game->add_point("Top UI Background", SCREEN_WIDTH/2, SCREEN_HEIGHT/10);

    //create buttons here

    //build buttons
    game->new_image("Build Icon One", "images/build_tower_icon.png", 0, 0, {0,0,95,95});
    game->set_active("Build Icon One", true);
    game->add_point("Build Icon One", 70, 100);

    std::vector<SDL_Rect> build_button_1 = std::vector<SDL_Rect>();
    build_button_1.push_back({70-95/2,100-95/2,95,95});
    game->new_button("Build Button One", 0, 0, build_button_1);
    game->set_button_active("Build Button One", true);

    game->add_mouse_procedure(room_procedure(build_button_one_push_down, true, false, 2, 1), 0, 0);
    game->add_mouse_procedure(room_procedure(build_button_one_push_up, true, false, 1, 2), 0, 0);

    game->new_image("Build Icon Two", "images/build_tower_icon.png", 0, 0, {0,0,95,95});
    game->set_active("Build Icon Two", true);
    game->add_point("Build Icon Two", 170, 100);

    std::vector<SDL_Rect> build_button_2 = std::vector<SDL_Rect>();
    build_button_2.push_back({170-95/2,100-95/2,95,95});
    game->new_button("Build Button Two", 0, 0, build_button_2);
    game->set_button_active("Build Button Two", true);

    game->add_mouse_procedure(room_procedure(build_button_two_push_down, true, false, 7, 3), 0, 0);
    game->add_mouse_procedure(room_procedure(build_button_two_push_up, true, false, 6, 4), 0, 0);

    game->new_image("Build Icon Three", "images/build_tower_icon.png", 0, 0, {0,0,95,95});
    game->set_active("Build Icon Three", true);
    game->add_point("Build Icon Three", 270, 100);

    std::vector<SDL_Rect> build_button_3 = std::vector<SDL_Rect>();
    build_button_3.push_back({270-95/2,100-95/2,95,95});
    game->new_button("Build Button Three", 0, 0, build_button_3);
    game->set_button_active("Build Button Three", true);

    game->add_mouse_procedure(room_procedure(build_button_three_push_down, true, false, 12, 5), 0, 0);
    game->add_mouse_procedure(room_procedure(build_button_three_push_up, true, false, 11, 6), 0, 0);

    game->new_image("Build Icon Four", "images/build_tower_icon.png", 0, 0, {0,0,95,95});
    game->set_active("Build Icon Four", true);
    game->add_point("Build Icon Four", 370, 100);

    std::vector<SDL_Rect> build_button_4 = std::vector<SDL_Rect>();
    build_button_4.push_back({370-95/2,100-95/2,95,95});
    game->new_button("Build Button Four", 0, 0, build_button_4);
    game->set_button_active("Build Button Four", true);

    game->add_mouse_procedure(room_procedure(build_button_four_push_down, true, false, 17, 7), 0, 0);
    game->add_mouse_procedure(room_procedure(build_button_four_push_up, true, false, 16, 8), 0, 0);

    game->new_image("Build Icon Five", "images/build_tower_icon.png", 0, 0, {0,0,95,95});
    game->set_active("Build Icon Five", true);
    game->add_point("Build Icon Five", 470, 100);

    std::vector<SDL_Rect> build_button_5 = std::vector<SDL_Rect>();
    build_button_5.push_back({470-95/2,100-95/2,95,95});
    game->new_button("Build Button Five", 0, 0, build_button_5);
    game->set_button_active("Build Button Five", true);

    game->add_mouse_procedure(room_procedure(build_button_five_push_down, true, false, 22, 9), 0, 0);
    game->add_mouse_procedure(room_procedure(build_button_five_push_up, true, false, 21, 10), 0, 0);

    game->new_image("Build Icon Six", "images/build_tower_icon.png", 0, 0, {0,0,95,95});
    game->set_active("Build Icon Six", true);
    game->add_point("Build Icon Six", 570, 100);

    std::vector<SDL_Rect> build_button_6 = std::vector<SDL_Rect>();
    build_button_6.push_back({570-95/2,100-95/2,95,95});
    game->new_button("Build Button Six", 0, 0, build_button_6);
    game->set_button_active("Build Button Six", true);

    game->add_mouse_procedure(room_procedure(build_button_six_push_down, true, false, 27, 11), 0, 0);
    game->add_mouse_procedure(room_procedure(build_button_six_push_up, true, false, 26, 12), 0, 0);

    game->new_image("Build Icon Seven", "images/build_tower_icon.png", 0, 0, {0,0,95,95});
    game->set_active("Build Icon Seven", true);
    game->add_point("Build Icon Seven", 670, 100);

    std::vector<SDL_Rect> build_button_7 = std::vector<SDL_Rect>();
    build_button_7.push_back({670-95/2,100-95/2,95,95});
    game->new_button("Build Button Seven", 0, 0, build_button_7);
    game->set_button_active("Build Button Seven", true);

    game->add_mouse_procedure(room_procedure(build_button_seven_push_down, true, false, 32, 13), 0, 0);
    game->add_mouse_procedure(room_procedure(build_button_seven_push_up, true, false, 31, 14), 0, 0);

    game->new_image("Build Icon Eight", "images/build_tower_icon.png", 0, 0, {0,0,95,95});
    game->set_active("Build Icon Eight", true);
    game->add_point("Build Icon Eight", 770, 100);

    std::vector<SDL_Rect> build_button_8 = std::vector<SDL_Rect>();
    build_button_8.push_back({770-95/2,100-95/2,95,95});
    game->new_button("Build Button Eight", 0, 0, build_button_8);
    game->set_button_active("Build Button Eight", true);

    game->add_mouse_procedure(room_procedure(build_button_eight_push_down, true, false, 37, 15), 0, 0);
    game->add_mouse_procedure(room_procedure(build_button_eight_push_up, true, false, 36, 16), 0, 0);

    game->new_image("Build Icon Nine", "images/build_tower_icon.png", 0, 0, {0,0,95,95});
    game->set_active("Build Icon Nine", true);
    game->add_point("Build Icon Nine", 870, 100);

    std::vector<SDL_Rect> build_button_9 = std::vector<SDL_Rect>();
    build_button_9.push_back({870-95/2,100-95/2,95,95});
    game->new_button("Build Button Nine", 0, 0, build_button_9);
    game->set_button_active("Build Button Nine", true);

    game->add_mouse_procedure(room_procedure(build_button_nine_push_down, true, false, 42, 17), 0, 0);
    game->add_mouse_procedure(room_procedure(build_button_nine_push_up, true, false, 41, 18), 0, 0);
    game->add_mouse_procedure(room_procedure(build_button_clear_set, true, false, -1, 18), 0, 0);

    //build set buttons
    game->new_image("Set Icon One", "images/build_set_one.png", 0, 0, {0,0,50,46});
    game->set_active("Set Icon One", true);
    game->add_point("Set Icon One", 950, 76);

    std::vector<SDL_Rect> build_set_button_1 = std::vector<SDL_Rect>();
    build_set_button_1.push_back({950-50/2,76-46/2,50,46});
    game->new_button("Build Set Button One", 0, 0, build_set_button_1);
    game->set_button_active("Build Set Button One", true);

    game->add_mouse_procedure(room_procedure(build_set_button_one_push_down, true, false, 47, 17), 0, 0);
    game->add_mouse_procedure(room_procedure(build_set_button_one_push_up, true, false, 46, 18), 0, 0);
    game->add_mouse_procedure(room_procedure(build_set_button_one_push_up, true, false, -1, 18), 0, 0);

    game->new_image("Set Icon Two", "images/build_set_two.png", 0, 0, {0,0,50,46});
    game->set_active("Set Icon Two", true);
    game->add_point("Set Icon Two", 950, 125);

    std::vector<SDL_Rect> build_set_button_2 = std::vector<SDL_Rect>();
    build_set_button_2.push_back({950-50/2,125-46/2,50,46});
    game->new_button("Build Set Button Two", 0, 0, build_set_button_2);
    game->set_button_active("Build Set Button Two", true);

    game->add_mouse_procedure(room_procedure(build_set_button_two_push_down, true, false, 52, 17), 0, 0);
    game->add_mouse_procedure(room_procedure(build_set_button_two_push_up, true, false, 51, 18), 0, 0);
    game->add_mouse_procedure(room_procedure(build_set_button_two_push_up, true, false, -1, 18), 0, 0);

    //start button
    game->new_image("Start Button", "images/start_button.png", 0, 0, {0,0,250,70});
    game->set_active("Start Button", true);
    game->add_point("Start Button", 1130, 115);

    std::vector<SDL_Rect> start_button = std::vector<SDL_Rect>();
    start_button.push_back({1130-125,115-35,250,70});
    game->new_button("Start Button", 0, 0, start_button);
    game->set_button_active("Start Button", true);

    game->add_mouse_procedure(room_procedure(start_button_push_down, true, false, 57, 3), 0, 0);
    game->add_mouse_procedure(room_procedure(start_button_push_up, true, false, 56, 4), 0, 0);
    game->add_mouse_procedure(room_procedure(start_button_push_up, true, false, -1, 4), 0, 0);

    //speed button
    game->new_image("Speed Button", "images/speed_button.png", 0, 0, {0,0,66,66});
    game->set_active("Speed Button", true);
    game->add_point("Speed Button", 1025, 44);

    std::vector<SDL_Rect> speed_button = std::vector<SDL_Rect>();
    speed_button.push_back({992,11,66,66});
    game->new_button("Speed Button", 0, 0, speed_button);
    game->set_button_active("Speed Button", true);

    game->add_mouse_procedure(room_procedure(speed_button_push_down, true, false, 62, 20), 0, 0);
}

int upgrade_push_down(){
    game->set_spot("Upgrade Button", {236,0,236,68});

    module->upgrade_tower();

    return 0;
}

int upgrade_push_up(){
    game->set_spot("Upgrade Button", {0,0,236,68});

    return 0;
}

int sell_push_down(){
    game->set_spot("Sell Button", {236,0,236,68});

    module->sell_tower();

    return 0;
}

int sell_push_up(){
    game->set_spot("Sell Button", {0,0,236,68});

    return 0;
}

void creating_td_info_display(){
    //TD INFO BACKGROUND
    game->new_image("Tower Info Background", "images/tower_stat_ui.png", 0, 2);
    game->add_point("Tower Info Background", SCREEN_WIDTH/10, SCREEN_HEIGHT*2/5);
    game->set_active("Tower Info Background", true);

    //COST DISPLAY AND UPGRADE BUTTON
    std::vector<SDL_Rect> upgrade_button = std::vector<SDL_Rect>();
    upgrade_button.push_back({SCREEN_WIDTH/10 - 118,530-34,236,68});

    game->new_image("Cost Display", "images/cost_display.png", 0, 2, {0,0,236,68});
    game->add_point("Cost Display", SCREEN_WIDTH/10, 530);

    game->new_image("Upgrade Button", "images/upgrade_button.png", 0, 2, {0,0,236,68});
    game->add_point("Upgrade Button", SCREEN_WIDTH/10, 530);

    game->new_image("Button Metal", "images/resource_icons/metal_icon_small.png", 0, 2, {0,0,15,15});
    game->set_blend_mode("Button Metal", SDL_BLENDMODE_BLEND);
    game->add_point("Button Metal", SCREEN_WIDTH/10-106, 552);

    game->new_text("Metal Cost", "display font costs", 0, 2, "30", false, 0);
    game->add_point("Metal Cost", SCREEN_WIDTH/10-96+game->get_spot("Metal Cost").w/2, 552);

    game->new_image("Button Wood", "images/resource_icons/wood_icon_small.png", 0, 2, {0,0,15,15});
    game->set_blend_mode("Button Wood", SDL_BLENDMODE_BLEND);
    game->add_point("Button Wood", SCREEN_WIDTH/10-29, 552);

    game->new_text("Wood Cost", "display font costs", 0, 2, "30", false, 0);
    game->add_point("Wood Cost", SCREEN_WIDTH/10-19+game->get_spot("Wood Cost").w/2, 552);

    //std::cout << SCREEN_WIDTH/10-19 << std::endl; //109

    game->new_image("Button Crystal", "images/resource_icons/crystal_icon_small.png", 0, 2, {0,0,15,15});
    game->set_blend_mode("Button Crystal", SDL_BLENDMODE_BLEND);
    game->add_point("Button Crystal", SCREEN_WIDTH/10+49, 552);

    //std::cout << SCREEN_WIDTH/10+49 << std::endl; //177

    game->new_text("Crystal Cost", "display font costs", 0, 2, "30", false, 0);
    game->add_point("Crystal Cost", SCREEN_WIDTH/10+59+game->get_spot("Crystal Cost").w/2, 552);

    game->new_button("Upgrade Button", 0, 2, upgrade_button);
    game->add_mouse_procedure(room_procedure(upgrade_push_down, true, false, 2, 4), 0, 2);
    game->add_mouse_procedure(room_procedure(upgrade_push_up, true, false, 1, 5), 0, 2);
    game->add_mouse_procedure(room_procedure(upgrade_push_up, true, false, -1, 6), 0, 2);

    game->new_image("Blank Upgrade Button", "images/invalid_display.png", 0, 2);
    game->add_point("Blank Upgrade Button", SCREEN_WIDTH/10, 530);

    //SELL BUTTON
    std::vector<SDL_Rect> sell_button = std::vector<SDL_Rect>();
    sell_button.push_back({SCREEN_WIDTH/10 - 118,600-34,236,68});

    game->new_image("Sell Button", "images/sell_button.png", 0, 2, {0,0,236,68});
    game->add_point("Sell Button", SCREEN_WIDTH/10, 600);

    game->copy_image("Blank Sell Button", "Blank Upgrade Button");
    game->add_point("Blank Sell Button", SCREEN_WIDTH/10, 600);

    game->copy_image("Sell Button Metal", "Button Metal");
    game->copy_image("Sell Button Wood", "Button Wood");
    game->copy_image("Sell Button Crystal", "Button Crystal");

    game->add_point("Sell Button Metal", SCREEN_WIDTH/10-106, 622);
    game->add_point("Sell Button Wood", SCREEN_WIDTH/10-29, 622);
    game->add_point("Sell Button Crystal", SCREEN_WIDTH/10+49, 622);

    game->new_text("Sell Metal Cost", "display font costs", 0, 2, "30", false, 0);
    game->add_point("Sell Metal Cost", SCREEN_WIDTH/10-96+game->get_spot("Sell Metal Cost").w/2, 622);

    game->new_text("Sell Wood Cost", "display font costs", 0, 2, "30", false, 0);
    game->add_point("Sell Wood Cost", SCREEN_WIDTH/10-19+game->get_spot("Sell Wood Cost").w/2, 622);

    game->new_text("Sell Crystal Cost", "display font costs", 0, 2, "30", false, 0);
    game->add_point("Sell Crystal Cost", SCREEN_WIDTH/10+49+game->get_spot("Sell Crystal Cost").w/2, 622);

    game->new_button("Sell Button", 0, 2, sell_button);
    game->add_mouse_procedure(room_procedure(sell_push_down, true, false, 7, 7), 0, 2);
    game->add_mouse_procedure(room_procedure(sell_push_up, true, false, 6, 8), 0, 2);
    game->add_mouse_procedure(room_procedure(sell_push_up, true, false, -1, 9), 0, 2);
    //game->set_button_active("Sell Button", true);

    game->new_text("Tower Name", "base font", 0, 2, "Tower", false, 0);
    game->add_point("Tower Name", SCREEN_WIDTH/10, 40);
    //game->set_active("Tower Name", true);

    game->new_text("Attack", "base font", 0, 2, "Attack: 10", false, 0);
    game->add_point("Attack", SCREEN_WIDTH/10, 90);
    //game->set_active("Attack", true);

    game->new_text("Range", "base font", 0, 2, "Range: 10", false, 0);
    game->add_point("Range", SCREEN_WIDTH/10, 130);
    //game->set_active("Range", true);

    game->new_text("Rate", "base font", 0, 2, "Rate: 10", false, 0);
    game->add_point("Rate", SCREEN_WIDTH/10, 170);
    //game->set_active("Rate", true);

    game->new_text("Tower Description", "base font", 0, 2, "Rate: 10", false, 0);
    game->add_point("Tower Description", SCREEN_WIDTH/10, 215);

    game->new_image("Select", "images/select_blank.png", 0, 2);
    game->add_point("Select", SCREEN_WIDTH/10, SCREEN_HEIGHT*2/5);
    game->set_active("Select", true);



    //board
    game->new_text("Metal", "base font", 0, 0, "Metal: 200", 0xFF, 0xFF, 0xFF, 0xFF, false, 0);
    game->add_point("Metal", 30+game->get_spot("Metal").w/2, 30);
    game->set_active("Metal", true);

    game->new_text("Wood", "base font", 0, 0, "Lumber: 100", 0xFF, 0xFF, 0xFF, 0xFF, false, 0);
    game->add_point("Wood", 200+game->get_spot("Wood").w/2, 30);
    game->set_active("Wood", true);

    game->new_text("Crystal", "base font", 0, 0, "Crystal: 10", 0xFF, 0xFF, 0xFF, 0xFF, false, 0);
    game->add_point("Crystal", 500+game->get_spot("Crystal").w/2, 30);
    game->set_active("Crystal", true);

    game->new_text("Level", "base font", 0, 0, "Level: 1", 0xFF, 0xFF, 0xFF, 0xFF, false, 0);
    game->add_point("Level", 750+game->get_spot("Level").w/2, 30);
    game->set_active("Level", true);

    game->new_text("Lives", "base font", 0, 0, "Lives: 15", 0xFF, 0xFF, 0xFF, 0xFF, false, 0);
    game->add_point("Lives", 900+game->get_spot("Lives").w/2, 30);
    game->set_active("Lives", true);
}

int mouse_follow(unsigned int ticks){
    static int x, y;
    static Uint32 mouse_state;

    mouse_state = SDL_GetMouseState(&x, &y);

    ///Consider if the mouse is over the grid and the grid is currently building something
    if (module->get_state() == MODULE_BUILD){
        if (x < SCREEN_WIDTH*4/5 && (y > SCREEN_HEIGHT/5 && y < SCREEN_HEIGHT) && game->get_active("Cursor")){
            game->set_active("Cursor", false);
        } else if (!(x < SCREEN_WIDTH*4/5 && (y > SCREEN_HEIGHT/5 && y < SCREEN_HEIGHT)) && !game->get_active("Cursor")){
            game->set_active("Cursor", true);
            game->clear_points("Tower Select");
        }
    } else if (!game->get_active("Cursor")){
        game->set_active("Cursor", true);
    }

    if (mouse_state == SDL_BUTTON_LEFT)
        game->set_spot("Cursor", {50, 0, 50, 50});
    else
        game->set_spot("Cursor", {0, 0, 50, 50});

    ///Mouse follow
    game->clear_points("Cursor");
    game->add_point("Cursor", x+12, y+15);

    ///Check also if the mouse is over a tower or enemy

    return 0;
}

int press_camera_up(){
    module->move_up(true);

    return 0;
}

int release_camera_up(){
    module->move_up(false);

    return 0;
}

int press_camera_down(){
    module->move_down(true);

    return 0;
}

int release_camera_down(){
    module->move_down(false);

    return 0;
}

int press_camera_left(){
    module->move_left(true);

    return 0;
}

int release_camera_left(){
    module->move_left(false);

    return 0;
}

int press_camera_right(){
    module->move_right(true);

    return 0;
}

int release_camera_right(){
    module->move_right(false);

    return 0;
}

int grid_click(){
    int x, y;
    x = game->get_button_over_x("TD Grid");
    y = game->get_button_over_y("TD Grid");

    module->click_on_grid(x, y);

    return 0;
}

int grid_over(){
    int x, y;
    x = game->get_button_over_x("TD Grid");
    y = game->get_button_over_y("TD Grid");

    module->over_grid(x, y);

    return 0;
}

int grid_start(){
    module->start_level();

    return 0;
}

int update_module(unsigned int ticks){
    module->update_td_module(ticks);

    return 0;
}

void load_module_room(){
    //Cursor
    game->new_image("Cursor", "images/cursor.png", 0, {0,0,50,50});
    game->set_blend_mode("Cursor", SDL_BLENDMODE_BLEND);
    game->set_active("Cursor", true);

    //TD grid, towers, and enemies
    //grid
    load_grid_tiles();

    //destination points
    load_destination_points();

    //effects
    load_debuffs();

    //enemy
    load_enemies();

    //tower
    load_towers();
    load_tower_selection();
    load_bullets();

    //notification
    game->new_text("Notification", "notification font", 0, "blank", false, 0);
    game->set_color("Notification", {0xFF, 0xFF, 0x33, 0xFF});
    game->add_point("Notification", SCREEN_WIDTH/2, SCREEN_HEIGHT/3);

    ///clicking grid & buttons
    creating_td_clicker();
    creating_td_ui();
    load_resource_icons();
    creating_td_info_display();

    ///LOADING MAP
    module->set_selected_map(SELECTED_LEVEL);
    module->load_map();
    module->set_points();

    module->draw_grid();
    module->draw_points();

    module->set_button_data_set();

    game->add_pre_render_procedure(loop_procedure(update_module, true, true, true, 1));

    ///LOADING RACES
    module->load_button_mapping(BUILD_RACE_ONE);
    build_set_button_one_push_down();
}

int title_click(){
    game->set_room(0);

    load_module_room();

    return 0;
}

int set_map_to_default(){
    SELECTED_LEVEL = "Default";

    return 0;
}

int set_map_to_crossing(){
    SELECTED_LEVEL = "Crossing";

    return 0;
}

int set_map_to_traditional(){
    SELECTED_LEVEL = "Traditional";

    return 0;
}

void load_title_room(){
    game->new_image("Title Image", "images/title_screen_bg_and_title.png", TITLE_ROOM, 0);
    game->add_point("Title Image", SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    game->set_active("Title Image", true);

    game->new_text("Title Text", "notification font", TITLE_ROOM, 0, "Press anywhere to go to the game", 0xFF, 0xFF, 0x00, 0xFF, false, 0);
    game->add_point("Title Text", SCREEN_WIDTH*2/3+20, SCREEN_HEIGHT*8/9 + 40);
    game->set_active("Title Text", true);

    game->new_text("Settings Text", "display font stats", TITLE_ROOM, 0, "Press 'i' for default map    Press 'o' for crossing map    Press 'p' for traditional map", 0xFF, 0xFF, 0x00, 0xFF, true, 350);
    game->add_point("Settings Text", SCREEN_WIDTH*1/4-80, SCREEN_HEIGHT*7/9+80);
    game->set_active("Settings Text", true);

    std::vector<SDL_Rect> title_rect = std::vector<SDL_Rect>();
    title_rect.push_back({0,0,SCREEN_WIDTH, SCREEN_HEIGHT});

    game->new_button("Title Button" , 1, 0, title_rect);
    game->add_mouse_procedure(room_procedure(title_click, true, false, 2, 0), TITLE_ROOM, 0);
    game->set_button_active("Title Button", true);

    game->add_key_procedure(key_procedure(set_map_to_default, true, true, SDL_SCANCODE_I, 0));
    game->add_key_procedure(key_procedure(set_map_to_crossing, true, true, SDL_SCANCODE_O, 1));
    game->add_key_procedure(key_procedure(set_map_to_traditional, true, true, SDL_SCANCODE_P, 2));
}

int main(int args, char* argv[]){
    game = NULL;
    module = NULL;

    game = new main_controller(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NAME, PRINTING);
    game->set_cursor(SDL_DISABLE);

    module = new td_module(180, 180, 15, 15);

    table = new td_level_loader();

    //INITIALIZING THE MODULE

    if (!game->initialize()){
        std::cout << "This framework has failed!" << std::endl;
    } else {
        std::cout << "This framework has loaded!" << std::endl;
        int ticks;

        game->add_font("base font", "fonts/Primitive.ttf", 28);
        game->add_font("notification font", "fonts/Primitive.ttf", 34);

        game->add_font("display font header", "fonts/Primitive.ttf", 26);
        game->add_font("display font stats", "fonts/Primitive.ttf", 22);
        game->add_font("display font description", "fonts/Primitive.ttf", 18);
        game->add_font("display font costs", "fonts/Primitive.ttf", 14);

        ///Adding the rooms & panels

        game->new_room();
        game->new_panel(GAME_ROOM, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT/5);
        game->new_panel(GAME_ROOM, 0, SCREEN_HEIGHT/5, SCREEN_WIDTH*4/5, SCREEN_HEIGHT*4/5, SQUARE_SIZE*GRID_SIZE_X, SQUARE_SIZE*GRID_SIZE_Y);
        game->new_panel(GAME_ROOM, SCREEN_WIDTH*4/5, SCREEN_HEIGHT/5, SCREEN_WIDTH/5, SCREEN_HEIGHT*4/5);

        game->new_room();
        game->new_panel(TITLE_ROOM, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

        game->set_room(TITLE_ROOM);

        ///====================================================================Loading assets

        ///-------------------------------TITLE ROOM
        load_title_room();


        ///-------------------------------MODULE ROOM
        ///Adding procedures
        //cursor
        game->add_pre_render_procedure(loop_procedure(mouse_follow, false, true, true, 0));

        //camera
        game->add_key_procedure(key_procedure(press_camera_up, true, true, SDL_SCANCODE_W, 0));
        game->add_key_procedure(key_procedure(release_camera_up, true, true, -SDL_SCANCODE_W, 0));
        game->add_key_procedure(key_procedure(press_camera_down, true, true, SDL_SCANCODE_S, 1));
        game->add_key_procedure(key_procedure(release_camera_down, true, true, -SDL_SCANCODE_S, 1));
        game->add_key_procedure(key_procedure(press_camera_left, true, true, SDL_SCANCODE_A, 2));
        game->add_key_procedure(key_procedure(release_camera_left, true, true, -SDL_SCANCODE_A, 2));
        game->add_key_procedure(key_procedure(press_camera_right, true, true, SDL_SCANCODE_D, 3));
        game->add_key_procedure(key_procedure(release_camera_right, true, true, -SDL_SCANCODE_D, 3));

        while ((ticks = game->loop_run()) != -1){
            //std::cout << ticks << std::endl;
        }
    }

    delete table;
    table = NULL;

    delete module;
    module = NULL;

    game->close();

    delete game;
    game = NULL;

    return 0;
}
