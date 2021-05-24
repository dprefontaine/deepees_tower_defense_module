#ifndef TOWER_DATA_H_INCLUDED
#define TOWER_DATA_H_INCLUDED

//SERVES AS A DATA CELL FOR TOWER DATA

enum TARGET_BUILDOVER{
    TOWER_PHASEABLE,
    TOWER_UNPHASEABLE,
    TOWER_DIGGING
};

struct tower_data{
public:
    tower_data(){}
    ~tower_data(){}

    //EFFECT
    std::string bullet_data_name = "";

    int attack_rate = 0;            //INCOME RATE DURING THE LEVEL IF AN INCOME TOWER
    int attack_range = 0;           //NOT REQUIRED IF AN INCOME TOWER

    //TERRAIN
    TARGET_BUILDOVER new_tile = TOWER_UNPHASEABLE;

    //TOWER
    std::string tower_name = "";
    std::string tower_image = "";
    std::string tower_image_link = "images/tower.png";
    std::string description = "Add a description here!";

    std::string tower_icon_name = "images/build_tower_icon.png";

    //UPGRADE
    bool has_upgrade = false;
    std::string upgrade_name = "";

    //AURAS
    std::vector<buff_aura> auras = std::vector<buff_aura>();

    //RESOURCE USE
    int metal_use = 10;
    int metal_sell = 10;

    int wood_use = 10;
    int wood_sell = 10;

    int crystal_use = 10;
    int crystal_sell = 10;
};

#endif // TOWER_DATA_H_INCLUDED
