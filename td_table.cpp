#include "td_table.h"

td_level_loader::td_level_loader(){
    td_tower_types = std::map<std::string, tower_data>();
    td_tower_bullets = std::map<std::string, tower_bullet_data>();
    buff_auras = std::map<std::string, buff_aura>();
    td_bullet_debuffs = std::map<std::string, debuff_data>();

    tower_races = std::map<std::string, std::vector<TOWER_MAPPING>>();

    td_enemy_types = std::map<std::string, enemy_data>();
    td_enemy_waves = std::map<std::string, std::queue<std::string>>();

    td_terrains = std::map<std::string, std::vector<int>>();

    load_debuffs();
    load_auras();
    load_bullets();
    load_towers();

    load_tower_races();

    load_enemy_types();
    load_waves();

    load_terrains();
}

td_level_loader::~td_level_loader(){
    std::map<std::string, buff_aura>().swap(buff_auras);
    std::map<std::string, debuff_data>().swap(td_bullet_debuffs);
    std::map<std::string, tower_data>().swap(td_tower_types);
    std::map<std::string, tower_bullet_data>().swap(td_tower_bullets);

    std::map<std::string, std::vector<TOWER_MAPPING>>().swap(tower_races);

    std::map<std::string, enemy_data>().swap(td_enemy_types);
    std::map<std::string, std::queue<std::string>>().swap(td_enemy_waves);

    std::map<std::string, std::vector<int>>().swap(td_terrains);
}

