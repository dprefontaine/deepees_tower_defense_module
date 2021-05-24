#ifndef GRID_STATE_H_INCLUDED
#define GRID_STATE_H_INCLUDED

#include <iostream>

extern int action_status;

enum GRID_STATES : int {
    GRID_STATE_INACTIVE = 0,
    GRID_STATE_SETTING_TILE = 1,
    GRID_STATE_SETTING_DESTINATION_SELECTION,
    GRID_STATE_SETTING_DESTINATION_PLACING,
    GRID_STATE_SETTING_START,
    GRID_STATE_TOTAL
};

bool no_other_action(){
    return (action_status != GRID_STATE_SETTING_DESTINATION_PLACING);
}

int button_setting_grid_tile(){
    //MAKING SURE IT'S NOT IN THE MIDDLE OF ANY OTHER ACTION
    if (no_other_action()){
        if (action_status == GRID_STATE_SETTING_TILE)
            action_status = GRID_STATE_INACTIVE;
        else
            action_status = GRID_STATE_SETTING_TILE;
    }

    return 0;
}

int button_selecting_destination(){
    if (no_other_action()){
        if (action_status == GRID_STATE_SETTING_DESTINATION_SELECTION)
            action_status = GRID_STATE_INACTIVE;
        else
            action_status = GRID_STATE_SETTING_DESTINATION_SELECTION;
    }

    return 0;
}

int button_placing_destination(){
    //THIS CAN ONLY BE ACCESSED FROM A CERTAIN STATE
    action_status = GRID_STATE_SETTING_DESTINATION_PLACING;

    return 0;
}

int button_setting_grid_start(){
    if (no_other_action()){
        if (action_status == GRID_STATE_SETTING_START)
            action_status = GRID_STATE_INACTIVE;
        else
            action_status = GRID_STATE_SETTING_START;
    }

    return 0;
}


#endif // GRID_STATE_H_INCLUDED
