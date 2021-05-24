#ifndef TD_MODULE_H_INCLUDED
#define TD_MODULE_H_INCLUDED

#include "td_table.h"

extern const unsigned int START_POINT_X;
extern const unsigned int START_POINT_Y;

extern const unsigned int GRID_SIZE_X;
extern const unsigned int GRID_SIZE_Y;

extern const unsigned int ONE_POINT_X;
extern const unsigned int ONE_POINT_Y;

extern const unsigned int TWO_POINT_X;
extern const unsigned int TWO_POINT_Y;

extern const unsigned int END_POINT_X;
extern const unsigned int END_POINT_Y;

extern const unsigned int SQUARE_SIZE;

enum td_module_state{
    MODULE_DEFAULT,
    MODULE_BUILD
};

enum td_module_build_race{
    BUILD_RACE_NONE,
    BUILD_RACE_ONE,
    BUILD_RACE_TWO
};

int determine_buildover(TARGET_BUILDOVER buildover, int grid_data);

class td_module{
public:
    td_module(int cam_x_accel, int cam_y_accel, int max_x_vel, int max_y_vel);
    ~td_module();

    //updating
    void update_td_module(unsigned int ticks);

    int toggling_speed();

    //clicking on grid
    void click_on_grid(unsigned int x_click, unsigned int y_click);
    void over_grid(unsigned int x_over, unsigned int y_over);

    td_module_state get_state();

    //setting grid interactions
    void set_build_click(td_module_build_button_selection new_build_click);
    td_module_build_button_selection get_build_click();
    void set_button_data_set();

    void upgrade_tower();
    void sell_tower();

    //for camera
    void move_up(bool move_state);
    void move_down(bool move_state);
    void move_left(bool move_state);
    void move_right(bool move_state);

    void start_level();

    //set levels
    void set_points();
    void load_map();

    //drawing
    void add_tower_image(std::string tower_image_spot, std::string tower_image_source);
    void remove_tower_image(std::string tower_image_spot);
    void draw_towers();

    void draw_grid();
    void draw_board();
    void draw_points();

    void draw_enemies();

    void add_bullet_image(std::string bullet_image, std::string bullet_image_source);
    void remove_bullet_image(std::string bullet_image_spot);
    void draw_bullets();

    void draw_selection(bool is_building, bool is_selling);

    void set_selected_map(std::string new_map);
    std::string get_selected_map();

    void set_build_race_one(std::string new_race_one);
    void set_build_race_two(std::string new_race_two);

    void set_to_race_one();
    void set_to_race_two();

    void load_button_mapping(td_module_build_race current_build_race){
        build_button_mappings.clear();

        extern td_level_loader* table;
        std::vector<TOWER_MAPPING> tower_map_data;

        if (current_build_race == BUILD_RACE_ONE){
            //LOOK UP THE BUILD RACE IN BUILD RACE ONE
            tower_map_data = table->get_tower_race(build_race_1);

            for (unsigned int i = 0; i < tower_map_data.size(); i++){
                build_button_mappings.insert(tower_map_data.at(i));
            }

        } else if (current_build_race == BUILD_RACE_TWO){
            //LOOK UP THE BUILD RACE IN BUILD RACE TWO
            tower_map_data = table->get_tower_race(build_race_2);

            for (unsigned int i = 0; i < tower_map_data.size(); i++){
                build_button_mappings.insert(tower_map_data.at(i));
            }
        }
    }

    //OPTION BUTTONS
    void click_speed_option();      //FOR CHANGING SPEED FROM 1x >> 2x >> 4x and back to 1x
    void click_waves_option();      //FOR PULLING UP WAVES
    void click_help_option();       //FOR PULLING UP CONTROLS
    void click_settings_option();   //FOR SETTING AUDIO, VIDEO, EXITING CURRENT SESSION, QUITTING GAME...

private:
    unsigned int speed_multiplier = 1;          //SPEED MULTIPLIER

    void set_state(td_module_state new_state);