void td_level_loader::load_towers(){
    td_tower_types.insert(std::pair<std::string, tower_data>("Error", tower_data()));

    td_tower_types.at("Error").tower_name = "Error";
    td_tower_types.at("Error").tower_image = "Error";

    ///TEST BUILD RACE 1

    td_tower_types.insert(std::pair<std::string, tower_data>("Tower", tower_data()));

    td_tower_types.at("Tower").tower_name = "Tower";
    td_tower_types.at("Tower").tower_image = "Tower";
    //td_tower_types.at("Tower").tower_image_link = "images/tower.png";

    td_tower_types.at("Tower").attack_rate = 1200;
    td_tower_types.at("Tower").attack_range = 130;

    td_tower_types.at("Tower").new_tile = TOWER_UNPHASEABLE;

    td_tower_types.at("Tower").bullet_data_name = "Tower Bullet";

    td_tower_types.at("Tower").description = "A basic, single-targeting tower";

    td_tower_types.at("Tower").upgrade_name = "Splash";
    td_tower_types.at("Tower").has_upgrade = true;

    td_tower_types.at("Tower").metal_use = 30;
    td_tower_types.at("Tower").metal_sell = 15;

    td_tower_types.at("Tower").wood_use = 10;
    td_tower_types.at("Tower").wood_sell = 5;

    td_tower_types.at("Tower").crystal_use = 0;
    td_tower_types.at("Tower").crystal_sell = 0;


    td_tower_types.insert(std::pair<std::string, tower_data>("Quake", tower_data()));

    td_tower_types.at("Quake").tower_name = "Quake";
    td_tower_types.at("Quake").tower_image = "Quake Tower";
    td_tower_types.at("Quake").tower_image_link = "images/quake_tower.png";

    td_tower_types.at("Quake").attack_rate = 1800;
    td_tower_types.at("Quake").attack_range = 130;

    td_tower_types.at("Quake").new_tile = TOWER_UNPHASEABLE;

    td_tower_types.at("Quake").bullet_data_name = "Quake";

    td_tower_types.at("Quake").description = "A tower that attacks all enemies around it";

    td_tower_types.at("Quake").metal_use = 125;
    td_tower_types.at("Quake").metal_sell = 10;

    td_tower_types.at("Quake").wood_use = 70;
    td_tower_types.at("Quake").wood_sell = 35;

    td_tower_types.at("Quake").crystal_use = 1;
    td_tower_types.at("Quake").crystal_sell = 0;

    td_tower_types.at("Quake").tower_icon_name = "images/build_quake_icon.png";


    td_tower_types.insert(std::pair<std::string, tower_data>("Miner Tower", tower_data()));

    td_tower_types.at("Miner Tower").tower_name = "Miner Tower";
    td_tower_types.at("Miner Tower").tower_image = "Miner Tower";
    td_tower_types.at("Miner Tower").tower_image_link = "images/miner_tower.png";

    td_tower_types.at("Miner Tower").attack_rate = 2000;
    td_tower_types.at("Miner Tower").attack_range = 13000;

    td_tower_types.at("Miner Tower").new_tile = TOWER_UNPHASEABLE;

    td_tower_types.at("Miner Tower").bullet_data_name = "Miner";

    td_tower_types.at("Miner Tower").description = "A tower that generates resources";

    td_tower_types.at("Miner Tower").metal_use = 140;
    td_tower_types.at("Miner Tower").metal_sell = 0;

    td_tower_types.at("Miner Tower").wood_use = 50;
    td_tower_types.at("Miner Tower").wood_sell = 0;

    td_tower_types.at("Miner Tower").crystal_use = 0;
    td_tower_types.at("Miner Tower").crystal_sell = 0;

    td_tower_types.at("Miner Tower").tower_icon_name = "images/build_miner_icon.png";


    td_tower_types.insert(std::pair<std::string, tower_data>("WreckingBall", tower_data()));

    td_tower_types.at("WreckingBall").tower_name = "WreckingBall";
    td_tower_types.at("WreckingBall").tower_image = "Ball Tower";
    td_tower_types.at("WreckingBall").tower_image_link = "images/tower_ball.png";

    td_tower_types.at("WreckingBall").attack_rate = 2600;
    td_tower_types.at("WreckingBall").attack_range = 240;

    td_tower_types.at("WreckingBall").new_tile = TOWER_UNPHASEABLE;

    td_tower_types.at("WreckingBall").bullet_data_name = "Ball";

    td_tower_types.at("WreckingBall").description = "A tower that throws a wrecking ball at enemies";

    td_tower_types.at("WreckingBall").metal_use = 130;
    td_tower_types.at("WreckingBall").metal_sell = 65;

    td_tower_types.at("WreckingBall").wood_use = 20;
    td_tower_types.at("WreckingBall").wood_sell = 10;

    td_tower_types.at("WreckingBall").crystal_use = 1;
    td_tower_types.at("WreckingBall").crystal_sell = 0;

    td_tower_types.at("WreckingBall").tower_icon_name = "images/build_ball_icon.png";

    td_tower_types.insert(std::pair<std::string, tower_data>("Splash", tower_data()));

    td_tower_types.at("Splash").tower_name = "Splash";
    td_tower_types.at("Splash").tower_image = "Splash Tower";
    td_tower_types.at("Splash").tower_image_link = "images/splash_tower.png";

    td_tower_types.at("Splash").attack_rate = 1700;
    td_tower_types.at("Splash").attack_range = 190;

    td_tower_types.at("Splash").new_tile = TOWER_UNPHASEABLE;

    td_tower_types.at("Splash").bullet_data_name = "Splash Bullet";

    td_tower_types.at("Splash").description = "A tower whose bullet explodes on contact";

    td_tower_types.at("Splash").metal_use = 90;
    td_tower_types.at("Splash").metal_sell = 45;

    td_tower_types.at("Splash").wood_use = 40;
    td_tower_types.at("Splash").wood_sell = 20;

    td_tower_types.at("Splash").crystal_use = 0;
    td_tower_types.at("Splash").crystal_sell = 0;

    td_tower_types.at("Splash").tower_icon_name = "images/build_splash_icon.png";

    td_tower_types.insert(std::pair<std::string, tower_data>("Multi", tower_data()));

    td_tower_types.at("Multi").tower_name = "Multi";
    td_tower_types.at("Multi").tower_image = "Multi Tower";
    td_tower_types.at("Multi").tower_image_link = "images/multi_tower.png";

    td_tower_types.at("Multi").attack_rate = 1100;
    td_tower_types.at("Multi").attack_range = 310;

    td_tower_types.at("Multi").new_tile = TOWER_UNPHASEABLE;

    td_tower_types.at("Multi").bullet_data_name = "Multi Bullet";

    td_tower_types.at("Multi").description = "A tower that targets up to six enemies";

    td_tower_types.at("Multi").metal_use = 200;
    td_tower_types.at("Multi").metal_sell = 100;

    td_tower_types.at("Multi").wood_use = 60;
    td_tower_types.at("Multi").wood_sell = 30;

    td_tower_types.at("Multi").crystal_use = 1;
    td_tower_types.at("Multi").crystal_sell = 0;

    td_tower_types.at("Multi").tower_icon_name = "images/build_multi_icon.png";

    td_tower_types.insert(std::pair<std::string, tower_data>("Thief", tower_data()));

    td_tower_types.at("Thief").tower_name = "Thief";
    td_tower_types.at("Thief").tower_image = "Thief Tower";
    td_tower_types.at("Thief").tower_image_link = "images/thief_tower.png";

    td_tower_types.at("Thief").attack_rate = 1700;
    td_tower_types.at("Thief").attack_range = 260;

    td_tower_types.at("Thief").new_tile = TOWER_UNPHASEABLE;

    td_tower_types.at("Thief").bullet_data_name = "Steal Bullet";

    td_tower_types.at("Thief").description = "A tower that generates income for every attack";

    td_tower_types.at("Thief").metal_use = 100;
    td_tower_types.at("Thief").metal_sell = 10;

    td_tower_types.at("Thief").wood_use = 120;
    td_tower_types.at("Thief").wood_sell = 60;

    td_tower_types.at("Thief").crystal_use = 1;
    td_tower_types.at("Thief").crystal_sell = 0;

    td_tower_types.at("Thief").tower_icon_name = "images/build_thief_icon.png";


    td_tower_types.insert(std::pair<std::string, tower_data>("Support", tower_data()));

    td_tower_types.at("Support").tower_name = "Support";
    td_tower_types.at("Support").tower_image = "Support Tower";
    td_tower_types.at("Support").tower_image_link = "images/support_tower.png";

    td_tower_types.at("Support").attack_rate = 170000;
    td_tower_types.at("Support").attack_range = 0;

    td_tower_types.at("Support").new_tile = TOWER_UNPHASEABLE;

    td_tower_types.at("Support").bullet_data_name = "Error";

    td_tower_types.at("Support").description = "A tower that speeds up the attack of surrounding towers";

    td_tower_types.at("Support").auras.push_back(buff_auras.at("Support"));

    td_tower_types.at("Support").metal_use = 120;
    td_tower_types.at("Support").metal_sell = 60;

    td_tower_types.at("Support").wood_use = 150;
    td_tower_types.at("Support").wood_sell = 75;

    td_tower_types.at("Support").crystal_use = 2;
    td_tower_types.at("Support").crystal_sell = 0;

    td_tower_types.at("Support").tower_icon_name = "images/build_support_icon.png";


    td_tower_types.insert(std::pair<std::string, tower_data>("Slow", tower_data()));

    td_tower_types.at("Slow").tower_name = "Slow";
    td_tower_types.at("Slow").tower_image = "Slow Tower";
    td_tower_types.at("Slow").tower_image_link = "images/slow_tower.png";

    td_tower_types.at("Slow").attack_rate = 1700;
    td_tower_types.at("Slow").attack_range = 160;

    td_tower_types.at("Slow").new_tile = TOWER_UNPHASEABLE;

    td_tower_types.at("Slow").bullet_data_name = "Slow Bullet";

    td_tower_types.at("Slow").description = "A tower that slows down enemies";

    td_tower_types.at("Slow").metal_use = 30;
    td_tower_types.at("Slow").metal_sell = 15;

    td_tower_types.at("Slow").wood_use = 30;
    td_tower_types.at("Slow").wood_sell = 15;

    td_tower_types.at("Slow").crystal_use = 2;
    td_tower_types.at("Slow").crystal_sell = 0;

    td_tower_types.at("Slow").tower_icon_name = "images/build_slow_icon.png";



    ///TEST BUILD RACE 2


    td_tower_types.insert(std::pair<std::string, tower_data>("Melee", tower_data()));

    td_tower_types.at("Melee").tower_name = "Melee";
    td_tower_types.at("Melee").tower_image = "Melee Tower";
    td_tower_types.at("Melee").tower_image_link = "images/melee_tower.png";

    td_tower_types.at("Melee").attack_rate = 600;
    td_tower_types.at("Melee").attack_range = 60;

    td_tower_types.at("Melee").new_tile = TOWER_UNPHASEABLE;

    td_tower_types.at("Melee").bullet_data_name = "Melee Bullet";

    td_tower_types.at("Melee").description = "A very short ranged, but powerful tower";

    td_tower_types.at("Melee").metal_use = 60;
    td_tower_types.at("Melee").metal_sell = 30;

    td_tower_types.at("Melee").wood_use = 30;
    td_tower_types.at("Melee").wood_sell = 15;

    td_tower_types.at("Melee").crystal_use = 0;
    td_tower_types.at("Melee").crystal_sell = 0;

    td_tower_types.at("Melee").tower_icon_name = "images/build_melee_icon.png";

    td_tower_types.insert(std::pair<std::string, tower_data>("Flame", tower_data()));

    td_tower_types.at("Flame").tower_name = "Flame";
    td_tower_types.at("Flame").tower_image = "Flame Tower";
    td_tower_types.at("Flame").tower_image_link = "images/flame_tower.png";

    td_tower_types.at("Flame").attack_rate = 200;
    td_tower_types.at("Flame").attack_range = 150;

    td_tower_types.at("Flame").new_tile = TOWER_UNPHASEABLE;

    td_tower_types.at("Flame").bullet_data_name = "Flame Bullet";

    td_tower_types.at("Flame").description = "A tower that spews fire";

    td_tower_types.at("Flame").metal_use = 130;
    td_tower_types.at("Flame").metal_sell = 65;

    td_tower_types.at("Flame").wood_use = 40;
    td_tower_types.at("Flame").wood_sell = 20;

    td_tower_types.at("Flame").crystal_use = 1;
    td_tower_types.at("Flame").crystal_sell = 0;

    td_tower_types.at("Flame").tower_icon_name = "images/build_flame_icon.png";

    td_tower_types.insert(std::pair<std::string, tower_data>("Melt", tower_data()));

    td_tower_types.at("Melt").tower_name = "Melt Tower";
    td_tower_types.at("Melt").tower_image = "Melt Tower";
    td_tower_types.at("Melt").tower_image_link = "images/melt_tower.png";

    td_tower_types.at("Melt").attack_rate = 1000;
    td_tower_types.at("Melt").attack_range = 200;

    td_tower_types.at("Melt").new_tile = TOWER_UNPHASEABLE;

    td_tower_types.at("Melt").bullet_data_name = "Melt Bullet";

    td_tower_types.at("Melt").description = "A tower that melts enemy armor";

    td_tower_types.at("Melt").metal_use = 70;
    td_tower_types.at("Melt").metal_sell = 35;

    td_tower_types.at("Melt").wood_use = 70;
    td_tower_types.at("Melt").wood_sell = 35;

    td_tower_types.at("Melt").crystal_use = 1;
    td_tower_types.at("Melt").crystal_sell = 0;

    td_tower_types.at("Melt").tower_icon_name = "images/build_melt_icon.png";

    td_tower_types.insert(std::pair<std::string, tower_data>("AttackBuff", tower_data()));

    td_tower_types.at("AttackBuff").tower_name = "Attack Buff";
    td_tower_types.at("AttackBuff").tower_image = "Attack Buff Tower";
    td_tower_types.at("AttackBuff").tower_image_link = "images/attack_buff_tower.png";

    td_tower_types.at("AttackBuff").attack_rate = 26000000;
    td_tower_types.at("AttackBuff").attack_range = 0;

    td_tower_types.at("AttackBuff").new_tile = TOWER_UNPHASEABLE;

    td_tower_types.at("AttackBuff").bullet_data_name = "Error";

    td_tower_types.at("AttackBuff").description = "A tower that increases attack";

    td_tower_types.at("AttackBuff").metal_use = 150;
    td_tower_types.at("AttackBuff").metal_sell = 75;

    td_tower_types.at("AttackBuff").wood_use = 90;
    td_tower_types.at("AttackBuff").wood_sell = 45;

    td_tower_types.at("AttackBuff").crystal_use = 2;
    td_tower_types.at("AttackBuff").crystal_sell = 0;

    td_tower_types.at("AttackBuff").tower_icon_name = "images/build_attack_buff_icon.png";

    td_tower_types.at("AttackBuff").auras.push_back(buff_auras.at("AttackBuff"));

    td_tower_types.insert(std::pair<std::string, tower_data>("DigTerrain", tower_data()));

    td_tower_types.at("DigTerrain").tower_name = "Dig Terrain";
    td_tower_types.at("DigTerrain").tower_image = "Dig Pit";
    td_tower_types.at("DigTerrain").tower_image_link = "images/terrain_dig.png";

    td_tower_types.at("DigTerrain").attack_rate = 1000;
    td_tower_types.at("DigTerrain").attack_range = 20;

    td_tower_types.at("DigTerrain").new_tile = TOWER_DIGGING;

    td_tower_types.at("DigTerrain").bullet_data_name = "Dig Bullet";

    td_tower_types.at("DigTerrain").description = "Dig through the terrain, slightly slows down enemies that cross through";

    td_tower_types.at("DigTerrain").metal_use = 80;
    td_tower_types.at("DigTerrain").metal_sell = 0;

    td_tower_types.at("DigTerrain").wood_use = 80;
    td_tower_types.at("DigTerrain").wood_sell = 0;

    td_tower_types.at("DigTerrain").crystal_use = 0;
    td_tower_types.at("DigTerrain").crystal_sell = 0;

    td_tower_types.at("DigTerrain").tower_icon_name = "images/build_dig_icon.png";


    td_tower_types.insert(std::pair<std::string, tower_data>("Poison", tower_data()));

    td_tower_types.at("Poison").tower_name = "Poison";
    td_tower_types.at("Poison").tower_image = "Poison Tower";
    td_tower_types.at("Poison").tower_image_link = "images/poison_tower.png";

    td_tower_types.at("Poison").attack_rate = 1800;
    td_tower_types.at("Poison").attack_range = 60;

    td_tower_types.at("Poison").new_tile = TOWER_UNPHASEABLE;

    td_tower_types.at("Poison").bullet_data_name = "Poison Bullet";

    td_tower_types.at("Poison").description = "A tower that poisons enemies";

    td_tower_types.at("Poison").metal_use = 60;
    td_tower_types.at("Poison").metal_sell = 30;

    td_tower_types.at("Poison").wood_use = 90;
    td_tower_types.at("Poison").wood_sell = 45;

    td_tower_types.at("Poison").crystal_use = 2;
    td_tower_types.at("Poison").crystal_sell = 0;

    td_tower_types.at("Poison").tower_icon_name = "images/build_poison_icon.png";

    td_tower_types.insert(std::pair<std::string, tower_data>("Observatory", tower_data()));

    td_tower_types.at("Observatory").tower_name = "Observatory";
    td_tower_types.at("Observatory").tower_image = "Observatory Tower";
    td_tower_types.at("Observatory").tower_image_link = "images/observatory_tower.png";

    td_tower_types.at("Observatory").attack_rate = 190000;
    td_tower_types.at("Observatory").attack_range = 0;

    td_tower_types.at("Observatory").new_tile = TOWER_UNPHASEABLE;

    td_tower_types.at("Observatory").bullet_data_name = "Error";

    td_tower_types.at("Observatory").description = "A tower that amplifies tower range";

    td_tower_types.at("Observatory").metal_use = 100;
    td_tower_types.at("Observatory").metal_sell = 10;

    td_tower_types.at("Observatory").wood_use = 120;
    td_tower_types.at("Observatory").wood_sell = 60;

    td_tower_types.at("Observatory").crystal_use = 2;
    td_tower_types.at("Observatory").crystal_sell = 0;

    td_tower_types.at("Observatory").tower_icon_name = "images/build_observatory_icon.png";

    td_tower_types.at("Observatory").auras.push_back(buff_auras.at("RangeBuff"));


    td_tower_types.insert(std::pair<std::string, tower_data>("Storm", tower_data()));

    td_tower_types.at("Storm").tower_name = "Storm";
    td_tower_types.at("Storm").tower_image = "Storm Tower";
    td_tower_types.at("Storm").tower_image_link = "images/storm_tower.png";

    td_tower_types.at("Storm").attack_rate = 1700;
    td_tower_types.at("Storm").attack_range = 200;

    td_tower_types.at("Storm").new_tile = TOWER_UNPHASEABLE;

    td_tower_types.at("Storm").bullet_data_name = "Storm Bullet";

    td_tower_types.at("Storm").description = "A tower that sends a tornado towards enemies";

    //td_tower_types.at("Storm").auras.push_back(buff_auras.at("Storm"));

    td_tower_types.at("Storm").metal_use = 160;
    td_tower_types.at("Storm").metal_sell = 80;

    td_tower_types.at("Storm").wood_use = 120;
    td_tower_types.at("Storm").wood_sell = 60;

    td_tower_types.at("Storm").crystal_use = 3;
    td_tower_types.at("Storm").crystal_sell = 0;

    td_tower_types.at("Storm").tower_icon_name = "images/build_storm_icon.png";


    td_tower_types.insert(std::pair<std::string, tower_data>("Search", tower_data()));

    td_tower_types.at("Search").tower_name = "Search";
    td_tower_types.at("Search").tower_image = "Search Tower";
    td_tower_types.at("Search").tower_image_link = "images/search_tower.png";

    td_tower_types.at("Search").attack_rate = 3400;
    td_tower_types.at("Search").attack_range = 600;

    td_tower_types.at("Search").new_tile = TOWER_UNPHASEABLE;

    td_tower_types.at("Search").bullet_data_name = "Search Bullet";

    td_tower_types.at("Search").description = "A tower that snipes enemies";

    td_tower_types.at("Search").metal_use = 200;
    td_tower_types.at("Search").metal_sell = 100;

    td_tower_types.at("Search").wood_use = 70;
    td_tower_types.at("Search").wood_sell = 35;

    td_tower_types.at("Search").crystal_use = 1;
    td_tower_types.at("Search").crystal_sell = 0;

    td_tower_types.at("Search").tower_icon_name = "images/build_search_icon.png";
}

