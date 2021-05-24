#include "td_loading.h"

void load_resource_icons(){
    load_resource_icon("Metal Resource Icon", "images/resource_icons/metal_icon.png", 50, 30);
    load_resource_icon("Wood Resource Icon", "images/resource_icons/wood_icon.png", 210, 30);
    load_resource_icon("Crystal Resource Icon", "images/resource_icons/crystal_icon.png", 370, 30);
    load_resource_icon("Level Resource Icon", "images/resource_icons/level_icon.png", 535, 30);
    load_resource_icon("Life Resource Icon", "images/resource_icons/life_icon.png", 920, 30);
}

void load_resource_icon(std::string icon_name, std::string icon_link, int x_pos, int y_pos){
    extern main_controller* game;

    game->new_image(icon_name, icon_link, 0, 0, {0,0,30,30});
    game->set_blend_mode(icon_name, SDL_BLENDMODE_BLEND);
    game->set_active(icon_name, true);
    game->add_point(icon_name, x_pos, y_pos);
}

void load_grid_tiles(){
    extern main_controller* game;

    game->new_image("Grey Tile", "images/tiles.png", 0, 1, {0,0,(int)SQUARE_SIZE, (int)SQUARE_SIZE});
    game->set_blend_mode("Grey Tiles", SDL_BLENDMODE_BLEND);
    game->set_active("Grey Tile", true);

    game->copy_image("Pink Tile", "Grey Tile", {(int)SQUARE_SIZE, 0, (int)SQUARE_SIZE, (int)SQUARE_SIZE});
    game->set_active("Pink Tile", true);

    game->copy_image("Orange Tile", "Grey Tile", {(int)SQUARE_SIZE*2, 0, (int)SQUARE_SIZE, (int)SQUARE_SIZE});
    game->set_active("Orange Tile", true);

    game->copy_image("Blue Tile", "Grey Tile", {(int)SQUARE_SIZE*3, 0, (int)SQUARE_SIZE, (int)SQUARE_SIZE});
    game->set_active("Blue Tile", true);
}

void load_destination_points(){
    extern main_controller* game;

    game->new_image("Start Portal", "images/starting.png", 0, 1);
    game->set_blend_mode("Start Portal", SDL_BLENDMODE_BLEND);
    game->set_active("Start Portal", true);

    game->new_image("Move Point One", "images/diamonds.png", 0, 1, {0,0,90,90});
    game->set_blend_mode("Move Point One", SDL_BLENDMODE_BLEND);
    game->set_active("Move Point One", true);

    game->copy_image("Move Point Two", "Move Point One", {90,0,90,90});
    game->set_active("Move Point Two", true);

    game->new_image("House", "images/house.png", 0, 1);
    game->set_blend_mode("House", SDL_BLENDMODE_BLEND);
    game->set_active("House", true);
}

void load_enemies(){
    load_enemy("Enemy One", "images/enemy_one.png");
    load_enemy("Enemy Two", "images/enemy_two.png");
    load_enemy("Enemy Three", "images/enemy_three.png");
}

void load_enemy(std::string enemy_name, std::string enemy_image_directory){
    extern main_controller* game;

    game->new_image(enemy_name, enemy_image_directory, 0, 1, {0,0,(int)SQUARE_SIZE, (int)SQUARE_SIZE});
    game->set_blend_mode(enemy_name, SDL_BLENDMODE_BLEND);
    game->set_active(enemy_name, true);
    game->remove_image_copy(enemy_name);
}

void load_towers(){
    ///SET ONE
    load_tower("Tower", "images/tower.png");
    load_tower("Quake Tower", "images/quake_tower.png");
    load_tower("Miner Tower", "images/miner_tower.png");
    load_tower("Ball Tower", "images/tower_ball.png");
    load_tower("Splash Tower", "images/splash_tower.png");
    load_tower("Multi Tower", "images/multi_tower.png");
    load_tower("Thief Tower", "images/thief_tower.png");
    load_tower("Support Tower", "images/support_tower.png");
    load_tower("Slow Tower", "images/slow_tower.png");

    ///SET TWO
    load_tower("Melee Tower", "images/melee_tower.png");
    load_tower("Flame Tower", "images/flame_tower.png");
    load_tower("Melt Tower", "images/melt_tower.png");
    load_tower("Attack Buff Tower", "images/attack_buff_tower.png");
    load_tower("Dig Tower", "images/dig_tower.png");
    load_tower("Poison Tower", "images/poison_tower.png");
    load_tower("Observatory Tower", "images/observatory_tower.png");
    load_tower("Storm Tower", "images/storm_tower.png");
    load_tower("Search Tower", "images/search_tower.png");
}

void load_tower_selection(){
    extern main_controller* game;

    game->new_image("Tower Select", "images/tower.png", 0, 1);
    game->set_blend_mode("Tower Select", SDL_BLENDMODE_BLEND);
    game->set_color("Tower Select", {0x00, 0xFF, 0x00, 0xAA});
    game->set_alpha("Tower Select", 0xAA);
    game->set_active("Tower Select", true);

    game->new_image("Circle Select", "images/circle_select.png", 0, 1);
    game->set_blend_mode("Circle Select", SDL_BLENDMODE_BLEND);
    game->set_active("Circle Select", true);

    game->new_image("Circle Selected", "images/circle_selected.png", 0, 1);
    game->set_blend_mode("Circle Selected", SDL_BLENDMODE_BLEND);
    game->set_active("Circle Selected", true);
}

void load_tower(std::string tower_name, std::string tower_image_directory){
    extern main_controller* game;

    game->new_image(tower_name, tower_image_directory, 0, 1);
    game->set_blend_mode(tower_name, SDL_BLENDMODE_BLEND);
    game->remove_image_copy(tower_name);
    game->set_active(tower_name, true);
}

void load_bullets(){
    load_bullet("Tower Bullet", "images/tower_bullet.png");
    load_bullet("Tower Splash", "images/tower_splash.png");
    load_bullet("Tower Quake", "images/tower_quake.png");
    load_bullet("Split Range", "images/split_range.png");
    load_bullet("Split Bullet", "images/split_bullet.png");
    load_bullet("WreckingBall", "images/wrecking_ball.png");

    load_bullet("Flame Bullet", "images/flame_bullet.png");
    load_bullet("Storm Bullet", "images/storm_bullet.png");
    load_bullet("Search Bullet", "images/search_bullet.png");
}

void load_bullet(std::string bullet_name, std::string bullet_image_directory){
    extern main_controller* game;

    game->new_image(bullet_name, bullet_image_directory, 0, 1);
    game->set_blend_mode(bullet_name, SDL_BLENDMODE_BLEND);
    game->set_active(bullet_name, true);
}

void load_debuffs(){
    load_debuff("Slowed", "images/slowed.png");
    load_debuff("Melted", "images/armor_melt.png");
    load_debuff("Dig Slow", "images/dig_slow.png");
    load_debuff("Poison", "images/poisoned.png");
}

void load_debuff(std::string debuff_name, std::string debuff_image_directory){
    extern main_controller* game;

    game->new_image(debuff_name, debuff_image_directory, 0, 1, {0,0, (int)SQUARE_SIZE, (int)SQUARE_SIZE});
    game->set_blend_mode(debuff_name, SDL_BLENDMODE_BLEND);
    game->set_active(debuff_name, true);
    game->remove_image_copy(debuff_name);
}