    //data_manager
    std::string tower_data_name = "Tower";
    td_module_build_button_selection build_data_select = BUILD_BUTTON_NONE;
    std::map<td_module_build_button_selection, std::string> build_button_mappings;

    td_module_build_race current_build_race = BUILD_RACE_NONE;
    std::string build_race_1 = "Race One";
    std::string build_race_2 = "Race Two";

    //FOR LOADING A DEFAULT MAPPING
    void load_button_mapping(){
        build_button_mappings.insert(TOWER_MAPPING(BUILD_BUTTON_ONE, "Tower"));
        build_button_mappings.insert(TOWER_MAPPING(BUILD_BUTTON_TWO, "Tower"));
        build_button_mappings.insert(TOWER_MAPPING(BUILD_BUTTON_THREE, "Tower"));
        build_button_mappings.insert(TOWER_MAPPING(BUILD_BUTTON_FOUR, "Tower"));
        build_button_mappings.insert(TOWER_MAPPING(BUILD_BUTTON_FIVE, "Tower"));
        build_button_mappings.insert(TOWER_MAPPING(BUILD_BUTTON_SIX, "Tower"));
        build_button_mappings.insert(TOWER_MAPPING(BUILD_BUTTON_SEVEN, "Tower"));
        build_button_mappings.insert(TOWER_MAPPING(BUILD_BUTTON_EIGHT, "Tower"));
        build_button_mappings.insert(TOWER_MAPPING(BUILD_BUTTON_NINE, "Tower"));
    }

    void set_tower_data_to_look_up(std::string new_tower_data_name);

    std::string enemy_data_name = "Enemy One";

    ///SETTING WAVES (IN THE H FILE TO MAKE IT EASIER TO MANAGE WAVES)
    void load_waves(){
        td_waves.push("Wave One");
        td_waves.push("Wave Two");
        td_waves.push("Wave Three");
        td_waves.push("Wave Four");
        td_waves.push("Wave Five");

        level = resource(1, td_waves.size());
    }

    unsigned int total_wave_enemies = 0;

    //controls
    void observe_grid_click();
    void build_tower_click();

    void observe_grid_over();
    void build_tower_over();

    bool over_tower_on_point();
    bool can_build_on_point();

    //tower management
    void create_tower();
    td_bullet create_bullet(tower_bullet_data bullet_data);
    void erase_tower();
    bool have_resources();

    void tower_found();

    void activate_selection(bool is_building, bool is_selling);
    void deactivate_selection();

    //enemy management
    void create_enemy();
    bool remaining_enemies_to_spawn();
    void spawn_enemy();
    void kill_enemy(int enemy_index);
    void enemy_bountied(int enemy_index);
    void enemy_at_end(int enemy_index);

    //strange to put it here, but only the module needs to look up enemies, since wave loading is going to take place within the module class (and keeping consistency with how look-up strings are treated here)
    void set_enemy_data_to_look_up(std::string new_enemy_data_name);

    //levels and win/lose conditions
    void increase_level();
    void remove_life();

    //CONFIGURATION
    std::string selected_map = "Default";

    //DATA
    grid_manager td_grid;
    std::stack<std::pair<int, enemy>> enemies_to_spawn;

    std::map<int, enemy> td_enemies;
    unsigned int total_enemies = 0;

    std::queue<std::string> td_waves;
    std::vector<point> level_path;

    std::vector<tower> td_towers;
    unsigned int total_towers = 0;

    bullet_space td_bullets;
    //std::vector<td_impact> td_impacts;
    //std::vector<td_buffs> td_buff;

    int selected_tower_index = -1;
    alarm spawn_rate = alarm(1200);

    std::map<std::string, resource> td_resources;
    resource lives = resource(0,0);
    resource level = resource(0,0);

    int x_click, y_click;
    td_module_state control_state;
    bool level_playing;

    bool notification_on;
    std::string notification_message;

    //camera
    bool moving_up, moving_down, moving_left, moving_right;
    int x_vel, y_vel, x_vel_max, y_vel_max;
    int x_acc, y_acc;
    float vert_accel, horz_accel;
};

#endif // TD_MODULE_H_INCLUDED