void td_level_loader::load_bullets(){
    td_tower_bullets.insert(std::pair<std::string, tower_bullet_data>("Error", tower_bullet_data()));

    td_tower_bullets.at("Error").bullet_image = "Error";
    td_tower_bullets.at("Error").bullet_name = "Error";

    td_tower_bullets.insert(std::pair<std::string, tower_bullet_data>("Tower Bullet", tower_bullet_data()));

    td_tower_bullets.at("Tower Bullet").bullet_damage = 25;
    td_tower_bullets.at("Tower Bullet").bullet_speed = 400;
    td_tower_bullets.at("Tower Bullet").bullet_radius = 15;

    td_tower_bullets.at("Tower Bullet").bullet_name = "Tower Bullet";
    td_tower_bullets.at("Tower Bullet").bullet_image = "Tower Bullet";

    //td_tower_bullets.at("Tower Bullet").bullets_to_create_after.push_back(td_tower_bullets.at("Tower Splash"));

    td_tower_bullets.insert(std::pair<std::string, tower_bullet_data>("Quake", tower_bullet_data()));

    td_tower_bullets.at("Quake").bullet_damage = 100;
    td_tower_bullets.at("Quake").bullet_speed = 0;
    td_tower_bullets.at("Quake").bullet_radius = 120;

    td_tower_bullets.at("Quake").bullet_name = "Tower Quake";
    td_tower_bullets.at("Quake").bullet_image = "Tower Quake";

    td_tower_bullets.at("Quake").bullet_type = BULLET_TYPE_HITBOX;

    td_tower_bullets.at("Quake").duration = 130;

    td_tower_bullets.at("Quake").threshold_hits = 30;

    //td_tower_bullets.at("Tower Bullet").bullets_to_create_after.push_back(td_tower_bullets.at("Tower Splash"));

    td_tower_bullets.insert(std::pair<std::string, tower_bullet_data>("Miner", tower_bullet_data()));

    td_tower_bullets.at("Miner").bullet_damage = 10;
    td_tower_bullets.at("Miner").bullet_damage_type = INCOME_TYPE_WOOD;
    td_tower_bullets.at("Miner").bullet_type = BULLET_TYPE_INCOME;

    td_tower_bullets.insert(std::pair<std::string, tower_bullet_data>("Ball", tower_bullet_data()));

    td_tower_bullets.at("Ball").bullet_damage = 120;
    td_tower_bullets.at("Ball").bullet_speed = 450;
    td_tower_bullets.at("Ball").bullet_radius = 30;

    td_tower_bullets.at("Ball").bullet_name = "WreckingBall";
    td_tower_bullets.at("Ball").bullet_image = "WreckingBall";

    td_tower_bullets.at("Ball").bullet_type = BULLET_TYPE_HITBOX_DIRECTED;

    td_tower_bullets.at("Ball").duration = 1000;
    td_tower_bullets.at("Ball").threshold_hits = 3;

    //CHAINED BULLETS
    td_tower_bullets.insert(std::pair<std::string, tower_bullet_data>("Tower Splash", tower_bullet_data()));

    td_tower_bullets.at("Tower Splash").bullet_damage = 70;
    td_tower_bullets.at("Tower Splash").bullet_radius = 60;

    td_tower_bullets.at("Tower Splash").bullet_name = "Tower Splash";
    td_tower_bullets.at("Tower Splash").bullet_image = "Tower Splash";

    td_tower_bullets.at("Tower Splash").bullet_x_speed = 0;
    td_tower_bullets.at("Tower Splash").bullet_y_speed = 0;

    td_tower_bullets.at("Tower Splash").duration = 400;

    td_tower_bullets.at("Tower Splash").bullet_type = BULLET_TYPE_HITBOX;

    td_tower_bullets.insert(std::pair<std::string, tower_bullet_data>("Splash Bullet", tower_bullet_data()));

    td_tower_bullets.at("Splash Bullet").bullet_damage = 10;
    td_tower_bullets.at("Splash Bullet").bullet_radius = 15;

    td_tower_bullets.at("Splash Bullet").bullet_name = "Splash Bullet";
    td_tower_bullets.at("Splash Bullet").bullet_image = "Tower Bullet";

    td_tower_bullets.at("Splash Bullet").bullet_speed = 400;

    td_tower_bullets.at("Splash Bullet").bullet_type = BULLET_TYPE_TARGET;

    td_tower_bullets.at("Splash Bullet").bullets_to_create_after.push_back(td_tower_bullets.at("Tower Splash"));


    td_tower_bullets.insert(std::pair<std::string, tower_bullet_data>("Split Bullet", tower_bullet_data()));

    td_tower_bullets.at("Split Bullet").bullet_damage = 50;
    td_tower_bullets.at("Split Bullet").bullet_radius = 15;

    td_tower_bullets.at("Split Bullet").bullet_name = "Split Bullet";
    td_tower_bullets.at("Split Bullet").bullet_image = "Split Bullet";

    td_tower_bullets.at("Split Bullet").bullet_speed = 1300;

    td_tower_bullets.at("Split Bullet").bullet_type = BULLET_TYPE_TARGET;

    td_tower_bullets.insert(std::pair<std::string, tower_bullet_data>("Multi Bullet", tower_bullet_data()));

    td_tower_bullets.at("Multi Bullet").bullet_damage = 0;
    td_tower_bullets.at("Multi Bullet").bullet_radius = 160;

    td_tower_bullets.at("Multi Bullet").bullet_name = "Multi Bullet";
    td_tower_bullets.at("Multi Bullet").bullet_image = "Split Range";

    td_tower_bullets.at("Multi Bullet").duration = 100;

    td_tower_bullets.at("Multi Bullet").bullet_type = BULLET_TYPE_HITBOX;

    td_tower_bullets.at("Multi Bullet").threshold_hits = 6;

    td_tower_bullets.at("Multi Bullet").bullets_to_create_after.push_back(td_tower_bullets.at("Split Bullet"));

    td_tower_bullets.insert(std::pair<std::string, tower_bullet_data>("Tower Steal", tower_bullet_data()));

    td_tower_bullets.at("Tower Steal").bullet_damage = 30;
    td_tower_bullets.at("Tower Steal").bullet_type = BULLET_TYPE_INCOME;
    td_tower_bullets.at("Tower Steal").bullet_damage_type = INCOME_TYPE_METAL;

    td_tower_bullets.insert(std::pair<std::string, tower_bullet_data>("Steal Bullet", tower_bullet_data()));

    td_tower_bullets.at("Steal Bullet").bullet_damage = 30;
    td_tower_bullets.at("Steal Bullet").bullet_radius = 15;

    td_tower_bullets.at("Steal Bullet").bullet_name = "Steal Bullet";
    td_tower_bullets.at("Steal Bullet").bullet_image = "Tower Bullet";

    td_tower_bullets.at("Steal Bullet").bullet_speed = 700;

    td_tower_bullets.at("Steal Bullet").bullet_type = BULLET_TYPE_TARGET;

    td_tower_bullets.at("Steal Bullet").bullets_to_create_after.push_back(td_tower_bullets.at("Tower Steal"));


    //FOR TESTING  DEBUFFS
    td_tower_bullets.insert(std::pair<std::string, tower_bullet_data>("Slow Bullet", tower_bullet_data()));

    td_tower_bullets.at("Slow Bullet").bullet_damage = 10;
    td_tower_bullets.at("Slow Bullet").bullet_radius = 15;

    td_tower_bullets.at("Slow Bullet").bullet_name = "Slow Bullet";
    td_tower_bullets.at("Slow Bullet").bullet_image = "Tower Bullet";

    td_tower_bullets.at("Slow Bullet").bullet_speed = 600;

    td_tower_bullets.at("Slow Bullet").bullet_type = BULLET_TYPE_TARGET;

    td_tower_bullets.at("Slow Bullet").bullet_debuffs.push_back(td_bullet_debuffs.at("Slow"));

    ///PHASE TWO

    td_tower_bullets.insert(std::pair<std::string, tower_bullet_data>("Melee Bullet", tower_bullet_data()));

    td_tower_bullets.at("Melee Bullet").bullet_damage = 30;
    td_tower_bullets.at("Melee Bullet").bullet_speed = 6000;
    td_tower_bullets.at("Melee Bullet").bullet_radius = 15;

    td_tower_bullets.at("Melee Bullet").bullet_name = "Tower Bullet";
    td_tower_bullets.at("Melee Bullet").bullet_image = "Tower Bullet";

    td_tower_bullets.insert(std::pair<std::string, tower_bullet_data>("Flame Bullet", tower_bullet_data()));

    td_tower_bullets.at("Flame Bullet").bullet_damage = 8;
    td_tower_bullets.at("Flame Bullet").bullet_speed = 500;
    td_tower_bullets.at("Flame Bullet").bullet_radius = 30;

    td_tower_bullets.at("Flame Bullet").bullet_name = "Flame Bullet";
    td_tower_bullets.at("Flame Bullet").bullet_image = "Flame Bullet";

    td_tower_bullets.at("Flame Bullet").bullet_type = BULLET_TYPE_HITBOX_DIRECTED;

    td_tower_bullets.at("Flame Bullet").duration = 600;
    td_tower_bullets.at("Flame Bullet").threshold_hits = 2;


    td_tower_bullets.insert(std::pair<std::string, tower_bullet_data>("Melt Bullet", tower_bullet_data()));

    td_tower_bullets.at("Melt Bullet").bullet_damage = 20;
    td_tower_bullets.at("Melt Bullet").bullet_speed = 2500;
    td_tower_bullets.at("Melt Bullet").bullet_radius = 15;

    td_tower_bullets.at("Melt Bullet").bullet_name = "Tower Bullet";
    td_tower_bullets.at("Melt Bullet").bullet_image = "Tower Bullet";

    td_tower_bullets.at("Melt Bullet").bullet_debuffs.push_back(td_bullet_debuffs.at("Melt"));


    td_tower_bullets.insert(std::pair<std::string, tower_bullet_data>("Dig Bullet", tower_bullet_data()));

    td_tower_bullets.at("Dig Bullet").bullet_damage = 0;
    td_tower_bullets.at("Dig Bullet").bullet_radius = 15;

    td_tower_bullets.at("Dig Bullet").bullet_name = "Dig Bullet";
    td_tower_bullets.at("Dig Bullet").bullet_image = "Tower Bullet";

    td_tower_bullets.at("Dig Bullet").bullet_speed = 600;

    td_tower_bullets.at("Dig Bullet").bullet_type = BULLET_TYPE_TARGET;

    td_tower_bullets.at("Dig Bullet").bullet_debuffs.push_back(td_bullet_debuffs.at("Dig Slow"));


    td_tower_bullets.insert(std::pair<std::string, tower_bullet_data>("Poison Bullet", tower_bullet_data()));

    td_tower_bullets.at("Poison Bullet").bullet_damage = 5;
    td_tower_bullets.at("Poison Bullet").bullet_radius = 15;

    td_tower_bullets.at("Poison Bullet").bullet_name = "Poison Bullet";
    td_tower_bullets.at("Poison Bullet").bullet_image = "Tower Bullet";

    td_tower_bullets.at("Poison Bullet").bullet_speed = 600;

    td_tower_bullets.at("Poison Bullet").bullet_type = BULLET_TYPE_TARGET;

    td_tower_bullets.at("Poison Bullet").bullet_debuffs.push_back(td_bullet_debuffs.at("Poison"));


    td_tower_bullets.insert(std::pair<std::string, tower_bullet_data>("Storm Debris", tower_bullet_data()));

    td_tower_bullets.at("Storm Debris").bullet_damage = 35;
    td_tower_bullets.at("Storm Debris").bullet_radius = 15;

    td_tower_bullets.at("Storm Debris").bullet_name = "Storm Debris";
    td_tower_bullets.at("Storm Debris").bullet_image = "Tower Bullet";

    td_tower_bullets.at("Storm Debris").bullet_speed = 1900;

    td_tower_bullets.at("Storm Debris").bullet_type = BULLET_TYPE_TARGET;


    td_tower_bullets.insert(std::pair<std::string, tower_bullet_data>("Storm Bullet", tower_bullet_data()));

    td_tower_bullets.at("Storm Bullet").bullet_damage = 10;
    td_tower_bullets.at("Storm Bullet").bullet_radius = 110;

    td_tower_bullets.at("Storm Bullet").duration = 7000;

    td_tower_bullets.at("Storm Bullet").threshold_hits = 100;

    td_tower_bullets.at("Storm Bullet").bullet_name = "Storm Bullet";
    td_tower_bullets.at("Storm Bullet").bullet_image = "Storm Bullet";

    td_tower_bullets.at("Storm Bullet").bullet_speed = 200;

    td_tower_bullets.at("Storm Bullet").bullet_type = BULLET_TYPE_HITBOX_DIRECTED;

    td_tower_bullets.at("Storm Bullet").bullet_debuffs.push_back(td_bullet_debuffs.at("Slow"));
    td_tower_bullets.at("Storm Bullet").bullets_to_create_after.push_back(td_tower_bullets.at("Storm Debris"));


    td_tower_bullets.insert(std::pair<std::string, tower_bullet_data>("Search Explosion", tower_bullet_data()));

    td_tower_bullets.at("Search Explosion").bullet_damage = 500;
    td_tower_bullets.at("Search Explosion").bullet_radius = 30;

    td_tower_bullets.at("Search Explosion").bullet_name = "Search Explosion";
    td_tower_bullets.at("Search Explosion").bullet_image = "Tower Splash";

    td_tower_bullets.at("Search Explosion").duration = 100;

    td_tower_bullets.at("Search Explosion").bullet_type = BULLET_TYPE_HITBOX;


    td_tower_bullets.insert(std::pair<std::string, tower_bullet_data>("Search Bullet", tower_bullet_data()));

    td_tower_bullets.at("Search Bullet").bullet_damage = 0;
    td_tower_bullets.at("Search Bullet").bullet_radius = 10;

    td_tower_bullets.at("Search Bullet").duration = 3000;

    td_tower_bullets.at("Search Bullet").threshold_hits = 1;

    td_tower_bullets.at("Search Bullet").bullet_name = "Search Bullet";
    td_tower_bullets.at("Search Bullet").bullet_image = "Search Bullet";

    td_tower_bullets.at("Search Bullet").bullet_speed = 300;

    td_tower_bullets.at("Search Bullet").bullet_type = BULLET_TYPE_HITBOX_DIRECTED;

    td_tower_bullets.at("Search Bullet").bullets_to_create_after.push_back(td_tower_bullets.at("Search Explosion"));

}

