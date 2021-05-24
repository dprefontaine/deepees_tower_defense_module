#include "grid_manager.h"

grid_manager::grid_manager(){
    //Initializing the grid
    grid_x = grid_y = 0;
}

grid_manager::~grid_manager(){
    //Deleting grid...

    //Deleting path...
}

bool grid_manager::set_grid_point(unsigned int x, unsigned int y){
    if (x < GRID_SIZE_X && y < GRID_SIZE_Y){
        grid_index = module_grid.set_current_point(x, y);
        grid_x = x;
        grid_y = y;

        return true;
    } else {
        return false;
    }
}

bool grid_manager::set_grid_data(int new_value){
    module_grid.set_point_data(new_value);

    return true;
}

bool grid_manager::inc_grid_point(){
    if ((int)module_grid.set_to_next_point() > -1){
        grid_index = module_grid.get_current_point();
        grid_to_x_coord();
        grid_to_y_coord();

        return true;
    } else {
        return false;
    }
}

bool grid_manager::move_grid_point_up(){
    if ((int)module_grid.set_to_previous_point(GRID_SIZE_X) > -1){
        grid_index = module_grid.get_current_point();
        grid_to_x_coord();
        grid_to_y_coord();

        return true;
    } else {
        return false;
    }
}

bool grid_manager::move_grid_point_down(){
    if ((int)module_grid.set_to_next_point(GRID_SIZE_X) > -1){
        grid_index = module_grid.get_current_point();
        grid_to_x_coord();
        grid_to_y_coord();

        return true;
    } else {
        return false;
    }
}

bool grid_manager::move_grid_point_left(){
    //KEEP TRACK OF PREVIOUS POINT
    unsigned int previous_y_coord = grid_y;

    if ((int)module_grid.set_to_previous_point() > -1){
        grid_index = module_grid.get_current_point();
        grid_to_x_coord();
        grid_to_y_coord();

        //CHECK IF WRAPPING BACK
        if (previous_y_coord == grid_y){
            //std::cout << "new point is " << grid_x << ", " << grid_y << std::endl;
            return true;
        } else {
        //UNDO CHANGES
            module_grid.set_to_next_point();
            grid_to_x_coord();
            grid_to_y_coord();

            return false;
        }
    } else {
        return false;
    }
}

bool grid_manager::move_grid_point_right(){
    //KEEP TRACK OF PREVIOUS POINT
    unsigned int previous_y_coord = grid_y;

    if ((int)module_grid.set_to_next_point() > -1){
        grid_index = module_grid.get_current_point();
        grid_to_x_coord();
        grid_to_y_coord();

        //CHECK IF WRAPPING BACK
        if (previous_y_coord == grid_y){
            return true;
        } else {
        //UNDO CHANGES
            module_grid.set_to_previous_point();
            grid_to_x_coord();
            grid_to_y_coord();

            return false;
        }
    } else {
        return false;
    }
}

int grid_manager::get_grid_data_at_current_point(){
    return module_grid.get_point_data();
}

unsigned int grid_manager::get_grid_x_current_point(){
    return grid_x;
}

unsigned int grid_manager::get_grid_y_current_point(){
    return grid_y;
}

void grid_manager::coord_to_grid(){
    grid_index = (grid_y*GRID_SIZE_X)+grid_x;
}

void grid_manager::grid_to_x_coord(){
    grid_x = grid_index%GRID_SIZE_X;
}

void grid_manager::grid_to_y_coord(){
    grid_y = grid_index/GRID_SIZE_X;
}

unsigned int grid_manager::get_destination_x(){
    if ((int)selected_destination != -1){
        return module_path.get_destination_x(selected_destination);
    } else
        return -1;
}

unsigned int grid_manager::get_destination_y(){
    if ((int)selected_destination != -1){
        return module_path.get_destination_y(selected_destination);
    } else
        return -1;
}

