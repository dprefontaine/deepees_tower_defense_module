//#include "td_module.h"
#include "td_loading.h"

///LOADING BUTTONS
void creating_td_clicker();
void creating_td_ui();

///GRID CONSTANTS
const unsigned int GRID_SIZE_X = 23;
const unsigned int GRID_SIZE_Y = 11;

const unsigned int START_POINT_X = 1;
const unsigned int START_POINT_Y = 0;

const unsigned int ONE_POINT_X = 5;
const unsigned int ONE_POINT_Y = 5;

const unsigned int TWO_POINT_X = 11;
const unsigned int TWO_POINT_Y = 5;

const unsigned int END_POINT_X = 17;
const unsigned int END_POINT_Y = 5;

const unsigned int SQUARE_SIZE = 90;

///MAIN DATA AND FRAMEWORK
const std::string SCREEN_NAME = "DeepP's Tower Defense Module";

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;

const bool PRINTING = false;

///ROOM ENUMS
enum ROOM_NAME{
    GAME_ROOM,
    TITLE_ROOM,
    MENU_ROOM
};

//the main objects
main_controller* game = NULL;
td_module* module = NULL;
td_level_loader* table = NULL;

std::string SELECTED_LEVEL = "Default";
//"Crossing"
//"Traditional"

//map
void loading_into_map(std::queue<int>* map_to_load);

//cursor
int mouse_follow(unsigned int ticks);

//camera
int press_camera_up();
int release_camera_up();

int press_camera_down();
int release_camera_down();

int press_camera_left();
int release_camera_left();

int press_camera_right();
int release_camera_right();

//button clicking
int build_button_clear_set();

int build_button_one_push_down();
int build_button_one_push_up();

int build_button_two_push_down();
int build_button_two_push_up();

int build_button_three_push_down();
int build_button_three_push_up();

int build_button_four_push_down();
int build_button_four_push_up();

int build_button_five_push_down();
int build_button_five_push_up();

int build_button_six_push_down();
int build_button_six_push_up();

int build_button_seven_push_down();
int build_button_seven_push_up();

int build_button_eight_push_down();
int build_button_eight_push_up();

int build_button_nine_push_down();
int build_button_nine_push_up();

int build_set_button_one_push_down();
int build_set_button_one_push_up();

int build_set_button_two_push_down();
int build_set_button_two_push_up();

int start_button_push_down();
int start_button_push_up();

//grid
int grid_click();
int grid_over();
int grid_update(unsigned int ticks);

//setting grid states
int grid_buy();
int grid_start();

int main(int args, char* argv[]);