void td_level_loader::load_debuffs(){
    td_bullet_debuffs.insert(std::pair<std::string, debuff_data>("Slow", debuff_data(3000, 60, DEBUFF_SPEED)));

    td_bullet_debuffs.at("Slow").debuff_name = "Slow";
    td_bullet_debuffs.at("Slow").debuff_image = "Slowed";

    td_bullet_debuffs.insert(std::pair<std::string, debuff_data>("Melt", debuff_data(3500, 30, DEBUFF_ARMOR)));

    td_bullet_debuffs.at("Melt").debuff_name = "Melt";
    td_bullet_debuffs.at("Melt").debuff_image = "Melted";

    td_bullet_debuffs.insert(std::pair<std::string, debuff_data>("Dig Slow", debuff_data(1000, 20, DEBUFF_SPEED)));

    td_bullet_debuffs.at("Dig Slow").debuff_name = "Dig Slow";
    td_bullet_debuffs.at("Dig Slow").debuff_image = "Dig Slow";

    td_bullet_debuffs.insert(std::pair<std::string, debuff_data>("Poison", debuff_data(3600, 55, DEBUFF_REGEN)));

    td_bullet_debuffs.at("Poison").debuff_name = "Poison";
    td_bullet_debuffs.at("Poison").debuff_image = "Poison";
}

