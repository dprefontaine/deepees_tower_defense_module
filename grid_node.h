#ifndef GRID_NODE_H_INCLUDED
#define GRID_NODE_H_INCLUDED

template <typename T>
struct grid_node{
public:
    grid_node(unsigned int x_coord, unsigned int y_coord, T value){
        this->x_coord = x_coord;
        this->y_coord = y_coord;
        this->value = value;
    }

    unsigned int x_coord, y_coord;
    T value;
};

#endif // GRID_NODE_H_INCLUDED
