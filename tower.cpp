#include "tower.h"

tower::tower(int x, int y, int radius, int index, int attack_rate, TARGET_BUILDOVER tile_type, int previous_tile_value, std::string display_name, std::string name, std::string image, tower_bullet_data resulting_bullet){
    tower_hitbox = circle_hitbox(x, y, radius, index);
    attack_cd = tower_attack_rate = attack_rate;
    new_tower_tile = tile_type;
    previous_tower_tile = previous_tile_value;
    display_tower_name = display_name;
    tower_name = name;
    image_name = image;
    this->tower_bullet = resulting_bullet;

    auras = std::vector<buff_aura>();
    buffs_to_add = std::queue<buff_data>();
    td_buffs = std::map<std::string, buff_data>();
}

tower::~tower(){
    towers = NULL;
    td_bullets = NULL;
    td_enemies = NULL;

    std::vector<buff_aura>().swap(auras);
    std::map<std::string, buff_data>().swap(td_buffs);
}

void tower::set_bullets(bullet_space* bullets){
    td_bullets = bullets;
}

void tower::set_towers(std::vector<tower>* towers){
    this->towers = towers;
}

void tower::set_enemies(std::map<int, enemy>* enemies){
    td_enemies = enemies;
}

void tower::set_wave_size(unsigned int new_size){
    wave_size = new_size;
}

void tower::add_tower_aura(buff_aura new_aura){
    new_aura.aura_hitbox.set_x(tower_hitbox.get_x());
    new_aura.aura_hitbox.set_y(tower_hitbox.get_y());

    auras.push_back(new_aura);
}

void tower::add_buff_to_queue(buff_data buff){
    buffs_to_add.push(buff);
}

void tower::add_buff(std::string buff_name, buff_data buff){
    if (td_buffs.find(buff_name) == td_buffs.end()){
        td_buffs.insert(std::pair<std::string, buff_data>(buff_name, buff));

        std::cout << "ADDING BUFF" << std::endl;

        //APPLY BUFF
        switch (buff.buff_stat){
        case (BUFF_ATTACK):
            tower_bullet.update_attack(buff.degree);
            break;
        case (BUFF_ATTACK_SPEED):
            tower_attack_rate-=buff.degree;
            break;
        case (BUFF_RANGE):
            tower_hitbox.set_radius(buff.degree+tower_hitbox.get_radius());

            if (tower_bullet.bullet_type == BULLET_TYPE_HITBOX)
               tower_bullet.bullet_radius+=buff.degree;

            break;
        }

    } else {
        td_buffs.at(buff_name).reset_ticks();
    }
}

void tower::update(unsigned int ticks){
    //MANAGING ATTACK COOLDOWN
    attack_cd+=ticks;

    //MINIMUM ATTACK
    if (tower_attack_rate < 50){
        if (attack_cd > 50)
            attack_cd = 50;
    } else {
        if (attack_cd > tower_attack_rate)
            attack_cd = tower_attack_rate;
    }

    if (target_within_range()){
        attacking();
    } else {
        set_target();
    }

    //SETTING BUFF EXPIRATIONS
    //SET EXPIRATIONS
    for (std::map<std::string, buff_data>::iterator buff_iterator = td_buffs.begin(), next_buff_iterator = buff_iterator; buff_iterator != td_buffs.end(); buff_iterator=next_buff_iterator){
        ++next_buff_iterator;

        if (buff_iterator->second.has_expired(ticks)){
            //REMOVE STAT BUFF
            switch (buff_iterator->second.buff_stat){
                case BUFF_ATTACK:
                    tower_bullet.update_attack(-(buff_iterator->second.degree));
                break;
                case BUFF_ATTACK_SPEED:
                    tower_attack_rate+=buff_iterator->second.degree;
                break;
                case BUFF_RANGE:
                    tower_hitbox.set_radius(tower_hitbox.get_radius() - buff_iterator->second.degree);

                    if (tower_bullet.bullet_type == BULLET_TYPE_HITBOX)
                        tower_bullet.bullet_radius-=buff_iterator->second.degree;

                break;
            }

            td_buffs.erase(buff_iterator);
        }
    }

    //MANAGING BUFFS
    update_buffs();
}

void tower::update_buffs(){
    //CHECK EACH TOWER
    for (std::vector<tower>::iterator tower_iterator = towers->begin(); tower_iterator != towers->end(); tower_iterator++){
        //GET THAT TOWER'S AURAS
        std::vector<buff_aura> aura_obs = tower_iterator->get_auras();

        if (!aura_obs.empty()){
            //CHECK IF IN CONTACT, AND ADD TO BUFFS IF IN CONTACT
            for (unsigned int i = 0; i < aura_obs.size(); i++){
                if (aura_obs.at(i).aura_hitbox.check_contact_with_circle(get_range())){
                    add_buff_to_queue(aura_obs.at(i).buff_to_give);
                }
            }
        }
    }

    //ADD BUFFS FROM QUEUE
    while (!buffs_to_add.empty()){
        add_buff(buffs_to_add.front().buff_name, buffs_to_add.front());
        buffs_to_add.pop();
    }
}

void tower::attacking(){
    //TOWER ATTACK RATE LIMIT
    if (tower_attack_rate < 50){
        if (attack_cd == 50){
            attack_cd -= 50;

            td_bullets->create_bullet(tower_bullet, enemy_targeted, tower_hitbox.get_x(), tower_hitbox.get_y());
        }
    } else {
        if (attack_cd == tower_attack_rate){
            attack_cd -= tower_attack_rate;

            td_bullets->create_bullet(tower_bullet, enemy_targeted, tower_hitbox.get_x(), tower_hitbox.get_y());
        }
    }
}

void tower::set_target(){
    static unsigned int target_obs;
    target_obs = 0;
    enemy_targeted = -1;

    while (target_obs < wave_size){
        try {
            if (tower_hitbox.check_contact_with_circle(td_enemies->at(target_obs).get_hitbox())){
                enemy_targeted = target_obs;
            }
        } catch (std::out_of_range e){}

        target_obs++;
    }
}

bool tower::target_within_range(){
    try {
        return tower_hitbox.check_contact_with_circle(td_enemies->at(enemy_targeted).get_hitbox());
    } catch (std::out_of_range e){
        return false;
    }
}

circle_hitbox* tower::get_range(){
    return &tower_hitbox;
}

std::vector<buff_aura> tower::get_auras(){
    return auras;
}

std::string tower::get_display_name(){
    return display_tower_name;
}

std::string tower::get_name(){
    return tower_name;
}

std::string tower::get_image(){
    return image_name;
}

int tower::get_damage(){
    return tower_bullet.get_attack();
}

int tower::get_attack_rate(){
    return tower_attack_rate;
}

TARGET_BUILDOVER tower::get_buildover_type(){
    return new_tower_tile;
}

int tower::get_old_tile(){
    return previous_tower_tile;
}