void td_level_loader::load_auras(){
    buff_auras.insert(std::pair<std::string, buff_aura>("Support", buff_aura()));

    buff_auras.at("Support").aura_hitbox.set_radius(100);
    buff_auras.at("Support").buff_to_give = buff_data(1200, 500, BUFF_ATTACK_SPEED);


    buff_auras.insert(std::pair<std::string, buff_aura>("AttackBuff", buff_aura()));

    buff_auras.at("AttackBuff").aura_hitbox.set_radius(80);
    buff_auras.at("AttackBuff").buff_to_give = buff_data(1200, 20, BUFF_ATTACK);


    buff_auras.insert(std::pair<std::string, buff_aura>("RangeBuff", buff_aura()));

    buff_auras.at("RangeBuff").aura_hitbox.set_radius(50);
    buff_auras.at("RangeBuff").buff_to_give = buff_data(1200, 30, BUFF_RANGE);
}

void td_level_loader::load_tower_races(){
    tower_races.insert(std::pair<std::string, std::vector<TOWER_MAPPING>>("Race One", std::vector<TOWER_MAPPING>()));

    tower_races.at("Race One").push_back(TOWER_MAPPING(BUILD_BUTTON_ONE, "Tower"));
    tower_races.at("Race One").push_back(TOWER_MAPPING(BUILD_BUTTON_TWO, "Quake"));
    tower_races.at("Race One").push_back(TOWER_MAPPING(BUILD_BUTTON_THREE, "Miner Tower"));
    tower_races.at("Race One").push_back(TOWER_MAPPING(BUILD_BUTTON_FOUR, "WreckingBall"));
    tower_races.at("Race One").push_back(TOWER_MAPPING(BUILD_BUTTON_FIVE, "Splash"));
    tower_races.at("Race One").push_back(TOWER_MAPPING(BUILD_BUTTON_SIX, "Multi"));
    tower_races.at("Race One").push_back(TOWER_MAPPING(BUILD_BUTTON_SEVEN, "Thief"));
    tower_races.at("Race One").push_back(TOWER_MAPPING(BUILD_BUTTON_EIGHT, "Support"));
    tower_races.at("Race One").push_back(TOWER_MAPPING(BUILD_BUTTON_NINE, "Slow"));

    tower_races.insert(std::pair<std::string, std::vector<TOWER_MAPPING>>("Race Two", std::vector<TOWER_MAPPING>()));

    tower_races.at("Race Two").push_back(TOWER_MAPPING(BUILD_BUTTON_ONE, "Melee"));
    tower_races.at("Race Two").push_back(TOWER_MAPPING(BUILD_BUTTON_TWO, "Flame"));
    tower_races.at("Race Two").push_back(TOWER_MAPPING(BUILD_BUTTON_THREE, "Melt"));
    tower_races.at("Race Two").push_back(TOWER_MAPPING(BUILD_BUTTON_FOUR, "AttackBuff"));
    tower_races.at("Race Two").push_back(TOWER_MAPPING(BUILD_BUTTON_FIVE, "DigTerrain"));
    tower_races.at("Race Two").push_back(TOWER_MAPPING(BUILD_BUTTON_SIX, "Poison"));
    tower_races.at("Race Two").push_back(TOWER_MAPPING(BUILD_BUTTON_SEVEN, "Observatory"));
    tower_races.at("Race Two").push_back(TOWER_MAPPING(BUILD_BUTTON_EIGHT, "Storm"));
    tower_races.at("Race Two").push_back(TOWER_MAPPING(BUILD_BUTTON_NINE, "Search"));

    /*
    tower_races.insert(std::pair<std::string, std::vector<TOWER_MAPPING>>("Race Two", std::vector<TOWER_MAPPING>()));

    tower_races.at("Race Two").push_back(TOWER_MAPPING(BUILD_BUTTON_ONE, "Trap"));
    tower_races.at("Race Two").push_back(TOWER_MAPPING(BUILD_BUTTON_TWO, "Melt"));
    tower_races.at("Race Two").push_back(TOWER_MAPPING(BUILD_BUTTON_THREE, "Attack Support"));
    tower_races.at("Race Two").push_back(TOWER_MAPPING(BUILD_BUTTON_FOUR, "Observatory"));
    tower_races.at("Race Two").push_back(TOWER_MAPPING(BUILD_BUTTON_FIVE, "Poison"));
    tower_races.at("Race Two").push_back(TOWER_MAPPING(BUILD_BUTTON_SIX, "Melee"));
    tower_races.at("Race Two").push_back(TOWER_MAPPING(BUILD_BUTTON_SEVEN, "Cloud"));
    tower_races.at("Race Two").push_back(TOWER_MAPPING(BUILD_BUTTON_EIGHT, "Flamethrower"));
    tower_races.at("Race Two").push_back(TOWER_MAPPING(BUILD_BUTTON_NINE, "Sniper"));

    tower_races.insert(std::pair<std::string, std::vector<TOWER_MAPPING>>("Race Three", std::vector<TOWER_MAPPING>()));

    tower_races.at("Race Three").push_back(TOWER_MAPPING(BUILD_BUTTON_ONE, "Crystal Lab"));
    tower_races.at("Race Three").push_back(TOWER_MAPPING(BUILD_BUTTON_TWO, "Thundershock"));
    tower_races.at("Race Three").push_back(TOWER_MAPPING(BUILD_BUTTON_THREE, "BouncingBall"));
    tower_races.at("Race Three").push_back(TOWER_MAPPING(BUILD_BUTTON_FOUR, "Chain"));
    tower_races.at("Race Three").push_back(TOWER_MAPPING(BUILD_BUTTON_FIVE, "Splash Slow"));
    tower_races.at("Race Three").push_back(TOWER_MAPPING(BUILD_BUTTON_SIX, "Wall"));
    tower_races.at("Race Three").push_back(TOWER_MAPPING(BUILD_BUTTON_SEVEN, "Sniper"));
    tower_races.at("Race Three").push_back(TOWER_MAPPING(BUILD_BUTTON_EIGHT, "Rain"));
    tower_races.at("Race Three").push_back(TOWER_MAPPING(BUILD_BUTTON_NINE, "Hero Tower"));
    */
}

