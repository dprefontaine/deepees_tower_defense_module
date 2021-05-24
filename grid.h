#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

//MAY CONVERT THIS INTO A GENERIC THAT ACCEPTS CLASSES LATER
template <typename T>
class grid {
public:
    //Constructor
    grid<T>(int grid_size_x, int grid_size_y);
    //Destructor
    ~grid<T>();

    //Setting index
    unsigned int set_current_point(unsigned int x,unsigned int y);
    unsigned int set_to_next_point(unsigned int addition = 1);
    unsigned int set_to_previous_point(unsigned int subtraction = 1);

    //Getting index data
    unsigned int get_current_point();

    //Grid data
    T get_point_data();
    void set_point_data(T new_value);

private:
    T *grid_data;
    unsigned int grid_size_x, grid_size_y;
    unsigned int current_point;

    unsigned int is_within_grid(unsigned int new_point);
};

//Constructor
template <typename T>
grid<T>::grid(int grid_size_x, int grid_size_y){
    grid_data = new T[grid_size_x*grid_size_y];
    this->grid_size_x = grid_size_x;
    this->grid_size_y = grid_size_y;
    current_point = 0;

    //INITIALIZING ALL GRID DATA
    for (int i = 0; i < grid_size_x*grid_size_y; i++)
        grid_data[i] = 0;
}

//Destructor
template <typename T>
grid<T>::~grid(){
    //delete[] grid_data;
}

//Point setter
template <typename T>
unsigned int grid<T>::set_current_point(unsigned int x, unsigned int y){
    if (x < grid_size_x && y < grid_size_y)
        return is_within_grid(x + y*grid_size_x);
    else
        return -1;
}

template <typename T>
unsigned int grid<T>::set_to_next_point(unsigned int addition){
    return is_within_grid(current_point+addition);
}

template <typename T>
unsigned int grid<T>::set_to_previous_point(unsigned int subtraction){
    return is_within_grid(current_point-subtraction);
}

//Getting current point
template <typename T>
unsigned int grid<T>::get_current_point(){
    return current_point;
}

//Getting index data
template <typename T>
T grid<T>::get_point_data(){
    return grid_data[current_point];
}

//Setting index data
template <typename T>
void grid<T>::set_point_data(T new_value){
    grid_data[current_point] = new_value;
}

//For getting proper points
template <typename T>
unsigned int grid<T>::is_within_grid(unsigned int new_point){
    if (new_point < grid_size_x*grid_size_y){
        return current_point = new_point;
    } else
        return -1;
}

#endif // GRID_H_INCLUDED