///THE BIG BOY
std::vector<grid_node<int>> grid_manager::create_path(){
    ///SET ALL DESTINATIONS TO TRAVEL TO
    std::queue<int> available_ids = module_path.get_destination_ids();
    std::stack<grid_node<int>> reverser = std::stack<grid_node<int>>();

    ///BLOCK FLAG (IN CASE TRAPPED)
    bool block_flag = false;

    //ORIGINAL STARTING POINT
    unsigned int original_start_x = get_start_x();
    unsigned int original_start_y = get_start_y();

    module_path.clear_path();
    std::stack<grid_node<int>>().swap(path_result);
    std::vector<grid_node<int>>().swap(final_path);

    //KEEP TRAVELLING UNTIL NO DESTINATION TO TRAVEL TO LEFT
    while (!available_ids.empty() && !block_flag){
        selected_destination = module_path.get_destination_by_id(available_ids.front());
        module_grid.set_current_point(get_start_x(),get_start_y());

        block_flag = !djiskt();

        while (!path_result.empty()){
            reverser.push(path_result.top());
            path_result.pop();
        }

        while (!reverser.empty()){
            //std::cout << "(" << reverser.top().x_coord << ", " << reverser.top().y_coord << ") ";
            final_path.push_back(reverser.top());
            reverser.pop();
        }

        //std::cout <<  std::endl;
        //std::cout << "-----" << std::endl;

        //SET THE PREVIOUS DESTINATION AS THE NEW POINT
        set_grid_point(get_destination_x(),get_destination_y());
        set_start_on_point();
        available_ids.pop();
    }

    //GO BACK TO ORIGINAL START
    set_grid_point(original_start_x,original_start_y);
    set_start_on_point();

    if (!block_flag){
        //FLATTEN THE POINTS
        unsigned int final_path_index = 1;
        int prev_horz_difference = 0;
        int prev_vert_difference = 0;
        int next_horz_difference = 0;
        int next_vert_difference = 0;

        while (final_path_index < final_path.size() - 1){
            //std::cout << "Current direction " << horz_difference << ", " << vert_difference << std::endl;

            //GETTING DIFFERENCE IN NEXT MOVE
            next_horz_difference = final_path.at(final_path_index+1).x_coord - final_path.at(final_path_index).x_coord;
            next_vert_difference = final_path.at(final_path_index+1).y_coord - final_path.at(final_path_index).y_coord;

            if (next_horz_difference != 0){
                next_horz_difference /= abs(next_horz_difference);
            }

            if (next_vert_difference != 0){
                next_vert_difference /= abs(next_vert_difference);
            }

            //GETTING DIFFERENCE IN PREVIOUS MOVE
            prev_horz_difference = final_path.at(final_path_index).x_coord - final_path.at(final_path_index-1).x_coord;
            prev_vert_difference = final_path.at(final_path_index).y_coord - final_path.at(final_path_index-1).y_coord;

            if (prev_horz_difference != 0){
                prev_horz_difference /= abs(prev_horz_difference);
            }

            if (prev_vert_difference != 0){
                prev_vert_difference /= abs(prev_vert_difference);
            }

            if ((next_horz_difference == prev_horz_difference &&
                    next_vert_difference == prev_vert_difference) ||
                    ((next_horz_difference == 0) &&
                    (next_vert_difference == 0))){

                //std::cout << "No direction difference at (" << final_path.at(final_path_index).x_coord << ", " << final_path.at(final_path_index).y_coord << ")" << std::endl;
                final_path.erase(final_path.begin()+final_path_index);
                final_path_index--;

            //IF THERE IS A CHANGE, KEEP THAT POINT
            }

            final_path_index++;
        }

        final_path_index = 0;

        return final_path;
    } else {
        return std::vector<grid_node<int>>();
    }
}

bool grid_manager::check_valid_point(){
    //CHECK IF A BLOCK (OTHER CONDITIONS UP TO THE CONTEXT OF THE ACTION ITSELF)
    return (module_grid.get_point_data() > -1);
}

bool grid_manager::set_start_on_point(){
    //CHECK IF OVER A BLOCK
    if (check_valid_point()){
        //THEN CHECK IF OVER A DESTINATION (FIRST EVALUATION TO SAVE TROUBLE OF CHECKING USELESS CASES BEFOREHAND)
        //if ((int)module_path.get_destination(grid_x, grid_y) == -1){
            module_path.set_start_x(grid_x);
            module_path.set_start_y(grid_y);

            return true;
        //}
    }

    return false;
}

unsigned int grid_manager::get_start_x(){
    return module_path.get_start_x();
}

unsigned int grid_manager::get_start_y(){
    return module_path.get_start_y();
}

bool grid_manager::over_start_point(){
    return (grid_x == module_path.get_start_x()&&
            grid_y == module_path.get_start_y());
}

bool grid_manager::selecting_destination(){
    //CHECK IF GRID POINT IS OVER A DESTINATION
    if ((int)(selected_destination = module_path.get_destination(grid_x, grid_y)) > -1){
        //RETURN A CONFIRMED DESTINATION
        return true;
    }

    return false;
}

bool grid_manager::set_destination_on_point(){
    //CHECK IF OVER A BLOCK
    if (check_valid_point()){
        //THEN CHECK IF OVER A DESTINATION OR THE START(FIRST EVALUATION TO SAVE TROUBLE OF CHECKING USELESS CASES BEFOREHAND)
        if ((int)module_path.get_destination(grid_x, grid_y) == -1 &&
            !(module_path.get_start_x() == grid_x &&
            module_path.get_start_y() == grid_y)){
            //REMOVE AND PLACE THE DESTINATION IN THE NEW SPOT
            if (module_path.remove_destination(selected_destination)){
                //std::cout << "Result " << grid_x << " " << grid_y << " | " << selected_destination << std::endl;
                module_path.add_destination(grid_x, grid_y, selected_destination);
            }

            return true;
        }
    }

    return false;
}

bool grid_manager::over_destination_point(){
    return ((int)module_path.get_destination(grid_x, grid_y) != -1);
}

bool grid_manager::destination_present(int destination){
    if ((int)(selected_destination = module_path.get_destination_by_id(destination)) != -1){
        //SETTING GRID COORDINATES
        module_path.get_destination_x(selected_destination);
        module_path.get_destination_y(selected_destination);

        return true;
    } else {
        return false;
    }
}