std::vector<TOWER_MAPPING> td_level_loader::get_tower_race(std::string race_name){
    return tower_races.at(race_name);
}

void td_level_loader::load_enemy_types(){
    td_enemy_types.insert(std::pair<std::string, enemy_data>("Error", enemy_data()));

    td_enemy_types.at("Error").enemy_name = "Error";
    td_enemy_types.at("Error").enemy_image_source = "Error";

    td_enemy_types.insert(std::pair<std::string, enemy_data>("Enemy One", enemy_data()));

    td_enemy_types.at("Enemy One").enemy_hp_base = 25;
    td_enemy_types.at("Enemy One").enemy_hp_scale = 175;

    td_enemy_types.at("Enemy One").enemy_speed_base = 80;
    td_enemy_types.at("Enemy One").enemy_speed_scale = 10;

    td_enemy_types.at("Enemy One").enemy_armor_base = 10;
    td_enemy_types.at("Enemy One").enemy_armor_scale = 1;
    td_enemy_types.at("Enemy One").enemy_armor_type = ARMOR_TYPE_BASIC;

    td_enemy_types.at("Enemy One").enemy_metal_bounty_base = 10;
    td_enemy_types.at("Enemy One").enemy_metal_bounty_scale = 2;

    td_enemy_types.at("Enemy One").enemy_wood_bounty_base = 5;
    td_enemy_types.at("Enemy One").enemy_wood_bounty_scale = 3;

    td_enemy_types.at("Enemy One").enemy_crystal_bounty_base = 0;
    td_enemy_types.at("Enemy One").enemy_crystal_bounty_scale = 0;

    td_enemy_types.at("Enemy One").enemy_name = "Enemy One";
    td_enemy_types.at("Enemy One").enemy_image_source = "Enemy One";


    td_enemy_types.insert(std::pair<std::string, enemy_data>("Enemy Two", enemy_data()));

    td_enemy_types.at("Enemy Two").enemy_hp_base = 100;
    td_enemy_types.at("Enemy Two").enemy_hp_scale = 100;

    td_enemy_types.at("Enemy Two").enemy_speed_base = 100;
    td_enemy_types.at("Enemy Two").enemy_speed_scale = 35;

    td_enemy_types.at("Enemy Two").enemy_armor_base = 4;
    td_enemy_types.at("Enemy Two").enemy_armor_scale = 1;
    td_enemy_types.at("Enemy Two").enemy_armor_type = ARMOR_TYPE_BASIC;

    td_enemy_types.at("Enemy Two").enemy_metal_bounty_base = 8;
    td_enemy_types.at("Enemy Two").enemy_metal_bounty_scale = 3;

    td_enemy_types.at("Enemy Two").enemy_wood_bounty_base = 10;
    td_enemy_types.at("Enemy Two").enemy_wood_bounty_scale = 2;

    td_enemy_types.at("Enemy Two").enemy_crystal_bounty_base = 0;
    td_enemy_types.at("Enemy Two").enemy_crystal_bounty_scale = 0;

    td_enemy_types.at("Enemy Two").enemy_name = "Enemy Two";
    td_enemy_types.at("Enemy Two").enemy_image_source = "Enemy Two";


    td_enemy_types.insert(std::pair<std::string, enemy_data>("Enemy Three", enemy_data()));

    td_enemy_types.at("Enemy Three").enemy_hp_base = 200;
    td_enemy_types.at("Enemy Three").enemy_hp_scale = 375;

    td_enemy_types.at("Enemy Three").enemy_regen_base = 0;
    td_enemy_types.at("Enemy Three").enemy_regen_scale = 3;

    td_enemy_types.at("Enemy Three").enemy_speed_base = 70;
    td_enemy_types.at("Enemy Three").enemy_speed_scale = 5;

    td_enemy_types.at("Enemy Three").enemy_armor_base = 8;
    td_enemy_types.at("Enemy Three").enemy_armor_scale = 2;
    td_enemy_types.at("Enemy Three").enemy_armor_type = ARMOR_TYPE_BASIC;

    td_enemy_types.at("Enemy Three").enemy_metal_bounty_base = 100;
    td_enemy_types.at("Enemy Three").enemy_metal_bounty_scale = 10;

    td_enemy_types.at("Enemy Three").enemy_wood_bounty_base = 100;
    td_enemy_types.at("Enemy Three").enemy_wood_bounty_scale = 10;

    td_enemy_types.at("Enemy Three").enemy_crystal_bounty_base = 5;
    td_enemy_types.at("Enemy Three").enemy_crystal_bounty_scale = 0;

    td_enemy_types.at("Enemy Three").enemy_name = "Enemy Three";
    td_enemy_types.at("Enemy Three").enemy_image_source = "Enemy Three";
}

