#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

#include <queue>
#include <vector>
#include <iostream>

#include "grid_node.h"

enum PATH_MOVEMENT {
    PATH_MOVEMENT_NONE = 0,
    PATH_MOVEMENT_UP,
    PATH_MOVEMENT_DOWN,
    PATH_MOVEMENT_LEFT,
    PATH_MOVEMENT_RIGHT,
    PATH_MOVEMENT_TOTAL
};

template <typename T>
class path{
public:
    //Constructor
    path();

    //Destructor
    ~path();

    //Start manager
    unsigned int get_start_x();
    void set_start_x(unsigned int start_x);

    unsigned int get_start_y();
    void set_start_y(unsigned int start_y);

    //Destination manager
    unsigned int add_destination(unsigned int x, unsigned y , int index = -1);
    unsigned int get_destination(unsigned int x, unsigned y);
    unsigned int get_destination_by_id(int other_id);
    bool remove_destination(unsigned int destination_index);

    unsigned int total_destinations();

    unsigned int get_destination_x(unsigned int destination_id);
    unsigned int get_destination_y(unsigned int destination_id);

    std::queue<int> get_destination_ids();

    //Path manager
    void clear_path();
    void concat_path(grid_node<int> new_path_node);

    bool found_gap();
    bool set_path_point(unsigned int path_point);
    unsigned int inc_path_point();
    unsigned int dec_path_point();
    PATH_MOVEMENT get_path_change();

    T get_path_point_data();
    T set_path_point_data(T new_value);

private:
    bool travelling_to_find_gap();

    //Points to start or go to
    grid_node<int> start_point = grid_node<int>(0,0,0);
    std::vector<grid_node<int>> destination_points = std::vector<grid_node<int>>();      //KEEPING TRACK OF DESTINATION POINTS TO GO TO
    std::vector<grid_node<T>> path_created = std::vector<grid_node<T>>();
    unsigned int path_point = 0;
};

template <typename T>
path<T>::path(){

}

template <typename T>
path<T>::~path(){

}

template <typename T>
unsigned int path<T>::get_start_x(){
    return start_point.x_coord;
}

template <typename T>
void path<T>::set_start_x(unsigned int start_x){
    start_point.x_coord = start_x;
}

template <typename T>
unsigned int path<T>::get_start_y(){
    return start_point.y_coord;
}

template <typename T>
void path<T>::set_start_y(unsigned int start_y){
    start_point.y_coord = start_y;
}

template <typename T>
unsigned int path<T>::add_destination(unsigned int x, unsigned y , int index){
    destination_points.insert(destination_points.begin(),grid_node<int>(x,y, index));

    return index;
}

template <typename T>
unsigned int path<T>::get_destination(unsigned int x, unsigned y){
    for (unsigned int index = 0; index < destination_points.size(); index++)
        if (destination_points.at(index).x_coord == x &&
            destination_points.at(index).y_coord == y)
            return destination_points.at(index).value;

    return -1;
}

template <typename T>
unsigned int path<T>::get_destination_by_id(int other_id){
    for (unsigned int index = 0; index < destination_points.size(); index++)
        if (destination_points.at(index).value == other_id)
            return index;

    return -1;
}

template <typename T>
bool path<T>::remove_destination(unsigned int destination_index){
    if ((int)get_destination_by_id(destination_index) > -1){
        destination_points.erase(destination_points.begin()+get_destination_by_id(destination_index));
        return true;
    }

    return false;
}

template <typename T>
unsigned int path<T>::total_destinations(){
    return destination_points.size();
}

template <typename T>
unsigned int path<T>::get_destination_x(unsigned int index){
    if (index < total_destinations())
        return destination_points.at(index).x_coord;
    else
        return -1;
}

template <typename T>
unsigned int path<T>::get_destination_y(unsigned int index){
    if (index < total_destinations())
        return destination_points.at(index).y_coord;
    else
        return -1;
}

template <typename T>
std::queue<int> path<T>::get_destination_ids(){
    ///IDS SHOULDN'T OVERLAP
    std::queue<int> returning_ids = std::queue<int>();

    //RETURN A SORTED SET OF VECTOR
    for (unsigned int current_id = 0; current_id < destination_points.size(); current_id++){
        unsigned int index_result = get_destination_by_id(current_id);

        if ((int)index_result != -1){
            returning_ids.push(current_id);
        }
    }

    return returning_ids;
}

template <typename T>
void path<T>::clear_path(){
    path_created.clear();
}

template <typename T>
void path<T>::concat_path(grid_node<int> new_path_node){
    //CHECK IF THAT PATH DOESN'T EQUAL THE TOP
    path_created.push_back(new_path_node);
}

template <typename T>
bool path<T>::found_gap(){
    if (path_created.size() > 0 && set_path_point(0)){
        std::cout << path_created.front().x_coord << std::endl;
        return travelling_to_find_gap();
    } else {
        return false;
    }
}

template <typename T>
bool path<T>::travelling_to_find_gap(){
    if (inc_path_point()){
        //CHECK DIFFERENCE FROM PREVIOUS POINT
        if (abs((path_created.at(path_point).x_coord - path_created.at(path_point-1).x_coord) +
            (path_created.at(path_point).y_coord - path_created.at(path_point-1).y_coord)) == 1){
            return travelling_to_find_gap();
        } else {
            return false;
        }
    } else {
        return true;
    }
}

template <typename T>
bool path<T>::set_path_point(unsigned int path_point){
    if (path_point < path_created.size()){
        this->path_point = path_point;
        return true;
    } else {
        return false;
    }
}

template <typename T>
unsigned int path<T>::inc_path_point(){
    if (path_point+1 < path_created.size()){
        return path_point++;
    } else {
        return -1;
    }
}

template <typename T>
unsigned int path<T>::dec_path_point(){
    if (path_point-1 < path_created.size()){
        return path_point--;
    } else {
        return -1;
    }
}

template <typename T>
T path<T>::get_path_point_data(){
    if (path_point < path_created.size()){
        return path_created.at(path_point).value;
    } else {
        return -1;
    }
}

template <typename T>
PATH_MOVEMENT path<T>::get_path_change(){
    if ((int)set_path_point(path_point) > 0){
        switch (path_created.at(path_point).y_coord - path_created.at(path_point-1).y_coord){
        case -1:
            return PATH_MOVEMENT_UP;
        break;
        case 1:
            return PATH_MOVEMENT_DOWN;
        break;
        }

        switch (path_created.at(path_point).x_coord - path_created.at(path_point-1).x_coord){
        case -1:
            return PATH_MOVEMENT_LEFT;
        break;
        case 1:
            return PATH_MOVEMENT_RIGHT;
        break;
        default:
            return PATH_MOVEMENT_NONE;
        break;
        }

    } else {
        return PATH_MOVEMENT_NONE;
    }
}

template <typename T>
T path<T>::set_path_point_data(T new_value){
    if (path_point < path_created.size()){
        return path_created.at(path_point).value = new_value;
    } else {
        return -1;
    }
}

#endif // PATH_H_INCLUDED
