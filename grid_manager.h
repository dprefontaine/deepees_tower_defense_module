#ifndef PATH_MODULE_H_INCLUDED
#define PATH_MODULE_H_INCLUDED

#include <deepees_framework.h>

#include "grid.h"
#include "path.h"

#include <stack>

///MODIFIED FROM THE PATHFINDING MODULE BEFORE

extern const unsigned int GRID_SIZE_X;
extern const unsigned int GRID_SIZE_Y;

class grid_manager{
public:
    //Constructor
    grid_manager();

    //Destructor
    ~grid_manager();

    //Displaying grid and path on screen will be managed in the main file

    ///Grid management:
    //Getting grid point & contents
    int get_grid_data_at_current_point();
    unsigned int get_grid_x_current_point();
    unsigned int get_grid_y_current_point();

    //Setting grid point or grid data
    bool set_grid_point(unsigned int x, unsigned int y);
    bool set_grid_base_data(int new_value);
    bool set_grid_data(int new_value);

    //Directions
    bool move_grid_point_up();
    bool move_grid_point_down();
    bool move_grid_point_left();
    bool move_grid_point_right();

    //Traversing
    bool inc_grid_point();

    ///Path management:
    //
    //Paths
    std::vector<grid_node<int>>  create_path();

    //Points
    bool check_valid_point();

    //Start
    unsigned int get_start_x();
    unsigned int get_start_y();
    bool set_start_on_point();
    bool over_start_point();

    //Destinations
    bool selecting_destination();
    bool set_destination_on_point();
    bool over_destination_point();

    bool destination_present(int destination);
    bool only_destination();

    void add_destination(int destination_id, int x, int y);
    void remove_destination(int destination_id);

    unsigned int get_destination_x();
    unsigned int get_destination_y();

    //Path
    void start_path();
    bool inc_path();

private:
    //GRID INDEX TO COORDINATE COMMUNICATORS
    void coord_to_grid();
    void grid_to_x_coord();
    void grid_to_y_coord();

    ///PATHING (AT THE VERY END OF THE CPP FILE)
    bool djiskt();
    bool found_gap();
    void djiskt_travel(grid<int>* travelled_nodes, std::stack<grid_node<int>>* final_travel, unsigned int current_x, unsigned int current_y, std::stack<grid_node<int>> current_travel, int total_cost);

    //THE MAIN TWO DATA
    grid<int> module_grid = grid<int>(GRID_SIZE_X, GRID_SIZE_Y);
    path<int> module_path = path<int>();

    //COORDINATE GRID POINT
    unsigned int grid_index;
    unsigned int grid_x;
    unsigned int grid_y;

    //PATH TRACKING
    unsigned int selected_destination;

    //PATH TO USE
    std::stack<grid_node<int>> path_result = std::stack<grid_node<int>>();

    //FINAL PATH
    std::vector<grid_node<int>> final_path = std::vector<grid_node<int>>();
};

#endif // PATH_MODULE_H_INCLUDED