tower_data td_level_loader::get_tower_data(std::string tower_data_name){
    if (td_tower_types.find(tower_data_name) != td_tower_types.end()){
        return td_tower_types.at(tower_data_name);
    } else {
        return td_tower_types.at("Error");
    }
}

tower_bullet_data td_level_loader::get_bullet_data(std::string bullet_data_name){
    if (td_tower_bullets.find(bullet_data_name) != td_tower_bullets.end()){
        return td_tower_bullets.at(bullet_data_name);
    } else {
        return td_tower_bullets.at("Error");
    }
}

enemy_data td_level_loader::get_enemy_data(std::string enemy_data_name){
    if (td_enemy_types.find(enemy_data_name) != td_enemy_types.end()){
        return td_enemy_types.at(enemy_data_name);
    } else {
        return td_enemy_types.at("Error");
    }
}

void td_level_loader::load_waves(){
    td_enemy_waves.insert(std::pair<std::string, std::queue<std::string>>("Error", std::queue<std::string>()));

    td_enemy_waves.insert(std::pair<std::string, std::queue<std::string>>("Wave One", std::queue<std::string>()));

    for (unsigned int i = 0; i < 10; i++){
        td_enemy_waves.at("Wave One").push("Enemy One");
    }

    td_enemy_waves.insert(std::pair<std::string, std::queue<std::string>>("Wave Two", std::queue<std::string>()));

    for (unsigned int i = 0; i < 10; i++){
        td_enemy_waves.at("Wave Two").push("Enemy Two");
    }

    td_enemy_waves.insert(std::pair<std::string, std::queue<std::string>>("Wave Three", std::queue<std::string>()));

    for (unsigned int i = 0; i < 5; i++){
        td_enemy_waves.at("Wave Three").push("Enemy One");
    }

    for (unsigned int i = 0; i < 5; i++){
        td_enemy_waves.at("Wave Three").push("Enemy Two");
    }

    td_enemy_waves.insert(std::pair<std::string, std::queue<std::string>>("Wave Four", std::queue<std::string>()));

    td_enemy_waves.at("Wave Four").push("Enemy Three");

    for (unsigned int i = 0; i < 4; i++){
        td_enemy_waves.at("Wave Four").push("Enemy One");
    }

    for (unsigned int i = 0; i < 5; i++){
        td_enemy_waves.at("Wave Four").push("Enemy Two");
    }

    td_enemy_waves.insert(std::pair<std::string, std::queue<std::string>>("Wave Five", std::queue<std::string>()));

    for (unsigned int i = 0; i < 3; i++){
        td_enemy_waves.at("Wave Five").push("Enemy Three");
    }

    for (unsigned int i = 0; i < 3; i++){
        td_enemy_waves.at("Wave Five").push("Enemy One");
    }

    for (unsigned int i = 0; i < 6; i++){
        td_enemy_waves.at("Wave Five").push("Enemy Two");
    }
}