bool grid_manager::only_destination(){
    return (module_path.total_destinations() < 2);
}

void grid_manager::add_destination(int destination_id, int x, int y){
    set_grid_point(x,y);

    bool place_flag = true;

    //FIND A CLEAR POINT ON THE GRID
    while (!check_valid_point() ||                                                 //CHECKING IF OVER BLOCK
           (int)module_path.get_destination(grid_x, grid_y) != -1 ||                                  //CHECKING IF OVER ANOTHER DESTINATION
           (module_path.get_start_x() == grid_x && module_path.get_start_y() == grid_y) ||         //CHECKING IF OVER START
           !place_flag){
           place_flag = inc_grid_point();
          }

    if (place_flag)
        module_path.add_destination(grid_x, grid_y, destination_id);
}

void grid_manager::remove_destination(int destination_id){
    //std::cout << "Removing destination of id: " << destination_id << std::endl;
    module_path.remove_destination(destination_id);
}

void grid_manager::start_path(){
    module_path.set_path_point(0);
}

bool grid_manager::inc_path(){
    return ((int)module_path.inc_path_point() != -1);
}

///**************************************************************************THE PATHFINDING ALGORITHMS THEMSELVES

bool grid_manager::djiskt(){
    //PATH FLAG
    bool djiskt_flag = true;

    //CREATE A GRID
    grid<int>* djiskt_nodes = new grid<int>(GRID_SIZE_X, GRID_SIZE_Y);
    std::stack<grid_node<int>> djiskt_stack = std::stack<grid_node<int>>();

    do {
        djiskt_nodes->set_point_data(-1);
    } while ((int)djiskt_nodes->set_to_next_point() != -1);

    //START TRAVELLING
    djiskt_travel(djiskt_nodes, &djiskt_stack, get_start_x(), get_start_y(), std::stack<grid_node<int>>(), 0);

    delete djiskt_nodes;
    djiskt_nodes = NULL;

    path_result.swap(djiskt_stack);

    djiskt_flag = !found_gap();

    return djiskt_flag;
}

bool grid_manager::found_gap(){
    return path_result.empty();
}

void grid_manager::djiskt_travel(grid<int>* travelled_nodes, std::stack<grid_node<int>>* final_travel, unsigned int current_x, unsigned int current_y, std::stack<grid_node<int>> current_travel, int total_cost){
    //SETTING OBSERVED NODES AT THAT POINT
    //AND CHECKING IF A VALID POINT ON THE GRID
    if ((int)travelled_nodes->set_current_point(current_x, current_y) != -1 &&
        (int)module_grid.set_current_point(current_x, current_y) != -1){

        int current_spot_cost = travelled_nodes->get_point_data();

        //COST AT A POINT IS THE MAGNITUDE BETWEEN THAT POINT AND THE STARING POINT
        int cost_at_that_point = (get_start_x()-current_x)*(get_start_x()-current_x)+(get_start_y()-current_y)*(get_start_y()-current_y);

        //CHECK IF THE CURRENT POINT COST IS GREATER THAN BEFORE TO PREVENT BACKTRACKING
        //CHECK IF AT THE DESTINATION
        if (current_x == module_path.get_destination_x(selected_destination) &&
            current_y == module_path.get_destination_y(selected_destination)){

            //CHECK IF DESTINATION ALREADY TRAVELLED
            if (current_spot_cost < 0 ||
                current_spot_cost > total_cost+cost_at_that_point){
                //SET THAT AS THE MINIMAL PATH TRAVELLED
                //OR REPLACE THE RECORDED RUN WITH THIS CURRENT RUN AND ITS LESSER COST

                current_travel.push(grid_node<int>(current_x, current_y, cost_at_that_point));
                total_cost+=cost_at_that_point;
                travelled_nodes->set_point_data(total_cost);

                //SWAP WITH THE FINAL PATH
                final_travel->swap(current_travel);
            }

        //SINCE ASSUMED A VALID POINT, CHECK IF THIS GRID TILE IS WALKABLE
        } else if (module_grid.get_point_data() < 2){

            //CHECK IF ALREADY TRAVELLED
            if (current_spot_cost < 0 ||
                current_spot_cost > total_cost+cost_at_that_point){
                //SET THAT AS THE MINIMAL PATH TRAVELLED
                //OR REPLACE THE RECORDED RUN WITH THIS CURRENT RUN AND ITS LESSER COST

                current_travel.push(grid_node<int>(current_x, current_y, cost_at_that_point));
                total_cost+=cost_at_that_point;
                travelled_nodes->set_point_data(total_cost);

                //TRAVEL TO THE NEXT DIRECTIONS IF SUCCESSFUL
                djiskt_travel(travelled_nodes,final_travel,current_x+1,current_y, current_travel, total_cost);
                djiskt_travel(travelled_nodes,final_travel,current_x-1,current_y, current_travel, total_cost);
                djiskt_travel(travelled_nodes,final_travel,current_x,current_y+1, current_travel, total_cost);
                djiskt_travel(travelled_nodes,final_travel,current_x,current_y-1, current_travel, total_cost);
            }
        }
    }
}