std::queue<std::string> td_level_loader::get_wave(std::string wave_data_name){
    if (td_enemy_waves.find(wave_data_name) != td_enemy_waves.end()){
        return td_enemy_waves.at(wave_data_name);
    } else {
        return td_enemy_waves.at("Error");
    }
}

void td_level_loader::load_terrains(){
    read_terrain("Default","levels/default.bin");
    read_terrain("Crossing","levels/crossing.bin");
    read_terrain("Traditional","levels/traditional.bin");
}

void td_level_loader::set_map(std::queue<int>* map_to_load, std::string map_name){
    if (td_terrains.find(map_name) != td_terrains.end()){
        if (!td_terrains.at(map_name).empty())
            for (unsigned int map_index = 0; map_index < td_terrains.at(map_name).size(); map_index++)
                map_to_load->push(td_terrains.at(map_name).at(map_index));
    } else {
        //LOAD THE BLANK TERRAIN
        map_to_load->push(1);
        map_to_load->push(0);

        for (unsigned int i = 2; i < 23*11; i++){
            map_to_load->push(1);
        }
    }
}

void td_level_loader::read_terrain(std::string terrain_name, std::string terrain_file_name){
    ///THE TERRAIN FILE NAME HAS TO BE A JSON FILE

    file_reader test_reader = file_reader(23*11);

    if (test_reader.read_bin_file(terrain_file_name)){
        test_reader.new_vector_serial(terrain_name);
        test_reader.read_data_to_vector(terrain_name, 0, 23*11);
        std::vector<int> test_vector = test_reader.get_serial_vector(terrain_name);

        td_terrains.insert(std::pair<std::string, std::vector<int>>(terrain_name,std::vector<int>()));

        for (int i = 0; i < 23*11; i++){
            td_terrains.at(terrain_name).push_back(test_vector.at(i));
            //std::cout << test_vector.at(i) << " ";
        }

        //std::cout << std::endl;
    }
}
